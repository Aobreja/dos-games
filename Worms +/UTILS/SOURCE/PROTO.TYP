/****************************************************
 * This file contains all the prototype information *
 ****************************************************/
void main(void);
void Main_loop(void);
uint Install_mouse(uint opt);
uint Allocate_space(void);
uint Setup_screen(uint opt);
uint Load_menu_data(void);
int  Find_box(uchar *box_name);
uint Get_menu_data(uchar *string,uint position);
void Init_startup(void);
uint Get_text_width(uchar *text_string);
uint Make_display_box(uchar *box_name,uint box_store);
void Display_boxes(void);
int  Dump_text(uchar *string,uint text_x,uint text_y,uint colour);
uint Set_display_box(uint box_store);
void Get_mouse(void);
void Do_action(void);
void Mouse_cursor_onoff(uint type);
void Get_path(void);
void Get_mouse(void);
void Get_directory(uchar *spec,uint stlye);
uint Remake_current(void);
void Grab_the_name(uchar *string);
uint Load_set(uchar *string);
ulong Get_long(void);
uint Load_sample(uchar *string);
uint Save_set(void);
uint Loaded(void);
uint Check_copy(uint);
ulong Get_total(void);
void Sort_directory(int first, int last);
int __far diskerrr(unsigned ,unsigned ,unsigned far *);

















