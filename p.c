#include "p.h"
#include <stdio.h>
#include <string.h>
#include "k.h"
#include "sym.h"

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

char *_P=":+-*%&|<>=~.!@?#_^,$";

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

static char *VNAMES[256];
static U *VVALUES[256];
static VI=0;
static U vlookup(char *v) {
  int i;
  U r=0;
  char *s=(char*)((U)v^15L<<60);
  for(i=0;i<VI;i++) if(s==VNAMES[i]) return VVALUES[i];
  return r;
}
U pgreduce(pr *r) {
  int i,j;
  char c,q;
  U A[256],*pA=A,a,b,v;
  for(i=0;i<r->n;i++) {
    int n=r->bcn[i];
    char *bc=r->bc[i];
    U *values=r->values[i];
    pA=A;
    for(j=0;j<n;j++) {
      c=bc[j];
      q=c>>5;
      if(!q) *pA++=values[c];
      else if(q==1) { /* 32 33 34 ... */
        a=*--pA;
        if(15==a>>60) a=vlookup(a);
        *pA++=k(c,a,0);
      }
      else if(q==2) { /* 64 65 66 ... */
        b=*--pA;
        a=*--pA;
        if(c==64&&15==a>>60) { /* a:1 */
          if(15==b>>60) b=vlookup(b);
          VNAMES[VI]=sp(((U)a^15L<<60));
          VVALUES[VI++]=kref(b);
        }
        else {
          if(15==a>>60) a=vlookup(a);
          if(15==b>>60) b=vlookup(b);
          *pA++=k(c,a,b);
        }
      }
      else if(q==3) { /* 96 97 98 ... sys monadic (exit) */
        if(c==96) exit(0);
      }
      //suspend console, invoke repl
      //if(pA[-1]==255) printf("!error\n");
    }
    v=*--pA;
    if(15==v>>60) v=vlookup(v);
    kprint(v);
  }
  return *pA;
}

static void r000(pgs *s) { /* $a > s */
}
static void r001(pgs *s) { /* s > e se */
  s->vi--;
}
static void r002(pgs *s) { /* e > o ez */
  pn b=s->V[s->vi--];
  char *a;
  if(b.n) if((a=strchr(_P,b.v))) s->pbc[s->pbci++]=64+a-_P;
}
static void r003(pgs *s) { /* e > ez */
  pn b=Vvi;
  char *a;
  if((a=strchr(_P,b.v))) s->pbc[s->pbci++]=32+a-_P;
  else s->pbc[s->pbci++]=b.v; /* sys exit 96 */
}
static void r004(pgs *s) { /* se > ';' */
}
static void r005(pgs *s) { /* se > '\n' */
}
static void r006(pgs *s) { /* o > N */
  s->values[s->valuei]=Vvi.n;
  Vvi.n=s->valuei++;
  s->pbc[s->pbci++]=Vvi.n;
}
static void r007(pgs *s) { /* o > klist */
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
}
static void r011(pgs *s) { /* klist > '(' elist ')' */
  s->vi-=2;
  s->V[s->vi]=s->V[s->vi+1];
}
static void r012(pgs *s) { /* plist > '[' elist ']' */
}
static void r013(pgs *s) { /* elist > e elistz */
}
static void r014(pgs *s) { /* elistz > */
}
static void r015(pgs *s) { /* elistz > se e elistz */
}

static void (*F[16])(pgs *s)={r000,r001,r002,r003,r004,r005,r006,r007,r008,r009,r010,r011,r012,r013,r014,r015};


pgs* pgnew() { pgs *s=xcalloc(1,sizeof(pgs)); s->valuei=1; return s; }
void pgfree(pgs *s) { xfree(s); }
pr* prnew() {
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
}
pr* pgparse(char *q) {
  int i,j,r;
  pr *z=prnew();
  pgs *s=pgnew();
  s->p=q;
  s->ti=0;s->tc=0;s->si=-1;s->ri=-1;s->vi=-1;
  memset(s->V,0,sizeof(s->V));
  if(!lex(s)||s->tc<1) { pgfree(s); return 0; }

  while(1+s->ti<s->tc) {
    s->si=-1;s->ri=-1;s->vi=-1;
    z->bc[z->n]=xcalloc(1,256);
    z->values[z->n]=xcalloc(1,256*sizeof(U));
    s->pbc=z->bc[z->n];
    s->pbci=z->bcn[z->n];
    s->values=z->values[z->n];
    s->valuei=0;

    s->S[++s->si]=T000; /* $a */
    for(i=0;;i++) {
      if(s->S[s->si]==s->t[s->ti]) {
        s->V[++s->vi].n=s->v[s->ti++];
        --s->si;
      }
      else {
        if(s->S[s->si]>=LI) { fprintf(stderr,"parse\n"); break; }
        if(s->t[s->ti]>=LJ) { fprintf(stderr,"parse\n"); break; }
        r=LL[s->S[s->si--]][s->t[s->ti]];
        if(r==-1) { fprintf(stderr,"parse\n"); break; }
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
