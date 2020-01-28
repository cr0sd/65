#pragma once
//#include"cpu.h"
//#include"ram.h"
//#include"rom.h"

#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

#define PROG "65"
#define new(x) malloc(sizeof(x))

#define PRG_ROM_OFFSET 0x8000

void puterr(const char*msg,...);
