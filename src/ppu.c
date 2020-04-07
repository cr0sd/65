#include"ppu.h"
#include"sdl.h"
#include"ram.h"
#include<stdlib.h>

// Create PPU & state
ppu_t*ppu_init(uint32_t w,uint32_t h)
{
	ppu_t*ppu=malloc(sizeof(ppu_t));

	ppu->pixels=malloc(w*h*4);
	ppu->w=w;
	ppu->h=h;

	ppu->vid=sdl_init(ppu);
	if(!ppu->vid)puts("error: PPU video failed to initialize");

	memset(ppu->pixels,0,ppu->w*ppu->h*4);

	return ppu;
}

// Free PPU state
void ppu_del(ppu_t*ppu)
{
	sdl_del(ppu->vid);
	if(ppu->pixels)free(ppu->pixels);
	if(ppu->vid)free(ppu->vid);
	ppu->pixels=NULL;
}

// Update PPU software pixel buffer
void ppu_update(ppu_t*ppu,ram_t*ram)
{
	for(int i=0;i<512;++i)
	{
		if(ram->ram[i]>3)continue;

		// Draw one of four palette colors specified in VRAM
		ppu->pixels[i]=*((uint32_t*)(ram->ram+0x3f00+ram->ram[VRAM+i]));
	}

	sdl_update(ppu->vid,ppu);
}
