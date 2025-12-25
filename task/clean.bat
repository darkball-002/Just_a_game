@echo off

call task/config.bat

cd "%num%w"

echo.
echo ===================
echo    task start
echo ===================
echo.

(
%Lcmake% --build %Lobject% --target clean
) > %Llog% 2>&1

if %ERRORLEVEL%==0 goto run

echo.
echo ===================
echo    task failed
echo ===================
echo.

exit /b 1

:run

echo.
echo ===================
echo    task completed
echo ===================
echo.

set /p ok=remove assets folder in bin? <y, n>

if "ok"=="y" rmdir /s "%Lexport%/assets"


exit /b 0
