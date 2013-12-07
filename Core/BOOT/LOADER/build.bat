::**************************************************************************
::
::这个工程需要用到Turbo C++ 3.0用于编译16位的部分。
::对于64位Win7的用户则无法编译这个工程，请注意。
::
::**************************************************************************
::让控制台窗口能正常显示16位程序输出的信息，我们运行debug并使其秒退
@echo off
echo q|debug>nul
call ..\..\SETENV
::linklist是要链接的OBJ文件的列表
set linklist=

::编译
echo Compiling...
call :AssembleOBJ entry.asm
call :AssembleOBJ video.asm
call :CompileC c_entry.c

::链接
echo Linking...
tlink /x /n /3 /c %linklist%,out\loader.ex_
pause
echo.

::已完成链接，删除OBJ文件以减少大小
del %linklist%

::链接得到EXE文件（改名为ex_防止误运行），将其去掉并进行重定向
echo Locating EXE to 0:7C00
exe2bin -o0:7c00 out\loader.ex_ out\loader.raw
if not exist out\loader.ex_ goto :failed
pause
echo.

::已经完成重定向，删掉链接得到的文件
del out\loader.ex_

::切掉多余的字节
echo Cutting excess bytes.
nasm final.asm -o out\loader.sys
if not exist out\loader.sys goto :failed
pause
echo.

::已完成文件切割，删除旧文件。
del out\loader.raw

::完成批命令，退出
goto :eof

::编译汇编文件的子批命令
:AssembleOBJ
echo nasm -f obj %1 -o out\%~n1.obj
nasm -f obj %1 -o out\%~n1.obj
if not exist out\%~n1.obj goto :failed
set linklist=%linklist% out\%~n1.obj
echo Success
pause
echo.
goto :eof

::编译C文件的子批命令
:CompileC
echo tcc -C -G -O -c -nout %1
tcc -C -G -O -c -nout %1
if not exist out\%~n1.obj goto :failed
set linklist=%linklist% out\%~n1.obj
echo Success
pause
echo.
goto :eof

::提示编译出错的子批命令
:failed
echo Failed to compile %1
pause
echo.
goto :eof


