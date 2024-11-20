#ifndef K_H
#define K_H

#include <limits.h>

typedef unsigned long U;
extern U k(int,U,U);
extern U tn(int,int);
#define b(i) ((1L<<(i))-1)
#define ax !(x>>63)
#define tx (7&x>>60)
#define mx (b(16)&x>>32)
#define nx (int)x
#define _(z) ({z;})
#define W(z) while(_(z))
#define i(b,z) {int $=b;int i=0;W(i<$){z;++i;}}
#define j(b,z) {int $=b;int j=0;W(j<$){z;++j;}}
#define t(t,z) ((U)(t)<<60|(z))

#define I2F(a) \
  ((a)==INT_MAX ? INFINITY \
: (((a)==INT_MIN ? NAN \
: (((a)==INT_MIN+1) ? -INFINITY \
: (float)(a)))))

void* px(U x);
void kfree(U x);
U kref(U x);
void kinit();
void kprint(U x);

#endif /* K_H */
