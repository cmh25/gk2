#ifndef P_H
#define P_H

#include "k.h"

extern unsigned int TIMES;

#define T000   0 /* $a */
#define T001   1 /* e */
#define T002   2 /* o */
#define T003   3 /* ez */
#define T004   4 /* N */
#define T005   5 /* '(' */
#define T006   6 /* ')' */
#define T007   7 /* V */
#define T008   8 /* $e */

typedef struct { char v; U n; } pn;
typedef struct {
  char *p;       /* buffer */
  int S[1024];   /* state */
  int R[1024];   /* rules */
  pn V[1024];    /* values */
  int si,ri,vi;  /* index */
  int t[1024];   /* tokens */
  int ti,tc;     /* tokens index,count */
  U v[1024];     /* token values */
  int lt;        /* last token */
  U values[256];
  int valuei;
  char pbc[256];
  int pbci;
} pgs;

pgs* pgnew(void);   
void pgfree(pgs *s);
void pgparse(pgs *s);
U pgreduce(pgs *s);

#endif /* P_H */
