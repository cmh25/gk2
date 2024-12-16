#include "pn.h"
#include "x.h"
pn* pnnew(int t, U v, U n, int m) {
  pn *r=xmalloc(sizeof(pn));
  r->t=t;
  r->v=v;
  r->n=n;
  r->m=m;
  r->f=0;
  r->a=m?xcalloc(m,sizeof(pn*)):0;
  return r;
}
void pnfree(pn *n) {
  if(n->m) xfree(n->a);
  xfree(n);
}
pn* pnappend(pn *n0, pn *n1) {
  n0->a=xrealloc(n0->a,sizeof(pn*)*(1+n0->m));
  n0->a[n1->m++]=(struct pn*)n1;
  return n0;
}
