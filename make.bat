@echo off
if "%1%"=="test" goto test
if "%1%"=="testp" goto testp
cd k.default
cmd /c make.bat
cd ..
cl p.c pn.c lex.c timer.c x.c k.c main.c repl.c sym.c zv.c dict.c systime.c scope.c fn.c sys.c k.default/k.lib /Fe:gk /O2
exit /b 0
:test
cd t
cmd /c t.bat
cd ..
exit /b 0
:testp
cd t
cmd /c p.bat
cd ..
exit /b 0
