@echo off
echo �����������������������ļ��ı��룬�粻��Ҫ������ص��˴��ڡ�
pause

echo ����Tools
cd Core\Tools
call build.bat

echo ����DBR������������
cd ..\BOOT
call build.bat

echo ����LOADER.SYS
cd LOADER
call build.bat

echo ȫ��������ɣ������Ƿ��д��������
pause