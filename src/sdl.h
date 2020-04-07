#pragma once
#include<SDL2/SDL.h>
//#include"ppu.h"

struct ppu_t;
typedef struct ppu_t ppu_t;

typedef struct sdl_t
{
	SDL_Window*w;
	SDL_Event e;
	SDL_Renderer*r;
	SDL_Texture*t;
	int quit;
}sdl_t;

sdl_t*sdl_init(ppu_t*ppu);
void sdl_del(sdl_t*sdl);
void sdl_update(sdl_t*sdl,ppu_t*ppu);
