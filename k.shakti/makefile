o=-Ofast -fno-builtin -funsigned-char -fno-unwind-tables -Wno-multichar -Wno-parentheses -Wno-incompatible-pointer-types -Wfatal-errors
g=-gdwarf-4 -fno-builtin -funsigned-char -fno-unwind-tables -Wno-multichar -Wno-parentheses -Wno-incompatible-pointer-types -Wfatal-errors

a:?.[ch] makefile
	clang-17 -c -fPIC a.c $o -nostdlib -march=native
	ar r k.a a.o
	clang-17 -c -fPIC a.c $g -nostdlib -march=native
	ar r kd.a a.o

clean:
	rm -f *.a *.o
