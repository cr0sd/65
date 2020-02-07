#pragma once

#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

WINDOW*win;

#define PROG "65"
#define new(x) malloc(sizeof(x))

#define PRG_ROM_OFFSET 0x8000
#define STATUSLINE 20
#define LASTHEXOFFSET (0x10000-40)

// Print error
void puterr(const char*msg,...);
