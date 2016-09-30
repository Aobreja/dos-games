@echo off
ultrinit
lh ultrawlf\ultrawlf ultrawlf
REM     lh ultrawlf c:\wolf\ultrawlf /i11 /b220
if errorlevel 1 goto terminate
wolf3d
ultrawlf\ultrawlf
:terminate
