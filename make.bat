@echo off
if "%1%"=="test" goto test
cd k.default
cmd /c make.bat
cd ..
cl p.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c systime.c scope.c fn.c sys.c k.default/k.lib /Fe:gk /O2
exit /b 0
:test
cd t
cmd /c t.bat
cd ..
