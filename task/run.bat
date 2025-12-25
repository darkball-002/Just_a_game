@echo off

call task/config.bat

cd "%num%w/%Lexport%/"

echo.
echo ===================
echo    task start
echo ===================
echo.

(
    if exist "%LN%.exe" goto run
) > ../%Llog% 2>&1

echo.
echo ===================
echo    task failed
echo ===================
echo.

exit /b 0

:run 
(
    call "%LN%.exe"
) >> ../%Llog% 2>&1

echo.
echo ===================
echo    task completed
echo ===================
echo.

echo code = %ERRORLEVEL% >> ../%Llog%
