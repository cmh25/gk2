#ifndef K_H
#define K_H

#include <limits.h>

#ifdef _WIN32
  typedef unsigned long long U;
#else
  typedef unsigned long U;
#endif
extern U k_(int,U);
extern U k(int,U,U);
extern U tn(int,int);
#define b(i) (((U)1<<(i))-1)
#define ax !(x>>63)
#define tx (x>>60)
#define mx (b(16)&x>>32)
#define nx (int)x
#define i(b,z) {int n=b;int i=0;while(i<n){z;++i;}}
#define j(b,z) {int n=b;int j=0;while(j<n){z;++j;}}
#define t(t,z) ((U)(t)<<60|(z))
#define fu(x) (*(float*)&x)

#define FI(a) \
  ((a)==INT_MAX ? INFINITY \
: (((a)==INT_MIN ? NAN \
: (((a)==INT_MIN+1) ? -INFINITY \
: (float)(a)))))

void* px(U x);
void kfree(U x);
U kref(U x);
void kinit(void);
void kprint(U x, char *s, char *e);
U kerror(char *e);
U knorm(U x);

#endif /* K_H */
