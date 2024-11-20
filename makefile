o=-Oz -funsigned-char -fno-unwind-tables -Wno-parentheses -Wno-incompatible-pointer-types -Wfatal-errors
g=-g -funsigned-char -fno-unwind-tables -Wno-parentheses -Wno-incompatible-pointer-types -Wfatal-errors

all: gk

gk:
	clang-17 -ogk k/a.c p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c $o -mavx512f -mavx512bw -mpclmul -mavx512dq -mavx512vbmi -mavx512vpopcntdq

gkd:
	clang-17 -ogk k/a.c p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c $g -mavx512f -mavx512bw -mpclmul -mavx512dq -mavx512vbmi -mavx512vpopcntdq

test: gk
	$(MAKE) -C t

clean:
	rm -f gk

.PHONY: test
