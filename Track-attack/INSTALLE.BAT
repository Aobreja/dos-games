@ECHO OFF

CLS
ECHO  JOYSTICK, HORS SERIE CD No2
ECHO.
ECHO.
ECHO Installation de TRACK ATTACK
ECHO _____________________________
ECHO.
ECHO.
ECHO.
CHOICE /C:on Proc‚dez-vous … l'installation depuis Windows 3.1 ou 3.11
if errorlevel 2 goto ok
if errorlevel 1 goto win

:win
CLS
ECHO Si vous ex‚cutez cette installation depuis Windows 3.X, il est pr‚f‚rable
ECHO de repasser sous DOS.
ECHO TRACK ATTACK ne peut ˆtre lancer … partir de Windows 3.1 ou 3.11. Vous devrez
ECHO donc lancer le programme … partir de l'invite du DOS aprŠs son installation.
ECHO Si vous pr‚f‚rez proc‚der … l'installation … partir du DOS, quittez Windows
ECHO et tapez l'invite du CD-ROM
ECHO.
ECHO.   Exemple : si votre CD-Rom se trouve en D:, tapez   D: [entr‚e]
ECHO.                                   puis la commande   DOSINST [entr‚e]
ECHO.
ECHO Si au contraire vous d‚sirez continuer l'installation depuis Windows 3.X,
ECHO quittez Windows 3.X une fois le soft install‚ et lancez TRACK ATTACK
ECHO … partir du DOS.
ECHO.
ECHO.
CHOICE /c:on Voulez-vous continuer :
if errorlevel 2 goto fin
if errorlevel 1 goto ok

:ok
CLS
CHOICE /c:on Attention, l'installation n‚cessite 32 Mo de libre sur C:. Continuer
if errorlevel 2 goto fin
if errorlevel 1 goto ok1

:ok1
trakatak -x -y c:\joydemos\trakatak\
cd\
c:
cd\joydemos\trakatak
CLS
TYPE TECH.TXT | MORE
TYPE README.TXT | MORE
ECHO.
CLS
ECHO ***********************************************************
ECHO La d‚mo est install‚e dans le r‚pertoire C:\JOYDEMOS\TRAKATAK\
ECHO.
ECHO.
ECHO. La d‚mo de Track Attack n'intŠgre aucun son.
ECHO.
ECHO. Pour lancer le jeu, tapez GO
ECHO.
PAUSE

:fin
exit

