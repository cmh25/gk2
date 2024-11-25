CORE=k.cmh
#CORE=k.shakti
export CORE

all: gk

gk:
	$(MAKE) -C $(CORE)
	clang -O3 -ogk p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c $(CORE)/k.a

gkd:
	$(MAKE) -C $(CORE)
	clang -gdwarf-4 -ogk p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c scope.c fn.c $(CORE)/kd.a

test: gk
	$(MAKE) -C t

testv: gk
	$(MAKE) -C t testv

clean:
	$(MAKE) -C t clean
	$(MAKE) -C $(CORE) clean
	rm -f gk

.PHONY: test
