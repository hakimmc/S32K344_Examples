
set PATH=%NXP_MBD_S32K3_GCC_PATH%\bin;%PATH%

cd .

if "%1"=="" ("C:\PROGRA~1\MATLAB\R2024a\bin\win64\gmake"  -f TJA1042_Loop_Example.mk -j all) else ("C:\PROGRA~1\MATLAB\R2024a\bin\win64\gmake"  -f TJA1042_Loop_Example.mk -j %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1