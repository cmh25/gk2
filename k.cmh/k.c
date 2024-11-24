#include "k.h"
#include <stdlib.h>
#include "v.h"
#include <stdio.h>

static void *O[512];
static int R[512];
static int F[512];
static int oi,om=512,fm=512,fi=-1;

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
    case 0: if(!x&&!x(a,ax)) r=(U)O[b(12)&a>>48]; break; /* deref */
    case 1: r=plus(a,x); break;
    case 2: r=minus(a,x); break;
    case 3: r=times(a,x); break;
    case 4: r=divide(a,x); break;
    case 5: r=minand(a,x); break;
    case 6: r=maxor(a,x); break;
    case 7: r=less(a,x); break;
    case 8: r=more(a,x); break;
    case 9: r=equal(a,x); break;
    case 10: r=match(a,x); break;
    }
  }
  else { /* monad */
    switch(i) {
    case 0: if(x) { R[b(12)&x>>48]++; r=x; } break; /* ref + */
    case 2: r=negate(x); break;
    case 3: r=square(x); break;
    case 12: r=bang(x); break;
    case 15: /* ref - */
      if(x&&!ax) {
        j=b(12)&x>>48;
        if(R[j])R[j]--;
        else { free(O[j]); F[++fi]=j; }
      }
    }
  }
  return r;
}

U tn(int t,int n) {
  U r=0;
  void *v=0;
  int j;
  if(t==3) v=malloc(sizeof(int)*n);
  else if(t==4) v=malloc(sizeof(float)*n);
  if(v) {
    if(fi>-1) j=fi--;
    else j=oi++;
    O[j]=v;
    r=t(t+8,n);
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
      if(i==x(a,nx) && i<nx) { r=-1; break; }
      else if(i==nx && i<x(a,nx)) { r=1; break; }
      else if(i==x(a,nx) && i==nx) break;
      else if(pai[i]<pxi[i]) { r=-1; break; }
      else if(pai[i]>pxi[i]) { r=1; break; }
    }
  }
  else if(at==0xc) {
    paf=(float*)k(0,a,0);
    pxf=(float*)k(0,x,0);
    for(i=0;;++i) {
      if(i==x(a,nx) && i<nx) { r=-1; break; }
      else if(i==nx && i<x(a,nx)) { r=1; break; }
      else if(i==x(a,nx) && i==nx) break;
      else if(paf[i]<pxf[i]) { r=-1; break; }
      else if(paf[i]>pxf[i]) { r=1; break; }
    }
  }
  return r;
}
