o=-Ofast -fno-builtin -funsigned-char -fno-unwind-tables -Wno-parentheses -Wno-incompatible-pointer-types -Wfatal-errors -march=native
g=-gdwarf-4 -fno-builtin -funsigned-char -fno-unwind-tables -Wno-parentheses -Wno-incompatible-pointer-types -Wfatal-errors -march=native

a:?.[ch] makefile
	clang-17 -c -fPIC a.c $o
	ar r k.a a.o
	clang-17 -c -fPIC a.c $g
	ar r kd.a a.o

clean:
	rm -f *.a *.o
