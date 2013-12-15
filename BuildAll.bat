echo q|debug>nul

echo compiling Tools...
cd Core\Tools
mingw32-make

echo compiling DBR...
cd ..\BOOT
mingw32-make

echo compiling LOADER.SYS...
cd LOADER
mingw32-make

echo compile finished.
pause