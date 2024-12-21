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
k_(0,0)  // init
k_(0,x)  // ref -
k_(1,x)  // ref +
k_(2,x)  // raw pointer
*/
U k_(int i,U x) {
  U r=0;
  int j;
  U *pxu;
  switch(i) {
  case 0:
    if(!x) break; /* init */
    if(!ax) { /* ref - */
      j=b(12)&x>>48;
      if(R[j])R[j]--;
      else {
        if(tx==8) { PXU; i(nx,k_(0,pxu[i])) }
        free(O[j]); O[j]=0; F[++fi]=j;
      }
      if(fi==fm) { fprintf(stderr,"error: fm\n"); exit(1); }
    }
    break;
  case 1: if(!ax) { R[ox]++; r=x; } break; /* ref + */
  case 2: if(!ax) r=(U)O[ox]; break; /* deref */
  }
  return r;
}

// P=":+-*%&|<>=~.!@?#_^,$LMSA..ERZ'/\\"
U k(int i,U a,U x) {
  U r=0;
  if(a) { /* dyad */
    switch(i) {
    case 30: r=over(a,x); break;
    default: if(i>=FDSIZE||!FD[i]) return 0; r=FD[i](a,x); break;
    }
    if(i) { k_(0,a); k_(0,x); }
  }
  else { /* monad */
    switch(i) {
    default: if(i>=FMSIZE||!FM[i]) return 0; r=FM[i](x); k_(0,x); break;
    }
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
  case 7: v=malloc(sizeof(char*)*n); break;
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
  else if(at==0xb) { PAI; PXI;
    for(i=0;;++i) {
      if(i==na && i<nx) { r=-1; break; }
      else if(i==nx && i<na) { r=1; break; }
      else if(i==na && i==nx) break;
      else if(pai[i]<pxi[i]) { r=-1; break; }
      else if(pai[i]>pxi[i]) { r=1; break; }
    }
  }
  else if(at==0xc) { PAF; PXF;
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
  char *prc,*pxc;
  int *pri,*pxi;
  float *prf,*pxf;
  switch(tx) {
  case 2: r=x; break;
  case 3: r=x; break;
  case 4: r=x; break;
  case 0xa: r=tn(2,nx); PRC; PXC; i(nx,*prc++=*pxc++) break;
  case 0xb: r=tn(3,nx); PRI; PXI; i(nx,*pri++=*pxi++) break;
  case 0xc: r=tn(4,nx); PRF; PXF; i(nx,*prf++=*pxf++) break;
  }
  return r;
}
