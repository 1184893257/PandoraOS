@echo off
call ..\SETENV
echo Compiling...
for /f %%i in ('dir /b *.ASM') do (
	echo %%i-^>OUT\%%~ni.COM
	nasm %%i -o OUT\%%~ni.COM
	pause
)
cd exe2bin
echo EXE2BIN-^>build
call build.bat
cd ..
pause