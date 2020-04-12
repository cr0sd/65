#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h>

#define new(x) malloc(sizeof(x))

// Memory
#define VRAM	0x2000
#define PPUTMAP	0x0200	// Tile map (256 bytes)
#define PPUTILE	0x0300	// Tile page (240 bytes)
#define PRGROM	0x8000

// Peripheral Hardware RAM registers
#define OAMDMA	0x4014
#define JOY1	0x4016
#define JOY2	0x4017

// Print error
void puterr(const char*msg,...);
