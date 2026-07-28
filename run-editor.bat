@echo off
rem SURFKINI — Launch Unreal Engine Editor directly
echo [SURFKINI] Launching Unreal Engine 5.8 Editor...
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command ^
  "& { $editor = 'D:\GMS\UE_5.8\Engine\Binaries\Win64\UnrealEditor.exe'; $proj = 'D:\CODING\SURFKINI\SURFKINI\SURFKINI.uproject'; if (-not (Test-Path $editor)) { Write-Host '[ERROR] UE 5.8 Editor not found at ' + $editor -ForegroundColor Red; pause; exit 1 }; Write-Host '[UE5] Launching SURFKINI Editor...' -ForegroundColor Green; Start-Process $editor -ArgumentList `"$proj`" }"
exit /b %ERRORLEVEL%
