#ifndef FN_H
#define FN_H

#include "k.h"
#include "scope.h"
#include "p.h"

typedef struct fn {
  char *d;    /* definition */
  int v;      /* valence */
  pr *n;      /* parse result */
  scope *s;   /* scope */
  int q;      /* formal params */
} fn;

fn* fnnew(char *f);
void fnfree(fn *f);
U fnd(fn *f);
U fne(fn *f, U *x, int n);

#endif /* FN_H */
