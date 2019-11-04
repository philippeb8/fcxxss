@echo off

set PATH=%FCXXSS_DIR%\bin;%PATH%
set FCXXSS_CC=cl.sh
set FCXXSS_DIR=%~dp0\..

bash -c "fcxxss-cl.sh %*"
