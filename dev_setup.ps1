Invoke-WebRequest -Uri "https://github.com/microsoft/vcpkg/archive/2020.04.zip" -OutFile "vcpkg.zip"
Expand-Archive -Path vcpkg.zip
Set-Location vcpkg\vcpkg-2020.04
./bootstrap-vcpkg.bat
$IntegrateResult = ./vcpkg integrate project
Write-Output $IntegrateResult
$InstallCmd = ($IntegrateResult -split "\n")[-2].Trim()
Write-Output $InstallCmd

Set-Location ../..
$Install_Shell = @"
$InstallCmd -Project coolq_sdk_x
$InstallCmd -Project CQPlus.Api
$InstallCmd -Project CQPlus.Script.Python27
$InstallCmd -Project CQPlus.Script.Python37

Set-Location vcpkg\vcpkg-2020.04
.\vspkg install boost-algorithm libiconv
"@


Write-Output $Install_shell | Out-File -Filepath ./install_package.ps1 -Encoding ASCII