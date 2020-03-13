#pragma once

//#define DO_NOT_USE_CURSES

#ifndef DO_NOT_USE_CURSES
#	include<ncurses.h>
#	define mvclr(y,x) do{move(y,x);clrtoeol();}while(0)
WINDOW*win;

#else
#	define printw printf
#endif
