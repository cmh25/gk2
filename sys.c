#include "sys.h"
#include <stdlib.h>
#include "scope.h"
#include "sym.h"

void exit_(int i) {
  scope_free(gs);
  sf();
  exit(i);
}
