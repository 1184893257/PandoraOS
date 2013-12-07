@echo off
call ..\SETENV
echo on
nasm DBRFAT12.ASM -o OUT\DBRFAT12.BIN
@pause
nasm DBRFAT16.ASM -o OUT\DBRFAT16.BIN
@pause
nasm DBRFAT32.ASM -o OUT\DBRFAT32.BIN
@pause