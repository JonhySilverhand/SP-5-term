@echo off
chcp 1251
cls
:: ��������� ���������� � ����� ��������
for %%A in ("%~dpnx0") do (
  set "FilePath=%%~fA"
  set "FileName=%%~nA"
)

:: ��������� ���� � ������� �������� �����
for /f "tokens=1-2" %%B in ('dir /tc "%FilePath%" ^| find "%FileName%"') do (
  set "FileCreateDateDate=%%B"
  set "FileCreateTime=%%C"
)
echo -- ��� ����� bat-�����: %~n0
echo -- ���� bat-���� ������: %FileCreateDateDate%, %FileCreateTime%
echo -- ���� bat-�����: %~f0

pause