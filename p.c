#include "p.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k.h"
#include "sym.h"
#include "zv.h"
#include "scope.h"
#include "x.h"
#include "lex.h"
#include "timer.h"
#include "repl.h"
#include "sys.h"

/*
s > e se
e > o ez | ez
se > ';' | '\n'
o > N | klist
ez > | V e | plist
klist > '(' elist ')'
plist > '[' elist ']'
elist > e elistz
elistz > | se e elistz
*/

static char *P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\";

#define LI 10
#define LJ 19
static int LL[10][19]={
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,-1,0,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,1,-1,1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,2,3,2,3,3,3,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,5,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,-1,7,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,8,-1,9,-1,8,10,8,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,13,13,13,13,13,13,13,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,-1,-1,-1,14,-1,14,-1}
};

static int RT[16][3]={
{T001},
{T002,T003},
{T004,T005},
{T005},
{T010},
{T011},
{T012},
{T006},
{-1},
{T013,T002},
{T007},
{T014,T008,T015},
{T016,T008,T017},
{T002,T009},
{-1},
{T003,T002,T009}
};

static int RC[16]={1,2,2,1,1,1,1,1,0,2,1,3,3,2,0,3};

#define Vvi s->V[s->vi]

static U vlookup(U v) {
  char *s=(char*)(v^(U)15<<60);
  return scope_get(gs,s);
}

U pgreduce(pr *r, int p) {
  int i,j,quiet,w,timer=0,times=1;
  char c,q,n;
  char *e,*s,*bc,*s2;
  U A[256],*pA=A,a,b,v=0,v0,a0;
  if(!r->n) return v;
  for(i=0;i<r->n;i++) {
    if(!(n=r->bcn[i])) continue;
    bc=r->bc[i];
    U *values=r->values[i];
    if(bc[1]==96) { prfree(r); exit_(0); }
    else if(bc[1]==97) {
      timer=1;
      a=values[(int)bc[0]];
      if(zv(a)) { a=zvget(a); if(15==a>>60) a=vlookup(a); }
      times=(int)a;
      timer_start();
      continue;
    }
    else if(bc[1]==98) {
      a=values[(int)bc[0]];
      s=(char*)k(0,a,0);
      s2=xmalloc(1+(int)a);
      *s2=0;
      strncat(s2,s,(int)a);
      load(s2,2);
      kfree(a);
      xfree(s2);
      continue;
    }
    while(times--) {
    pA=A;
    for(j=0;j<n;j++) {
      quiet=0;
      c=bc[j];
      q=c>>5;
      if(!q) *pA++=values[(int)c];
      else if(q==1) { /* 32 33 34 ... */
        if(pA>A) {
        a=*--pA;
        if(zv(a)) { a=zvget(a); if(15==a>>60) a=vlookup(a); }
        else if(timer&&times) kref(a);
        *pA++=k(c%32,0,a);
        }
      }
      else if(q==2) { /* 64 65 66 ... */
        if(pA>A+1) {
        b=*--pA;
        a=*--pA;
        if(c==64&&zv(a)) { /* a:1 */
          a0=a;
          a=zvget(a);
          if(zv(b)) { b=zvget(b); if(15==b>>60) b=vlookup(b); }
          else if(timer&&times) kref(b);
          scope_set(gs,(char*)(a^(U)15<<60),b);
          *pA++=a0;
          quiet=1;
          kfree(b);
        }
        else {
          if(zv(a)) { a=zvget(a); if(15==a>>60) a=vlookup(a); }
          else if(timer&&times) kref(a);
          if(zv(b)) { b=zvget(b); if(15==b>>60) b=vlookup(b); }
          else if(timer&&times) kref(b);
          /* adverb? / \ ' */
          w=c%32;
          if(w==30) {
            s=strchr(P,(char)a); a=s-P;
            *pA++=s?k(w,a,b):3; /* 3 = type */
          }
          else *pA++=k(w,a,b);
        }
        }
      }
      //todo: suspend console, invoke repl
      e=0;
      if(pA[-1]<4) {
        if(pA[-1]==0) { e="nyi"; }
        else if(pA[-1]==1) { e="rank"; }
        else if(pA[-1]==2) { e="len"; }
        else if(pA[-1]==3) { e="type"; }
      }
      if(e) pA[-1]=zvset((U)sp(e),0xe);
    }
    if(timer&&times)kfree(pA[-1]);
    }
    times=1;
    v=*--pA;
    if(zv(v)) { v0=zvget(v); if(15==v0>>60) v=vlookup(v0); }
    if(timer) { kfree(v); timer=0; printf("%f\n",timer_stop()); }
    else if(p) {
      if(quiet) { kfree(v); quiet=0; }
      else kprint(v,"\n");
    }
  }
  return v;
}

static void r000(pgs *s) { /* $a > s */
  (void)s;
}
static void r001(pgs *s) { /* s > e se */
  s->vi--;
}
static void r002(pgs *s) { /* e > o ez */
  pn b=s->V[s->vi--];
  char *a;
  if(b.v&&b.n) if((a=strchr(P,b.v))) s->pbc[s->pbci++]=64+a-P;
}
static void r003(pgs *s) { /* e > ez */
  pn b=Vvi;
  char *a;
  if(b.v) {
    if((a=strchr(P,b.v))) s->pbc[s->pbci++]=32+a-P;
    else s->pbc[s->pbci++]=b.v; /* sys exit 96 */
  }
}
static void r004(pgs *s) { /* se > ';' */
  (void)s;
}
static void r005(pgs *s) { /* se > '\n' */
  (void)s;
}
static void r006(pgs *s) { /* o > N */
  s->values[s->valuei]=Vvi.n;
  Vvi.n=s->valuei++;
  s->pbc[s->pbci++]=Vvi.n;
}
static void r007(pgs *s) { /* o > klist */
  (void)s;
}
static void r008(pgs *s) { /* ez > */
   s->V[++s->vi].v=0;
   s->V[s->vi].n=0;
}
static void r009(pgs *s) { /* ez > V e */
  pn b;
  b=s->V[s->vi--];
  Vvi.v=Vvi.n;
  Vvi.n=b.n;
}
static void r010(pgs *s) { /* ez > plist */
  (void)s;
}
static void r011(pgs *s) { /* klist > '(' elist ')' */
  s->vi-=2;
  s->V[s->vi]=s->V[s->vi+1];
}
static void r012(pgs *s) { /* plist > '[' elist ']' */
  (void)s;
}
static void r013(pgs *s) { /* elist > e elistz */
  (void)s;
}
static void r014(pgs *s) { /* elistz > */
  (void)s;
}
static void r015(pgs *s) { /* elistz > se e elistz */
  (void)s;
}

static void (*F[16])(pgs *s)={r000,r001,r002,r003,r004,r005,r006,r007,r008,r009,r010,r011,r012,r013,r014,r015};


pgs* pgnew(void) { pgs *s=xcalloc(1,sizeof(pgs)); s->valuei=1; return s; }
void pgfree(pgs *s) { xfree(s); }
pr* prnew(void) {
  pr *z=xcalloc(1,sizeof(pr));
  z->bc=xcalloc(256,sizeof(char*));
  z->bcn=xcalloc(256,sizeof(int));
  z->values=xcalloc(256,sizeof(U*));
  return z;
}
void prfree(pr *r) {
  int i;
  for(i=0;i<r->n;i++) {
    xfree(r->bc[i]);
    xfree(r->values[i]);
  }
  xfree(r->bc);
  xfree(r->bcn);
  xfree(r->values);
  xfree(r);
}
pr* pgparse(char *q, int load) {
  int j,r;
  pr *z=prnew();
  pgs *s=pgnew();
  s->p=q;
  s->ti=0;s->tc=0;s->si=-1;s->ri=-1;s->vi=-1;
  memset(s->V,0,sizeof(s->V));
  if(!lex(s,load)||s->tc<1) { pgfree(s); prfree(z); return 0; }

  while(1+s->ti<s->tc) {
    s->si=-1;s->ri=-1;s->vi=-1;
    z->bc[z->n]=xcalloc(1,256);
    z->values[z->n]=xcalloc(1,256*sizeof(U));
    s->pbc=z->bc[z->n];
    s->pbci=z->bcn[z->n];
    s->values=z->values[z->n];
    s->valuei=0;
    s->S[++s->si]=T000; /* $a */
    for(;;) {
      if(s->S[s->si]==s->t[s->ti]) {
        s->V[++s->vi].n=s->v[s->ti++];
        --s->si;
      }
      else {
        if(s->S[s->si]>=LI) { fprintf(stderr,"parse\n"); ++z->n; prfree(z); pgfree(s); return 0; }
        if(s->t[s->ti]>=LJ) { fprintf(stderr,"parse\n"); ++z->n; prfree(z); pgfree(s); return 0; }
        r=LL[s->S[s->si--]][s->t[s->ti]];
        if(r==-1) { fprintf(stderr,"parse\n"); ++z->n; prfree(z); pgfree(s); return 0; }
        s->R[++s->ri]=r;
        s->S[++s->si]=-2; /* reduction marker */
        for(j=RC[r]-1;j>=0;j--) s->S[++s->si]=RT[r][j];
      }
      while(s->si>=0&&s->S[s->si]==-2) { (*F[s->R[s->ri--]])(s); --s->si; }
      if(s->si<0) { --s->vi; break; }
    }
    z->bcn[z->n]=s->pbci;
    ++z->n;
  }
  pgfree(s);
  return z;
}
