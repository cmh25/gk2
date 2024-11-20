#include "repl.h"
#include "k.h"

int main(int argc, char **argv) {
  kinit();
  if(argc>1) load(argv[1]);
  repl();
  return 0;
}
