#define uchar unsigned char
#define uint  unsigned short
#define ulong unsigned long



#define FULL 1
#define EMPTY 0
#define CHANGED 2

#define START 0
#define STOP  1

#define ON 1
#define OFF 2

#define RIGHT 0
#define LEFT  1

#define SUBDIRECT  0
#define NORMFILE   1
#define DRIVE      2


#define NEW 0
#define EXTRA 1

#define DEAD_TITLE_COLOUR  0x08
#define TITLE_COLOUR       0x0f

#define DEAD_NORMAL_COLOUR 0x07
#define NORMAL_COLOUR      0x0e

#define DEAD_BUTTON_COLOUR 0x48
#define BUTTON_COLOUR      0x4e

#define DEAD_BOX_COLOUR    0x78
#define BOX_COLOUR         0x1f


#define BAD 0
#define GOOD 1
#define TOBIG 2
#define NOTTHERE 3
#define NOMEMORY 4
#define TOSMALL 5
#define CANTCREATE 6

#define MAX_LINES 2000

#define MAX_FILE_SIZE 758*1024
#define COLOUR_DIR 2
#define COLOUR_BOX_INACTIVE 2
#define COLOUR_BOX_ACTIVE 2
#define COLOUR_BOX_BACKGROUND 2
#define COLOUR_SCREEN_BACKGROUND 2


#define TEST(a)	stricmp(menu_buffer,a)==0
#define	GETNUMBER2(a)  ( ((*((a)+1)-'0')*10)+*((a)+2)-'0')
#define	GETNUMBER3(a)  ( ((*((a)+1)-'0')*100)+((*((a)+2)-'0')*10)+*((a)+3)-'0' )
#define GETNUMBER1(a)  ( *((a)+1)-'0')

