#ifndef DICT_H
#define DICT_H

#include "k.h"

typedef struct dict {
  int c;     /* count */
  char **k;  /* keys */
  U *v;      /* values */
  int r;     /* ref */
} dict;

dict* dnew(void);
void dfree(dict *d);
U dget(dict *d, char *key);
void dset(dict *d, char *key, U v);
dict* dcp(dict *d);

#endif /* DICT_H */
