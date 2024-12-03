@echo off
cl /c k.c v.c av.c /Fe:gk /O2 /fp:fast
lib /nologo /out:k.lib k.obj v.obj av.obj
exit /b
