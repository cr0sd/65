#include"65.h"
#include"sdl.h"

// Pthread thread callback
void*sdl_thread(void*d)
{
	sdl_t*sdl=(sdl_t*)d;

	sdl->scr_rect=(SDL_Rect){.x=32,.y=0,.w=255,.h=240};
	//SDL_Rect scr_rect={.x=32,.y=0,.w=255,.h=240};

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	sdl->win = SDL_CreateWindow("window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		320,
		240,
 		SDL_WINDOW_SHOWN);

	sdl->s=SDL_CreateRGBSurface(0,256,240,32,0x000000ff,0x0000ff00,
		0x00ff0000,0xff000000);
	sdl->r=SDL_CreateRenderer(sdl->win,-1,0);
	SDL_SetRenderDrawColor(sdl->r,0x10,0x10,0x10,255);

	sdl->i=SDL_AddTimer(10,sdl_timer_cb,sdl);

	//sdl_redraw(sdl);

	// RENDER LOOP -----
	// Allow other thread to request quit
	while(!sdl->halt)
	{

		// Redraw screen
		sdl_redraw(sdl);
		//sdl->t=SDL_CreateTextureFromSurface(sdl->r,sdl->s);
		SDL_RenderClear(sdl->r);
		//SDL_RenderCopy(sdl->r,sdl->t,NULL,&sdl->scr_rect);
		//SDL_RenderPresent(sdl->r);


		// Check keyboard state
		{
			uint8_t*kb;
			kb=(int8_t*)SDL_GetKeyboardState(NULL);

			if(kb[SDL_SCANCODE_Z])
				printf("A\tjoy:%02X\n",sdl->ram->ram[JOYPREG]);

			if(kb[SDL_SCANCODE_X])
				printf("B\tjoy:%02X\n",sdl->ram->ram[JOYPREG]);

			if(kb[SDL_SCANCODE_A])
				printf("Start\tjoy:%02X\n",sdl->ram->ram[JOYPREG]);

			sdl->joy->buttons.bits.left=(kb[SDL_SCANCODE_LEFT]!=0);
			sdl->joy->buttons.bits.right=(kb[SDL_SCANCODE_RIGHT]!=0);
			sdl->joy->buttons.bits.up=(kb[SDL_SCANCODE_UP]!=0);
			sdl->joy->buttons.bits.down=(kb[SDL_SCANCODE_DOWN]!=0);

			sdl->joy->buttons.bits.a=(kb[SDL_SCANCODE_Z]!=0);
			sdl->joy->buttons.bits.b=(kb[SDL_SCANCODE_X]!=0);
			sdl->joy->buttons.bits.start=(kb[SDL_SCANCODE_A]!=0);
			sdl->joy->buttons.bits.select=(kb[SDL_SCANCODE_S]!=0);
			if(kb[SDL_SCANCODE_S])
				printf("Select\tjoy:%02X\n",sdl->ram->ram[JOYPREG]);
		}

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
	sdl_halt(sdl,1);
	sdl_del(sdl);
	return NULL;
}

void sdl_del(sdl_t*sdl)
{
	static int already=0;
	if(!already)
	{
		if(sdl->i)SDL_RemoveTimer(sdl->i);
		if(sdl->s)SDL_FreeSurface(sdl->s);
		if(sdl->r)SDL_DestroyRenderer(sdl->r);
		if(sdl->t)SDL_DestroyTexture(sdl->t);
		if(sdl->win)SDL_DestroyWindow(sdl->win);
		sdl_halt(sdl,1);
		SDL_Quit();
		already=1;
		//puts("SDL_Quit");
	}
}


/*--- sdl_redraw(sdl)                           ---*/
// We want to draw the screen in RAM at location VRAM
// as a 256x240 pixel (32x30 [8x8] sprite) resolution
// screen

void sdl_redraw(sdl_t*sdl)
{
	volatile uint32_t*p=(uint32_t*)sdl->s->pixels;

	//for(int i=0;i<(sdl->s->w*sdl->s->h);++i)	// W x H
	//for(int i=0;i<0x4000;++i)					// 1 byte = 1 pixel
	for(int i=0;i<30*8;++i)						// Like 65v
	{
		uint8_t b=sdl->ram->ram[VRAM+i];
		uint32_t c=(0xff<<24)|(b<<16)|(b<<8)|(b);

		//p[i]=c;

		for(int j=0;j<8*8;++j)
			p[((i/20+j/8)+(i/20*8))*256+(i%20+j%8)+(i%20*8)]=c;

		//for(int j=0;j<8*8;++j)
			//p[(i/256+j/8)*256+(i%256+j%8)]=c;
	}
}

// SDL_TimerCallback
uint32_t sdl_timer_cb(uint32_t interval,void*d)
{
	sdl_t*sdl=(sdl_t*)d;
	sdl_redraw(sdl);

	sdl->t=SDL_CreateTextureFromSurface(sdl->r,sdl->s);
	SDL_RenderClear(sdl->r);
	SDL_RenderCopy(sdl->r,sdl->t,NULL,&sdl->scr_rect);
	SDL_RenderPresent(sdl->r);
	SDL_DestroyTexture(sdl->t);
	sdl->t=NULL;

	return interval;
}

// Communicate between threads that we want to close/join threads
void sdl_halt(sdl_t*sdl,int v)
{
	pthread_mutex_lock(&sdl->mut);
	sdl->halt=v;
	pthread_mutex_unlock(&sdl->mut);
}
