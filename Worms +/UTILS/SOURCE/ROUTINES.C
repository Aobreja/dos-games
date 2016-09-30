/***********************************
 * Name - Allocate_space()         *
 *                                 *
 * Purpose:                        *
 * To allocate all the space that  *
 * will be required by the editor  *
 *                                 *
 * Returns - BAD not enough memory *
 *           GOOD no problems      *
 *                                 *
 ***********************************/

uint Allocate_space(void)
{
	if( (screen_space=malloc(25*80*2))==NULL) return(BAD);


	return(GOOD);
}



/*************************************
 * Name - Install_mouse(opt)         *
 *                                   *
 * Purpose:                          *
 * To install or deinstall the mouse *
 *                                   *
 * opt - START install mouse driver  *
 *     - STOP  de-install mouse      *
 *                                   *
 * Returns - BAD no mouse            *
 *           GOOD found mouse        *
 *************************************/

uint Install_mouse(uint opt)
{
	int installed = 0;


	if(opt==START)
	{
    inregs.w.ax = 0;
    int386 (0x33, &inregs, &outregs);
		if( (outregs.w.ax != 0xffff))
		{
			return(BAD);
		}
		else
		{
			return(GOOD);
		}
	}
	return(GOOD);
}

/*************************************
 * Name - Get_mouse()                *
 *                                   *
 * Purpose - Get mouse data and fill *
 *           structure               *
 *                                   *
 *************************************/
void Get_mouse(void)
{


	inregs.w.ax = 3;
	int386(0x33,&inregs,&outregs);
	mouse_data.x_pos=(outregs.w.cx)/8;
	mouse_data.y_pos=(outregs.w.dx)/8;
	mouse_data.left=(outregs.w.bx)&1;
	mouse_data.right=((outregs.w.bx)&2)>>1;
}

/*************************************
 * Name - Mouse_Cursor_onoff()       *
 *                                   *
 * Purpose - to turn the cursor on   *
 *           and off                 *
 *                                   *
 * Input - ON/OFF                    *
 *************************************/
void Mouse_cursor_onoff(uint type)
{
	inregs.w.ax = type;
	int386(0x33,&inregs,&outregs);
	mouse_data.leftlast=0;
}





/**************************************
 * Name - Setup_screen(opt)           *
 *                                    *
 * Purpose: (opt = START)             *
 * To record the current screen mode  *
 * To change the screen mode          *
 * To display the initial screen      *
 *                                    *
 * Purpose: (opt = STOP)              *
 * To return the screen to its former *
 * mode                               *
 *                                    *
 * Returns - BAD errors in changing   *
 *           GOOD all ok              *
 **************************************/

uint Setup_screen(opt)
{
	if(opt==START)
	{
		// get the original screen mode
		inregs.w.ax = 0x0f00;
    int386 (0x10, &inregs, &outregs);
		original_screen_mode = outregs.h.al;

		// now change to 80x40 16 colour (mode 3)

    inregs.h.ah = 0x00;
		inregs.h.al = 0x3;
		int386( 0x10, &inregs, &outregs );

		// get the original cursor size

		inregs.w.ax = 0x300;
		inregs.w.bx = 0x0000;
    int386 (0x10, &inregs, &outregs);
		original_cursor_size = outregs.w.cx;

		// now kill the cursor

		inregs.w.ax = 0x100;
		inregs.w.cx = 0x2000;
    int386 (0x10, &inregs, &outregs);


		return(GOOD);
	}

	if(opt==STOP)
	{
		// restore original mode

    inregs.h.ah = 0x00;
		inregs.h.al = original_screen_mode;
		int386( 0x10, &inregs, &outregs );

		// restore the cursor

		inregs.w.ax = 0x100;
		inregs.w.cx = original_cursor_size;
    int386 (0x10, &inregs, &outregs);
		return(GOOD);
	}
	return(GOOD);
}




/*******************************************
 * Name - Load_menu_data                   *
 *                                         *
 * Purpose:                                *
 * To load the menu file and strip out all *
 * the comments                            *
 *                                         *
 * Returns - BAD an error occured          *
 *           GOOD no problems              *
 *******************************************/

uint Load_menu_data(void)
{
	uint counter=0;
	uint counter1=0;
	uint white_space_size;
	uchar character;
	char *white_space=" \n\t";    // setup up white space compare
	int  menu_buffer_size;

			// ****
			// * Open the menu file
			// ****

	if((menu_file=fopen("BANKEDIT.MNU","r"))==NULL)
	{
		printf("ERROR - Could not open menu file 'test.mnu'\n ");
		return(BAD);
	}

			// ****
			// * store the menu file in memory and remove white space and comments
			// ****

	while (fgets(menu_buffer,199,menu_file) != NULL)
	{
		white_space_size=strspn(menu_buffer,white_space);
		menu_buffer_size=strlen(menu_buffer)-white_space_size;

		if( (menu_buffer_size)>3 && (menu_buffer[white_space_size]!=';'))
		{
			strncpy(menu_data[counter],menu_buffer+white_space_size,menu_buffer_size);
			menu_data[counter++][menu_buffer_size]=0;
		}
		if(counter>=MAX_LINES)
		{
			printf("ERROR - Menu file 'test.mnu' is to big\n");
			fclose(menu_file);
			return(BAD);
		}
	}
	fclose(menu_file);
	if(counter<2) return(BAD);    // not enough data

			// ****
			// * make a list of all the BOX positions
			// ****

	menu_data_total=counter;
	counter1=0;
	for(counter=0;counter<menu_data_total;counter++)
	{
		Get_menu_data(menu_data[counter],0);
		if( stricmp("BOX",menu_buffer)==0)
		{
			box_positions[counter1++]=counter;
		}
	}
	box_total=counter1;
	return(GOOD);
}




/***********************************
 * Name - Init_startup             *
 *                                 *
 * Purpose:                        *
 * To initialise all the startup   *
 * values                          *
 *                                 *
 ***********************************/
void Init_startup(void)
{
	uint counter;

	if(getcwd(original_path,PATH_MAX)==NULL)
	{
		printf("ERROR - problem with getcwd command\n");
		exit();
	}



	if(Allocate_space()==BAD)
	{
		printf("\n\nSorry I require more memory to run\n");
		exit(0);
	}
	for(counter=0;counter<256;counter++)
	{
		sound_offset_start[counter]=0;
		sound_offset_end[counter]=0;
		sound_data[counter].allocated=0;
		sound_data[counter].checksum=0;
		sound_data[counter].change=0;
		box_data[counter].line=0;
		box_data[counter].y_pos=0;
		box_data[counter].x_pos=0;
		box_data[counter].y_size=0;
		box_data[counter].x_size=0;
		box_data[counter].act_x=0;
		box_data[counter].act_y=0;
		box_data[counter].outside=-1;
		box_data[counter].autoclose=0;
		box_data[counter].doubleclic=-1;
		sound_data[counter].size=0;
		sound_data[counter].data=0;
	}
	for(counter=0;counter<50;counter++)
	{
		button_data[counter].y_pos=0;
		button_data[counter].x_pos=0;
		button_data[counter].size=0;
		button_data[counter].line=0;
		button_data[counter].check=0;
	}
	current_check=0;
	total_buttons=0;
	menu_data_total=0;
	total_sound_data=0;
	box_total=0;
	last_box=0;
	for(counter=0;counter<(80*25*2);counter+=2)
	{
		*(screen_space+counter)=' ';
		*(screen_space+counter+1)=0;
	}

}



/**************************************
 * Name Loaded()                      *
 *                                    *
 * Purpose - to see if a set has been *
 *           loaded                   *
 *                                    *
 * Return  - FULL    = loaded         *
 *           CHANGED = a file changed *
 *           EMPTY   = no files loaded*
 **************************************/
uint Loaded(void)
{
	uint counter;
	uint changes=0;
	uint loads=0;
	uint result=0;
	for(counter=0;counter<69;counter++)
	{
		changes+=sound_data[counter].change;
		loads+=sound_data[counter].allocated;
	}
	if(loads==69) result+=FULL;
	if(changes!=0) result+=CHANGED;
	return(result);
}

/*************************************************
 * Name Check_copy()                             *
 *                                               *
 * Purpose: To check if samples have the same    *
 *				  data. If they do return sample number*
 *          or 999 if not                        *
 *************************************************/
uint Check_copy(uint sample)
{
	uint count2;
	uint check_sum;       // checksum compare
	ulong check_size;      // size compare
	ulong counts;
	uchar *check_ptr;
	uint diff=999;

	if(sound_data[sample].allocated==1)
	{
		check_sum=sound_data[sample].checksum;
		check_size=sound_data[sample].size;
		check_ptr=sound_data[sample].data;

		for(count2=0;count2<69;count2++)
		{
			if( (check_sum==sound_data[count2].checksum) && (check_size==sound_data[count2].size) && (sound_data[count2].allocated==1) && (check_size>4) && (count2!=sample))
			{
				// ok all the check seem correct SO FAR
				// check to see if same actual sample
				for(counts=0;counts<check_size;counts++)
				{
					if( *(check_ptr+counts)!=*(sound_data[count2].data+counts))
					{
						break;
					}
				}
				if(counts==check_size)
				{
					diff=count2;
					break;
				}
			}
		}
	}
	return(diff);
}

/*******************************
 * Name - Get_total()          *
 *                             *
 * Purpose: To return the total*
 *          set size           *
 *******************************/
ulong Get_total(void)
{
	ulong running_total=0;
	uint count;
	uint res;
	for(count=0;count<69;count++)
	{
		res=check_copy(count);
		if((res==999) || (res>count))
		{
			running_total+=sound_data[count].size;
		}
	}
	return(running_total);
}



/*******************************
 * name - Get_input(button)    *
 *                             *
 * Purpose: To get a File name *
 *******************************/
void Get_input(uint x,uint y)
{
	int count=0;
	int key;
	int counter;
	char filename[13];
	char filecopy[13];
	char *datain="QWERTYUIOPLKJHGFDSAZXCVBNM_1234567890~!$@";
	while(kbhit()!=0)
	{
		getch();
	}

	strcpy(filecopy,".SFX        ");
	for(counter=0;counter<12;counter++)
	{
		*(screen_space+((counter+x)*2)+(y*160))=filecopy[counter];
		*(screen_space+((counter+x)*2)+(y*160)+1)=15;
	}
	Display_boxes();

	filename[0]=0;
	while((key=getch())!=13)
	{
		key=toupper(key);
		if((key==0x8) && (count>0))
		{
			filename[--count]=0;
		}
		if((strchr(datain,key)!=NULL) && (count!=8))
		{
			filename[count++]=key;
			filename[count]=0;
		}
		strcpy(filecopy,filename);
		strncat(filecopy,".SFX        ",12-strlen(filename));
		for(counter=0;counter<12;counter++)
		{
			*(screen_space+((counter+x)*2)+(y*160))=filecopy[counter];
			*(screen_space+((counter+x)*2)+(y*160)+1)=15;
		}
		Display_boxes();
	}
	memcpy(current_file,filecopy,12);
}

/***********************
 * Name - Get_long()   *
 *                     *
 * Purpose: read a long*
 * from a file         *
 ***********************/
ulong Get_long(void)
{
	ulong read_long;
	ulong read_store;
	read_long=fgetc(load_file);
	read_store=fgetc(load_file);
	read_long+=read_store<<8;
	read_store=fgetc(load_file);
	read_long+=read_store<<16;
	read_store=fgetc(load_file);
	read_long+=read_store<<24;
	return(read_long);
}
