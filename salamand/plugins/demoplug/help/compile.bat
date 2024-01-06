@echo off

setlocal

set HHCEXE=C:\Program Files (x86)\HTML Help Workshop\hhc.exe

if not exist "%HHCEXE%" (
  echo Unable to find HTML Help Workshop.
  echo.
  pause
  endlocal
  exit /b
)

call "%HHCEXE%" demoplug.hhp

if not "%1"=="" (call "%1" demoplug.chm) else pause
endlocal
exit /b
