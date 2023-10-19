@echo off
chcp 1251
cls
:: Получение информации о файле сценария
for %%A in ("%~dpnx0") do (
  set "FilePath=%%~fA"
  set "FileName=%%~nA"
)

:: Получение даты и времени создания файла
for /f "tokens=1-2" %%B in ('dir /tc "%FilePath%" ^| find "%FileName%"') do (
  set "FileCreateDateDate=%%B"
  set "FileCreateTime=%%C"
)
echo -- имя этого bat-файла: %~n0
echo -- этот bat-файл создан: %FileCreateDateDate%, %FileCreateTime%
echo -- путь bat-файла: %~f0

pause