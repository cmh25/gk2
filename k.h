#ifndef K_H
#define K_H

#include "k/_.h"
#include <limits.h>

extern V _V[];extern U _j[];extern i0 _J[];extern U k(i2,U),K(i2,U,U);

#define tx (7&x>>60)
#define nx (i2)x
#define jx (15&x>>56)
#define kx (63&x>>50)
#define rx _J[1023&x>>50]
#define sx (i0*)(_V+(1+kx<<jx))
#define ax (8>x>>60)
#define N(z) i(nx,U*b=sx;x(b[i],z))

#define I2F(a) \
  ((a)==INT_MAX ? INFINITY \
: (((a)==INT_MIN ? NAN \
: (((a)==INT_MIN+1) ? -INFINITY \
: (float)(a)))))

void kprint(U x);
void kfree(U x);

#endif /* K_H */
