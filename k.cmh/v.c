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
    case 3: f=fu(a) O fi((int)x); r=t(4,*(uint*)&f); break; \
    case 4: f=fu(a) O fu(x); r=t(4,*(uint*)&f); break; \
    case 0xb: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      f=fu(a); \
      i(nx,*prf++=f O fi(*pxi);++pxi) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      f=fu(a); \
      i(nx,*prf++=f O *pxf++) \
      break; \
    } break; \
  case 0xb: \
    switch(xt) { \
    case 3: \
      r=tn(3,na); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      i(na,*pri++=*pai++ O (int)x) \
      break; \
    case 4: \
      r=tn(4,na); \
      prf=(float*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      f=fu(x); \
      i(na,*prf++=fi(*pai) O f;++pai) \
      break; \
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
    case 3: \
      r=tn(4,na); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      f=fi((int)x); \
      i(na,*prf++=*paf++ O f) \
      break; \
    case 4: \
      r=tn(4,na); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      f=fu(x); \
      i(na,*prf++=*paf++ O f) \
      break; \
    case 0xb: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*prf++=*paf++ O fi(*pxi);++pxi) \
      break; \
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
      r=tn(4,na);
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,a,0);
      f=fi((int)x);
      i(na,*prf++=fi(*pai) / f;++pai)
      break;
    case 4:
      r=tn(4,na);
      prf=(float*)k(0,r,0);
      pai=(int*)k(0,a,0);
      f=fu(x);
      i(na,*prf++=fi(*pai) / f;++pai)
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
      r=tn(4,na);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      f=fi((int)x);
      i(na,*prf++=*paf++ / f)
      break;
    case 4:
      r=tn(4,na);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      f=fu(x);
      i(na,*prf++=*paf++ / f)
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

#define MAMO(F,O) \
U F(U a,U x) { \
  U r; \
  int *pri,*pai,*pxi; \
  float *prf,*paf,*pxf; \
  int at=a>>60,xt=x>>60; \
  float f; \
  switch(at) { \
  case 3: \
    switch(xt) { \
    case 3: r=(int)a O (int)x?a:x; break; \
    case 4: f=fi((int)a); f=f O fu(x)?f:fu(x); r=t(4,*(uint*)&f); break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=(int)a O *pxi?a:*pxi;++pxi) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      f=fi((int)a); \
      i(nx,*prf++=f O *pxf?f:*pxf;++pxf) \
      break; \
    } break; \
  case 4: \
    switch(xt) { \
    case 3: f=fi((int)x); f=f O fu(a)?f:fu(a); r=t(4,*(uint*)&f); break; \
    case 4: r=fu(a) O fu(x)?a:x; break; \
    case 0xb: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      f=fu(a); \
      i(nx,*prf++=f O fi(*pxi)?f:fi(*pxi);++pxi) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      f=fu(a); \
      i(nx,*prf++=f O *pxf?f:*pxf;++pxf) \
      break; \
    } break; \
  case 0xb: \
    switch(xt) { \
    case 3: \
      r=tn(3,na); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      i(na,*pri++=*pai O (int)x?*pai:x;++pai) \
      break; \
    case 4: \
      r=tn(4,na); \
      prf=(float*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      f=fu(x); \
      i(na,*prf++=fi(*pai) O f?fi(*pai):f;++pai) \
      break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=*pai O *pxi?*pai:*pxi;++pai;++pxi) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*prf++=fi(*pai) O *pxf?fi(*pai):*pxf;++pai;++pxf) \
      break; \
    } break; \
  case 0xc: \
    switch(xt) { \
    case 3: \
      r=tn(4,na); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      f=fi((int)x); \
      i(na,*prf++=*paf O f?*paf:f;++paf) \
      break; \
    case 4: \
      r=tn(4,na); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      f=fu(x); \
      i(na,*prf++=*paf O f?*paf:f;++paf) \
      break; \
    case 0xb: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*prf++=*paf O fi(*pxi)?*paf:fi(*pxi);++paf;++pxi) \
      break; \
    case 0xc: \
      r=tn(4,nx); \
      prf=(float*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*prf++=*paf O *pxf?*paf:*pxf;++paf;++pxf) \
      break; \
    } break; \
  } \
  return r; \
}
MAMO(minand,<)
MAMO(maxor,>)

#define LME(F,O) \
U F(U a,U x) { \
  U r=0; \
  int *pri,*pai,*pxi; \
  float *prf,*paf,*pxf; \
  int at=a>>60,xt=x>>60; \
  float f; \
  switch(at) { \
  case 3: \
    switch(xt) { \
    case 3: r=t(3,(int)a O (int)x); break; \
    case 4: r=t(3,(int)a O fu(x)); break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=(int)a O *pxi++) \
      break; \
    case 0xc: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      f=fi((int)a); \
      i(nx,*pri++=f O *pxf++) \
      break; \
    } break; \
  case 4: \
    switch(xt) { \
    case 3: r=t(3,fu(a) O (int)x); break; \
    case 4: r=t(3,fu(a) O fu(x)); break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pxi=(int*)k(0,x,0); \
      f=fu(a); \
      i(nx,*pri++=f O fi(*pxi);++pxi) \
      break; \
    case 0xc: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pxf=(float*)k(0,x,0); \
      f=fu(a); \
      i(nx,*pri++=f O *pxf++) \
      break; \
    } break; \
  case 0xb: \
    switch(xt) { \
    case 3: \
      r=tn(3,na); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      i(na,*pri++=*pai++ O (int)x) \
      break; \
    case 4: \
      r=tn(3,na); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      f=fu(x); \
      i(na,*pri++=fi(*pai) O f;++pai) \
      break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=*pai++ O *pxi++) \
      break; \
    case 0xc: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      pai=(int*)k(0,a,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*pri++=fi(*pai) O *pxf++;++pai) \
      break; \
    } break; \
  case 0xc: \
    switch(xt) { \
    case 3: \
      r=tn(3,na); \
      pri=(int*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      f=fi((int)x); \
      i(na,*pri++=*paf++ O f) \
      break; \
    case 4: \
      r=tn(3,na); \
      pri=(int*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      f=fu(x); \
      i(na,*pri++=*paf++ O f) \
      break; \
    case 0xb: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      pxi=(int*)k(0,x,0); \
      i(nx,*pri++=*paf++ O fi(*pxi);++pxi) \
      break; \
    case 0xc: \
      r=tn(3,nx); \
      pri=(int*)k(0,r,0); \
      paf=(float*)k(0,a,0); \
      pxf=(float*)k(0,x,0); \
      i(nx,*pri++=*paf++ O *pxf++) \
      break; \
    } break; \
  } \
  return r; \
}
LME(less,<)
LME(more,>)
LME(equal,==)

U match(U a,U x) {
  return t(3,!kcmpr(a,x));
}