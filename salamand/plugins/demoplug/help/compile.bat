@call "%CURRENT_HHCEXE%" demoplug.hhp

@if not "%1"=="" (@call "%1" demoplug.chm %2) else @pause
@exit /b
