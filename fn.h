#ifndef FN_H
#define FN_H

#include "k.h"
#include "scope.h"
#include "p.h"

typedef struct fn {
  char *d;        /* definition */
  unsigned int v; /* valence */
  pr *n;          /* ast */
  scope *s_;      /* initial scope */
  scope *s;       /* active scope */
  int q;          /* explicit formal params */
} fn;

fn* fnnew(char *f);
void fnfree(fn *f);

#endif /* FN_H */
