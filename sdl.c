#include"65.h"
#include"sdl.h"

void*sdl_thread(void*d)
{
	sdl_t*sdl=(sdl_t*)d;
	volatile int*halt=&sdl->halt;

	sdl->scr_rect=(SDL_Rect){.x=32,.y=0,.w=255,.h=240};
	//SDL_Rect scr_rect={.x=32,.y=0,.w=255,.h=240};

	SDL_Init(SDL_INIT_VIDEO);
	sdl->win = SDL_CreateWindow("window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		320,
		240,
 		SDL_WINDOW_RESIZABLE);

	sdl->s=SDL_CreateRGBSurface(0,256,240,32,0x000000ff,0x0000ff00,
		0x00ff0000,0xff000000);
	sdl->r=SDL_CreateRenderer(sdl->win,-1,0);
	SDL_SetRenderDrawColor(sdl->r,0,0,0,255);

	sdl_redraw(sdl->s,sdl->ram);

	// RENDER LOOP -----
	// Allow other thread to request quit
	while(*halt==0)
	{

		// Redraw screen
		sdl->t=SDL_CreateTextureFromSurface(sdl->r,sdl->s);
		SDL_RenderClear(sdl->r);
		SDL_RenderCopy(sdl->r,sdl->t,NULL,&sdl->scr_rect);
		SDL_RenderPresent(sdl->r);

		// EVENT LOOP -----
		//if(SDL_PollEvent(&sdl->e))
		if(SDL_WaitEvent(&sdl->e))
		{
			switch(sdl->e.type)
			{

			// Keyboard events
			case SDL_KEYDOWN:
				{
					SDL_KeyboardEvent k=*((SDL_KeyboardEvent*)&sdl->e);
					//printf("e.keysym.sym: 0x%04X\n",k.keysym.sym);

					//if(k.keysym.sym>=SDLK_a && k.keysym.sym<SDLK_a+26)
						//printf("key: %c (0x%02X)\n",
							//k.keysym.sym,k.keysym.sym);
					if(k.keysym.sym==SDLK_LEFT)
						sdl->joy->buttons.bits.left=1,
						puts("left");
					if(k.keysym.sym==SDLK_RIGHT)
						sdl->joy->buttons.bits.right=1,
						puts("right");
					if(k.keysym.sym==SDLK_UP)
						sdl->joy->buttons.bits.up=1,
						puts("up");
					if(k.keysym.sym==SDLK_DOWN)
						sdl->joy->buttons.bits.down=1,
						puts("down");

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
			//SDL_Delay(20);
			//usleep(20000);
		}
	}

quit:
	// Free memory
	sdl_del(sdl);
	return NULL;
}

void sdl_del(sdl_t*sdl)
{
	static int already=0;
	if(!already)
	{
		SDL_Quit();
		if(sdl->s)SDL_FreeSurface(sdl->s);
		if(sdl->r)SDL_DestroyRenderer(sdl->r);
		if(sdl->t)SDL_DestroyTexture(sdl->t);
		sdl->halt=1;
	}
	already=1;
}

void sdl_redraw(SDL_Surface*s,ram_t*ram)
{
	uint8_t*p=(uint8_t*)s->pixels;
	for(int i=0;i<(s->w*s->h);++i)
		p[i]=ram->ram[VRAM+i];
}
