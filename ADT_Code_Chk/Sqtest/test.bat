:loop
make.exe
Sqtest.exe
fc State.txt stdState.txt
if errorlevel 1 goto end
fc ans.txt stdans.txt
if errorlevel 1 goto end
fc version0.txt versionStd0.txt
if errorlevel 1 goto end
fc version1.txt versionStd1.txt
if errorlevel 1 goto end
goto loop
:end