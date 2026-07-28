@echo off
rem SURFKINI — Launch Unreal Engine 5.4 Editor directly
echo [SURFKINI] Launching Unreal Engine 5.4 Editor...
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command ^
  "& { $editor = 'C:\Program Files\Epic Games\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe'; $proj = 'D:\CODING\SURFKINI\SURFKINI\SURFKINI.uproject'; if (-not (Test-Path $editor)) { Write-Host '[ERROR] UE 5.4 Editor not found at ' + $editor -ForegroundColor Red; pause; exit 1 }; Write-Host '[UE5] Launching SURFKINI Editor...' -ForegroundColor Green; Start-Process $editor -ArgumentList `"$proj`" }"
exit /b %ERRORLEVEL%
