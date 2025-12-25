@echo off

set /p num=id = 

rem ===== project =====
set LN=WindowGame
set Lexport=bin
set Lsource=source
set Lheader=header
set Lobject=object
set Lresources=resources

rem ===== depends =====
set Lglfw=H:/Dev/api/glfw-3.4
set Lglad=H:/Dev/api/glad
set Lcglm=H:/Dev/api/cglm-0.9.6

rem ===== cmake =====
set Lcmake=H:/Dev/program/compiler/cmake/bin/cmake.exe

rem ===== gcc ====
set Lgcc=H:/Dev/program/compiler/gcc/bin/clang.exe
set Lmake=H:/Dev/program/compiler/gcc/bin/mingw32-make.exe

rem ===== log ====

set Llog=output.log

cls