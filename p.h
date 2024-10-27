#ifndef P_H
#define P_H

#include "k.h"

extern unsigned int TIMES;

#define T000   0 /* $a */
#define T001   1 /* s */
#define T002   2 /* e */
#define T003   3 /* se */
#define T004   4 /* o */
#define T005   5 /* ez */
#define T006   6 /* klist */
#define T007   7 /* plist */
#define T008   8 /* elist */
#define T009   9 /* elistz */
#define T010  10 /* ';' */
#define T011  11 /* '\n' */
#define T012  12 /* N */
#define T013  13 /* V */
#define T014  14 /* '(' */
#define T015  15 /* ')' */
#define T016  16 /* '[' */
#define T017  17 /* ']' */
#define T018  18 /* $e */

//typedef struct { char bc[256]; int n; U values[256]; } pr;
typedef struct { char **bc; int *bcn; int n; U **values; } pr;
typedef struct { char v; U n; } pn;
typedef struct {
  char *p;       /* buffer */
  int S[1024];   /* state */
  int R[1024];   /* rules */
  pn V[1024];    /* values */
  int si,zri,vi;  /* index */
  int t[1024];   /* tokens */
  int ti,tc;     /* tokens index,count */
  U v[1024];     /* token values */
  int lt;        /* last token */
  U *values;
  int valuei;
  char *pbc;
  int pbci;
} pgs;

pgs* pgnew(void);   
void pgfree(pgs *s);
pr* pgparse(char *q);
U pgreduce(pr *r);
pr* prnew();
void prfree(pr *r);

#endif /* P_H */
