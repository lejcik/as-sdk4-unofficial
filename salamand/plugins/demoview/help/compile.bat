@call "%CURRENT_HHCEXE%" demoview.hhp

@if not "%1"=="" (@call "%1" demoview.chm %2) else @pause
@exit /b
