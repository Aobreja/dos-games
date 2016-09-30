SET NETINFO=-M_B9600 -M_DAT&F0&K0\R\2ATA\R\0\2

REM             -M_Dxxxxx  to send command data to modem
REM             -M_Bxxxxx  to set Baud Rate
REM             \E instead of '=' sign in Hayes comman string
REM             \R sends carriage return
REM             Number = seconds pause (0 waits for a keypress)        

REM             9600 is recommended connect baud rate.

REM             Hit a key when modems have connected.

REM             Problems? Email 'wormsmodem@team17.com'
REM             Or see the MODEMSUPPORT page on the Team17 Worm Web Pages.

REM ----------------------------------------------------------------------

REM             MODE-WORM! NOTES!

REM             TURN OFF ALL COMPRESSION!
REM             TURN OFF ALL ERROR CORRECTION!
REM             TURN OFF BUFFERS!
REM             TURN OFF FLOW CONTROL!
REM             USE DIRECT MODE IF APPLICABLE!


REM      \N1         ON MICROCOM 
REM      &F0&K0&Q0   ON HAYES  


REM HAYES:-

REM CALLER USES:
REM SET NETINFO=-M_DAT&F0&K0&Q0\R\2ATDT55555555555\R\0\2

REM RECEIVER USES:
REM SET NETINFO=-M_DAT&F0&K0&Q0\R\2ATA\R\0\2


REM MICROCOM:-

REM CALLER USES:
REM SET NETINFO=-M_DAT&F\\N1\R\2ATDT55555555555\R\0\2

REM RECEIVER USES:
SET NETINFO=-M_DAT&F\\N1\R\2ATA\R\0\2


