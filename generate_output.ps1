# Resolve the directory of this script
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

$InputDir = Join-Path $ScriptDir "inputs"
$OutputDir = Join-Path $ScriptDir "outputs"

# Remove old outputs directory
if (Test-Path $OutputDir) {
    Remove-Item -Recurse -Force $OutputDir
    Write-Host "Removed old outputs directory: $OutputDir"
}

# Create new outputs directory
New-Item -ItemType Directory -Path $OutputDir | Out-Null
Write-Host "Created new outputs directory: $OutputDir"

# Check the version of wireviz
wireviz --version

# Run wireviz on each input YAML file
Get-ChildItem -Path $InputDir -Filter *.yaml | ForEach-Object {
    wireviz $_.FullName --output-dir $OutputDir
}

# Remove any non-PNG files in the outputs directory
Get-ChildItem -Path $OutputDir -File | Where-Object { $_.Extension -ne ".png" } | Remove-Item -Force
