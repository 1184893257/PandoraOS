@set oldpath=%path%
@set path=D:\Tools\MinGW\bin;%oldpath%
gcc -O2 Entry.c -o..\out\EXE2BIN.EXE
@pause
@set path=D:\Tools\TC\bin;%oldpath%
tcc -C -G -O -n..\out -eEXE2BIND.EXE -ID:\Tools\TC\INCLUDE -LD:\Tools\TC\LIB entry.c
@pause
@del ..\out\*.obj
