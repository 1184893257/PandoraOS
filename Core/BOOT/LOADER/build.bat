::**************************************************************************
::
::���������Ҫ�õ�Turbo C++ 3.0���ڱ���16λ�Ĳ��֡�
::����64λWin7���û����޷�����������̣���ע�⡣
::
::**************************************************************************
::�ÿ���̨������������ʾ16λ�����������Ϣ����������debug��ʹ������
@echo off
echo q|debug>nul
call ..\..\SETENV
::linklist��Ҫ���ӵ�OBJ�ļ����б�
set linklist=

::����
echo Compiling...
call :AssembleOBJ entry.asm
call :AssembleOBJ video.asm
call :CompileC c_entry.c

::����
echo Linking...
tlink /x /n /3 /c %linklist%,out\loader.ex_
pause
echo.

::��������ӣ�ɾ��OBJ�ļ��Լ��ٴ�С
del %linklist%

::���ӵõ�EXE�ļ�������Ϊex_��ֹ�����У�������ȥ���������ض���
echo Locating EXE to 0:7C00
exe2bin -o0:7c00 out\loader.ex_ out\loader.raw
if not exist out\loader.ex_ goto :failed
pause
echo.

::�Ѿ�����ض���ɾ�����ӵõ����ļ�
del out\loader.ex_

::�е�������ֽ�
echo Cutting excess bytes.
nasm final.asm -o out\loader.sys
if not exist out\loader.sys goto :failed
pause
echo.

::������ļ��иɾ�����ļ���
del out\loader.raw

::���������˳�
goto :eof

::�������ļ�����������
:AssembleOBJ
echo nasm -f obj %1 -o out\%~n1.obj
nasm -f obj %1 -o out\%~n1.obj
if not exist out\%~n1.obj goto :failed
set linklist=%linklist% out\%~n1.obj
echo Success
pause
echo.
goto :eof

::����C�ļ�����������
:CompileC
echo tcc -C -G -O -c -nout %1
tcc -C -G -O -c -nout %1
if not exist out\%~n1.obj goto :failed
set linklist=%linklist% out\%~n1.obj
echo Success
pause
echo.
goto :eof

::��ʾ����������������
:failed
echo Failed to compile %1
pause
echo.
goto :eof


