all: k

k:
	clang-17 -O3 -c k.c v.c -fPIC
	ar r k.a k.o v.o
	clang-17 -gdwarf-4 -c k.c v.c -fPIC
	ar r kd.a k.o v.o

clean:
	rm -f *.a *.o
