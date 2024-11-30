#include "k.h"
#include <stdlib.h>
#include <stdio.h>
#include "v.h"
#include "av.h"

static void *O[512];
static int R[512];
static int F[512];
static int oi,om=512,fm=511,fi=-1;

/*
k(0,x,0)  // raw pointer
k(0,0,x)  // ref +
k(15,0,x) // ref -
k(0,0,0)  // workspace
*/
// P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ
U k(int i,U a,U x) {
  U r=0;
  int j;
  if(a) { /* dyad */
    switch(i) {
    case  0: if(!x&&!aa) r=(U)O[oa]; break; /* deref */
    case  1: r=plus(a,x); break;
    case  2: r=minus(a,x); break;
    case  3: r=times(a,x); break;
    case  4: r=divide(a,x); break;
    case  5: r=minand(a,x); break;
    case  6: r=maxor(a,x); break;
    case  7: r=less(a,x); break;
    case  8: r=more(a,x); break;
    case  9: r=equal(a,x); break;
    case 10: r=match(a,x); break;
    case 11: r=dot(a,x); break;
    case 12: r=mod(a,x); break;
    case 13: r=at(a,x); break;
    case 14: r=find(a,x); break;
    case 15: r=take(a,x); break;
    case 16: r=drop(a,x); break;
    case 17: r=cut(a,x); break;
    case 18: r=join(a,x); break;
    case 19: r=parse(a,x); break;
    case 30: r=over(a,x); break;
    }
    if(i) {k(15,0,a); k(15,0,x); }
  }
  else { /* monad */
    switch(i) {
    case  0: if(x) { R[ox]++; r=x; } break; /* ref + */
    case  1: r=pos(x); break;
    case  2: r=negate(x); break;
    case  3: r=square(x); break;
    case  4: r=sqrt_(x); break;
    case  5: r=flip(x); break;
    case  6: r=reverse(x); break;
    case  7: r=asc(x); break;
    case  8: r=desc(x); break;
    case  9: r=group(x); break;
    case 10: r=not_(x); break;
    case 11: r=value(x); break;
    case 12: r=bang(x); break;
    case 13: r=first(x); break;
    case 14: r=unique(x); break;
    case 15: /* ref - */
      if(x&&!ax) {
        j=b(12)&x>>48;
        if(R[j])R[j]--;
        else { free(O[j]); O[j]=0; F[++fi]=j; }
        if(fi==fm) { fprintf(stderr,"error: fm\n"); exit(1); }
        r=t(3,nx); /* #v */
      }
      else r=t(3,1); break;
      break;
    case 16: r=floor_(x); break;
    case 17: r=rule(x); break;
    case 18: r=enlist(x); break;
    case 19: r=str(x); break;
    }
    if(i&&i!=15) k(15,0,x);
  }
  return r;
}

U tn(int t,int n) {
  U r=0; void *v=0; int j;
  switch(t) {
  case 0: v=malloc(sizeof(U)*n); break;
  case 2: v=malloc(n); break;
  case 3: v=malloc(sizeof(int)*n); break;
  case 4: v=malloc(sizeof(float)*n); break;
  }
  if(v) {
    if(fi>-1) j=F[fi--];
    else j=oi++;
    if(oi==om) { fprintf(stderr,"error: om\n"); exit(1); }
    O[j]=v;
    r=t(8+t,n);
    r|=(U)j<<48;
  }
  return r;
}

int kcmpr(U a, U x) {
  int r=0,i,at=a>>60,xt=x>>60,*pai,*pxi;
  float *paf,*pxf;
  if(at<xt) r=-1;
  else if(at>xt) r=1;
  else if(at==3 && (int)a<(int)x) r=-1;
  else if(at==3 && (int)a>(int)x) r=1;
  else if(at==4 && fu(a)<fu(x)) r=-1;
  else if(at==4 && fu(a)>fu(x)) r=1;
  else if(at==0xb) {
    pai=(int*)k(0,a,0);
    pxi=(int*)k(0,x,0);
    for(i=0;;++i) {
      if(i==na && i<nx) { r=-1; break; }
      else if(i==nx && i<na) { r=1; break; }
      else if(i==na && i==nx) break;
      else if(pai[i]<pxi[i]) { r=-1; break; }
      else if(pai[i]>pxi[i]) { r=1; break; }
    }
  }
  else if(at==0xc) {
    paf=(float*)k(0,a,0);
    pxf=(float*)k(0,x,0);
    for(i=0;;++i) {
      if(i==na && i<nx) { r=-1; break; }
      else if(i==nx && i<na) { r=1; break; }
      else if(i==na && i==nx) break;
      else if(paf[i]<pxf[i]) { r=-1; break; }
      else if(paf[i]>pxf[i]) { r=1; break; }
    }
  }
  return r;
}

U kcp(U x) {
  U r=0;
  int *pri,*pxi;
  float *prf,*pxf;
  switch(tx) {
  case 3: r=x; break;
  case 4: r=x; break;
  case 0xb:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    pxi=(int*)k(0,x,0);
    i(nx,*pri++=*pxi++)
    break;
  case 0xc:
    r=tn(4,nx);
    prf=(float*)k(0,r,0);
    pxf=(float*)k(0,x,0);
    i(nx,*prf++=*pxf++)
    break;
  }
  return r;
}
