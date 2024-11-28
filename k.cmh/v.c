#include "v.h"
#include <stdlib.h>

#define PMT(F,O) \
U F(U a,U x) { \
  U r=0; \
  float f; \
  int *pri,*pai,*pxi; \
  float *prf,*paf,*pxf; \
  if(!(aa||ax)&&na!=nx) return 2; \
  switch(ta) { \
  case 3: \
    switch(tx) { \
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
    switch(tx) { \
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
    switch(tx) { \
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
    switch(tx) { \
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
  int *pai,*pxi;
  float *prf,*paf,*pxf;
  if(!(aa||ax)&&na!=nx) return 2;
  switch(ta) {
  case 3:
    switch(tx) {
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
    switch(tx) {
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
    switch(tx) {
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
    switch(tx) {
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

#define MAMO(F,O) \
U F(U a,U x) { \
  U r; \
  int *pri,*pai,*pxi; \
  float *prf,*paf,*pxf; \
  float f; \
  if(!(aa||ax)&&na!=nx) return 2; \
  switch(ta) { \
  case 3: \
    switch(tx) { \
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
    switch(tx) { \
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
    switch(tx) { \
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
    switch(tx) { \
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
  float *paf,*pxf; \
  float f; \
  if(!(aa||ax)&&na!=nx) return 2; \
  switch(ta) { \
  case 3: \
    switch(tx) { \
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
    switch(tx) { \
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
    switch(tx) { \
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
    switch(tx) { \
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
  (void)a; (void)x;
  return t(3,!kcmpr(a,x));
}

U dot(U a,U x) {
  (void)a; (void)x;
  return 0;
}

U mod(U a,U x) {
  (void)a; (void)x;
  return 0;
}

U at(U a,U x) {
  (void)a; (void)x;
  return 0;
}

U find(U a,U x) {
  (void)a; (void)x;
  return 0;
}

U take(U a,U x) {
  U r=0;
  int *pri,*pxi;
  float *prf,*pxf;
  int c,d;
  switch(ta) {
  case 3:
    c=(int)a<0?-a:a;
    switch(tx) {
    case 3:
      r=tn(3,c);
      pri=(int*)k(0,r,0);
      i(c,*pri++=(int)x)
      break;
    case 4:
      r=tn(4,c);
      prf=(float*)k(0,r,0);
      i(c,*prf++=fu(x))
      break;
    case 0xb:
      r=tn(3,c);
      pri=(int*)k(0,r,0);
      pxi=(int*)k(0,x,0);
      if((int)a<0) { d=c%nx; i(c,*pri++=pxi[(nx-d+i)%nx]) }
      else i(c,*pri++=pxi[i%nx])
      break;
    case 0xc:
      r=tn(4,c);
      prf=(float*)k(0,r,0);
      pxf=(float*)k(0,x,0);
      if((int)a<0) { d=c%nx; i(c,*prf++=pxf[(nx-d+i)%nx]) }
      else i(c,*prf++=pxf[i%nx])
      break;
    } break;
  }
  return r;
}

U drop(U a,U x) {
  U r=0;
  int *pri,*pxi;
  float *prf,*pxf;
  switch(ta) {
  case 3:
    switch(tx) {
    case 3: r=x; break;
    case 4: r=x; break;
    case 0xb:
      if(abs((int)a)>=nx) r=tn(3,0);
      else if((int)a>0) {
        r=tn(3,nx-(int)a);
        pri=(int*)k(0,r,0);
        pxi=(int*)k(0,x,0);
        i(nx-(int)a,*pri++=pxi[i+(int)a])
      }
      else if((int)a<0) {
        r=tn(3,nx+(int)a);
        pri=(int*)k(0,r,0);
        pxi=(int*)k(0,x,0);
        i(nx+(int)a,*pri++=*pxi++)
      }
      else r=kcp(x);
      break;
    case 0xc:
      if(abs((int)a)>=nx) r=tn(4,0);
      else if((int)a>0) {
        r=tn(4,nx-(int)a);
        prf=(float*)k(0,r,0);
        pxf=(float*)k(0,x,0);
        i(nx-(int)a,*prf++=pxf[i+(int)a])
      }
      else if((int)a<0) {
        r=tn(4,nx+(int)a);
        prf=(float*)k(0,r,0);
        pxf=(float*)k(0,x,0);
        i(nx+(int)a,*prf++=*pxf++)
      }
      else r=kcp(x);
      break;
    } break;
  default: r=3;
  }
  return r;
}

U cut(U a,U x) {
  (void)a; (void)x;
  return 0;
}

U join(U a,U x) {
  U r=0;
  int *pri,*pai,*pxi;
  float *prf,*paf,*pxf;
  switch(ta) {
  case 3:
    switch(tx) {
    case 3:
      r=tn(3,2);
      pri=(int*)k(0,r,0);
      pri[0]=(int)a;
      pri[1]=(int)x;
      break;
    case 0xb:
      r=tn(3,1+nx);
      pri=(int*)k(0,r,0);
      pxi=(int*)k(0,x,0);
      *pri++=(int)a;
      i(nx,*pri++=*pxi++)
      break;
    } break;
  case 4:
    switch(tx) {
    case 4:
      r=tn(4,2);
      prf=(float*)k(0,r,0);
      prf[0]=fu(a);
      prf[1]=fu(x);
      break;
    case 0xc:
      r=tn(4,1+nx);
      prf=(float*)k(0,r,0);
      pxf=(float*)k(0,x,0);
      *prf++=fu(a);
      i(nx,*prf++=*pxf++)
      break;
    } break;
  case 0xb:
    switch(tx) {
    case 3:
      r=tn(3,1+na);
      pri=(int*)k(0,r,0);
      pai=(int*)k(0,a,0);
      i(na,*pri++=*pai++)
      *pri=(int)x;
      break;
    case 0xb:
      r=tn(3,na+nx);
      pri=(int*)k(0,r,0);
      pai=(int*)k(0,a,0);
      pxi=(int*)k(0,x,0);
      i(na,*pri++=*pai++)
      i(nx,*pri++=*pxi++)
    } break;
  case 0xc:
    switch(tx) {
    case 4:
      r=tn(4,1+na);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      i(na,*prf++=*paf++)
      *prf=fu(x);
      break;
    case 0xc:
      r=tn(4,na+nx);
      prf=(float*)k(0,r,0);
      paf=(float*)k(0,a,0);
      pxf=(float*)k(0,x,0);
      i(na,*prf++=*paf++)
      i(nx,*prf++=*pxf++)
    } break;
  }
  return r;
}

U parse(U a,U x) {
  (void)a; (void)x;
  return 0;
}

U pos(U x) {
  (void)x;
  return 0;
}

U negate(U x) {
  U r;
  int *pri,*pxi;
  float *prf,*pxf;
  float f;
  switch(tx) {
  case 3: r=t(3,(uint)(-(int)x)); break;
  case 4: f=-fu(x); r=t(4,*(uint*)&f); break;
  case 0xb:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    pxi=(int*)k(0,x,0);
    i(nx,*pri++=-*pxi++)
    break;
  case 0xc:
    r=tn(4,nx);
    prf=(float*)k(0,r,0);
    pxf=(float*)k(0,x,0);
    i(nx,*prf++=-*pxf++)
    break;
  }
  return r;
}

U square(U x) {
  U r;
  int *pri,*pxi;
  float *prf,*pxf;
  float f;
  switch(tx) {
  case 3: r=t(3,(uint)((int)x*(int)x)); break;
  case 4: f=-fu(x); f*=f; r=t(4,*(uint*)&f); break;
  case 0xb:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    pxi=(int*)k(0,x,0);
    i(nx,*pri++=*pxi**pxi;++pxi)
    break;
  case 0xc:
    r=tn(4,nx);
    prf=(float*)k(0,r,0);
    pxf=(float*)k(0,x,0);
    i(nx,*prf++=*pxf**pxf;++pxf)
    break;
  }
  return r;
}

U sqrt_(U x) {
  U r=0;
  int *pxi;
  float *prf,*pxf;
  float f;
  switch(tx) {
  case 3: f=sqrtf(fi((int)x)); r=t(4,*(uint*)&f); break;
  case 4: f=sqrtf(fu(x)); r=t(4,*(uint*)&f); break;
  case 0xb:
    r=tn(4,nx);
    prf=(float*)k(0,r,0);
    pxi=(int*)k(0,x,0);
    i(nx,*prf++=sqrtf(fi(*pxi));++pxi)
    break;
  case 0xc:
    r=tn(4,nx);
    prf=(float*)k(0,r,0);
    pxf=(float*)k(0,x,0);
    i(nx,*prf++=sqrtf(*pxf++))
    break;
  }
  return r;
}

U flip(U x) {
  (void)x;
  return 0;
}

U reverse(U x) {
  U r=0;
  int *pri,*pxi;
  float *prf,*pxf;
  switch(tx) {
  case 3: r=x; break;
  case 4: r=x; break;
  case 0xb:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    pxi=(int*)k(0,x,0);
    i(nx,*pri++=pxi[nx-i-1])
    break;
  case 0xc:
    r=tn(4,nx);
    prf=(float*)k(0,r,0);
    pxf=(float*)k(0,x,0);
    i(nx,*prf++=pxf[nx-i-1])
    break;
  }
  return r;
}

U asc(U x) {
  (void)x;
  return 0;
}

U desc(U x) {
  (void)x;
  return 0;
}

U group(U x) {
  (void)x;
  return 0;
}

U not_(U x) {
  (void)x;
  return 0;
}

U value(U x) {
  (void)x;
  return 0;
}

U bang(U x) {
  U r;
  int *pri;
  switch(tx) {
  case 3:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    i(nx,*pri++=i)
    break;
  default: r=3;
  }
  return r;
}

U first(U x) {
  (void)x;
  return 0;
}

U unique(U x) {
  (void)x;
  return 0;
}

U floor_(U x) {
  U r=0;
  int *pri;
  float *pxf;
  switch(tx) {
  case 3: r=x; break;
  case 4: r=t(3,(uint)floor(fu(x))); break;
  case 0xb: r=kcp(x); break;
  case 0xc:
    r=tn(3,nx);
    pri=(int*)k(0,r,0);
    pxf=(float*)k(0,x,0);
    i(nx,*pri++=floor(fu(*pxf));++pxf)
    break;
  default: r=3;
  }
  return r;
}

U order(U x) {
  (void)x;
  return 0;
}

U enlist(U x) {
  U r=0;
  int *pri;
  float *prf;
  switch(tx) {
  case 3:
    r=tn(3,1);
    pri=(int*)k(0,r,0);
    *pri=(int)x;
    break;
  case 4:
    r=tn(4,1);
    prf=(float*)k(0,r,0);
    *prf=fu(x);
    break;
  }
  return r;
}

U str(U x) {
  (void)x;
  return 0;
}
