#include "scope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "x.h"
#include "sym.h"

#define SM 1000000

static scope *scopea[SM];
scope *ks,*gs,*cs;
//dict *ktree,*C,*Z;

void scope_init(void) {
  gs=cs=scope_new(0);
}

static scope* scope_new_(scope *p, char *k) {
  int i;
  scope *s = xmalloc(sizeof(scope));
  s->p = p;
  s->d = dnew();
  s->k = k;
  for(i=0;i<SM;i++) if(!scopea[i]) break;
  if(i==SM) {
    printf("error: scope_new() i==SM\n");
    exit(1);
  }
  scopea[i]=s;
  return s;
}
scope* scope_new(scope *p) { return scope_new_(p,0); }
scope* scope_newk(scope *p, char *k) { return scope_new_(p,k); }

void scope_free(scope *s) {
  int i;
  if(s->k) return;
  for(i=0;i<SM;i++) {
    if(!scopea[i]) break;
    if(scopea[i] && scopea[i] == s) scopea[i]=0;
  }
  dfree(s->d);
  xfree(s);
}

U scope_get(scope *s, char *n) {
  U r=0;
  if(!s) return 0;
  if(!n) return 0;
  r=dget(s->d,n);
  if(!r && s->p && s!=gs) r=scope_get(s->p,n);
  return r;
}

U scope_set(scope *s, char *n, U v) {
  dset(s->d,n,v);
  return 0;
}

scope* scope_cp(scope *s) {
  int i;
  if(!s) return 0;
  scope *s2 = xmalloc(sizeof(scope));
  s2->p = s->p;
  s2->d = dcp(s->d);
  s2->k = s->k;
  for(i=0;i<SM;i++) if(!scopea[i]) break;
  if(i==SM) {
    printf("error: scope_new() i==SM\n");
    exit(1);
  }
  scopea[i]=s2;
  return s2;
}
