#ifndef PN_H
#define PN_H
#include "k.h"
typedef struct pn {
  int t;         /* type */
  U v;           /* value verb */
  U n;           /* value noun */
  struct pn **a; /* children */
  int m;         /* children count */
  int f;         /* free? */
} pn;
pn* pnnew(int t, U v, U n, int m);
void pnfree(pn *n);
pn* pnappend(pn *n0, pn *n1);
#endif /* PN_H */
