#ifndef ZV_H
#define ZV_H

#include "k.h"

/*
# U value k-core
 1      3     12     16    32 bits
ax     tx     ox     mx    nx
63 62..60 59..48 47..32 31..0

z values are repl-level (non-kcore) objects. indicated when ax tx = 0 0 and mx != 0.
in this case, mx-1 is an index into the zv array of pointers. zv includes:
- variable
- lambda
- elided arg
- kerror (from core or signal)
*/

int svx(U x);
int svi(U x);
extern U zv[1024];
extern int zvi,zvm;

#endif /* ZV_H */
