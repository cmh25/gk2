#include "v.h"

#define PMT(F,O) \
U F(U a,U x) { \
  U r=0; \
  float f; \
  int *pri,*pai,*pxi; \
  float *prf,*paf,*pxf; \
  int at=a>>60,xt=x>>60; \
  switch(at) { \
  case 3: \
    switch(xt) { \
    case 3: r=t(3,(uint)((int)a O (int)x)); break; \
    case 4: f=fi((int)a) O fu(x); r=t(4,*(uint*)&f); break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=(int)a O *pxi++) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*prf++=fi((int)a) O *pxf++) \
      break; \
    } break; \
  case 4: \
    switch(xt) { \
    case 3: r=F(x,a); break; \
    case 4: f=fu(a) O fu(x); r=t(4,*(uint*)&f); break; \
    case 0xb: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*prf++=fu(a) O fi(*pxi);++pxi) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*prf++=fu(a) O *pxf++) \
      break; \
    } break; \
  case 0xb: \
    switch(xt) { \
    case 3: r=F(x,a); break; \
    case 4: r=F(x,a); break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=*pai++ O *pxi++) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*prf++=fi(*pai) O *pxf++;++pai) \
      break; \
    } break; \
  case 0xc: \
    switch(xt) { \
    case 3: r=F(x,a); break; \
    case 4: r=F(x,a); break; \
    case 0xb: r=F(x,a); break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*prf++=*paf++ O *pxf++) \
      break; \
    } break; \
  } \
  return r; \
}
PMT(plus,+)
PMT(minus,-)
PMT(times,*)

U divide(U a,U x) {
  U r=0;
  float f;
  int *pri,*pai,*pxi;
  float *prf,*paf,*pxf;
  int at=a>>60,xt=x>>60;
  switch(at) {
  case 3:
    switch(xt) {
    case 3: f=fi((int)a) / fi((int)x); r=t(4,*(uint*)&f); break;
    case 4: f=fi((int)a) / fu(x); r=t(4,*(uint*)&f); break;
    case 0xb:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxi=(int*)k(0,x,0);
      f=fi((int)a);
      i(nx,*prf++=f / fi(*pxi);++pxi)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxf=(float*)k(0,x,0);
      f=fi((int)a);
      i(nx,*prf++=f / *pxf++)
      break;
    } break;
  case 4:
    switch(xt) {
    case 3: f=fu(a) / fi((int)x); r=t(4,*(uint*)&f); break;
    case 4: f=fu(a) / fu(x); r=t(4,*(uint*)&f); break;
    case 0xb:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxi=(int*)k(0,x,0);
      f=fu(a);
      i(nx,*prf++=f / fi(*pxi);++pxi)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pxf=(float*)k(0,x,0);
      f=fu(a);
      i(nx,*prf++=f / *pxf++)
      break;
    } break;
  case 0xb:
    switch(xt) {
    case 3:
      r=tn(4,x(a,nx));
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,x,0);
      f=fi((int)x);
      i(x(a,nx),*prf++=fi(*pai) / f;++pai)
      break;
    case 4:
      r=tn(4,x(a,nx));
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,x,0);
      f=fu(x);
      i(x(a,nx),*prf++=fi(*pai) / f;++pai)
      break;
    case 0xb:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,a,0);
      pxi=(int*)k(0,x,0);
      i(nx,*prf++=fi(*pai) / fi(*pxi);++pai;++pxi)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,a,0);
      pxf=(float*)k(0,x,0);
      i(nx,*prf++=fi(*pai) / *pxf++;++pai)
      break;
    } break;
  case 0xc:
    switch(xt) {
    case 3:
      r=tn(4,x(a,nx));
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,x,0);
      f=fi((int)x);
      i(x(a,nx),*prf++=*paf++ / f)
      break;
    case 4:
      r=tn(4,x(a,nx));
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,x,0);
      f=fu(x);
      i(x(a,nx),*prf++=*paf++ / f)
      break;
    case 0xb:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      pxi=(int*)k(0,x,0);
      i(nx,*prf++=*paf++ / fi(*pxi);++pxi)
      break;
    case 0xc:
      r=tn(4,nx);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      pxf=(float*)k(0,x,0);
      i(nx,*prf++=*paf++ / *pxf++)
      break;
    } break;
  }
  return r;
}

U bang(U x) {
  U r;
  int xt=x>>60;
  int *pri;
  switch(xt) {
  case 3:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    i(nx,*pri++=i)
    break;
  }
  return r;
}

U negate(U x) {
  U r;
  int xt=x>>60;
  float f;
  switch(xt) {
  case 3: r=t(3,(uint)(-(int)x)); break;
  case 4: f=-fu(x); r=t(4,*(uint*)&f); break;
  }
  return r;
}

U square(U x) {
  U r;
  int xt=x>>60;
  float f;
  switch(xt) {
  case 3: r=t(3,(uint)((int)x*(int)x)); break;
  case 4: f=-fu(x); f*=f; r=t(4,*(uint*)&f); break;
  }
  return r;
}
