@echo off
call ..\SETENV
set PATH=%MINGW%;%OLDPATH%
echo on
@mingw32-make
@pause
