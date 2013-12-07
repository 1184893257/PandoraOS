@echo off
echo 本批命令将完成整个工程所有文件的编译，如不需要编译请关掉此窗口。
pause

echo 编译Tools
cd Core\Tools
call build.bat

echo 编译DBR引导扇区代码
cd ..\BOOT
call build.bat

echo 编译LOADER.SYS
cd LOADER
call build.bat

echo 全部编译完成，请检查是否有错误产生。
pause