# gk2

gk2 is a reimplementation of gk designed to be compatible with the high performance k-core from [shakti](https://shakti.com/)

:warning: **status: extremely experimental**

gk2 has a clean separation between the repl (read eval print loop) and the core k functions. There are currently two cores available:
1. k.default: portable, compiles and runs on lin/win/mac
2. k.shakti: extreme high performance on linux+avx512

To use the shakti core, change these line in the toplevel makefile:
```
CORE=k.default
#CORE=k.shakti
```

## build (lin/mac/win)
```
make
make test
```
on windows, you have to build in a console with visual studio cli tools (cl.exe).
