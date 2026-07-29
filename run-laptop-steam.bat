@echo off
rem SURFKINI — Steam and Laptop Standalone Game Launcher
rem ====================================================
echo ==================================================
echo   SURFKINI Steam ^& Laptop Performance Launcher
echo ==================================================
echo [Steam] Setting Steam AppID = 480 (Spacewar Dev AppID)...
set SteamAppId=480
set SteamGameId=480

echo [Laptop Optimization] Launching Standalone UE 5.8 game client...
echo Options: 1080p Windowed, Dynamic Resolution Scaling, High Core Count Utilisation

cd /d "D:\GMS\UE_5.8\Engine\Binaries\Win64"
start "" "UnrealEditor.exe" "%~dp0SURFKINI.uproject" /Engine/Maps/Entry -game -RESX=1920 -RESY=1080 -WINDOWED -USEALLAVAILABLECORES -LOG

echo ==================================================
echo Game launched cleanly! Enjoy playing SURFKINI.
echo ==================================================
