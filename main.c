#include "repl.h"

int main(int argc, char **argv) {
  kinit(0);
  if(argc>1) load(argv[1]);
  repl();
  return 0;
}
