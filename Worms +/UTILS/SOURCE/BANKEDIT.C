
/*************************************************************
 *  PROGRAME NAME ..... Bankedit                             *
 *                                                           *
 *  PROGRAM LANGUAGE .. C (using WATCOM C Compiler)          *
 *                                                           *
 *  PROGRAME PURPOSE .. To set up the sounds used in the     *
 *                      Worms Plus Pack                      *
 *                                                           *
 *  ASSOCIATED FILES .. menu config file (BANKEDIT.MNU)      *
 *                                                           *
 *  FOR ............... TEAM 17 Software Ltd                 *
 *                                                           *
 *  BY ................ Colin Surridge (Haircut)             *
 *                                                           *
 *  Date .............. 10/2/96                              *
 *                                                           *
 *************************************************************/


#include "dos.h"
#include "stdio.h"
#include <stdlib.h>
#include <ctype.h>
#include "malloc.h"
#include "conio.h"
#include "graph.h"
#include "string.h"
#include "io.h"
#include "direct.h"


#include "snddata.h"
#include "proto.typ"



/*******************************************
 * Routines                                *
 * --------                                *
 *                                         *
 * void  Main_loop(void)                   *
 * uint  Install_mouse(uint)               *
 * uint  Allocate_space(void)              *
 * uint  Setup_screen(uint)                *
 * uint  Load_menu_data(void)              *
 * int   Find_box(uchar *)                 *
 * uint  Get_menu_data(uchar *,uint)       *
 * void  Init_startup(void)                *
 * uint  Get_text_width(uchar *)           *
 * uint  Make_display_box(uchar *,uint)    *
 * void  Display_boxes(void)               *
 * int   Dump_text(uchar *,uint,uint,uint) *
 * uint  Set_display_box(uint)             *
 * void  Get_mouse(void)                   *
 * void  Do_action(void)                   *
 * void  Mouse_cursor_onoff(uint)          *
 * void  Get_path(void)                    *
 * void  Get_directory(uchar *,uint)       *
 * uint  Remake_current(void)              *
 * void  Grab_the_name(uchar *)            *
 * uint  Load_set(uchar *)                 *
 * ulong Get_long(void)                    *
 * uint  Load_sample(uchar *)              *
 * uint  Save_set(void)                    *
 * uint  Loaded(void)                      *
 * uint  Check_copy(uint)                  *
 * ulong Get_total(void)                   *
 * void Sort_directory(int , int)          *
 * int __far diskerrr(u ,u ,u far *)       *
 *******************************************/

/*************************************************************************
 * Globals                                                               *
 * -------                                                               *
 * Note: a 'u' before a char, short, int or long = unsigned              *
 *                                                                       *
 * menu_file                  - FILE *  used when loading the menu       *
 * load_file                  - FILE *  used when loading sound data     *
 * write_file                 - FILE *  used when saving sound data      *
 * screen_space               - uchar * used as a screen buffer          *
 * sound_offset_start[256]    - ulong   array of sound start positions   *
 * sound_offset_end[256]      - ulong   array of sound end positions     *
 * grab_name[13]              - uchar   used when making file names      *
 * sound_data                 - array   structure of sound info          *
 * colour_box                 - uchar   current colour of the box        *
 * colour_title               - uchar   current colour of the title      *
 * colour_normal              - uchar   current colour of standard text  *
 * colour_button              - uchar   current colour of the buttons    *
 * total_files_found          - uint    total of files in direvtory      *
 * directory_data[1000]       - array   structure of directory info      *
 * current_directory_position - uint    current position in directory    *
 * current_file[13]           - uchar   current file name                *
 * original_path[]            - uchar   store of path                    *
 * current_path[]             - uchar   current path                     *
 * show_path[31]              - uchar   used to show current path        *
 * current_slot               - uint    which file position hit          *
 * button_data[50]            - array   structure of button info         *
 * current_check              - uint    checksum of current sound sample *
 * total_buttons              - uint    total buttons found              *
 * box_data[256]              - array   structure of box/menu info       *
 * mouse_data                 - array   structure of mouse info          *
 * last_box									  - uint    last box found                   *
 * current_box                - uint    current box/menu displayed       *
 * menu_data[][]              - array   holds all the valid menu data    *
 * menu_data_total            - uint    total lines of valid data found  *
 * menu_buffer[200]           - uchar   work buffer                      *
 * total_sound_data           - ulong   total sound data stored          *
 * original_screen_mode       - uchar   the screen mode we were in before*
 * original_cursor_size       - uint    the type of cursor we had        *
 * box_positions[256]         - uint    where the menus start in the data*
 * box_total                  - uint    how many menus                   *
 * original_drive							- uint    original hard drive              *
 * current_drive              - uint    current paths hard drive         *
 * total_drives               - uint    total drives on the system       *
 * hard_err                   - uint    there has been a hardware error  *
 *************************************************************************/

struct SREGS sregs;
union REGS inregs, outregs;
struct find_t fileinfo;

uint hard_err;
FILE *menu_file;
FILE *load_file;
FILE *write_file;

uchar *screen_space;
ulong sound_offset_start[256];
ulong sound_offset_end[256];
uchar grab_name[13];

struct sound_info
{
	uchar *data;			// sound data
	ulong size;				// size of data
	uchar allocated;  // if 0 then never been allocated
	uchar change;     // 0 = changed
	uint  checksum;   // checksum of data
};
uchar colour_box;
uchar colour_title;
uchar colour_normal;
uchar colour_button;

struct sound_info sound_data[256];
uint total_files_found;

struct directory_info
{
	uchar name[13];   // name of file
	ulong size;       // size of file
	uchar type;       // type
};

struct directory_info directory_data[1000];

unsigned original_drive;
uint current_drive;
uint total_drives;

uint current_directory_position;
uchar current_file[13];
uchar original_path[PATH_MAX+1];
uchar current_path[PATH_MAX+1];
uchar show_path[31];
uint current_slot;

struct button_info
{
	uint y_pos;       // y (line) position
	uint x_pos;       // x (row)  position
	uint size;        // size in chars
	uint line;        // where to find it in the menu data
	uint check;				// 0 - no check
										// 1 - must have set loaded
};
uint current_check;

struct button_info button_data[50];
uint total_buttons;

struct box_info
{
	uint line;			  // where to find the box
	uint end;					// last line of box
	uint y_pos;				// y position
	uint x_pos;				// x position
	uint y_size;			// lines in box
	uint x_size;      // rows in box
	uint act_x;       // last active button x
	uint act_y;				// last active button y
	int  doubleclic;  // line number of double clic (-1 if not set)
	int  outside;			// the line of code if you click outside (-1 if not set)
	uint autoclose;		// if 1 then autoclose if left button not down
};

struct mouse_info
{
	uint x_pos;				// x position
	uint y_pos;       // y_position
	uint left;				// 0 = not pressed
	uint right;				// 0 = not pressed
	uint leftlast;    // 0 = not pressed last
};
struct mouse_info mouse_data;

struct box_info box_data[256];
uint last_box;
uint current_box;

uchar menu_data[MAX_LINES][120];
uint  menu_data_total;
uchar menu_buffer[200];
ulong total_sound_data;
uchar original_screen_mode;
uint  original_cursor_size;
uint  box_positions[256];
uint  box_total;

#include "routines.c"


/***********************************
 *            MAIN LOOP            *
 *            ---------            *
 *                                 *
 * Notes:                          *
 *                                 *
 * All variables and structures    *
 * will be in lowercase.           *
 *                                 *
 * All defines will be Uppercased  *
 * and can be found in 'snddata.h' *
 *                                 *
 * All routines will start with an *
 * uppercase character and will be *
 * prototyped in 'proto.typ'       *
 *                                 *
 *                                 *
 ***********************************/

void main(void)
{

	unsigned total;
	_harderr(diskerrr);
	Init_startup();			// setup init values

	if(Install_mouse(START)==BAD)
	{
		printf("\n\nI sad, I no find mouse driver, you install mouse driver then we play\n");
		exit(0);
	}


	if(Load_menu_data()==BAD) exit(0);

	if(Setup_screen(START)==BAD) exit(0);

	Main_loop();

	Install_mouse(STOP);
	Setup_screen(STOP);
	_dos_setdrive(original_drive,&total);
	chdir(original_path);
}





/******************************************
 * Name - Main_loop                       *
 *                                        *
 * Purpose:                               *
 * To monitor the mouse and keyboard      *
 * To control the flow of the editor      *
 *                                        *
 ******************************************/

void Main_loop(void)
{
	uint counter;
	current_box=0;
	Make_display_box("start",current_box++);

	while(current_box!=0)
	{
		for(counter=0;counter<current_box;counter++)
		{
			Set_display_box(counter);
		}
		Display_boxes();
		do
		{
			Get_mouse();
		}while(mouse_data.right==1);

		Mouse_cursor_onoff(ON);
		do
		{
			Get_mouse();
			if( (mouse_data.right==0) && (box_data[current_box-1].autoclose==1))
			{
				current_box--;
				break;
			}
		}while((mouse_data.left==0) && (mouse_data.right==0));
		Mouse_cursor_onoff(OFF);
		if((mouse_data.left!=0) || (mouse_data.right!=0) )Do_action();
	}
}


/******************************************
 * Name - Find_box                        *
 *                                        *
 * Purpose:                               *
 * To find the position number of a box   *
 *                                        *
 * Input  - string (i.e start)            *
 * Output - position No. in box_positions *
 *          -1 if not found               *
 ******************************************/
int Find_box(uchar *box_name)
{
	uint counter;
	int result=-1;

	for(counter=0;counter<box_total;counter++)
	{
		if(Get_menu_data(menu_data[box_positions[counter]],3)==BAD) return(result);
		if( (stricmp(menu_buffer,box_name))==0) result=counter;
	}
	return(result);
}


/***********************************
 * Name - Get_menu_data            *
 *                                 *
 * Purpose:                        *
 * To grab the next command or     *
 * text string                     *
 *                                 *
 * Input - string of data          *
 *       - position in string      *
 *                                 *
 * return - BAD no data found      *
 *        - uint position of last  *
 *          part of command found  *
 *        - command in menu_buffer *
 ***********************************/
uint Get_menu_data(uchar *string,uint position)
{
	uint string_size=strlen(string);
	char *white_space=" \n\t";    // setup up white space compare
	uint string_length;
	uchar text[3]={0x22,0x27,00};
	uint data;

	if(string_size<=position) return(BAD);
	position+=strspn(string+position,white_space);

	if(position>=string_size) return(BAD);
	data=string[position];

	if((data==';') || (data==0) ) return(BAD);
	if(strchr(text,data))
	{
		string_length=2+strcspn(string+position+1,text);
	}
	else
	{
		string_length=strcspn(string+position,white_space);
	}
	if((string_length<1) || ((string_length+position)>string_size)) return(BAD);
	strncpy(menu_buffer,string+position,string_length);
	menu_buffer[string_length]=0;
	return(position+string_length);
}


/*************************************
 * Name - Make_display_box           *
 *                                   *
 * Purpose:                          *
 * To get the data and put it in the *
 * box_data struct                   *
 *                                   *
 * Input - string (which box)        *
 *       - uint   (which store)      *
 *                                   *
 * Output - BAD failed               *
 *          GOOD ok                  *
 *************************************/
uint Make_display_box(uchar *box_name,uint box_store)
{
	int temp_x=0;
	int temp_y=0;
	int temp_x_size=0;
	int temp_y_size=0;
	int big_y_size=0;
	int big_x_size=0;
	int counter;
	int box_no=0;
	int position=0;
	int last_position=0;
	int in_position=0;
	uint result=GOOD;
	uint current_width=0;
	uchar box_title[90];
	uchar *sub_ptr;
	uint pozx;
	uint pozy;

	strcpy(box_title,box_name);

		// ****
		// * Look through data to see how long and wide it is
		// ****

	if( (box_no=Find_box(box_title))==-1) return(BAD);

	position=box_positions[box_no];
	box_data[box_store].line=position;
	box_data[box_store].autoclose=0;
	position++;	// move onto the first command


	while( ( (in_position=Get_menu_data(menu_data[position],0))!=BAD) && (result==GOOD) && (position<menu_data_total))
	{
		switch(0)
		{
			case 0:
			default:
				if(TEST("POSITION"))     //  is it the positional data
				{
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					if(	strnicmp(menu_buffer,"OLD",3)==0 )
					{
						if(box_store!=0) temp_x=box_data[box_store-1].act_x;
						if(menu_buffer[3]!=' ')
						{
							sub_ptr=menu_buffer+3;
							temp_x+=atoi(sub_ptr);
						}
					}
					else
					{
						temp_x+=atoi(menu_buffer);
					}
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					if(	strnicmp(menu_buffer,"OLD",3)==0 )
					{
						if(box_store!=0) temp_y=box_data[box_store-1].act_y;
						if(menu_buffer[3]!=' ')
						{
							sub_ptr=menu_buffer+3;
							temp_y+=atoi(sub_ptr);
						}
					}
					else
					{
						temp_y+=atoi(menu_buffer);
					}
					break;
				}
				if(TEST("DIRECTORY"))     // set up a directory
				{
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					Get_directory(menu_buffer,NEW);
					while((in_position=Get_menu_data(menu_data[position],in_position))!=BAD)
					{
						Get_directory(menu_buffer,EXTRA);
					}
					current_directory_position=0;
					break;
				}

				if(TEST("SIZE"))     			//  is it the size data
				{
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					{
						big_x_size=atoi(menu_buffer);
					}
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					{
						big_y_size=atoi(menu_buffer);
					}
					break;
				}

				if(TEST("BOX"))
				{
					last_position=position-1;
					position=menu_data_total;
					break;
				}
				if(TEST("AUTOCLOSE"))
				{
					box_data[box_store].autoclose=1;
					break;
				}
				if( TEST("BLANK") )
				{
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD)
					{
						temp_y_size++;
						current_width=0;
						break;
					}
					else
					{
						if( (counter=atoi(menu_buffer))>0)
						{
							if(current_width==0) temp_y_size++;
							current_width+=counter;
						}
					}
					break;
				}

				if( TEST("LINE"))
				{
					temp_y_size++;
					current_width=0;
					break;
				}

				if(TEST("TITLE"))
				{
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					current_width=Get_text_width(menu_buffer);
					if(temp_x_size<current_width) temp_x_size=current_width;
					current_width=0;
					temp_y_size++;
					break;
				}

				if( (TEST("TEXT")) || (TEST("ENTRY")) )
				{
					if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
					if(TEST("ADD"))
					{
						if(current_width!=0) temp_y_size--;
						if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
						switch(0)
						{
							case 0:
							default:
								if(  (TEST("CENTER")) || (TEST("RIGHT")) )
								{
									if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
									if(menu_buffer[0]!=0x27) return(BAD);
									current_width+=Get_text_width(menu_buffer);
									if(temp_x_size<current_width) temp_x_size=current_width;
									current_width=0;
									break;
								}
								if(menu_buffer[0]!=0x27) return(BAD);
								current_width+=Get_text_width(menu_buffer);
								break;
						}
						temp_y_size++;
						break;
					}
					if(  (TEST("CENTER")) || (TEST("RIGHT")) )
					{
						if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
						temp_y_size++;
						if(menu_buffer[0]!=0x27) return(BAD);
						current_width=Get_text_width(menu_buffer);
						if(current_width>temp_x_size) temp_x_size=current_width;
						current_width=0;
						break;
					}
					if( TEST("AT"))
					{
						if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
						pozx=atoi(menu_buffer);
						if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
						if(menu_buffer[0]!=0x27)
						{
							pozy=atoi(menu_buffer);
							if(pozy>big_y_size) big_y_size=pozy;
							if( (in_position=Get_menu_data(menu_data[position],in_position))==BAD) return(BAD);
						}
						if(menu_buffer[0]!=0x27) return(BAD);
						pozx+=Get_text_width(menu_buffer);
						if(pozx>big_x_size) big_x_size=pozx;
						break;
					}
					temp_y_size++;
					if(menu_buffer[0]!=0x27) return(BAD);
					current_width=Get_text_width(menu_buffer);
					break;
				}
				break;
		}
		if(current_width>temp_x_size) temp_x_size=current_width;
		position++;
		last_position++;

	}

	if( (temp_x_size==0) || (temp_y_size==0) ) return(BAD);
	temp_y_size+=2;
	temp_x_size+=2;
	if(temp_y_size<big_y_size) temp_y_size=big_y_size;
	if(temp_x_size<big_x_size) temp_x_size=big_x_size;
	if((temp_y<0)||(temp_y>24)) temp_y=0;
	if((temp_x<0)||(temp_x>79)) temp_x=0;
	if((temp_x_size>80)||(temp_y_size>25))
	{
		printf("x %d   y %d\n",temp_x_size,temp_y_size);
		getch();
		return(BAD);
	}
	if((temp_x+temp_x_size)>80) temp_x=80-temp_x_size;
	if((temp_y+temp_y_size)>25) temp_y=25-temp_y_size;

	if( ((temp_x_size+temp_x)>80)||((temp_y_size+temp_y)>25) )
	{
		printf("x %d   y %d\n",temp_x_size+temp_x,temp_y_size+temp_y);
		getch();
		return(BAD);
	}

	box_data[box_store].x_pos=temp_x;
	box_data[box_store].y_pos=temp_y;
	box_data[box_store].x_size=temp_x_size;
	box_data[box_store].y_size=temp_y_size;
	box_data[box_store].end=last_position-1;

	return(GOOD);
}




/*********************************
 * Name - Get_text_width         *
 *                               *
 * Purpose:                      *
 * To check a text string and    *
 * return its true width         *
 *                               *
 * Input  - string               *
 * Output - BAD not a text string*
 *        - size of text string  *
 *********************************/
uint Get_text_width(uchar *text_string)
{
	uint counter;
	uint total=0;
	uint text_size=strlen(text_string);

	for(counter=0;counter<text_size;counter++)
	{
		switch(text_string[counter])
		{
			case 39:     // '
				break;
			case  0:
				return(total);
				break;
			case '{':    // imb  command
				if((counter+1)==text_size) return(BAD);
				switch(text_string[counter+1])
				{
					case  'B':
					case  'F':
						if( (counter+3)>=text_size) return(BAD);
						counter+=3;
						break;
					case  'N':     // file name
						if( (counter+2)>=text_size) return(BAD);
						counter+=2;
						total+=12;
						break;
					case  'S':     // file size
						if( (counter+2)>=text_size) return(BAD);
						counter+=2;
						total+=10;
						break;
					case  'R':     // file size
						if( (counter+3)>=text_size) return(BAD);
						counter+=3;
						total+=10;
						break;
					case  'A':     // get special char
						if( (counter+4)>=text_size) return(BAD);
						counter+=4;
						total++;
						break;
					case  'T':     // total sound data
						if( (counter+1)>=text_size) return(BAD);
						counter++;
						total+=10;
						break;
					case  'C':     // total sound data
						if( (counter+1)>=text_size) return(BAD);
						counter++;
						total+=12;
						break;
					case  'P':     // total sound data
						if( (counter+1)>=text_size) return(BAD);
						counter++;
						total+=30;
						break;

					default:
						return(BAD);
						break;
				}
				break;
			default:
				total++;
				break;
		}
	}
	return(total);
}


/************************************
 * Name - Set_display_box           *
 *                                  *
 * Purpose:                         *
 * To get the display data          *
 * and put it in screen_space       *
 *                                  *
 * Input - uint (which box)         *
 *                                  *
 * Output - BAD failed              *
 *          GOOD ok                 *
 ************************************/
uint Set_display_box(uint box_store)
{
	int pozx,pozy;
	int xx=box_data[box_store].x_pos;
	int xxi=0;
	int yyi=0;
	int yy=box_data[box_store].y_pos;
	int xxs=box_data[box_store].x_size;
	int yys=box_data[box_store].y_size;
	int bstart=box_data[box_store].line;
	int bend=box_data[box_store].end;
	int counter;
	int counter1;
	int in_position=0;
	uint width=0;
	uchar text_colour;
	uchar filler[90];
	current_check=0;


	total_buttons=0;
	box_data[box_store].outside=-1;
	box_data[box_store].doubleclic=-1;

	if((box_store+1)>=current_box)
	{
		colour_box=BOX_COLOUR;
		colour_title=TITLE_COLOUR;
		colour_normal=NORMAL_COLOUR;
		colour_button=BUTTON_COLOUR;
	}
	else
	{
		colour_box=DEAD_BOX_COLOUR;
		colour_title=DEAD_TITLE_COLOUR;
		colour_normal=DEAD_NORMAL_COLOUR;
		colour_button=DEAD_BUTTON_COLOUR;
	}
	text_colour=colour_normal;

	for(counter=xx;counter<(xx+xxs);counter++)
	{
		for(counter1=yy;counter1<(yy+yys);counter1++)
		{
			*(screen_space+(counter*2)+(counter1*160))=' ';
			*(screen_space+(counter*2)+(counter1*160)+1)=text_colour;
		}
	}
	*(screen_space+(yy*160)+(xx*2))='Ú';
	*(screen_space+(yy*160)+(xx*2)+(xxs*2)-2)='¿';
	*(screen_space+(yy*160)+(xx*2)+(yys*160)+(xxs*2)-162)='Ù';
	*(screen_space+(yy*160)+(xx*2)+(yys*160)-160)='À';
	text_colour=colour_box;
	*(screen_space+(yy*160)+(xx*2)+1)=text_colour;
	*(screen_space+(yy*160)+(xx*2)+(xxs*2)-1)=text_colour;
	*(screen_space+(yy*160)+(xx*2)+(yys*160)+(xxs*2)-161)=text_colour;
	*(screen_space+(yy*160)+(xx*2)+(yys*160)-159)=text_colour;

	for(counter=xx+1;counter<xx+xxs-1;counter++)
	{
		*(screen_space+(yy*160)+(counter*2)+1)=text_colour;
		*(screen_space+(yy*160)+(counter*2)+(yys*160)-159)=text_colour;
		*(screen_space+(yy*160)+(counter*2))='Ä';
		*(screen_space+(yy*160)+(counter*2)+(yys*160)-160)='Ä';
	}
	for(counter=yy+1;counter<(yy+yys-1);counter++)
	{
		*(screen_space+(xx*2)+(counter*160)+1)=text_colour;
		*(screen_space+(xx*2)+(counter*160)+(xxs*2)-1)=text_colour;
		*(screen_space+(xx*2)+(counter*160))='³';
		*(screen_space+(xx*2)+(counter*160)+(xxs*2)-2)='³';
	}
	xx++;
	yy++;
	xxs-=2;
	yys-=2;

	while( ( (in_position=Get_menu_data(menu_data[++bstart],0))!=BAD) && (bstart<=bend))
	{
		switch(0)
		{
			case 0:
			default:

			if( TEST("IF"))
			{
				if( (in_position=Get_menu_data(menu_data[bstart],in_position))!=BAD)
				{
					if( TEST("FULL"))
					{
						current_check=1;
					}
				}
				break;
			}
			if(TEST("BOX"))
			{
				bstart=bend+1;
				break;
			}
			if( TEST("BLANK"))
			{
				if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD)
				{
					yyi++;
					xxi=0;
					break;
				}
				if( (counter=atoi(menu_buffer))>0)
				{
					if(xxi==0) yyi++;
					xxi+=counter;
				}
				break;
			}
			if( TEST("LINE"))
			{
				text_colour=colour_box;
				*(screen_space+((yy+yyi)*160)+(xx*2)-2)='Ã';
				*(screen_space+((yy+yyi)*160)+((xx+xxs)*2))='´';
				*(screen_space+((yy+yyi)*160)+(xx*2)-1)=text_colour;
				*(screen_space+((yy+yyi)*160)+((xx+xxs)*2)+1)=text_colour;
				for(counter=xx;counter<(xx+xxs);counter++)
				{
					*(screen_space+(counter*2)+((yy+yyi)*160))='Ä';
					*(screen_space+(counter*2)+((yy+yyi)*160)+1)=text_colour;
				}
				yyi++;
				xxi=0;
				break;
			}
			if(TEST("TITLE"))
			{
				text_colour=colour_title;
				xxi=0;
				if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
				width=Get_text_width(menu_buffer);
				memset(filler,32,80);
				filler[0]=0x27;
				filler[xxs+1]=0x27;
				filler[xxs+2]=0;
				Dump_text(filler,xx,yy+yyi,text_colour);
				xxi=(xxs-width)/2;
				xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour);
				xxi=0;
				yyi++;
				break;
			}
			if( TEST("OUTSIDE"))
			{
				box_data[box_store].outside=bstart;
				break;
			}
			if( TEST("DOUBLE"))
			{
				box_data[box_store].doubleclic=bstart;
				break;
			}
			if( TEST("TEXT"))
			{
				text_colour=colour_normal;
				if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
				if( TEST("AT"))
				{
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					pozx=atoi(menu_buffer);
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					if(menu_buffer[0]!=0x27)
					{
						pozy=atoi(menu_buffer);
						if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					}
					else
					{
						pozy=yyi-1;
					}
					Dump_text(menu_buffer,xx+pozx,yy+pozy,text_colour);
					break;
				}
				if(TEST("ADD"))
				{
					if(xxi!=0) yyi--;
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
				}
				else
				{
					xxi=0;
				}
				if(TEST("CENTER"))
				{
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					width=Get_text_width(menu_buffer);
					xxi+=( (xxs-xxi)-width)/2;
					xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour);
					xxi=0;
					yyi++;
					break;
				}
				if(TEST("RIGHT"))
				{
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					width=Get_text_width(menu_buffer);
					xxi=(xxs)-width;
					xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour);
					xxi=0;
					yyi++;
					break;
				}
				xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour)-xx;
				yyi++;
				break;
			}

			if( TEST("ENTRY"))
			{
				text_colour=colour_button;
				button_data[total_buttons].line=bstart;
				button_data[total_buttons].check=current_check;
				current_check=0;
				if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
				if( TEST("AT"))
				{
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					pozx=atoi(menu_buffer);
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					if(menu_buffer[0]!=0x27)
					{
						pozy=atoi(menu_buffer);
						if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					}
					else
					{
						pozy=yyi-1;
					}
					button_data[total_buttons].y_pos=yy+pozy;
					button_data[total_buttons].x_pos=xx+pozx;
					width=Get_text_width(menu_buffer);
					button_data[total_buttons++].size=width;
					Dump_text(menu_buffer,xx+pozx,yy+pozy,text_colour);
					break;
				}
				if(TEST("ADD"))
				{
					if(xxi!=0) yyi--;
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
				}
				else
				{
					xxi=0;
				}
				button_data[total_buttons].y_pos=yy+yyi;

				if(TEST("CENTER"))
				{
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					width=Get_text_width(menu_buffer);
					xxi+=( (xxs-xxi)-width)/2;
					button_data[total_buttons].x_pos=xx+xxi;
					button_data[total_buttons++].size=width;
					xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour);
					xxi=0;
					yyi++;
					break;
				}
				if(TEST("RIGHT"))
				{
					if( (in_position=Get_menu_data(menu_data[bstart],in_position))==BAD) return(BAD);
					width=Get_text_width(menu_buffer);
					xxi=xxs-width;
					button_data[total_buttons].x_pos=xx+xxi;
					button_data[total_buttons++].size=width;
					xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour);
					xxi=0;
					yyi++;
					break;
				}
				width=Get_text_width(menu_buffer);
				button_data[total_buttons].x_pos=xx+xxi;
				button_data[total_buttons++].size=width;
				xxi=Dump_text(menu_buffer,xx+xxi,yy+yyi,text_colour)-xx;
				yyi++;
				break;
			}
			break;
		}
	}
	return(GOOD);
}


/************************************
 * Name - Display_boxes()           *
 *                                  *
 * Purpose:                         *
 * To copy the memory screen to the *
 * real screen                      *
 ************************************/

void Display_boxes(void)
{
	uchar *video_mode;
	video_mode=(char *)0xb8000;
	memcpy(video_mode,screen_space,80*25*2);
}


/*********************************************
 * Name - Dump_text()                        *
 *                                           *
 * Purpose: To dump text to the screen_space *
 *          at the x & y co-ords in the text *
 *          colour supplied                  *
 *                                           *
 * Input - string (data to dump)             *
 *         text_x (x position)               *
 *         text_y (y position)               *
 *         colour (obvious)                  *
 *                                           *
 * Returns - text_x (the pos after the last) *
 *********************************************/
int Dump_text(uchar *string,uint text_x,uint text_y,uchar colour)
{
	uchar number;
	uchar data;
	uchar colour1=colour&0xf0;
	uint  counter;
	uchar text_data[35];
	string++;


	while((data=*(string))!=0x27)
	{
		switch(data)
		{
			case '{':
				data=*(++string);
				switch(data)
				{
					case 'B':   // background colour
						if(*(string+1)=='X')
						{
							colour&=15;
							colour+=colour_box&0xf0;
							string+=3;
							break;
						}
						if(*(string+1)=='T')
						{
							colour&=15;
							colour+=colour_title&0xf0;
							string+=3;
							break;
						}
						if(*(string+1)=='N')
						{
							colour&=15;
							colour+=colour_normal&0xf0;
							string+=3;
							break;
						}
						if(*(string+1)=='B')
						{
							colour&=0x0f;
							colour+=colour_button&0xf0;
							string+=3;
							break;
						}
						number=GETNUMBER2(string);
						if(number<16)
						{
							colour&=15;
							colour+=(number<<4);
						}
						string+=3;
						break;
					case 'F':   // get forground colour
						if(*(string+1)=='X')
						{
							colour&=0xf0;
							colour+=colour_box&0x0f;
							string+=3;
							break;
						}
						if(*(string+1)=='T')
						{
							colour&=0xf0;
							colour+=colour_title&0x0f;
							string+=3;
							break;
						}
						if(*(string+1)=='N')
						{
							colour&=0xf0;
							colour+=colour_normal&0x0f;
							string+=3;
							break;
						}
						if(*(string+1)=='B')
						{
							colour&=0xf0;
							colour+=colour_button&0x0f;
							string+=3;
							break;
						}
						number=GETNUMBER2(string);
						if(number<16)
						{
							colour&=0xf0;
							colour+=number;
						}
						string+=3;
						break;
					case 'A':   // get special char
						number=GETNUMBER3(string);
						*(screen_space+((text_x)*2)+(text_y*160))=number;
						*(screen_space+((text_x)*2)+(text_y*160)+1)=colour;
						string+=4;
						text_x++;
						break;

					case 'N':
						number=GETNUMBER1(string);
						string+=2;
						if((current_directory_position+number)>=total_files_found)
						{
							for(counter=0;counter<12;counter++)
							{
								*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
							}
							text_x+=12;
							break;
						}
						if(directory_data[current_directory_position+number].type!=NORMFILE)
						{
							colour1=(colour&0xf0)+4;
						}
						else
						{
							colour1=colour;
						}
						for(counter=0;counter<12;counter++)
						{
							*(screen_space+((counter+text_x)*2)+(text_y*160))=directory_data[current_directory_position+number].name[counter];
							*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour1;
						}
						text_x+=12;
						break;
					case 'S':
						number=GETNUMBER1(string);
						string+=2;
						if((current_directory_position+number)>=total_files_found)
						{
							for(counter=0;counter<10;counter++)
							{
								*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
							}
							text_x+=10;
							break;
						}
						if(directory_data[current_directory_position+number].type!=NORMFILE)
						{
							for(counter=0;counter<10;counter++)
							{
								*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
							}
							text_x+=10;
							break;
						}
						sprintf(text_data,"%7ld Kb",(directory_data[current_directory_position+number].size+1023)/1024);

						for(counter=0;counter<10;counter++)
						{
							*(screen_space+((counter+text_x)*2)+(text_y*160))=text_data[counter];
							*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
						}
						text_x+=10;
						break;
					case 'R':
						number=GETNUMBER2(string);
						string+=3;
						sprintf(text_data,"%ld Kb",(sound_data[number].size+1023)/1024);

						for(counter=0;counter<strlen(text_data);counter++)
						{
							*(screen_space+((counter+text_x)*2)+(text_y*160))=text_data[counter];
							*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
						}
						text_x+=strlen(text_data);
						break;
					case 'T':
						string++;
						sprintf(text_data,"%ld Kb",(total_sound_data+1023)/1024);
						if(total_sound_data>MAX_FILE_SIZE)
						{
							colour1=(colour&0x70)+0x84;
						}
						else
						{
							colour1=colour;
						}

						for(counter=0;counter<strlen(text_data);counter++)
						{
							*(screen_space+((counter+text_x)*2)+(text_y*160))=text_data[counter];
							*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour1;
						}
						text_x+=strlen(text_data);
						break;
					case 'C':
						string++;
						for(counter=0;counter<12;counter++)
						{
							*(screen_space+((counter+text_x)*2)+(text_y*160))=current_file[counter];
							*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
						}
						text_x+=12;
						break;
					case 'P':
						string++;
						Get_path();
						for(counter=0;counter<30;counter++)
						{
							*(screen_space+((counter+text_x)*2)+(text_y*160))=show_path[counter];
							*(screen_space+((counter+text_x)*2)+(text_y*160)+1)=colour;
						}
						text_x+=30;
						break;
					default:
						break;
				}
				break;
			default:
				*(screen_space+(text_x*2)+(text_y*160))=data;
				*(screen_space+(text_x*2)+(text_y*160)+1)=colour;
				text_x++;
				string++;
				break;
		}
	}
	return(text_x);
}


/************************************
 * Name - Do_action()               *
 *                                  *
 * Purpose - To check if the mouse  *
 *           was pointing at a      *
 *           button                 *
 *                                  *
 ************************************/
void Do_action(void)
{
	uint mx = mouse_data.x_pos;
	uint my = mouse_data.y_pos;
	uint mb;
	uint counter;
	uint box=current_box-1;
	int line_no=-1;
	uint in_position;
	unsigned total;
	uint drivet;



	if(mouse_data.left==1) mb=LEFT; else mb=RIGHT;
	if(mb==LEFT)
	{
		sound(440);
		delay(10);
		nosound();
		if(total_buttons!=0)
		{
			for(counter=0;counter<total_buttons;counter++)
			{
				if( (my==button_data[counter].y_pos) &&
						(mx>=button_data[counter].x_pos) &&
						(mx<(button_data[counter].x_pos+button_data[counter].size)) )
				{
					line_no=button_data[counter].line;
					break;
				}
			}
		}

		if(line_no!=-1)
		{
			if( (in_position=Get_menu_data(menu_data[line_no],0))==BAD) return;
			while(menu_buffer[0]!=0x27)
			{
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
			}
			Dump_text(menu_buffer,button_data[counter].x_pos,button_data[counter].y_pos,DEAD_BUTTON_COLOUR);
			box_data[box].act_x=button_data[counter].x_pos;
			box_data[box].act_y=button_data[counter].y_pos;
			Display_boxes();
			line_no++;
		}
	}

	do            // release button
	{
		Get_mouse();
	}while(mouse_data.left!=0);

	if(mb==LEFT)
	{
		if( (mx<box_data[box].x_pos) ||
				(mx>=(box_data[box].x_pos+box_data[box].x_size)) ||
				(my<box_data[box].y_pos) ||
				(my>=(box_data[box].y_pos+box_data[box].y_size)) )
		{
			line_no=box_data[box].outside;
		}
	}
	if((line_no==-1) && (total_buttons!=0))
	{
		for(counter=0;counter<total_buttons;counter++)
		{
			if( (my==button_data[counter].y_pos) &&
					(mx>=button_data[counter].x_pos) &&
					(mx<(button_data[counter].x_pos+button_data[counter].size)) )
			{
				line_no=button_data[counter].line+1;
				box_data[box].act_x=button_data[counter].x_pos;
				box_data[box].act_y=button_data[counter].y_pos;
				break;
			}
		}
	}
	if(line_no==-1) return;
	if( (in_position=Get_menu_data(menu_data[line_no],0))==BAD) return;
	if(mb==LEFT)
	{
		if( button_data[counter].check==1)
		{
			if((Loaded()&FULL)==0)
			{
				if((Make_display_box("errorfull",current_box++))==BAD) current_box--;
				return;
			}
		}

		if( (TEST("OUTSIDE")) || (TEST("ACTION")) )
		{
			if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
			if( TEST("COPY"))
			{
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
				counter=atoi(menu_buffer);
				if((current_directory_position+counter)>=total_files_found) return;
				if(directory_data[current_directory_position+counter].type==SUBDIRECT)
				{
					Grab_the_name(directory_data[current_directory_position+counter].name);
					if(chdir(grab_name)!=0) return;
					Remake_current();
					return;
				}
				if(directory_data[current_directory_position+counter].type==DRIVE)
				{
					drivet=directory_data[current_directory_position+counter].size;
					_dos_setdrive(drivet,&total);
					current_drive=drivet;
					Remake_current();
					return;
				}
				if((box_data[box].doubleclic!=-1) && (memcmp(current_file,directory_data[current_directory_position+counter].name,12)==0))
				{
					 line_no=box_data[box].doubleclic;
					 in_position=Get_menu_data(menu_data[line_no],0);
					 if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
				}
				else
				{
					memcpy(current_file,directory_data[current_directory_position+counter].name,12);
					return;
				}
			}
			if( TEST("QUIT"))
			{
				current_box=0;
				return;
			}
			if( TEST("CLOSE"))
			{
				current_box--;
				return;
			}
			if( TEST("OPEN"))
			{
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
				if((Make_display_box(menu_buffer,current_box++))==BAD) current_box--;
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))!=BAD)
				{
					current_slot=atoi(menu_buffer);
				}

				return;
			}

			if( TEST("INPUT"))
			{
				Get_input(box_data[box].act_x,box_data[box].act_y);
				return;
			}

			if( TEST("LOADALL"))
			{
				if(strcmp(current_file,"            ")==0) return;
				if((counter=Load_set(current_file))==GOOD)
				{
					current_box--;
					return;
				}
				if(counter==TOBIG)
				{
					if((Make_display_box("tobig",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==TOSMALL)
				{
					if((Make_display_box("tosmall",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==NOMEMORY)
				{
					if((Make_display_box("nomemory",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==NOTTHERE)
				{
					if((Make_display_box("notthere",current_box++))==BAD) current_box--;
					return;
				}
				return;
			}
			if( TEST("SAVEALL"))
			{
				if(strcmp(current_file,"            ")==0) return;
				if((counter=Save_set())==GOOD)
				{
					current_box--;
					return;
				}
				if(counter==TOBIG)
				{
					if((Make_display_box("savetobig",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==CANTCREATE)
				{
					if((Make_display_box("cannotcreate",current_box++))==BAD) current_box--;
					return;
				}
				return;
			}
			if( TEST("LOAD"))
			{
				if(strcmp(current_file,"            ")==0) return;
				if((counter=Load_sample(current_file))==GOOD)
				{
					current_box--;
					return;
				}
				if(counter==TOBIG)
				{
					if((Make_display_box("tobig",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==TOSMALL)
				{
					if((Make_display_box("tosmall",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==NOMEMORY)
				{
					if((Make_display_box("nomemory",current_box++))==BAD) current_box--;
					return;
				}
				if(counter==NOTTHERE)
				{
					if((Make_display_box("notthere",current_box++))==BAD) current_box--;
					return;
				}
				return;
			}

			if( TEST("BACK"))
			{
				if(chdir("..")!=0) return;
				Remake_current();
				return;
			}
			if( TEST("TOP"))
			{
				current_directory_position=0;
				return;
			}
			if( TEST("BOTTOM"))
			{
				if(total_files_found>10) current_directory_position=total_files_found-10; else current_directory_position=0;
				return;
			}
			if( TEST("MIDDLE"))
			{
				if(total_files_found>10) current_directory_position=total_files_found/2;
				return;
			}
			if( TEST("UP"))
			{
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
				counter=atoi(menu_buffer);
				if(current_directory_position>=counter) current_directory_position-=counter; else current_directory_position=0;
				return;
			}
			if( TEST("DOWN"))
			{
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
				counter=atoi(menu_buffer);
				if(total_files_found>10)
				{
					if((current_directory_position+counter+10)<total_files_found)
					{
						current_directory_position+=counter;
					}
					else
					{
						current_directory_position=total_files_found-10;
					}
				}
				return;
			}

		}
	}
	else
	{
		while( (in_position=Get_menu_data(menu_data[line_no],0))!=BAD)
		{
			if(TEST("HELP"))
			{
				if( (in_position=Get_menu_data(menu_data[line_no],in_position))==BAD) return;
				if((Make_display_box(menu_buffer,current_box++))==BAD) current_box--;
				return;
			}
			else
			{
				if( TEST("ACTION"))
				{
					line_no++;
				}
				else
				{
					return;
				}
			}
		}
	}

}




/*********************************
 * Name - Get Path               *
 *                               *
 * Purpose - to get the current  *
 * path and put what it can in   *
 * show_path                     *
 *********************************/
void Get_path(void)
{
	uchar *sub_ptr;
	uint number;

	memset(show_path,' ',30);

	if(getcwd(current_path,PATH_MAX)!=NULL)
	{
		if( (number=strlen(current_path))>30)
		{
			sub_ptr=current_path+number-30;
			*(sub_ptr)='.';
			*(sub_ptr+1)='.';
			memcpy(show_path,sub_ptr,30);
		}
		else
		{
			memcpy(show_path,current_path,number);
		}
	}
}


/***********************************************
 * Name - Get_directory                        *
 *                                             *
 * Purpose: To get the current                 *
 * directory and fill stuff with               *
 * it                                          *
 *                                             *
 * Input - spec = filetype (*.set)             *
 *         style - NEW (do directories as well *
 *                 EXTRA add to existing list  *
 ***********************************************/
void Get_directory(uchar *spec,uint style)
{
	int count;
	int current_dtotal=total_files_found;
	uchar tempname[13];

	if(style==NEW)
	{
		total_files_found=0;
		current_directory_position=0;
		memset(current_file,' ',12);
		for(count=1;count<total_drives+1;count++)
		{
			if((count!=current_drive) && (total_files_found<1000))
			{
				memset(directory_data[total_files_found].name,' ',12);
				directory_data[total_files_found].size=(ulong)count;
				sprintf(tempname,"[%c]",count+'A'-1);
				strncpy(directory_data[total_files_found].name,tempname,3);
				directory_data[total_files_found++].type=DRIVE;
			}
		}
		if(_dos_findfirst("*.*",_A_SUBDIR,&fileinfo)==0)
		{
			do
			{
				if(fileinfo.attrib==_A_SUBDIR)
				{
					if(strcmp(fileinfo.name,".")!=0)
					{
						memset(directory_data[total_files_found].name,' ',12);
						directory_data[total_files_found].size=fileinfo.size;
						strncpy(directory_data[total_files_found].name,fileinfo.name,strlen(fileinfo.name));
						directory_data[total_files_found++].type=SUBDIRECT;
					}
				}
			}while((_dos_findnext(&fileinfo)==0) && (total_files_found<1000));
			Sort_directory(0,total_files_found);
			current_dtotal=total_files_found;
		}
	}
	if(_dos_findfirst(spec,_A_NORMAL,&fileinfo)==0)
	{
		do
		{
			memset(directory_data[total_files_found].name,' ',12);
			directory_data[total_files_found].size=fileinfo.size;
			strncpy(directory_data[total_files_found].name,fileinfo.name,strlen(fileinfo.name));
			directory_data[total_files_found++].type=NORMFILE;
		}while(_dos_findnext(&fileinfo)==0);
		Sort_directory(current_dtotal,total_files_found);

	}
}

/*****************************************
 * Name - Sort_directory()               *
 *                                       *
 * Purpose: To sort the directory into   *
 *          order                      	 *
 *                                       *
 * Input: uint first (first pos in table)*
 *        uint last  (last pos in table) *
 *                                       *
 * Note: This is a slow sort method      *
 *****************************************/
void Sort_directory(int first, int last)
{
	uint count;
	uint changes;
	uchar dname[13];
	ulong dsize;
	uchar dtype;


	if((first+2)>last) return;
	last--;
	changes=1;
	while(changes!=0)
	{
		changes=0;
		for(count=first;count<last;count++)
		{
			if(memcmp(directory_data[count].name,directory_data[count+1].name,12)>0)
			{
				// swap them
				memcpy(dname,directory_data[count].name,13);
				dsize=directory_data[count].size;
				dtype=directory_data[count].type;
				memcpy(directory_data[count].name,directory_data[count+1].name,13);
				directory_data[count].size=directory_data[count+1].size;
				directory_data[count].type=directory_data[count+1].type;
				memcpy(directory_data[count+1].name,dname,13);
				directory_data[count+1].size=dsize;
				directory_data[count+1].type=dtype;
				changes++;
			}
		}
	}
}




/***************************************
 * Name - remake_current()             *
 *                                     *
 * To remake the current box           *
 *                                     *
 * output is the same as Make          *
 ***************************************/
uint Remake_current(void)
{
	uint in_position;

	if( (in_position=Get_menu_data(menu_data[box_data[current_box-1].line],0))==BAD) return(BAD);
	if( (in_position=Get_menu_data(menu_data[box_data[current_box-1].line],in_position))==BAD) return(BAD);
	return(Make_display_box(menu_buffer,current_box-1));
}

/**************************
 * Name - grab_the_name   *
 *                        *
 * Purpose: to get a file *
 * name/directore and     *
 * strip out the spaces   *
 **************************/
void Grab_the_name(uchar *string)
{
	int counter;
	memcpy(grab_name,string,12);
	for(counter=11;counter>=0;counter--)
	{
		if(grab_name[counter]==' ') grab_name[counter]=0; else break;
	}
}

/**************************
 * Name - Load_set()      *
 *                        *
 * Purpose - Load a set   *
 * into memory            *
 *                        *
 **************************/
uint Load_set(uchar *string)
{
	uint counter;
	long file_size;
	long check_size;
	uchar *loadset;
	long truecount;
	uint check_sum;


	Grab_the_name(string);
	if( (load_file=fopen(grab_name,"rb"))==NULL) return(NOTTHERE);
	if( (file_size=filelength(fileno(load_file)))==-1)
	{
		fclose(load_file);
		return(NOTTHERE);
	}
	if( file_size>(MAX_FILE_SIZE+5000) )
	{
		fclose(load_file);
		return(TOBIG);
	}
	if( file_size<2048)
	{
		fclose(load_file);
		return(TOSMALL);
	}
	if( (loadset=malloc(file_size-2048))==NULL)
	{
		fclose(load_file);
		return(NOMEMORY);
	}

	for(counter=0;counter<256;counter++)
	{
		sound_offset_start[counter]=Get_long();

	}
		sound_offset_start[69]=file_size-2048;
	for(counter=0;counter<256;counter++)
	{
		sound_offset_end[counter]=Get_long();
	}
	fread(loadset,1,file_size-2048,load_file);
	fclose(load_file);

	for(counter=0;counter<69;counter++)
	{
		if( (sound_offset_start[counter]>(file_size-2048)) || (sound_offset_end[counter]>(file_size-2048)) || (sound_offset_start[counter]>=sound_offset_end[counter]) )
		{
			if(sound_data[counter].allocated!=0)
			{
				free((void *)sound_data[counter].data);
				sound_data[counter].allocated=0;
			}
			if( (sound_data[counter].data=malloc(4))==NULL)
			{

				free((void *)loadset);
				return(NOMEMORY);
			}
			sound_data[counter].allocated=1;
			sound_data[counter].change=0;
			sound_data[counter].size=4;
			sound_data[counter].checksum=0;
			*(sound_data[counter].data)=0;
			*(sound_data[counter].data+1)=0;
			*(sound_data[counter].data+2)=0;
			*(sound_data[counter].data+3)=0;
		}
		else
		{
			if(sound_data[counter].allocated!=0)
			{
				free((void *)sound_data[counter].data);
				sound_data[counter].allocated=0;
			}
			check_size=sound_offset_end[counter]-sound_offset_start[counter];
			if( (sound_data[counter].data=malloc(check_size))==NULL)
			{
				free((void *)loadset);
				return(NOMEMORY);
			}
			sound_data[counter].allocated=1;
			sound_data[counter].change=0;
			memcpy(sound_data[counter].data,loadset+sound_offset_start[counter],check_size);
			sound_data[counter].size=check_size;
			check_sum=0;
			for(truecount=0;truecount<check_size;truecount++)
			{
				check_sum+=*(sound_data[counter].data+truecount);
			}
			sound_data[counter].checksum=check_sum;
		}
	}
	free((void *)loadset);
	total_sound_data=Get_total();
	return(GOOD);
}



/**************************
 * Name - Load_sample()   *
 *                        *
 * Purpose - Load a sample*
 * into memory            *
 *                        *
 **************************/
uint Load_sample(uchar *string)
{
	long counter;
	long file_size;
	long check_size;
	uchar *temp_alloc;
	long truecount;
	uint check_sum;


	Grab_the_name(string);

	if( (load_file=fopen(grab_name,"rb"))==NULL) return(NOTTHERE);
	if( (file_size=filelength(fileno(load_file)))==-1)
	{
		fclose(load_file);
		return(NOTTHERE);
	}
	if( file_size>MAX_FILE_SIZE )
	{
		fclose(load_file);
		return(TOBIG);
	}
	check_size=file_size;

	if(strstr(string,".RAW")==NULL)
	{
		// load as a sample in a set
		if( file_size<2048)
		{
			fclose(load_file);
			return(TOSMALL);
		}

		for(counter=0;counter<256;counter++)
		{
			sound_offset_start[counter]=Get_long();

		}
		sound_offset_start[69]=file_size-2048;
		for(counter=0;counter<256;counter++)
		{
			sound_offset_end[counter]=Get_long();
		}
		if((sound_offset_start[current_slot]>(file_size-2048)) || (sound_offset_end[current_slot]>(file_size-2048)) || (sound_offset_start[current_slot]>=sound_offset_end[current_slot]) )
		{
			if(sound_data[current_slot].allocated!=0)
			{
				free((void *)sound_data[current_slot].data);
				sound_data[current_slot].allocated=0;
			}
			if( (sound_data[current_slot].data=malloc(4))==NULL)
			{
				fclose(load_file);
				return(NOMEMORY);
			}
			sound_data[current_slot].allocated=1;
			sound_data[current_slot].size=4;
			sound_data[current_slot].checksum=0;
			*(sound_data[current_slot].data)=0;
			*(sound_data[current_slot].data+1)=0;
			*(sound_data[current_slot].data+2)=0;
			*(sound_data[current_slot].data+3)=0;
			sound_data[current_slot].change=1;
			fclose(load_file);
			return(GOOD);
		}

		if(sound_offset_start[current_slot]!=0)
		{
			for(counter=0;counter<sound_offset_start[current_slot];counter++)
			{
				fgetc(load_file);
			}
		}

		check_size=sound_offset_end[current_slot]-sound_offset_start[current_slot];
	}

	if( (temp_alloc=malloc(check_size))==NULL)
	{
		fclose(load_file);
		return(NOMEMORY);
	}
	if(fread(temp_alloc,1,check_size,load_file)!=check_size)
	{
		free((void *)temp_alloc);
		fclose(load_file);
		return(BAD);
	}
	fclose(load_file);

	if(sound_data[current_slot].allocated!=0)
	{
		free((void *)sound_data[current_slot].data);
		sound_data[current_slot].allocated=0;
	}
	if( (sound_data[current_slot].data=malloc(check_size))==NULL)
	{
		free((void *)temp_alloc);
		return(NOMEMORY);
	}
	sound_data[current_slot].allocated=1;
	memcpy(sound_data[current_slot].data,temp_alloc,check_size);
	check_sum=0;
	for(truecount=0;truecount<check_size;truecount++)
	{
		check_sum+=*(sound_data[current_slot].data+truecount);
	}
	sound_data[current_slot].checksum=check_sum;



	sound_data[current_slot].size=check_size;
	sound_data[current_slot].change=1;
	free((void *)temp_alloc);
	total_sound_data=Get_total();
	return(GOOD);
}


/******************************
 * Name - Save_set()          *
 *                            *
 * Purpose: save all the data *
 ******************************/
uint Save_set(void)
{
	ulong startpos=0;
	uint  data1;
	uint first_part;
	uint res;


	total_sound_data=Get_total();

	if(total_sound_data>MAX_FILE_SIZE) return(TOBIG);
	Grab_the_name(current_file);
	if( (write_file=fopen(grab_name,"wb"))==NULL) return(CANTCREATE);

	for(first_part=0;first_part<256;first_part++)
	{
		res=Check_copy(first_part);
		if( (res==999) || (res>first_part))
		{
			sound_offset_start[first_part]=startpos;
			startpos+=sound_data[first_part].size;
			sound_offset_end[first_part]=startpos;
		}
		else
		{
			sound_offset_start[first_part]=sound_offset_start[res];
			sound_offset_end[first_part]=sound_offset_end[res];
		}
	}

	for(first_part=0;first_part<256;first_part++)
	{
		startpos=sound_offset_start[first_part];
		data1=startpos&0xff;
		fputc(data1,write_file);
		data1=(startpos&0xff00)>>8;
		fputc(data1,write_file);
		data1=(startpos&0xff0000)>>16;
		fputc(data1,write_file);
		data1=(startpos&0xff000000)>>24;
		fputc(data1,write_file);
	}
	for(first_part=0;first_part<256;first_part++)
	{
		startpos=sound_offset_end[first_part];
		data1=startpos&0xff;
		fputc(data1,write_file);
		data1=(startpos&0xff00)>>8;
		fputc(data1,write_file);
		data1=(startpos&0xff0000)>>16;
		fputc(data1,write_file);
		data1=(startpos&0xff000000)>>24;
		fputc(data1,write_file);
	}
	startpos=0;
	for(first_part=0;first_part<69;first_part++)
	{
		if(sound_offset_end[first_part]>startpos)
		{
			fwrite(sound_data[first_part].data,1,sound_data[first_part].size,write_file);
			startpos=sound_offset_end[first_part];
		}
		sound_data[first_part].change=0;
	}
	fclose(write_file);
	return(GOOD);
}

/************************************
 * Name - diskerrr()                *
 *                                  *
 * Purpose: To trap hardware errors *
 *                                  *
 * sets the var hard_err to 1       *
 ************************************/

int __far diskerrr(unsigned devt,unsigned errt, unsigned far *dev)
{
	hard_err=1;
	return(_HARDERR_IGNORE);
}





