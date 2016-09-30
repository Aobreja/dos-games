echo off
cls
if not exist aeprog.exe goto :checkthere
echo The computer is loading
echo Ancient Empires
aeprog.exe %1 %2 %3
goto :end
:checkthere
if not exist \tlc\ae\aeprog.exe goto :notthere
echo The computer is loading
echo Ancient Empires
cd \tlc\ae
aeprog.exe %1 %2 %3
cd \
goto :end
:notthere
echo Ancient Empires could not
echo be found on this drive.
:end
