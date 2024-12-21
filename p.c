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
#include "fn.h"

/*
s > e se | se
e > o ez
se > ';' | '\n'
o > N | V | klist
ez > | e | plist
klist > '(' elist ')'
plist > '[' elist ']'
elist > | e elistz
elistz > | se e elistz
*/

static char *P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\;()";
static int R;

#define LI 10
#define LJ 19
static int LL[10][19]={
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,1,1,1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,5,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,7,8,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,9,10,10,10,9,11,9,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,15,15,14,-1,14,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,17,-1,-1,-1,16,-1,16,-1}
};

static int RT[18][3]={
{T001},
{T002,T003},
{T003},
{T004,T005},
{T010},
{T011},
{T012},
{T013},
{T006},
{-1},
{T002},
{T007},
{T014,T008,T015},
{T016,T008,T017},
{-1},
{T002,T009},
{-1},
{T003,T002,T009}
};

static int RC[18]={1,2,1,2,1,1,1,1,1,0,1,1,3,3,0,2,0,3};
static char *E[9]={"nyi","rank","len","type","value","range","domain","valence","index"};

#define Vvi s->V[s->vi]

static U vlookup(U v) {
  U r=scope_get(cs,(char*)(b(56)&v));
  return r?r:4;
}

U pgreduce_(char *bc, int n, U *values, int *quiet, int times) {
  int j,w,assign=0;
  char c,q,*e,*s;
  U A[256],*pA=A,a,b,v=0,v0,v1=0,a0,b0,aa[256],*pa,r;
  fn *f;
  pr *z;
  pA=A;
  for(j=0;j<n;j++) {
    *quiet=0;
    c=bc[j];
    q=c>>5;
    if(!q) {
      *pA++=v=values[(int)c];
      if(zv(v)) {
        v0=v; v=zvget(v);
        if(0xf==zx(v)) { v1=vlookup(v); if(zv(v1)) v=zvget(v1); else kfree(v1); }
        if(0xc==zx(v)) {
          f=(fn*)(b(56)&v);
          if(!f->s) fnd(f);
          if(j+1<n && 64==bc[j+1]) assign=1;
          if(pA>A+1 && !assign) {
            if(zvplist(pA[-2])) {
              U z=zvget(pA[-2]);
              plist *pl=(plist*)(b(56)&z);
              r=fne(f,px(pl->x),pl->n);
              kfree(pA[-2]); /* always free plist */
              if(!times) kfree(pA[-1]);
              --pA;
              pA[-1]=r;
            }
            else if(pA>A+(f->v?f->v:1) && !assign) {
              --pA;
              i(f->v,aa[i]=*--pA)
              *pA++=fne(f,aa,f->v);
              i(f->v,kfree(aa[i]))
            }
            else if(2==f->v && pA>A+1 && !assign) {
              aa[0]=values[++j];
              aa[1]=pA[-2];
              pA-=2;
              *pA++=fne(f,aa,f->v);
              i(2,kfree(aa[i]))
            }
            if(!times) zvfree(v0);
          }
          if(v1 && !assign) zvfree(v1);
        }
        else if(0xa==zx(v)) { /* klist */
          z=(pr*)(b(56)&v);
          a=tn(0,z->n);
          pa=(U*)px(a);
          i(z->n,pa[z->n-i-1]=pgreduce_(z->bc[i],z->bcn[i],z->values[i],quiet,times))
          pA[-1]=knorm(a);
          if(!times) prfree(z);
        }
        else if(0xb==zx(v)) { /* plist */
          z=(pr*)(b(56)&v);
          a=tn(0,z->n);
          pa=(U*)px(a);
          i(z->n,pa[z->n-i-1]=pgreduce_(z->bc[i],z->bcn[i],z->values[i],quiet,times))
          plist *pl=xmalloc(sizeof(plist));
          pl->n=z->n;
          if(z->n==2 && !pa[1]) pl->n=1;
          if(z->n==2 && !pa[0] && !pa[1]) pl->n=0;
          pl->x=a;
          pA[-1]=zvset((U)pl,0x9);
          if(!times) prfree(z);
        }
      }
    }
    else if(q==1) { /* 32 33 34 ... */
      if(pA>A) {
        a=*--pA;
        if(zv(a)) { a0=zvget(a); if(0xf==zx(a0)) a=vlookup(a0); }
        if(a==4) *pA++=4; /* value */
        else if(a==3) *pA++=3; /* type */
        else if(c==32) { *pA++=a; if(cs!=gs) { R=1; break; } }
        else *pA++=k(c%32,0,a);
      }
      else { *pA++=zvset((U)P[(int)c%32],0xd); break; }
    }
    else if(q==2) { /* 64 65 66 ... */
      if(pA>A+1) {
        b=*--pA;
        a=*--pA;
        if(c==64&&zv(a)) { /* a:1 */
          a0=a;
          a=zvget(a);
          if(zv(b)) { b0=zvget(b); if(0xf==zx(b0)) b=vlookup(b0); }
          if(b==4) *pA++=4;  /* value */
          else {
            scope_set(cs,(char*)(b(56)&a),b);
            *pA++=a0;
            *quiet=1;
            kfree(b);
          }
        }
        else {
          if(zv(a)) { a0=zvget(a); if(0xf==zx(a0)) a=vlookup(a0); }
          if(zv(b)) { b0=zvget(b); if(0xf==zx(b0)) b=vlookup(b0); }
          if(a==4||b==4) *pA++=4; /* value */
          else {
            if((w=c%32)==30) { /* adverb? / \ ' */
              s=strchr(P,(char)a); a=s-P;
              *pA++=s?k(w,a,b):3; /* 3 = type */
            }
            else if(zv(a) && 13==c%32) { /* f@x */
              a0=zvget(a);
              f=(fn*)(b(56)&a0);
              if(!f->s) fnd(f);
              if(0xc==zx(a0)) { aa[0]=b; *pA++=fne(f,aa,1); }
              kfree(a);
              kfree(b);
            }
            else *pA++=k(w,a,b);
          }
        }
      }
    }
    //todo: suspend console, invoke repl
    e=0;
    if(pA>A&&pA[-1]<9)e=E[pA[-1]];
    if(e) { pA[-1]=kerror(e); break; }
  }
  v=pA>A?*--pA:0;
  if(zv(v)) { v0=zvget(v); if(0xf==zx(v0)) v=vlookup(v0); }
  if(v==4) { e="value"; v=zvset((U)sp(e),0xe); }
  return v;
}
U pgreduce(pr *r, int p) {
  int i,n,quiet,timer=0,times=1;
  char *s,*bc;
  U a,v=0;
  if(!r||!r->n) return v;
  for(i=0;i<r->n;i++) {
    if(R) { R=0; break; }
    if(!(n=r->bcn[i])) continue;
    bc=r->bc[i];
    U *values=r->values[i];
    if(1<n) {
      if(bc[1]==96) { prfree(r); exit_(0); }
      else if(bc[1]==97) { timer=1; a=values[(int)bc[0]]; if(zv(a)) { a=zvget(a); if(0xf==zx(a)) a=vlookup(a); } times=(int)a; timer_start(); continue; }
      else if(bc[1]==98) { a=values[(int)bc[0]]; s=xstrndup((char*)px(a),(int)a); load(s,2); kfree(a); xfree(s); continue; }
    }
    while(times--) {
      v=pgreduce_(bc,n,values,&quiet,times);
      if(times) kfree(v);
    }
    if(timer) { kfree(v); timer=0; printf("%f\n",timer_stop()); }
    else if(p) {
      if(quiet) { kfree(v); quiet=0; }
      else { kprint(v,"","\n",""); kfree(v); }
    }
    timer=0; times=1;
    if(R) { R=0; break; }
  }
  return v;
}

static U listbc(pgs *s, pn *b, int t);
static void bc(pgs *s, pn *a, U *values, char *bc, int *valuei, int *bci) {
  char *t;
  pn *s0[1024],*s1[1024];
  int i0=0,i1=0;
  s0[++i0]=a;
  while(i0) {
    a=s0[i0--];
    s1[++i1]=a;
    if(a->t==5){} /* klist */
    else if(a->t==4){} /* plist */
    else i(a->m,if(a->a[i]) s0[++i0]=a->a[i])
  }
  while(i1) {
    a=s1[i1--];
    if(a->t==1) {
      if(zv(a->v)) {
        values[*valuei]=a->v;
        bc[(*bci)++]=(*valuei)++;
      }
      else if((t=strchr(P,a->v))) bc[(*bci)++]=(a->a[0]?64:32)+t-P;
      else bc[(*bci)++]=a->v; /* sys exit 96 */
    }
    else if(a->t==2) { values[*valuei]=a->n; a->n=(*valuei)++; bc[(*bci)++]=a->n; }
    else if(a->t==5) { values[*valuei]=listbc(s,a,0xa); bc[(*bci)++]=(*valuei)++;; } /* klist */
    else if(a->t==4) { values[*valuei]=listbc(s,a,0xb); bc[(*bci)++]=(*valuei)++;; } /* plist */
    if(a->f) pnfree(a);
  }
}
static U listbc(pgs *s, pn *a, int t) {
  int i,j=0;
  pr *z=prnew();
  for(i=0;i<a->m;i++) {
    if(!a->a[i]) continue;
    z->bc[i]=xcalloc(1,256);
    z->values[i]=xcalloc(1,256*sizeof(U));
    bc(s,a->a[i],z->values[i],z->bc[i],&j,&z->bcn[i]);
  }
  z->n=i;
  return zvset((U)z,t);
}
static void r000(pgs *s) { /* $a > s */
  bc(s,s->V[s->vi],s->values,s->pbc,&s->valuei,&s->pbci);
}
static void r001(pgs *s) { /* s > e se */
  --s->vi;
}
static void r002(pgs *s) { /* s > se */
  (void)s;
}
static void r003(pgs *s) { /* e > o ez */
  pn *b=s->V[s->vi--];
  pn *a=s->V[s->vi];
  if(!b) return;
  if(a->t==1 && b->t==1) {
    if(!a->a[1]) a->a[1]=b; /* 1+2+3 */
    else {                  /* (1+2)*3 */
      b->a[0]=a;
      s->V[s->vi]=b;
    }
  }
  else if(a->t==1) {
    a->a[0]=0;
    a->a[1]=b;
  }
  else if(a->t==2 && b->t==1) {
    b->a[0]=a;
    s->V[s->vi]=b;
  }
  else if(a->t==2 && b->t==4) {
    a->a[0]=0;
    a->a[1]=b;
  }
  else if(a->t==2 && b->t==2) {
    a->a[0]=b;
  }
}
static void r004(pgs *s) { /* se > ';' */
  (void)s;
}
static void r005(pgs *s) { /* se > '\n' */
  (void)s;
}
static void r006(pgs *s) { /* o > N */
  pn *a=s->V[s->vi];
  a->t=2;
}
static void r007(pgs *s) { /* o > V */
  pn *a=s->V[s->vi];
  a->t=1;
  a->v=a->n;
  a->n=0;
}
static void r008(pgs *s) { /* o > klist */
  (void)s;
}
static void r009(pgs *s) { /* ez > */
  s->V[++s->vi]=0;
}
static void r010(pgs *s) { /* ez > e */
  (void)s;
}
static void r011(pgs *s) { /* ez > plist */
  (void)s;
}
static void r012(pgs *s) { /* klist > '(' elist ')' */
  s->vi--;
  pn *b=s->V[s->vi--];
  if(!b) { b=pnnew(5,0,0,2); b->f=1; }
  else if(b->t==4) b->t=5;
  s->V[s->vi]=b;
}
static void r013(pgs *s) { /* plist > '[' elist ']' */
  s->vi--;
  pn *b=s->V[s->vi--];
  if(!b) { b=pnnew(4,0,0,2); b->f=1; }
  if(b->t==2 || b->t==1) {
    pn *a=pnnew(4,0,0,2);
    a->f=1;
    a->a[1]=b;
    s->V[s->vi]=a;
  }
  else s->V[s->vi]=b;
}
static void r014(pgs *s) { /* elist > */
  s->V[++s->vi]=0;
}
static void r015(pgs *s) { /* elist > e elistz */
  pn *b=s->V[s->vi--];
  pn *a=s->V[s->vi];
  if(!b) return;
  if(b->m==2&&!b->a[1]) b->a[1]=a;
  else {
    b->a=xrealloc(b->a,sizeof(U*)*(b->m+1));
    b->a[b->m++]=a;
  }
  s->V[s->vi]=b;
}
static void r016(pgs *s) { /* elistz > */
  s->V[++s->vi]=0;
}
static void r017(pgs *s) { /* elistz > se e elistz */
  (void)s;
  pn *c=s->V[s->vi--];
  pn *b=s->V[s->vi--];
  pn *a=s->V[s->vi];
  if(!c) {
    a->a[0]=b;
    a->t=4;
  }
  else {
    if(c->m==2&&!c->a[1]) c->a[1]=b;
    else {
      c->a=xrealloc(c->a,sizeof(U*)*(c->m+1));
      c->a[c->m++]=b;
    }
    s->V[s->vi]=c;
  }
}

static void (*F[18])(pgs *s)={r000,r001,r002,r003,r004,r005,r006,r007,r008,r009,r010,r011,r012,r013,r014,r015,r016,r017};

pgs* pgnew(void) {
  pgs *s=xcalloc(1,sizeof(pgs));
  s->Sm=s->Rm=s->Vm=1024;
  s->tm=s->vm=1024;
  s->S=xmalloc(s->Sm*sizeof(int));
  s->R=xmalloc(s->Rm*sizeof(int));
  s->V=xmalloc(s->Vm*sizeof(pn*));
  s->t=xmalloc(s->tm*sizeof(int));
  s->v=xmalloc(s->vm*sizeof(pn*));
  return s;
}
void pgfree(pgs *s) {
  //if(s->p) xfree(s->p);
  if(s->S) xfree(s->S);
  if(s->R) xfree(s->R);
  if(s->V) xfree(s->V);
  if(s->t) xfree(s->t);
  i(s->tc,pnfree(s->v[i]))
  if(s->v) xfree(s->v);
  xfree(s);
}
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
        s->V[++s->vi]=s->v[s->ti++];
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
