#pragma once

#define PROG "65db"
#define STATUSLINE		22
#define TOPROWHEIGHT	7
#define LASTHEXOFFSET	(0x10000-TOPROWHEIGHT*8)

#include<ncurses.h>
#define mvclr(y,x) do{move(y,x);clrtoeol();}while(0)
//WINDOW*win;
