#ifndef SCOPE_H
#define SCOPE_H

#include "dict.h"
#include "k.h"

typedef struct scope {
  struct scope *p; /* parent */
  dict *d;         /* function local vars */
  char *k;         /* ktree path */
} scope;

extern scope *ks,*gs,*cs;
//extern dict *ktree,*C,*Z;

void scope_init(void);
scope* scope_new(scope *p);
scope* scope_newk(scope *p, char *k);
void scope_free(scope *s);
U scope_get(scope *s, char *n);
U scope_set(scope *s, char *n, U v);

#endif /* SCOPE_H */
