@echo off
echo 你确定要清除所有已生成的文件吗？（这里指的是编译得到的文件）
echo 并不会清除源代码文件。如果要保留请关闭本窗口，否则
pause

echo 正在删除VS6产生的临时文件
for /r %%i in (*.dsw) do del /f /q %%~pi\*.ncb *.opt *.plg
echo 正在删除引导部分产生的文件
del /f /q Core\BOOT\OUT\*.BIN
del /f /q Core\BOOT\LOADER\out\*.obj
del /f /q Core\BOOT\LOADER\out\*.ex_
del /f /q Core\BOOT\LOADER\out\*.raw
del /f /q Core\BOOT\LOADER\out\*.sys
echo 正在删除16位小程序
del /f /q Core\TOOLS\OUT\*.COM
del /f /q Core\TOOLS\OUT\*.EXE
pause