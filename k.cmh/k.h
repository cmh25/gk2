#ifndef K_H
#define K_H

#include <limits.h>
#include <math.h>

#define b(i) ((1L<<(i))-1)
#define ax !(x>>63)
#define tx (7&x>>60)
#define mx (b(16)&x>>32)
#define nx (int)x
#define _(z) ({z;})
#define x(b,z) _(typeof(b)x=b;z)
#define W(z) while(_(z))
#define i(b,z) {int $=b;int i=0;W(i<$){z;++i;}}
#define j(b,z) {int $=b;int j=0;W(j<$){z;++j;}}
#define t(t,z) ((U)(t)<<60|(z))
#define fu(x) (*(float*)&x)

#define FI(a) \
  ((a)==INT_MAX ? INFINITY \
: (((a)==INT_MIN ? NAN \
: (((a)==INT_MIN+1) ? -INFINITY \
: (float)(a)))))

/*
# U value k-core
 1      3     12     16    32 bits
ax     tx     ox     mx    nx
63 62..60 59..48 47..32 31..0
*/
typedef unsigned long U;
typedef unsigned int uint;
U k(int i, U a, U x);
U tn(int t, int n);

#endif /* K_H */
