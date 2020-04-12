#pragma once
#include"ram.h"
#include"sdl.h"
#include<stdint.h>

typedef struct ppu_t
{
	uint32_t w;
	uint32_t h;
	uint32_t*pixels;
	uint32_t*pal;
	void*vid;		// Video display implementation
}ppu_t;

ppu_t*ppu_init(uint32_t w,uint32_t h);
void ppu_del(ppu_t*ppu);
void ppu_update(ppu_t*ppu,ram_t*ram);
