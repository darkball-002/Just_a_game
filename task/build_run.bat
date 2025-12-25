@echo off

call task/config.bat 

cd "%num%w"


echo.
echo ===================
echo    build start
echo ===================
echo.
(
%Lcmake% ^
-G "MinGW Makefiles" ^
-B %Lobject%\ ^
-DGLFW_BUILD_EXAMPLES=OFF ^
-DCMAKE_C_COMPILER=%Lgcc% ^
-DCMAKE_MAKE_PROGRAM=%Lmake% ^
-DLEXPORT=%Lexport% ^
-DLSOURCE=%Lsource% ^
-DLHEADER=%Lheader% ^
-DLGLFW=%Lglfw% ^
-DLGLAD=%Lglad% ^
-DLCGLM=%Lcglm% ^
-DLN=%LN%

%Lcmake% --build %Lobject%
) > %Llog% 2>&1

type %Llog%

if %ERRORLEVEL%==0 goto run


echo.
echo ===================
echo    build failed
echo ===================
echo.

exit /b 1


:run 

echo.
echo ===================
echo    build completed
echo ===================
echo.

cd "%Lexport%"

echo.
echo ===================
echo    runs start
echo ===================
echo.

(
    if exist "%LN%.exe" goto run2
) >> ../%Llog% 2>&1

echo.
echo ===================
echo    runs failed
echo ===================
echo.

exit /b 0

:run2

(
    call "%LN%.exe"
) >> ../%Llog% 2>&1

echo.
echo ===================
echo    runs completed
echo ===================
echo.

echo code = %ERRORLEVEL% >> ../%Llog%
