#include "dict.h"
#include <stdio.h>
#include <string.h>
#include "k.h"
#include "x.h"
#include "sym.h"

dict* dnew(void) {
  return xcalloc(1,sizeof(dict));
}

void dfree(dict *d) {
  if(!d) return;
  if(d->r) { d->r--; return; }
  i(d->c,kfree(d->v[i]))
  xfree(d->k);
  xfree(d->v);
  xfree(d);
}

U dget(dict *d, char *key) {
  U r=0;
  char *kk=sp(key);
  i(d->c,if(kk == d->k[i]) { r=kref(d->v[i]); break; })
  return r;
}

void dset(dict *d, char *key, U v) {
  U r=0;
  char *kk=sp(key);
  v=kref(v);
  i(d->c,if(kk == d->k[i]) { r=d->v[i]; kfree(r); d->v[i]=v; break; })
  if(!r) {
    d->k=xrealloc(d->k, sizeof(char*)*(d->c+1));
    d->v=xrealloc(d->v, sizeof(U)*(d->c+1));
    d->k[d->c]=kk;
    d->v[d->c]=v;
    d->c++;
  }
}

dict* dcp(dict *d) {
  dict *d2 = xmalloc(sizeof(dict));
  d2->c=d->c;
  d2->k=xmalloc(sizeof(char*)*d2->c);
  d2->v=xmalloc(sizeof(U)*d2->c);
  d2->r=0;
  i(d->c, d2->k[i]=d->k[i]; d2->v[i]=kref(d->v[i]))
  return d2;
}
