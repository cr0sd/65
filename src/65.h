#pragma once

#include"config.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

#define PROG "65"
#define new(x) malloc(sizeof(x))

#define STATUSLINE		22
#define TOPROWHEIGHT	7
#define LASTHEXOFFSET	(0x10000-TOPROWHEIGHT*8)

// Memory
#define VRAM	0x6000
#define PRGROM	0x8000
#define JOYPREG	0x4016

// Print error
void puterr(const char*msg,...);
