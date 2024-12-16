CORE=k.default
#CORE=k.shakti
export CORE
CC=clang

W=-Wall -Wformat=2 -Wextra -Wformat-security -Wformat-nonliteral -Wpedantic

all: gk

gk:
	$(MAKE) -C $(CORE)
	$(CC) -O3 -ogk p.c pn.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c sys.c $(CORE)/k.a -lm

gkd:
	$(MAKE) -C $(CORE)
	$(CC) -gdwarf-4 $(W) -ogk p.c pn.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c sys.c $(CORE)/kd.a -lm

test: gk
	$(MAKE) -C t

testv: gk
	$(MAKE) -C t testv

testp: gk
	$(MAKE) -C t testp

clean:
	$(MAKE) -C t clean
	$(MAKE) -C $(CORE) clean
	rm -f gk *.o

.PHONY: test testv testp
