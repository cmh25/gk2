#ifndef K_H
#define K_H

#include <limits.h>
#include <math.h>

/*
# U value k-core
 1      3     12     16    32 bits
ax     tx     ox     mx    nx
63 62..60 59..48 47..32 31..0
*/
#define b(i) (((U)1<<(i))-1)
#define ax !(x>>63)
#define tx (x>>60)
#define ox (b(12)&x>>48)
#define mx (b(16)&x>>32)
#define nx (int)x
#define aa !(a>>63)
#define ta (a>>60)
#define oa (b(12)&a>>48)
#define ma (b(16)&a>>32)
#define na (int)a
#define _(z) ({z;})
#define x(b,z) _(typeof(b)x=b;z)
#define i(b,z) {int n=b;int i=0;while(i<n){z;++i;}}
#define j(b,z) {int n=b;int j=0;while(j<n){z;++j;}}
#define t(t,z) ((U)(t)<<60|(z))
#define fu(x) (*(float*)&x)

#define fi(x) \
  ((x)==INT_MAX ? INFINITY \
: (((x)==INT_MIN ? NAN \
: (((x)==INT_MIN+1) ? -INFINITY \
: (float)(x)))))

#define PRC prc=(char*)k_(2,r)
#define PAC pac=(char*)k_(2,a)
#define PXC pxc=(char*)k_(2,x)
#define PRI pri=(int*)k_(2,r)
#define PAI pai=(int*)k_(2,a)
#define PXI pxi=(int*)k_(2,x)
#define PRF prf=(float*)k_(2,r)
#define PAF paf=(float*)k_(2,a)
#define PXF pxf=(float*)k_(2,x)
#define PRS prs=(char**)k_(2,r)
#define PAS pas=(char**)k_(2,a)
#define PXS pxs=(char**)k_(2,x)
#define PRU pru=(U*)k_(2,r)
#define PAU pau=(U*)k_(2,a)
#define PXU pxu=(U*)k_(2,x)

#ifdef _WIN32
  typedef unsigned long long U;
#else
  typedef unsigned long U;
#endif
typedef unsigned int uint;
U k_(int i, U x);
U k(int i, U a, U x);
U tn(int t, int n);
int kcmpr(U a, U x);
U kcp(U x);

#endif /* K_H */
