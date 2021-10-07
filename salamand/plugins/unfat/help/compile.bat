@call "%CURRENT_HHCEXE%" unfat.hhp

@if not "%1"=="" (@call "%1" unfat.chm) else @pause
@exit /b
