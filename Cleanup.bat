@echo off
echo ��ȷ��Ҫ������������ɵ��ļ��𣿣�����ָ���Ǳ���õ����ļ���
echo ���������Դ�����ļ������Ҫ������رձ����ڣ�����
pause

echo ����ɾ��VS6��������ʱ�ļ�
for /r %%i in (*.dsw) do del /f /q %%~pi\*.ncb *.opt *.plg
echo ����ɾ���������ֲ������ļ�
del /f /q Core\BOOT\OUT\*.BIN
del /f /q Core\BOOT\LOADER\out\*.obj
del /f /q Core\BOOT\LOADER\out\*.ex_
del /f /q Core\BOOT\LOADER\out\*.raw
del /f /q Core\BOOT\LOADER\out\*.sys
echo ����ɾ��16λС����
del /f /q Core\TOOLS\OUT\*.COM
del /f /q Core\TOOLS\OUT\*.EXE
pause