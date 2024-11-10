#ifndef DICT_H
#define DICT_H

#include "k.h"

typedef struct dict {
  int c;
  char **k;
  U *v;
  int r;
} dict;

dict* dnew(void);
void dfree(dict *d);
U dget(dict *d, char *key);
void dset(dict *d, char *key, U v);

#endif /* DICT_H */
