@echo off
set ec=0
for /f "tokens=*" %%t in (tests) do call :run %%t
:run
if "%1"=="" goto end
..\gk t%1 > %1 2>NUL
comp /a /l /m r%1 %1 > d%1
if "%errorlevel%"=="0" (echo %1: pass & del %1 d%1) else set /a ec+=1 & echo %1: fail *****
exit /b
:end