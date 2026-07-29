@echo off
rem SURFKINI — Launch Unreal Engine 5.8 Editor directly
echo [SURFKINI] Launching Unreal Engine 5.8 Editor...
cd /d "D:\GMS\UE_5.8\Engine\Binaries\Win64"
start "" "UnrealEditor.exe" "%~dp0SURFKINI.uproject"
