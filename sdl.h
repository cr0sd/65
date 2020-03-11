#include"65.h"
#include"cpu.h"
#include"ram.h"
#include"rom.h"
#include"joy.h"
#include<SDL2/SDL.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct sdl_t
{
	SDL_Window*win;
	SDL_Event e;
	SDL_Surface*s;
	SDL_Renderer*r;
	SDL_Texture*t;
	SDL_Rect scr_rect;

	ram_t*ram;
	joy_t*joy;
	int halt;
} sdl_t;

void sdl_del(sdl_t*sdl);
void sdl_redraw(SDL_Surface*s,ram_t*ram);
void*sdl_thread(void*d);
