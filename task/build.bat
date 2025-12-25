@echo off

call task/config.bat

cd "%num%w"


echo.
echo ===================
echo    task start
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

exit /b 0

rem unused:

rem %gcc_c% ^
rem -I %gcc_h% -I %glfw_h% -I %glad_h% -I %cglm_h% -I %pH% ^
rem -L %glfw_c% -lglfw3 -lopengl32 -lgdi32 ^
rem -Wl,-subsystem,windows ^
rem -s ^
rem %glad_c% %Lobject%\*.o -o %pExe%

rem set glfw_c="%Lglfw%\build\src"
rem set glfw_h="%Lglfw%\include"

rem set glad_c="%Lglad%\src\glad.c"
rem set glad_h="%Lglad%\include"

rem set cglm_h="%Lcglm%\include"
