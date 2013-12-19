set PROJDIR=%~dp0
set OLDPATH=%path%
set NASMENV=!-s!-i%PROJDIR%INCLUDE\!-i%PROJDIR%PROC16\!-i%PROJDIR%BOOT\OUT\
set TC=D:\Tools\TC\bin
set MINGW=D:\Tools\MINGW\bin
set TOOLS=%PROJDIR%TOOLS\OUT
if not exist %mingw% echo You must install MINGW here: %MINGW%
if not exist %tc% echo You must install Turbo C++ 3.0 here: %TC%
