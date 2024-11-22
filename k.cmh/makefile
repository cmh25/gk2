all: k

k:
	clang-17 -O3 -c k.c -fPIC
	ar r k.a k.o

kd:
	clang-17 -g -c k.c -fPIC
	ar r k.a k.o

clean:
	rm -f k.o k.a
