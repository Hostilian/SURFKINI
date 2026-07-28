@echo off
rem SURFKINI FCC Claude Launcher
rem Uses the global FCC install at %USERPROFILE%\.fcc\
rem The FCC server must be running (run fcc-server.bat first)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%USERPROFILE%\.fcc\Start-FCC-Claude-Correct.ps1" %*
exit /b %ERRORLEVEL%
