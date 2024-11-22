#include "v.h"

U plus(U a, U x) {
  U r=0;
  float f;
  int *pri,*pai,*pxi;
  float *prf,*paf,*pxf;
  int at=a>>60,xt=x>>60;
  switch(at) {
  case 3:
    switch(xt) {
    case 3: r=t(3,(uint)((int)a+(int)x)); break;
    case 4: f=FI((int)a)+fu(x); r=t(4,*(uint*)&f); break;
    case 0xb:
      r=tn(3,nx);
      pri=(int*)k(0,r,0);
      pxi=(int*)k(0,x,0);
      i(nx,*pri++=(int)a+*pxi++)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxf=(float*)k(0,x,0);
      i(nx,*prf++=FI((int)a)+*pxf++)
      break;
    } break;
  case 4:
    switch(xt) {
    case 3: r=plus(x,a); break;
    case 4: f=fu(a)+fu(x); r=t(4,*(uint*)&f); break;
    case 0xb:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxi=(int*)k(0,x,0);
      i(nx,*prf++=fu(a)+FI(*pxi);++pxi)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxf=(float*)k(0,x,0);
      i(nx,*prf++=fu(a)+*pxf++)
      break;
    } break;
  case 0xb:
    switch(xt) {
    case 3: r=plus(x,a); break;
    case 4: r=plus(x,a); break;
    case 0xb:
      r=tn(3,nx);
      pri=(int*)k(0,r,0);
      pai=(int*)k(0,a,0);
      pxi=(int*)k(0,x,0);
      i(nx,*pri++=*pai++ + *pxi++)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,a,0);
      pxf=(float*)k(0,x,0);
      i(nx,*prf++=FI(*pai)+*pxf++;++pai)
      break;
    } break;
  case 0xc:
    switch(xt) {
    case 3: r=plus(x,a); break;
    case 4: r=plus(x,a); break;
    case 0xb: r=plus(x,a); break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      pxf=(float*)k(0,x,0);
      i(nx,*prf++=*paf++ + *pxf++)
      break;
    } break;
  }
  return r;
}
