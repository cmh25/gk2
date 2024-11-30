#include "repl.h"
#include "k.h"
#include <stdio.h>

int main(int argc, char **argv) {
  fprintf(stderr, "gk2-v0.0.0 Copyright (c) 2023-2024 Charles Hall\n\n");
  kinit();
  if(argc>1) load(argv[1],1);
  repl();
  return 0;
}
