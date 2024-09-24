#include "p.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "timer.h"
#include "k.h"
#include "x.h"

/*
e > o ez | ez      # dyad | monad
o > N | '(' e ')'
ez > | V e
*/

char *_P=":+-*%&|<>=~.!@?#_^,$";
Z2 b[]={6,0,3,5,5,0,0,6};

/* added for vectors */
_g(tn,n3(x<<b[i]))
_f(lu,x?64-bu(clzl)(x):0)
_f(iu,x?bu(ctzl)(x):64)
G(M,ij=m(6,lu(tn(i,x)))-6;ik=iu(~_j[j]);_j[j]^=1L<<k;mz(8+i<<28|j<<24|k<<18|a,x))

#define LI 4
#define LJ 9
static int LL[4][9]={
{-1,-1,-1,-1,0,0,-1,0,-1},
{-1,-1,-1,-1,1,1,2,2,2},
{-1,-1,-1,-1,3,4,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,5,6,5}
};

static int RT[7][3]={
{T001},
{T002,T003},
{T003},
{T004},
{T005,T001,T006},
{-1},
{T007,T001}
};

static int RC[7]={1,2,1,1,3,0,2};

#define Vvi s->V[s->vi]

U pgreduce(pgs *s) {
  int i;
  char c,q;
  U A[256],*pA=A,a,b;
  for(i=0;i<s->pbci;i++) {
    c=s->pbc[i];
    q=c>>5;
    if(!q) *pA++=s->values[c];
    else if(q==1) { /* 32 33 34 ... */
      a=*--pA;
      *pA++=k(c-32-1,a);
    }
    else if(q==2) { /* 64 65 66 ... */
      b=*--pA;
      a=*--pA;
      *pA++=K(c-64-1,a,b);
    }
    //suspend console, invoke repl
    //if(pA[-1]==255) printf("!error\n");
  }
  return *--pA;
}

static void r000(pgs *s) { /* $a > e */
}
static void r001(pgs *s) { /* e > o ez */
  pn b=s->V[s->vi--];
  char *a;
  if(b.n) if((a=strchr(_P,b.v))) s->pbc[s->pbci++]=64+a-_P;
}
static void r002(pgs *s) { /* e > ez */
  pn b=Vvi;
  char *a;
  if((a=strchr(_P,b.v))) s->pbc[s->pbci++]=32+a-_P;
}
static void r003(pgs *s) { /* o > N */
  s->values[s->valuei]=Vvi.n;
  Vvi.n=s->valuei++;
  s->pbc[s->pbci++]=Vvi.n;
}
static void r004(pgs *s) { /* o > '(' e ')' */
  s->vi-=2;
  s->V[s->vi]=s->V[s->vi+1];
}
static void r005(pgs *s) { /* ez > */
   s->V[++s->vi].v=0;
   s->V[s->vi].n=0;
}
static void r006(pgs *s) { /* ez > V e */
  pn b;
  b=s->V[s->vi--];
  Vvi.v=Vvi.n;
  Vvi.n=b.n;
}

static void (*F[7])(pgs *s)={r000,r001,r002,r003,r004,r005,r006};

static void push(pgs *s, int tt, U tv) {
  s->t[s->tc]=tt;
  s->v[s->tc++]=tv;
  s->lt=tt;
}

static char *p;

static int iii;
static float fff;
static int gn_(void) {
  char c,*q=p;
  int s=0;
  while(1) {
    switch(s) {
    case 0:
      if(*p=='0') s=1;
      else if(isdigit(*p)) s=4;
      else if(*p=='-') s=5;
      else if(*p=='.') s=7;
      else s=10;
      break;
    case 1:
      if(*p=='n'||*p=='i') s=2;
      else if(*p=='N'||*p=='I') s=3;
      else if(*p=='e'||*p=='E') s=8;
      else if(*p=='.') s=6;
      else if(isdigit(*p)) s=4;
      else s=11;
      break;
    case 2: s=12; break;
    case 3: s=11; break;
    case 4:
      if(isdigit(*p)) s=4;
      else if(*p=='e'||*p=='E') s=8;
      else if(*p=='.') s=6;
      else s=11;
      break;
    case 5:
      if(*p=='0') s=1;
      else if(isdigit(*p)) s=4;
      else if(*p=='.') s=7;
      else s=10;
      break;
    case 6:
      if(isdigit(*p)) s=9;
      else if(*p=='e'||*p=='E') s=8;
      else s=12;
      break;
    case 7: if(isdigit(*p)) s=9; else s=10; break;
    case 8: if(isdigit(*p)||*p=='-'||*p=='+') s=9; else s=10; break;
    case 9:
      if(isdigit(*p)) s=9;
      else if(*p=='e'||*p=='E') s=8;
      else s=12;
      break;
    case 10: return 0; /* error */
    case 11: /* int */
      c=*--p; *p=0;
      iii=xatoi(q);
      *p=c;
      return 1;
    case 12: /* float */
      c=*--p; *p=0;
      fff=xstrtof(q);
      *p=c;
      return 2;
    }
    ++p;
  }
  return 0;
}

static int gn(pgs *pgs) {
  int r,*iv=0,i;
  int ic=0,fc=0,imm=1,fm=1;
  float *fv=0;
  char *q;
  r=gn_();
  if(isblank(*p)) {
    q=p;
    while(isblank(*p))++p;
    if(isdigit(*p)||((*p=='.'||*p=='-')&&isdigit(p[1]))) { /* convert to vector */
      if(r==1) { imm<<=1; iv=xrealloc(iv,imm*sizeof(int)); iv[ic++]=iii; }
      else if(r==2) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); fv[fc++]=fff; }
    }
    p=q;
    if(iv) {
      while(isblank(*p)) {
        q=p;
        while(isblank(*p))++p;
        r=gn_();
        if(r==1) {
          if(ic==imm) { imm<<=1; iv=xrealloc(iv,imm*sizeof(int)); }
          iv[ic++]=iii;
        }
        else if(r==2) {
          fm=imm;
          fv=xrealloc(fv,fm*sizeof(float));
          for(i=0;i<ic;i++) fv[fc++]=I2F(iv[i]);
          xfree(iv); iv=0; ic=0;
          if(fc==fm) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); }
          fv[fc++]=fff;
          break;
        }
        else { p=q; break; }
      }
    }
    if(fv) {
      while(isblank(*p)) {
        q=p;
        while(isblank(*p))++p;
        r=gn_();
        if(r==1) {
          fff=I2F(iii);
          if(fc==fm) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); }
          fv[fc++]=fff;
        }
        else if(r==2) {
          if(fc==fm) { fm<<=1; fv=xrealloc(fv,fm*sizeof(float)); }
          fv[fc++]=fff;
        }
        else { p=q; break; }
      }
    }
  }
  if(ic) {
    U x=M(3,0,ic);
    int *pi=sx;
    i(ic,pi[i]=iv[i])
    push(pgs,T004,x);
  }
  else if(fc) {
    U x=M(4,0,fc);
    float *pf=sx;
    i(fc,pf[i]=fv[i])
    push(pgs,T004,x);
  }
  else if(r==1) push(pgs,T004,iii&0xffffffff|3L<<60);
  else if(r==2) push(pgs,T004,*((int*)&fff)&0xffffffff|4L<<60);
  if(iv) xfree(iv);
  if(fv) xfree(fv);
  return r;
}

static void help() {
  printf(""
  "Verb    (monad)"
  "+ +            "
  "- -            "
  "* *      sqr   "
  "! mod    index "
  "@ @      first "
  "? find   unique"
  "# take   count \n");
}

unsigned int TIMES;
static int lex(pgs *pgs) {
  int f=1,s;
  TIMES=0;
  p=pgs->p;
  while(1) {
    s=isblank(*p);
    while(isblank(*p)) ++p;
    if(!*p) break;
    else if(*p=='-') {
      if(!(s|f)&&(pgs->lt==T004||pgs->lt==T006)) { ++p; push(pgs,T007,'-'); }
      else if(isdigit(p[1])||(p[1]=='.'&&isdigit(p[2]))) gn(pgs);
      else { ++p; push(pgs,T007,'-'); }
    }
    else if(isdigit(*p)||(*p=='.'&&isdigit(p[1]))) gn(pgs);
    else if(strchr(":+-*%&|<>=~.!@?#_^,$",*p)) { push(pgs,T007,*p); ++p; }
    else if(*p=='(') { ++p; push(pgs,T005,0); }
    else if(*p==')') { ++p; push(pgs,T006,0); }
    else if(*p=='\n') { if(f) return 0; else push(pgs,T008,0); break; }
    else if(*p=='\\'&&*(p+1)=='\\') exit(0);
    else if(*p=='\\'&&*(p+1)=='\n') { help(); return 0; }
    else if(*p=='\\'&&*(p+1)=='t') { p+=2; if(!(TIMES=atoi(p)))TIMES=1; while(isdigit(*p))++p; }
    else { printf("lex\n"); return 0; }
    f=0;
  }
  return 1;
}

pgs* pgnew() { pgs *s=xcalloc(1,sizeof(pgs)); s->valuei=1; return s; }
void pgfree(pgs *s) { xfree(s); }
void pgparse(pgs *s) {
  int i,j,r;
  s->ti=0;s->tc=0;s->si=-1;s->ri=-1;s->vi=-1;
  memset(s->V,0,sizeof(s->V));
  if(!lex(s)||s->tc<1) return;
  s->S[++s->si]=T000; /* $a */
  for(i=0;;i++) {
    if(s->S[s->si]==s->t[s->ti]) {
      s->V[++s->vi].n=s->v[s->ti++];
      --s->si;
    }
    else {
      if(s->S[s->si]>=LI) { printf("parse\n"); break; }
      if(s->t[s->ti]>=LJ) { printf("parse\n"); break; }
      r=LL[s->S[s->si--]][s->t[s->ti]];
      if(r==-1) { printf("parse\n"); break; }
      s->R[++s->ri]=r;
      s->S[++s->si]=-2; /* reduction marker */
      for(j=RC[r]-1;j>=0;j--) s->S[++s->si]=RT[r][j];
    }
    while(s->si>=0&&s->S[s->si]==-2) { (*F[s->R[s->ri--]])(s); --s->si; }
    if(s->si<0) { --s->vi; break; }
  }
}
