#include"65.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"
#include"vis.h"
#include"joy.h"
#include"disasm.h"

#include<ctype.h>
#include<stdbool.h>
#include<unistd.h>
#include<pthread.h>

// 65 with VRAM display
// instead of disassembly, registers & memory

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();
	joy_t*joy=joy_init(JOYPREG,2);
 	pthread_t thread;

	//printf("ram->ram:\t%p\njoy->ram->ram:\t%p\n",ram->ram,joy->ram->ram);
	//getch();
	//exit(0);

	// Setup curses
	win=initscr();
	curs_set(0);
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_CYAN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_BLUE,COLOR_BLACK);

	// Setup joypad
	//joy->codes[0]='z';
	//joy->codes[1]='x';

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		rom_map(rom,ram,PRGROM);
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=PRGROM;

	if(!ram || !rom || !joy)puts("error"),exit(1);

	pthread_create(&thread,NULL,joy_thread_update,joy);

	// Render -----
	while(true)
	{
		joy_update_ram(joy,ram);
		cpu_exec(cpu,ram);

		vis_display(cpu,ram);
		mvclr(15,0);
		mvprintw(15,0,"joy button: $%02X",joy->buttons.reg);
		mvclr(16,0);
		mvprintw(16,0,"$%04X: $%02X (%c)",
			JOYPREG,ram->ram[JOYPREG],
			(ram->ram[JOYPREG]<0x20)?('.'):(ram->ram[JOYPREG]));
		refresh();
		usleep(1);
	}

	pthread_cancel(thread);

	// Free memory
	free(cpu);
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
	joy_del(joy);
	free(joy);
	endwin();
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
