#include "zv.h"
#include <stdio.h>
#include <stdlib.h>
#include "fn.h"
#include "p.h"
#include "x.h"

static U zva[1024];
static int zvr[1024];
static int zvi,zvm=1024;

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
  fn *f; pr *p; plist *q; U a=x;
  if(zvr[svi(x)]) { zvr[svi(x)]--; return; }
  x=zvget(x);
  if(0xc==zx(x)) { f=(fn*)(b(56)&x); fnfree(f); }
  else if(0xa==zx(x)) { p=(pr*)(b(56)&x); prfree(p); }
  else if(0xb==zx(x)) { p=(pr*)(b(56)&x); prfree(p); }
  else if(0x9==zx(x)) { q=(plist*)(b(56)&x); kfree(q->x); xfree(q); }
  zva[svi(a)]=0;
}

int zvplist(U x) {
  return zv(x)&&zx(zva[svi(x)])==0x9;
}
