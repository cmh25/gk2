#include "zv.h"
#include <stdio.h>
#include <stdlib.h>
U zv[1024];
int zvi,zvm=1024;
int svx(U x) { return tx==0&&mx!=0; }
int svi(U x) { return mx-1; }
U zvadd(U v,int t) {
  int zi;
  U zval=(U)v|(U)t<<60;
  for(zi=0;zi<zvi;++zi)if(zv[zi]==zval)break;
  if(zi==zvi)zi=++zvi;
  if(zvi==zvm) { fprintf(stderr,"error: zvm\n"); exit(1); }
  zv[zi++]=zval;
  return (U)zi<<32;
}
