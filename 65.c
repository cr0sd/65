#include"65.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"
#include<ncurses.h>

void cpu65_exec(cpu_t*cpu,ram_t*ram)
{
	//printf("pc: 0x%04x\t",cpu->pc);
	//printf("ac: 0x%02x",cpu->ac);
	//puts("");
	printw("0x%04x: 0x%02x\n",cpu->pc,ram->ram[cpu->pc]);
	cpu_exec(cpu,ram);
	cpu->pc+=1;
	refresh();
}

WINDOW*win;
void puterr(const char*fmt,...)
{
	va_list list;
	va_start(list,fmt);
	//fprintf(stderr,PROG": Error: ");
	printw(PROG": ");
	attron(COLOR_PAIR(2));
	printw("Error: ");
	attron(COLOR_PAIR(1));
	//vfprintf(stderr,fmt,list);
	vwprintw(win,fmt,list);
	va_end(list);
}

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();

	win=initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_CYAN,COLOR_BLACK);

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		rom_print_header_info(rom);
		refresh();

		// Map ROM into $8000 by default
		// TODO: Learn where exactly to map 'PRG-ROM'
		rom_map(rom,ram,PRG_ROM_OFFSET);
		refresh();
		//for(int i=0;i<100;++i)
			//printf("%2x",ram->ram[i]);
		//puts("");
	}

	// Execute ROM
	if(rom->rom)
	{
		cpu->pc=PRG_ROM_OFFSET;
		// Read instructions for testing purposes
		#define INSNS 4
		printw("Displaying %d instructions:\n",INSNS);
		for(int i=0;i<INSNS;++i)
			cpu65_exec(cpu,ram);
	}
	else
		puterr("%s: No ROM loaded\n",__func__);

	while(true)
	{
		refresh();
		switch(getchar())
		{
		case 'i':
			printw("a: 0x%x\n",cpu->a);
			break;
		case 's':
			cpu65_exec(cpu,ram);
			break;
		case 'q':
			goto quit;
		}
	}

quit:
	// Free memory
	free(cpu);
	rom_del(rom);
	free(rom);
	ram_del(ram);
	free(ram);
	endwin();
}
