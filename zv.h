#ifndef ZV_H
#define ZV_H

#include "k.h"

/*
ax|tx
----------
0     8 kv
1     9
2 c   a cv
3 i   b iv
4 f   c fv
5     d
6     e
7 s   f sv

# U value k-core
 1      3     12     16    32 bits
ax     tx     ox     mx    nx
63 62..60 59..48 47..32 31..0

z values are repl-level (non-kcore) objects. indicated when ax tx = 0 0 and mx != 0.
in this case, mx-1 is an index into the zv array of pointers. each zv pointer is
tagged with one of these types in the high 8 bits.
(no conflict with core types since ox bits will never be set for atoms)
- 0f: variable
- 0e: kerror
- 0d: elided arg
- 0c: lambda
- 0b: plist
- 0a: klist

# z value
     8      8    48 bits
    tz      0    pz
63..56 55..48 47..0
*/

#define zv(x) ((b(16)&x>>32)&&!(x>>60))
#define svi(x) ((b(16)&x>>32)-1)
#define zx(x) (x>>56)

typedef struct plist { U x; int n; } plist;

U zvset(U x,int t);
U zvget(U x);
U zvref(U x);
void zvfree(U x);
int zvplist(U x);

#endif /* ZV_H */
