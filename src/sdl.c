#include"ppu.h"
#include"sdl.h"

// Update SDL window, graphics
void sdl_update(sdl_t*sdl,ppu_t*ppu)
{
	// Update SDL graphics
	SDL_RenderClear(sdl->r);
	SDL_UpdateTexture(sdl->t,NULL,ppu->pixels,ppu->w*4);
	SDL_RenderCopy(sdl->r,sdl->t,NULL,NULL);
	SDL_RenderPresent(sdl->r);

	// Event 'loop'
	if(SDL_PollEvent(&sdl->e))
		if(sdl->e.type==SDL_QUIT)
			sdl->quit=1;
		else if(sdl->e.type==SDL_KEYDOWN)
			if(((SDL_KeyboardEvent*)(&sdl->e))->keysym.sym==SDLK_ESCAPE)
				sdl->quit=1;
}

// SDL video implementation
sdl_t*sdl_init(ppu_t*ppu)
{
	sdl_t*sdl=malloc(sizeof(sdl_t));
	if(!sdl)return NULL;
	sdl->w=SDL_CreateWindow("title",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		ppu->w,ppu->h,SDL_WINDOW_SHOWN);

	sdl->r=SDL_CreateRenderer(sdl->w,-1,0);
	sdl->t=SDL_CreateTexture(sdl->r,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		256,240);

	return sdl;
}

void sdl_del(sdl_t*sdl)
{
	if(sdl->r)SDL_DestroyRenderer(sdl->r);
	if(sdl->w)SDL_DestroyWindow(sdl->w);
	if(sdl->t)SDL_DestroyTexture(sdl->t);
}
