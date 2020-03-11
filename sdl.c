#include"65.h"
#include"cpu.h"
#include"ram.h"
#include"rom.h"
#include"joy.h"
#include<SDL2/SDL.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();
	joy_t*joy=joy_init(JOYPREG,2);

	srand(time(NULL));

	SDL_Event e;
	SDL_Surface*s;
	SDL_Renderer*r;
	SDL_Texture*t;
	SDL_Rect scr_rect={.x=32,.y=0,.w=255,.h=240};

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window*window=
		SDL_CreateWindow("window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		320,
		240,
 		SDL_WINDOW_RESIZABLE);

	s=SDL_CreateRGBSurface(0,256,240,32,0x000000ff,0x0000ff00,
		0x00ff0000,0xff000000);
	r=SDL_CreateRenderer(window,-1,0);
	SDL_SetRenderDrawColor(r,0,0,0,255);

	// Randomize bmp
	{
		uint32_t*p=(uint32_t*)s->pixels;
		for(int i=0;i<(s->w*s->h);++i)
			p[i]=rand()|0xff000000;
	}

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		rom_map(rom,ram,PRGROM);
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=PRGROM;
	else
		puts("Failed to load ROM");

	if(!ram || !rom || !joy)puts("error"),exit(1);

	// Main loop
	for(;;)
	{
		joy_update_ram(joy,ram);
		cpu_exec(cpu,ram);

		// RENDER -----

		// Randomize bmp
		{
			uint8_t*p=(uint8_t*)s->pixels;
			for(int i=0;i<(s->w*s->h);++i)
				p[i]=ram->ram[VRAM+i];
		}

		// Redraw screen
		t=SDL_CreateTextureFromSurface(r,s);
		SDL_RenderClear(r);
		SDL_RenderCopy(r,t,NULL,&scr_rect);
		SDL_RenderPresent(r);

		SDL_WaitEvent(&e);

		// EVENT LOOP -----
		if(SDL_PollEvent(&e))
		{
			switch(e.type)
			{

			// Keyboard events
			case SDL_KEYDOWN:
				{
					SDL_KeyboardEvent k=*((SDL_KeyboardEvent*)&e);
					printf("e.keysym.sym: 0x%04X\n",k.keysym.sym);

					if(k.keysym.sym>=SDLK_a &&
						k.keysym.sym<SDLK_a+26)
						printf("key: %c (0x%02X)\n",
						k.keysym.sym,k.keysym.sym);

					if(k.keysym.sym==SDLK_ESCAPE)
					{
						puts("KEY_ESCAPE");
						goto quit;
					}
					break;
				}

			// Quit event
			case SDL_QUIT:
				goto quit;
			}
			SDL_Delay(20);
			//usleep(20000);
		}
		usleep(1);
	}

quit:
	// Free memory
	SDL_Quit();
	SDL_FreeSurface(s);
	SDL_DestroyRenderer(r);
	SDL_DestroyTexture(t);

	free(cpu);
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
	joy_del(joy);
	free(joy);
}

// Print formatted error message
void puterr(const char*fmt,...)
{
	va_list list;
	va_start(list,fmt);
	mvclr(STATUSLINE,0);
	mvprintw(STATUSLINE,0,PROG": ");
	attron(COLOR_PAIR(2));
	printw("Error: ");
	attron(COLOR_PAIR(1));
	vw_printw(win,fmt,list);
	va_end(list);
}
