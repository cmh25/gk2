#include "fn.h"
#include <ctype.h>
#include <string.h>
#include "x.h"
#include "sym.h"
#include "p.h"

fn* fnnew(char *s) {
  fn *f=xcalloc(1,sizeof(fn));
  f->d=xstrdup(s);
  return f;
}

void fnfree(fn *f) {
  xfree(f->d);
  if(f->n) prfree(f->n);
  xfree(f);
}
