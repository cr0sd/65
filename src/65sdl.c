#include"65.h"
#include"cpu.h"
#include"ram.h"
#include"rom.h"
#include"joy.h"
#include"sdl.h"
#include<SDL2/SDL.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define PROG "65sdl"

int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();
	joy_t*joy=joy_init(JOY1,2);
	sdl_t*sdl=new(sdl_t);

	sdl->ram=ram;
	sdl->joy=joy;

	pthread_t sdl_th;

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		rom_map(rom,ram,PRGROM);
		SDL_SetWindowTitle(sdl->win,argv[1]);
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=PRGROM;
	else
		puts("Failed to load ROM");

	if(!ram || !rom || !joy)puts("error"),exit(1);

	pthread_create(&sdl_th,NULL,sdl_thread,sdl);

	// Main loop
	for(;;)
	{
		joy_update_ram(joy,ram);
		cpu_exec(cpu,ram);
		if(sdl->halt) goto quit;
		usleep(50);
		//usleep(20000);
	}

quit:
	//sdl->halt=1;
	sdl_halt(sdl,1);
	pthread_join(sdl_th,NULL);
	//pthread_cancel(sdl_th);

	free(cpu);
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
	joy_del(joy);
	free(joy);
	sdl_del(sdl);
	free(sdl);
}

// Print formatted error message
void puterr(const char*fmt,...)
{
	va_list list;
	char b[1024];

	va_start(list,fmt);
	//mvclr(STATUSLINE,0);
	sprintf(b,PROG": ");
	//attron(COLOR_PAIR(2));
	sprintf(b,"Error: ");
	//attron(COLOR_PAIR(1));
	vsprintf(b,fmt,list);
	//vw_printw(win,fmt,list);
	va_end(list);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		"Error",
		b,
		NULL);
}
