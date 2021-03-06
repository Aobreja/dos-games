@echo off

echo.
echo ��� ��� ��� ��� � ��    ��� ��� ��� ��� ��� � ��
echo  �  ��� ��� � � ���     ���  �   �  ��� � � ��� 
echo  �  � � � �  �  �  �    � �  �   �  � �  �  �  �
echo ��� ��� �� �� ���    � � ��� ��� ��� ��� ��� �� �
echo � � ��  � � � � �    ��� ��  ���  ��  �  � � � ��
echo ��  ��� �   �  �      �  ��� � � ��  ���  �  �  �

rem =====================================================================

if "%1" == "" GOTO Syntax
if "%1" == "/?" GOTO Syntax
if NOT "%2" == "" GOTO Syntax

if NOT EXIST %1\nul goto no_path

if EXIST %1\TA\nul goto skip_create_dir
md %1\TA > nul
if ERRORLEVEL == 1 goto cant_create_dir
:skip_create_dir

if NOT EXIST TRAKATAK.EXE goto no_file

echo Please wait a few days...

copy TRAKATAK.EXE %1\TA\TRAKATAK.EXE > nul

cd %1\TA

TRAKATAK.EXE -y > nul
if ERRORLEVEL == 1 goto cant_unarj

del TRAKATAK.EXE > nul

echo.
echo Installation is complete, type 'soundset.exe' to configure the sound
echo and 'go.exe' to run Track Attack.

goto exit

rem =====================================================================

:syntax

echo Syntax: install [path]
echo.
echo This will install Track Attack to the TA directory in the given path.
echo.
echo Eg. 'install C:\GAMES' will install Track Attack to 'C:\GAMES\TA'

goto exit

rem =====================================================================

:no_path

echo Track Attack cannot install because the path '%1' does not exist.

goto exit

rem =====================================================================

:cant_create_dir

echo Track Attack cannot create the directory '%1\TA'.

goto exit

rem =====================================================================

:cant_copy_file

echo Track Attack cannot copy the file 'TRAKATAK.EXE' to '%1\TA\TRAKATAK.EXE'.

goto exit

rem =====================================================================

:no_file

echo You are missing the file 'TRAKATAK.EXE'.

goto exit

rem =====================================================================

:cant_unarj

echo Track Attack cannot uncompress the file 'TRAKATAK.EXE'.

goto exit

rem =====================================================================

:exit

rem =====================================================================
