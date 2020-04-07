#include"65.h"
#include<SDL2/SDL.h>
#include"rom.h"
#include"ram.h"
#include"cpu.h"
#include"joy.h"
#include"ppu.h"
#include"sdl.h"
#include<signal.h>
#define PROG "ves"

int quit=0;

void sighandler(int sig);

int main(int argc,char**argv)
{
	rom_t*rom=malloc(sizeof(rom_t));
	ram_t*ram=ram_init();
	cpu_t*cpu=cpu_init();
	ppu_t*ppu=ppu_init(320,240);
	joy_t*joy=joy_init(JOY1,2);

	signal(SIGINT,sighandler);

	if(argc<2)puts("error: no ROM file"),exit(1);
	rom_load_file(rom,argv[1]);
	rom_map(rom,ram,PRGROM);

	cpu->pc=PRGROM;

	// Create picture palette
	uint32_t*pal=(uint32_t*)(ram->ram+0x3f00);
	pal[0]=0xff000000;
	pal[1]=0xff8080ff;
	pal[2]=0xff80ff80;
	pal[3]=0xffff8080;

	// Verify state is loaded
	if(!rom)quit=1,puts("error: failed to allocate ROM");
	else if(!rom->rom)quit=1,puts("error: no ROM loaded");
	if(!ram)quit=1,puts("error: failed to allocate RAM");
	if(!cpu)quit=1,puts("error: failed to allocate CPU");
	if(!joy)quit=1,puts("error: failed to allocate JOY");

	// Execution loop
	while(!quit)
	{
		//printf("PPAL: %08X\n",((uint32_t*)ram->ram)[0x3f00]);
		for(int i=0;i<64;++i)
			cpu_exec(cpu,ram);
		ppu_update(ppu,ram);
		if(((sdl_t*)(ppu->vid))->quit)break;
		usleep(5000);
	}

	printf("\ncpu->a: %d (%02X)\n",cpu->a,cpu->a);

	// Release resources
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
	joy_del(joy);
	free(joy);
	ppu_del(ppu);
	free(ppu);
}


void puterr(const char*fmt,...)
{
	va_list list;
	char b[1024];

	va_start(list,fmt);
	sprintf(b,PROG": ");
	sprintf(b,"Error: ");
	vsprintf(b,fmt,list);
	va_end(list);
}

void sighandler(int sig)
{
	if(sig==SIGINT)quit=true;
}
