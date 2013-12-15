@echo off
echo q|debug>nul
call ..\..\SETENV
set path=%TOOLS%;%MINGW%;%TC%;%PATH%
mingw32-make
pause
