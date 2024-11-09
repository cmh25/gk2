#ifndef K_H
#define K_H

#include "k/k.h"
#include <limits.h>

U k(i2,i3,i3);
U K(i2,i3);

#define I2F(a) \
  ((a)==INT_MAX ? INFINITY \
: (((a)==INT_MIN ? NAN \
: (((a)==INT_MIN+1) ? -INFINITY \
: (float)(a)))))

void kprint(U x);
void kfree(U x);
U kref(U x);

#endif /* K_H */
