all: gk

gk:
	clang-13 -Ofast -ogk k/[az].c p.c lex.c timer.c x.c k.c main.c repl.c sym.c -w -march=native -funsigned-char -fno-stack-protector -fno-unwind-tables

gkd:
	clang-13 -g -ogk k/[az].c p.c lex.c timer.c x.c k.c main.c repl.c sym.c -w -march=native -funsigned-char -fno-stack-protector -fno-unwind-tables

test: gk
	$(MAKE) -C test

clean:
	rm -f gk

.PHONY: test
