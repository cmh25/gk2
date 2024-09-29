#include "repl.h"

int main(int argc, char **argv) {
  if(argc>1) load(argv[1]);
  repl();
  return 0;
}
