@echo off

set FCXXSS_CC=cl.sh
set FCXXSS_DIR=%~dp0\..
set PATH=%FCXXSS_DIR%\bin;%PATH%

bash -c "fcxxss-cl.sh %*"
