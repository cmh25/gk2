CORE=k.cmh
#CORE=k.shakti
export CORE

W=-Wall -Wformat=2 -Wextra -Wformat-security -Wformat-nonliteral -Wpedantic

all: gk

gk:
	$(MAKE) -C $(CORE)
	clang -O3 -ogk p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c sys.c $(CORE)/k.a -lm

gkd:
	$(MAKE) -C $(CORE)
	clang -gdwarf-4 $(W) -ogk p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c sys.c $(CORE)/kd.a -lm

test: gk
	$(MAKE) -C t

testv: gk
	$(MAKE) -C t testv

clean:
	$(MAKE) -C t clean
	$(MAKE) -C $(CORE) clean
	rm -f gk *.o

.PHONY: test
