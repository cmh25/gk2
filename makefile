all: gk

gk:
	clang-13 -Ofast -oa k/[az].c p.c timer.c x.c k.c main.c -w -march=native -funsigned-char -fno-stack-protector -fno-unwind-tables

test: gk
	$(MAKE) -C test

clean:
	rm -f a

.PHONY: test
