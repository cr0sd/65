#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

#define new(x) malloc(sizeof(x))

// Memory
#define VRAM	0x2000
#define PRGROM	0x8000
#define JOY1	0x4016
#define JOY2	0x4017

// Print error
void puterr(const char*msg,...);
