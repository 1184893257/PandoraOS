@echo off
echo q|debug>nul

echo cleaning Tools...
cd Core\Tools
mingw32-make clean
echo.

echo cleaning DBR...
cd ..\BOOT
mingw32-make clean
echo.

echo cleaning LOADER.SYS...
cd LOADER
mingw32-make clean
echo.

echo clean finished.
pause
