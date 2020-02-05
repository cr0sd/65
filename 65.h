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

// Print error
void puterr(const char*msg,...);
