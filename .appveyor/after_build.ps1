$ErrorActionPreference = "Stop"

if ($env:configuration -ne "Release") {
    # Artifacts are only useful when building in release mode. When not in release mode, the artifacts aren't needed.
    # Not packaging the artifacts here will mean that AppVeyor won't find them and nothing will be uploaded.
    return
}

Set-Location $env:APPVEYOR_BUILD_FOLDER

$archiveName = "starryfilespp_$env:arch.zip"
7z a $archiveName $env:APPVEYOR_BUILD_FOLDER\StarryFiles++\StarryFiles++\$env:platform\$env:configuration\StarryFiles++.exe
7z a $archiveName $env:APPVEYOR_BUILD_FOLDER\Documentation\User\History.txt
7z a $archiveName $env:APPVEYOR_BUILD_FOLDER\Documentation\User\License.txt
7z a $archiveName $env:APPVEYOR_BUILD_FOLDER\Documentation\User\Readme.txt

7z a starryfilespp_${env:arch}_symbols.zip $env:APPVEYOR_BUILD_FOLDER\StarryFiles++\StarryFiles++\$env:platform\$env:configuration\StarryFiles++.pdb

if ($env:platform -ne "ARM64") {
    Copy-Item $env:APPVEYOR_BUILD_FOLDER\StarryFiles++\Installer\bin\$env:arch\$env:configuration\starryfilespp_${env:arch}_setup.msi .
}

7z a starryfilespp_translations.zip $env:APPVEYOR_BUILD_FOLDER\StarryFiles++\Win32\$env:configuration\StarryFiles++*.dll

$env:APPVEYOR_BUILD_VERSION | Out-File -NoNewline latest_version.txt