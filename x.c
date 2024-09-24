#include "x.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

void* xmalloc(size_t s) {
  void *p=0;
  if(!(p=malloc(s))) {
    printf("error: xmalloc(): memory allocation failed\n");
    exit(1);
  }
  return p;
}

void xfree(void *p) {
  if(p) free(p);
}

void* xcalloc(size_t n, size_t s) {
  void *p=0;
  if(!(p=calloc(n, s))) {
    printf("error: xcalloc(): memory allocation failed\n");
    exit(1);
  }
  return p;
}

void* xrealloc(void *p, size_t s) {
  void *p2=0;
  if(!(p2=realloc(p, s))) {
    printf("error: xrealloc(): memory allocation failed\n");
    exit(1);
  }
  return p2;
}

int xatoi(char *s) {
  int r;
  long a;
  char *e;
  if(!s||!strlen(s)) return r=INT_MIN;
  else if(!strcmp(s,"0I")) r=INT_MAX;
  else if(!strcmp(s,"0N")) r=INT_MIN;
  else if(!strcmp(s,"-0N")) r=INT_MIN;
  else if(!strcmp(s,"-0I")) r=INT_MIN+1;
  else {
    a=strtol(s,&e,10);
    if((size_t)(e-s)!=strlen(s)) r=INT_MIN;
    else if(a>INT_MAX) r=INT_MAX;
    else if(a<INT_MIN) r=INT_MIN;
    else r=a;
  }
  return r;
}

float xstrtof(char *s) {
  float r;
  char *e;
  if(!s||!strlen(s)) r=NAN;
  else if(!strcmp(s,"0i")||!strcmp(s,"0I")) r=INFINITY;
  else if(!strcmp(s,"0n")||!strcmp(s,"0N")) r=NAN;
  else if(!strcmp(s,"-0n")||!strcmp(s,"-0N")) r=NAN;
  else if(!strcmp(s,"-0i")||!strcmp(s,"-0I")) r=-INFINITY;
  else {
    r=strtof(s,&e);
    if((size_t)(e-s)!=strlen(s)) r=NAN;
  }
  return r;
}
