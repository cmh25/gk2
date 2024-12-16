#ifndef P_H
#define P_H

#include "k.h"
#include "pn.h"

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

typedef struct { char **bc; int *bcn; int n; U **values; } pr;
typedef struct {
  char *p;       /* buffer */
  int *S;        /* state */
  int *R;        /* rules */
  pn **V;        /* values */
  int si,ri,vi;  /* index */
  int *t,ti,tc;  /* tokens, index,count */
  pn **v;        /* token values */
  int lt;        /* last token */
  int Sm,Rm,Vm;  /* max for S R V */
  int tm,vm;     /* max for t v */
  U *values;
  int valuei;
  char *pbc;
  int pbci;
} pgs;

pgs* pgnew(void);   
void pgfree(pgs *s);
pr* pgparse(char *q, int load);
U pgreduce(pr *r, int p);
pr* prnew(void);
void prfree(pr *r);

#endif /* P_H */
