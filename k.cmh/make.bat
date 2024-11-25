@echo off
cl /c k.c v.c /Fe:gk /O2
lib /nologo /out:k.lib k.obj v.obj
exit /b