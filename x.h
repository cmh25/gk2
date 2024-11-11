#ifndef X_H
#define X_H

#include <stdlib.h>
#include <stdint.h>

void* xmalloc(size_t s);
void xfree(void *p);
void* xcalloc(size_t n, size_t s);
void* xrealloc(void *p, size_t s);
void* xstrdup(const char *s);
void* xstrndup(const char *s, size_t n);
int xatoi(char *s);
float xstrtof(char *s);
char* xesc(char *p);
char* xunesc(char *p);
char* xeqs(char *p);

#endif /* X_H */
