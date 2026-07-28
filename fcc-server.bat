@echo off
rem SURFKINI — Start the FCC AI Proxy Server (server only, no Claude Code terminal)
rem The server reads API keys from %USERPROFILE%\.fcc\.env
rem Binds to http://127.0.0.1:8082
rem Connect Cline in VS Code to: http://127.0.0.1:8082  token: freecc

echo [SURFKINI FCC] Starting AI proxy server on port 8082...
echo [SURFKINI FCC] API keys from: %USERPROFILE%\.fcc\.env
echo [SURFKINI FCC] After startup, connect Cline to http://127.0.0.1:8082 with token: freecc
echo.

powershell.exe -NoProfile -ExecutionPolicy Bypass -Command ^
  "& { $fcc = '%USERPROFILE%\.local\bin\fcc-server.exe'; $dir = '%USERPROFILE%\.fcc'; if (-not (Test-Path $fcc)) { Write-Host '[ERROR] fcc-server.exe not found at ' + $fcc -ForegroundColor Red; pause; exit 1 }; Write-Host '[FCC] Launching server...' -ForegroundColor Green; Set-Location $dir; & $fcc }"

exit /b %ERRORLEVEL%
