#include "zv.h"
#include <stdio.h>
#include <stdlib.h>
#include "fn.h"
#include "p.h"
#include "x.h"

static U zva[1024];
static int zvr[1024];
static int zvi,zvm=1024;

static int svi(U x) { return mx-1; }

int zv(U x) { return tx==0&&mx!=0; }

U zvset(U x,int t) {
  int zi;
  U zval=(U)x|(U)t<<56;
  for(zi=0;zi<zvi;++zi)if(!zva[zi])break;
  if(zi==zvi)zi=++zvi;
  if(zvi==zvm) { fprintf(stderr,"error: zvm\n"); exit(1); }
  zva[zi++]=zval;
  return (U)zi<<32;
}

U zvget(U x) {
  return zva[svi(x)];
}

U zvref(U x) {
  zvr[svi(x)]++;
  return x;
}

void zvfree(U x) {
  fn *f;
  pr *p;
  plist *q;
  U a=x;
  if(zvr[svi(x)]) { zvr[svi(x)]--; return; }
  x=zvget(x);
  if(0xc==x>>56) { f=(fn*)(((U)0xc<<56)^x); fnfree(f); }
  else if(0xa==x>>56) { p=(pr*)(((U)0xa<<56)^x); prfree(p); }
  else if(0xb==x>>56) { p=(pr*)(((U)0xb<<56)^x); prfree(p); }
  else if(0x9==x>>56) { q=(plist*)(((U)0x9<<56)^x); kfree(q->x); xfree(q); }
  zva[svi(a)]=0;
}

int zvplist(U x) {
  if(!zv(x)) return 0;
  if(zva[svi(x)]>>56==0x9) return 1;
  return 0;
}
