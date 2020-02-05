#include"65.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"

void cpu65_exec(cpu_t*cpu,ram_t*ram)
{
	//printf("pc: 0x%04x\t",cpu->pc);
	//printf("ac: 0x%02x",cpu->ac);
	//puts("");
	//printw("0x%04x: 0x%02x\n",cpu->pc,ram->ram[cpu->pc]);
	cpu_exec(cpu,ram);
	cpu->pc+=1;
	refresh();
}

void puterr(const char*fmt,...)
{
	va_list list;
	va_start(list,fmt);
	//fprintf(stderr,PROG": Error: ");
	mvprintw(20,0,PROG": ");
	attron(COLOR_PAIR(2));
	printw("Error: ");
	attron(COLOR_PAIR(1));
	//vfprintf(stderr,fmt,list);
	vwprintw(win,fmt,list);
	va_end(list);
}

// Print register info
void print_registers(cpu_t*cpu)
{
	// Print Register info at (0,0)
	mvprintw(0,0,"Registers:");
	mvprintw(1,0,"a:  $%02x\n",cpu->a);
	mvprintw(2,0,"x:  $%02x\n",cpu->x);
	mvprintw(3,0,"y:  $%02x\n",cpu->y);
	mvprintw(4,0,"sr: $%02x\n",cpu->sr.reg);
	mvprintw(5,0,"pc: $%04x\n",cpu->pc);
}

// Print hexdump
void print_hexdump(cpu_t*cpu,ram_t*ram)
{
	// Print hexdump at (16,0)
	mvprintw(0,16,"Hexdump:");
	for(int i=0;i<4;++i)
	{
		attron(COLOR_PAIR(3));
		mvprintw(i+1,16,"%04x",cpu->pc+i*8);
		attroff(COLOR_PAIR(3));
		for(int j=0;j<8;++j)
			mvprintw(i+1,24+j*4,"%02x\n",ram->ram[cpu->pc+i*8+j]);
	}
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
		//rom_print_header_info(rom);
		refresh();

		// Map ROM into $8000 by default
		// TODO: Learn where exactly to map 'PRG-ROM'
		rom_map(rom,ram,PRG_ROM_OFFSET);
		refresh();
		//for(int i=0;i<100;++i)
			//printf("%2x",ram->ram[i]);
		//puts("");
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=PRG_ROM_OFFSET;
	else
		puterr("%s: No ROM loaded\n",__func__);

	// Render -----
	while(true)
	{

		print_registers(cpu);
		print_hexdump(cpu,ram);
		refresh();
		// Get keyboard input
		switch(getchar())
		{

		// Step
		case 's':
			cpu65_exec(cpu,ram);
			break;

		// Quit command
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
