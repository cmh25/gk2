#ifndef K_H
#define K_H

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

/*
# U value k-core
 1      3     12     16    32 bits
ax     tx     ox     mx    nx
63 62..60 59..48 47..32 31..0
*/
typedef unsigned long U;
U k(int i, U a, U x);
U tn(int t, int n);

#endif /* K_H */
