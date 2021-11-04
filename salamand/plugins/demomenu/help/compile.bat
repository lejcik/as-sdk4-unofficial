@call "%CURRENT_HHCEXE%" demomenu.hhp

@if not "%1"=="" (@call "%1" demomenu.chm %2) else @pause
@exit /b
