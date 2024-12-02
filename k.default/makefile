all: k

W=-Wall -Wformat=2 -Wextra -Wformat-security -Wformat-nonliteral -Wpedantic

k:
	clang -Ofast -march=native -c k.c v.c av.c -fPIC
	ar r k.a k.o v.o av.o
	clang -gdwarf-4 $(W) -c k.c v.c av.c -fPIC
	ar r kd.a k.o v.o av.o

clean:
	rm -f *.a *.o
