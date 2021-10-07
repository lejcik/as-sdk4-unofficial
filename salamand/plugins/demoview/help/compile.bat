@call "%CURRENT_HHCEXE%" demoview.hhp

@if not "%1"=="" (@call "%1" demoview.chm) else @pause
@exit /b
