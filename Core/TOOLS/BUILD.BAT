@echo off
call ..\SETENV
set path=%MINGW%;%OLDPATH%
echo on
@mingw32-make
@pause
