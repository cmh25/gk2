#include "zv.h"
#include <stdio.h>
#include <stdlib.h>
static U zva[1024];
static int zvi,zvm=1024;
static int svi(U x) { return mx-1; }
int zv(U x) { return tx==0&&mx!=0; }
U zvset(U v,int t) {
  int zi;
  U zval=(U)v|(U)t<<60;
  for(zi=0;zi<zvi;++zi)if(zva[zi]==zval)break;
  if(zi==zvi)zi=++zvi;
  if(zvi==zvm) { fprintf(stderr,"error: zvm\n"); exit(1); }
  zva[zi++]=zval;
  return (U)zi<<32;
}
U zvget(U z) {
  return zva[svi(z)];
}
