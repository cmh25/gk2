#include "k.h"
#include <stdlib.h>

static void *O[512];
static int R[512];
static int F[512];
static int oi,om=512,fm=512,fi=-1;

U plus(U a, U x) {
  U r=0;
  float f;
  switch(x(a,tx)) {
  case 3:
    r=t(3,(int)a+(int)x);
    break;
  case 4:
    f=(*(float*)&a)+(*(float*)&x);
    r=t(4,*((int*)&f));
    break;
  }
  return r;
}

/*
k(0,x,0)  // raw pointer
k(0,0,x)  // ref +
k(15,0,x) // ref -
k(0,0,0)  // workspace
*/
U k(int i, U a, U x) {
  U r=0;
  int j;
  switch(i) {
  case 0:
    if(a&&!x) r=(U)O[b(12)&a>>48]; /* deref */
    if((!a)&&x) R[b(12)&a>>48]++;    /* ref + */
    break;
  case 1: r=plus(a,x); break;
  case 15:
    if((!a)&x) {
      j=b(12&a>>48);
      if(R[j])R[j]--;
      else { free(O[j]); F[++fi]=j; }
    }
  }
  return r;
}

U tn(int t, int n) {
  U r=0;
  void *v=0;
  int j;
  if(t==3) v=malloc(sizeof(int)*n);
  else if(t==4) v=malloc(sizeof(float)*n);
  if(v) {
    if(fi>-1) j=fi--;
    else j=oi++;
    O[j]=v;
    r=t(11,n);
    r|=(U)j<<48;
  }
  return r;
}
