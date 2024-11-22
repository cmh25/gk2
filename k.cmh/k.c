#include "k.h"
#include <stdlib.h>

static void *O[512];
static int R[512];
static int oi,om=512;

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
  case 15:
    if((!a)&x) {
      j=b(12&a>>48);
      if(R[j])R[j]--;
      else free(O[j]);
    }
  }
  return r;
}

U tn(int t, int n) {
  U r=0;
  void *v=0;
  if(t==3) v=malloc(sizeof(int)*n);
  if(v) {
    O[oi]=v;
    r=t(11,n);
    r|=(U)oi<<48;
    ++oi;
  }
  return r;
}
