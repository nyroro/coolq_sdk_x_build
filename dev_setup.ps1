# Invoke-WebRequest -Uri "https://github.com/microsoft/vcpkg/archive/2020.04.zip" -OutFile "vcpkg.zip"
# Expand-Archive -Path vcpkg.zip
Set-Location vcpkg\vcpkg-2020.04
# ./bootstrap-vcpkg.bat
$IntegrateResult = ./vcpkg integrate project
Write-Output $IntegrateResult
$InstallCmd = ($IntegrateResult -split "\n")[-2].Trim()
Write-Output $InstallCmd

Set-Location ../..