#pragma once

#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

WINDOW*win;

#define PROG "65"
#define new(x) malloc(sizeof(x))
#define mvclr(y,x) do{move(y,x);clrtoeol();}while(0)

#define STATUSLINE		21
#define TOPROWHEIGHT	7
#define LASTHEXOFFSET	(0x10000-TOPROWHEIGHT*8)

// Memory
#define VRAM	0x6000
#define PRGROM	0x8000

// Print error
void puterr(const char*msg,...);
