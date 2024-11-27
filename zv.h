#ifndef ZV_H
#define ZV_H

#include "k.h"

/*
# U value k-core
 1      3     12     16    32 bits
ax     tx     ox     mx    nx
63 62..60 59..48 47..32 31..0

z values are repl-level (non-kcore) objects. indicated when ax tx = 0 0 and mx != 0.
in this case, mx-1 is an index into the zv array of pointers. each zv pointer is
tagged with one of these types in the high 4 bits.
- f: variable
- e: kerror (from core or signal)
- d: elided arg
- c: lambda
*/

int zv(U x);
U zvset(U v,int t);
U zvget(U z);

#endif /* ZV_H */
