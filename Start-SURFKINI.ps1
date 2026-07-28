# SURFKINI — One-Click Launcher
# Starts FCC AI server then opens VS Code in the project folder
#
# Usage: Right-click -> Run with PowerShell
#        OR: powershell -File Start-SURFKINI.ps1

$ProjectRoot = "D:\CODING\SURFKINI\SURFKINI"
$FccEnv = "$env:USERPROFILE\.fcc\.env"
$FccServerScript = "$env:USERPROFILE\.fcc\Start-FCC-Work.ps1"

Write-Host "==================================================" -ForegroundColor Cyan
Write-Host "  SURFKINI Project Launcher" -ForegroundColor Cyan
Write-Host "==================================================" -ForegroundColor Cyan

# --- Check FCC server is installed ---
if (-not (Test-Path $FccEnv)) {
    Write-Host "[ERROR] FCC not found at $FccEnv" -ForegroundColor Red
    Write-Host "        Copy the FCC setup from D:\CODING\eushop" -ForegroundColor Yellow
    pause; exit 1
}

# --- Start FCC server in a new window ---
$alreadyRunning = $false
try {
    $response = Invoke-WebRequest -Uri "http://127.0.0.1:8082/health" -TimeoutSec 2 -ErrorAction Stop
    if ($response.StatusCode -eq 200) {
        Write-Host "[FCC] Server already running on port 8082" -ForegroundColor Green
        $alreadyRunning = $true
    }
} catch { }

if (-not $alreadyRunning) {
    Write-Host "[FCC] Starting AI proxy server (port 8082)..." -ForegroundColor Yellow
    Start-Process powershell.exe -ArgumentList "-NoProfile -ExecutionPolicy Bypass -File `"$FccServerScript`"" -WindowStyle Normal
    Write-Host "[FCC] Waiting for server to initialize..."
    Start-Sleep -Seconds 4
}

# --- Open VS Code ---
Write-Host "[VS Code] Opening SURFKINI project..." -ForegroundColor Yellow
$codePath = Get-Command code -ErrorAction SilentlyContinue
if ($codePath) {
    & code $ProjectRoot
    Write-Host "[VS Code] Opened: $ProjectRoot" -ForegroundColor Green
} else {
    Write-Host "[WARNING] VS Code 'code' command not found in PATH." -ForegroundColor Yellow
    Write-Host "          Open VS Code manually and File -> Open Folder -> $ProjectRoot" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "==================================================" -ForegroundColor Cyan
Write-Host "  Setup complete!" -ForegroundColor Green
Write-Host "  FCC AI Proxy : http://127.0.0.1:8082" -ForegroundColor Green
Write-Host "  Token        : freecc" -ForegroundColor Green
Write-Host "  Project      : $ProjectRoot" -ForegroundColor Green
Write-Host "  Next steps:" -ForegroundColor White
Write-Host "    1. In VS Code -> Install recommended extensions" -ForegroundColor White
Write-Host "    2. Open Cline -> set base URL http://127.0.0.1:8082 / token freecc" -ForegroundColor White
Write-Host "    3. Right-click .uproject -> Generate VS project files" -ForegroundColor White
Write-Host "    4. Press Ctrl+Shift+B -> Build (Development Editor)" -ForegroundColor White
Write-Host "==================================================" -ForegroundColor Cyan
