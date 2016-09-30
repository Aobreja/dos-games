DUNE 2000: LONG LIVE THE FIGHTERS!

LATE BREAKING NEWS

Copyright (c) 1998 Westwood Studios, Inc.
All rights reserved.

"Westwood Studios" is a trademark of Westwood Studios, Inc.
"Dune" is a trademark and copyright of the Dino DeLaurentis Corporation.
Licensed by Universal Studios Licensing, Inc.  All rights reserved.

August 8, 1998

For latest goodies, news and updates visit WWW.WESTWOOD.COM


Contents:

1. General Information.

	1.1.	Microsoft DirectX.

2.	Troubleshooting.

	2.1.	Known Video Card Problems
		2.1.1. Error Message "Set Cooperative Level Returned - 2005532097"
		2.1.2. Display only appears in top 1/3rd of screen.
		2.1.3. Video Flicker during play.
		2.1.4. "Scratchy" or distorted display.
	2.2.	Known Sound Card Problems
	2.3.	Install Problems.
		2.3.1.	Lockup during "Registering Dune 2000 and creating shortcuts in Start Menu"
		2.3.2.	Lockup while "Installation Complete" is displayed.
	2.4.	Uninstalling Dune 2000.
	2.5.	Virtual Memory Settings.
	2.6.	Microsoft PowerToys.
	2.7.	Microsoft Home Mouse and Natural Keyboard.
	2.8.	Autoplay.
	2.9.	16 bit CD-ROM drivers.
	2.10.	Microsoft Office Toolbar.
	2.11.	Game or audio stutters after being paused.
	2.12.	Choppy movie performance.
	2.13.	Increasing performance on minimum spec systems.
	2.14.	Westwood Online.
		2.14.1.	Duplicate Channel columns.
		2.14.2. 4 Player Internet Games
	2.15.	Multi-player problems.
	2.16.	Power Saving Modes.
	2.17.	HP Pavilion Computers..
		2.17.1.	Background Applications
		2.17.2.	LT Win Modem
	2.18.	Game Updates and Patches.
	2.19.	Playing Without a Dune 2000 CD (spawning).


3.  Gameplay Notes

	3.1. 	Infantry Only Areas
  	3.2. 	Capturing Enemy Buildings - Part I
  	3.3. 	Capture Enemy Buildings - Part II
  	3.4. 	Spice controls the universe
  	3.5. 	Keep an eye out!
  	3.6. 	Turrets
  	3.7. 	Infantry
  	3.8. 	Use your strengths
	3.9.	Deviators
	3.10. 	Hot keys
	3.11	Multiplayer Handicapping

4.  Unit Comparisons


1. General Information.

	1.1. Microsoft DirectX.

The Windows 95 version of Dune 2000 is a Microsoft DirectX application. Version 5.0a of  
Microsoft DirectX is included on the CD and you have the option to install it when Dune 2000 is 
installed.

If you have difficulty running Windows 95 after these new Microsoft DirectX drivers have been 
installed, please contact your local Microsoft subsidiary, or write:

	Microsoft Customer Sales and Service,
	One Microsoft Way,
	Redmond, WA 98052-6399, USA

	USA telephone: 1-800-426-9400
	International telephone: ++1-206-882-8080

All Microsoft DirectX drivers are located in the Dxsetup folder off of the root of the CD. To 
reinstall the Microsoft DirectX drivers go into the Dxsetup folder and run Dxsetup.exe. You can 
explore the CD by choosing the "Explore the CD" option in the Autoplay title screen.

Microsoft DirectX Direct Play.

If you already have DirectX version 5.0 installed and did not install the DirectX drivers from the 
Dune 2000 CD please ensure you install the Direct Play 5.0a patch from the Dxsetup folder off of 
the root of the CD. This patches some bugs in the original Direct Play 5.0 release and will not 
affect any other products you may have that use Directx.

2. Troubleshooting.

	2.1.  Known Video Card Problems.

Most video display problems can be corrected by installing the latest drivers for your particular 
card. Please consult your video card documentation for details on how to get the latest drivers for 
your card. Here are some hints and tips for specific video cards found while testing Dune 2000 
under Windows 95 and Windows 98.

		2.1.1. Error Message "Set Cooperative Level Returned - 2005532097"

This message will appear on older video cards that do not support hardware page flipping. To 
solve the problem create a shortcut and add the option "-f" to the command line. A shortcut is 
created by right clicking on the Dune2000 program icon and selecting "Create Shortcut". 
Right click on the shortcut and select "Properties". Click on the end of the "target" line and 
add the new command line option.

		2.1.2. Display only appears in top 1/3rd of screen.

If this happens please add the "-g" option to the command line for Dune 2000. Please refer to 
2.1.1 for details on how to do this.

		2.1.3. Video Flicker during play

If the video display flickers during the game every 20 seconds or so then this can be 
prevented by adding "-f" to the command line for Dune 2000. Please refer to 2.1.1 for details 
on how to do this
.
		2.1.4. "Scratchy" or distorted display.
			
If the video display looks scratchy and there is no static image then please use the "-g" 
command line to fix this. You can also make sure that the driver for your monitor is correct as 
the monitor being incorrectly set for display modes it cannot handle causes this problem.

	2.2  Known Sound Card Problems

Crystal PnP Audio System on Dell Dimension XPS R400
The factory sound card settings on this system appear to be incompatible with Dune 2000, which 
will drop back to the Windows desktop, sometimes with a dialog stating, "Unable to create Direct 
Sound object". We have found that the following adjustments allow Dune 2000 to work perfectly 
on this system:

Open the Control Panel under Settings on the Start menu.
Open the Multimedia applet
Click the Audio tab
Select CS4236/37/38 as the Preferred Device
Check the "Use Only Preferred Devices" option.
Close the Multimedia applet and the Control Panel. 

	2.3.  Install Problems

		2.3.1.  Lockup during "Registering Dune 2000 and creating shortcuts in Start Menu"

Should the install program lockup while registering the Dune 2000 application then you may 
want to run the install program with the "-a" option. However this means that to play Internet 
games you must register the WOLAPI.DLL manually. The easiest way to do this is to go to 
start -> find and find the file regsvr32.exe. Then open the folder containing the Westwood 
Internet components, the default is c:\westwood\internet. Drag the wolapi.dll onto the 
regsvr32.exe icon. Wolapi.dll will now be registered.

		2.3.2 Lockup while "Installation complete" is displayed.

If the message "Installation complete" does not go away and closing the window produces the 
error "Setup is incomplete ..." please restart the setup application with the command switch "-
b". To do this go to start->run, click browse and then locate the Dune 2000 CD. The setup.exe 
is on the root of the CD. Click OK and then add " -b" to the end of the line. It would look like 
this if your CDROM is your D: drive : "d:\setup.exe -b".

	2.4.  Uninstalling Dune 2000.

After running the Uninstall program, if the Dune 2000 group is still present, try rebooting your 
computer. This should clean up the Dune 2000 start menu folder.

	2.5.  Virtual Memory Settings.

Dune 2000 may need to use more RAM than is present on your system. Windows 95 
automatically takes care of this by using what is known as "Virtual Memory" - it uses space on 
your hard disk to simulate the memory it needs and swaps data back and forth from your hard disk 
as required. Windows 95 allows you to manually set the amount of hard drive space it uses for 
Virtual Memory: WE HIGHLY RECOMMEND THAT YOU DO NOT DO THIS! To let 
Windows 95 manage the Virtual Memory, go to the Windows 95 START menu, select 
SETTINGS\CONTROL PANEL, then double-click SYSTEM, click PERFORMANCE\FILE 
SYSTEM\VIRTUAL MEMORY and then select "Let Windows manage my virtual memory 
settings (recommended)".

	2.6.  Microsoft PowerToys.

If you have the Microsoft PowerToys system extensions installed on your system (including 
QuickRes and FlexiCD) you may experience excessive accessing of the CD followed by system 
lockup. If this happens, you should remove the Microsoft PowerToys while playing Dune 2000.

	2.7.  Microsoft Home Mouse and Natural Keyboard.

If you are using a Microsoft Home Mouse, the Microsoft Natural Keyboard or are using 
Microsoft's IntelliPoint Tools and Controls Software, having the "Sonar" setting on under 
"Visibility" in the "Mouse Properties" section in the "Control Panel" can cause Dune 2000 to 
crash.  Please turn this setting off when playing Dune 2000. Using the 'point' feature of the 
Microsoft keyboard may cause mouse trails to be left on screen. Do not use this feature while 
playing Dune 2000.

	2.8. Autoplay.

If your CD does not Autoplay when inserted in the drive, you may have this feature disabled. To 
Enable Autoplay, right click on 'My Computer' and select 'Properties' then 'Device Manager'. 
Select your CD-ROM drive and click 'Properties'. Select 'Settings' and check the 'Auto insert 
notification' box.

	2.9. 16 bit CD-ROM drivers.

Dune 2000 may fail to start if there is a 16 bit CD-ROM driver loaded from the 
AUTOEXEC.BAT or CONFIG.SYS. If you have references to MSCDEX or equivalent drivers 
then try removing them from your autoexec.bat and config.sys files. Windows 95 does not 
generally need these drivers to work and in most cases will actually perform better without them.

	2.10. Microsoft Office Toolbar.

If you make use of this feature of Microsoft Office and it appears over the game screen when 
playing Dune 2000 then you will have to disable the Office Toolbar before playing.

	2.11.  Game or audio stutters after being paused.

If the game is left in the paused state with the game options menu up for an extended period of 
time, performance may be reduced for a while after play is resumed. This is due to Windows 95 
giving the game's resources to other tasks while it is not being played.

A possible symptom of poor video performance is that of the video freezing. If the video freezes 
the game has not crashed, just hit ESC to skip the movie. Try adjusting the settings cache settings 
and updating the video drivers to solve the freezing.

	2.12. Choppy movie performance.

If you find that the movie performance is choppy or jerky, try reducing the Windows 95 CD 
caching by going to the Start/Settings/Control Panel and double-clicking the System applet. In the 
System Properties dialog, click the Performance tab and then click the File System button. From 
the File System Properties dialog, click the CD-ROM tab and note the Supplemental Cache Size 
setting (so that you can reset the cache size if need be). Now set the Supplemental Cache Size to 
Small. This should have a marked effect on movie performance.

	2.13. Increasing performance on minimum spec systems.

If you are playing Dune 2000 on a minimum spec. system, we recommend playing the game in 8 
bit mode, by selecting the option on the main menu, or by starting the game with the 8 bit icon in 
the start menu.

You may also be able to improve performance by turning off in-game music scores. To do this, go 
to the in game options menu (select the options tab) and go to the sound controls section. Move 
the music volume slider all the way to the left to disable in-game music.

Another option that sometimes speeds the game up, depending on the video card, is to use the "-f" 
command switch. Please see section 2.1.1 for details on how to do this.

	2.14. Westwood Online.

		2.14.1. Duplicate Channel names columns.

We have found that certain versions of COMCTL32.DLL (the Windows common controls 
library which handles standard Windows interface elements) do not support certain 
Westwood Online features, which is most obvious in the user/channel list area when you will 
see repeated columns (e.g., you see each channel name listed twice). The solution to this is to 
update your COMCTL32.DLL and one way to do this is to install Microsoft Internet Explorer 
version 3.02 or above. Alternatively, checkout Microsoft's web site at 
http://www.microsoft.com.

		2.14.2.  4 Player Internet Games

If you are playing more than 2 player internet games, we strongly recommend that you have a 
Pentium 200 or higher, as performance will be greatly improved.  Playing in 8 bit will also 
help.

		2.14.3.  Modem Problems

During multiplayer games if you recieve excessive pauses or messages telling you that the 
game is trying to reconnect it is possible that your modem and computer are not 
communicating effectively. Sometimes this is due to the modem to computer speed being set 
too high. Setting this to 56K rather than 112K on some machines will help a lot.


	2.15.  Multi-player problems
	
If you experience disconnects while playing multi-player games or that games do not appear in the 
multi-player lobbies both on internet and local area networks please ensure you installed the 
Direct Play 5.0a patch from the Dxsetup folder off of the root of the CD. This patches some bugs 
in the original Direct Play 5.0 release and will not affect any other products you may have that use 
DirectX. You do not need to do this if you installed Direct X 5.0 from the Dune 2000 CD as it is 
done automatically.


	2.16.  Power Saving Modes.

It is possible that your computer loses connection to your ISP due to long periods of inactivity. 
Sometimes this is caused by the sleep mode in your "Power Saving" options. This can cause 
problems during gameplay or when connected to Westwood Online. To avoid any problems 
please make sure that your screen saver or power-saving modes are set to enable after long delay 
times.

	2.17.  HP Pavallion Computers.

We have found a number of problems whilst testing Dune 2000 on HP Pavallion Computers all of 
these can be fixed by adjusting user settings. We also saw a dramatic speed improvement when 
playing under Windows 98 rather than Windows 95 on these machines.

		2.17.1.	Background Applications
Like all games, especially ones that can play over the internet, Dune 2000 puts a lot of 
demand upon your HP Pavallion Computer. Please close all tasks that are running in the 
background especially Find Fast and Media Indexer. Control panels for both these 
applications can be found in Start -> Settings -> Control Panel. Switch both to off. We have 
found cases where these applications launched every hour and this would cause a dramatic 
loss of performance when playing Dune 2000.

		2.17.2.	LT Win Modem
If you experience excessive pauses during Please make sure you have the latest LT Win 
Modem drivers from http://www.hp.com . We have also found that for best performace 
during modem play or Internet play the HP Pavallion should be set to communicate to the LT 
Win Modem at 56K. To set this use Start -> Settings -> Control Panel -> Modems. Open the 
modems control panel by double clicking, select the modem, then click properties then set 
maximum speed to 57600. 

	2.18.	   Game Updates And Patches.
		
Dune 2000 contains an auto updating feature. Updated versions of the game will be announced to 
you when playing Dune 2000 on Westwood Online. When an updated version of the game is 
available you will be able to receive it and automatically have it installed, if you wish. If you do 
not intend to play Dune 2000 on Westwood Online then please check 
HTTP://www.westwood.com for update information.

	2.19.	   Playing Without a Dune 2000 CD (spawning).
	
It is possible to join a network game if you do not have a Dune 2000 CD in your drive but you 
have installed the game. You do need a CD however to play an Internet, Practice or the Campaign 
game. Please do not remove the CD when Dune 2000 is playing a mission, as this will cause the 
game to fail.

					
3. Gameplay Notes.
 
	3.1 Infantry Only Areas

There are some areas on the battlefield that only infantry can pass.  When you have only infantry 
selected, you will get a blue "move" cursor to indicate that you can move your infantry into and 
through that area.  Vehicles will get a "no move" cursor.

	3.2 Capturing Enemy Buildings - Part I

Capturing enemy buildings will sometimes provide the ability to build structures or units not 
otherwise available.  Capturing an enemy's Construction Yard will allow you to build that side's 
Palace and, in the case of the Atreides, the High Tech Factory (to generate Ornithopters).  To 
acquire enemy units, you need to capture an enemy's Heavy Factory, and have all the prerequisite 
buildings.

For example, if you capture an Atreides Construction Yard, you will be able to build an Atreides 
High Tech Factory, which allows you to build Ornithopters.  You can also, if you have the 
appropriate prerequisite buildings, build an Atreides Palace, and create Fremen.

If you capture an Atreides Heavy Factory, and already have the prerequisite buildings, you will be 
able to build the Sonic Tank.

One exception to this rule: capturing the Emperor's construction yard will not allow you to build 
the Emperor's palace.

	3.3 Capture Enemy Buildings - Part II

Once you capture a building, if there is space, you can build concrete inside your enemy's base.  
This provides a very potent method of harassing an opponent (AI and Human).  Because there is 
no way of telling what concrete is 'owned' by you, once somebody builds concrete inside your 
base, the only way to prevent him from building in your base is to quickly destroy the concrete he 
has built.  Here are some suggestions to counter this tactic:

Pay attention and keep engineers out!  Siege Tanks, Trikes, and infantry are effective guards 
against a sneak attack.

If somebody captures a building in your base, notice where it is, and destroy it quickly!  If any 
new concrete springs up, destroy it!  It is very easy to destroy concrete, but not all weapons work 
well against it.  Siege Tanks and Trikes can destroy concrete quickly.

Early in the game, build concrete around the critical areas of your base.  This will prevent people 
from taking a remote building, and quickly building concrete into key areas of your base.  If 
you've already built concrete, your enemy can't!

If you don't have time to destroy the concrete, a last resort is to spread out units in areas you think 
your opponent might build.  You can't build on top of an enemy unit!  This will buy you time to 
destroy the concrete later.

	3.4 Spice controls the universe

To make sure that money is always available place your refineries as close to the spice as possible 
without exposing them to the enemy, always try to use carryalls when the spice is further away. 
The optimum is two harvesters per refinery anymore and they have to wait too long to unload. 

	3.5 Keep an eye out!

Use scouts and the radar outpost to spot attacks on your harvesters early so you can get them back 
to your base or get some units out to defend them. Using the outpost to spot units early also comes 
in useful when the AI is using Saboteurs, as you can catch them before they cloak.

In the later missions make sure you have infantry scattered around your base as they have the 
ability to reveal stealth units such as Fremen or Saboteurs. Be careful squishing Sardaukar - they 
will damage tanks as they run them over by exploding.

	3.6 Turrets

Using gun and rocket turrets in clusters is also a valid tactic, if your turrets are spread out along walls 
the AI will be able to concentrate against one at a time. Turrets are very effective except against 
infantry. When you have a cluster of turrets you should support them with Siege Tanks. Turrets and 
infantry are particularly effective against Deviators as they do not effect them. Turrets can be 
outranged by Siege Tanks and Missile Tanks, so you will need to keep a reserve to deal with this 
problem.

	3.7 Infantry

Standing troopers on infantry rock can be a useful tactic against most units except siege tanks and 
light infantry. It is probably best to run infantry away from siege tanks as they will annihilate 
them. Placing turrets near infantry rock and using them along with infantry can be very effective. 

	3.8 Use your strengths

All units have their weaknesses as well as strengths so exploit them. For example, Devastators are 
vulnerable to Rocket Tanks that are constantly moving; Quads are particularly weak against 
Troopers. Also, each side has strengths and weaknesses. The Harkonnen are very powerful but 
slow, Atreides are average whereas the Ordos are quick but weak.

	3.9 Deviators 

If a unit becomes deviated, control can be regained by firing at that unit. Each time the deviated 
unit is damaged the remaining time until the player regains control is reduced. This means it is 
best to attack it with weapons that fire rapidly but do little damage. Sonic tanks can be very 
effective against Deviators, but they need to be used in pairs.

	3.10 Hot keys

You can switch your cursor to the 'repair' cursor automatically by pressing "t" - and similarly, you 
can switch to the 'sell' cursor by pressing "y."  In the heat of battle, this can be extremely helpful.  
Also, if you right click on the up and down arrows, the icons will move an entire screen upward or 
downward, which can save time in finding the unit or structure you want to build.

You can use the function keys to communicate with other players during the multiplayer games. 
F1 through F5 sends messages to individual users, F6 sends a message to everyone, F7 responds 
to a Westwood Online page and F8 enables or disables incoming pages.

	3.11 Multiplayer Handicapping

In multiplayer games, it is possible to give yourself or your opponent an advantage through Dune 
2000's handicapping system.  This system provides a way for players of different skill levels to be 
able to enjoy games together on a more equal footing.  In the multiplayer game setup screen, each 
player has an icon next to the user name with either one, two or three stars.  This icon describes 
the handicap level of the player.  The handicap effects the prices of buildings and units in the 
game.  One star means that player has a price advantage compared to the default setting of two 
stars.  Three stars increases prices over the default.  Only the host of a multiplayer game can 
change player's handicap levels - but each player must approve the settings before the host can 
launch the game.



4. Unit Comparisons

Unit 				Side 		Armor		Health 	Cost 	Tech
---------			--------	--------	------	----	----
Light Inf 			All 		Infantry	600 	50 	1
Trooper 			All	 	Infantry	700 	90 	3
Engineer 			All 		Infantry	500 	400 	4
Thumper 			All 		Infantry 	375 	200 	7
Sardaukar 			Emperor 	Infantry 	1000 	120 	6
Fremen 				Atreides 	Infantry 	700 	N/A 	7
Saboteur 			Ordos 		Infantry 	400 	N/A 	6
Harvester 			All 		Heavy 		4500 	1200 	1
Trike 				Atr. & Hark. 	None 		900 	300 	2
Raider 				Ordos 		None 		1000 	350 	2
Quad 				All 		Light 		1100 	400 	3
Atr. Combat Tank 		Atreides 	Heavy 		2100 	700 	4
Hark. Combat Tank 		Harkonnen 	Heavy 		2700 	700 	4
Ord. Combat Tank 		Ordos 		Heavy 		1800 	700 	4
MCV 				All 		Light 		4500 	2000 	4
Missile Tank 			Atr. & Hark.	None 		1300 	900 	5
Siege Tank 			All 		Light 		1200 	700 	6
Sonic Tank 			Atreides 	Light 		3000 	1000 	7
Devastator Tank 		Harkonnen 	Heavy 		5000 	1050 	7
Deviator 			Ordos 		None 		1100 	1000 	7
Carryall 			All	 	Light		4800 	1100 	5
Ornithopter 			Atreides 	Light 		900 	N/A 	7

Note - cost is at medium difficulty level.
