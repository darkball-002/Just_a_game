@echo off

call config.bat

cd "../%num%w"

%Lcmake% ^
-G "MinGW Makefiles" ^
-B %Lobject%\ ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
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

pause
