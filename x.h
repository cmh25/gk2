#ifndef X_H
#define X_H

#include <stdlib.h>
#include <stdint.h>

void* xmalloc(size_t s);
void xfree(void *p);
void* xcalloc(size_t n, size_t s);
void* xrealloc(void *p, size_t s);
int xatoi(char *s);
float xstrtof(char *s);

#endif /* X_H */
