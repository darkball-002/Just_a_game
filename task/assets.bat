@echo off

call task/config.bat

cd "../%num%w"

(
    echo.
    echo ===================
    echo    assets copying
    echo ===================
    echo.

    robocopy "%Lresources%" "%Lexport%" /E /R:1 /W:1

    echo.
    echo ===================
    echo    task completed
    echo ===================
    echo.
) >> %Llog% 2>&1

type %Llog%
