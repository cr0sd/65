#include"65.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"
#include"disasm.h"

// Print formatted error message
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
	attron(COLOR_PAIR(4));
	mvprintw(0,0,"Registers:");
	attroff(COLOR_PAIR(4));
	mvprintw(1,0,"a:  $%02X\n",cpu->a);
	mvprintw(2,0,"x:  $%02X\n",cpu->x);
	mvprintw(3,0,"y:  $%02X\n",cpu->y);
	mvprintw(4,0,"sr: $%02X\n",cpu->sr.reg);
	mvprintw(5,0,"pc: $%04X\n",cpu->pc);
}

// Print hexdump
void print_hexdump(cpu_t*cpu,ram_t*ram)
{
	// Print hexdump at (16,0)
	attron(COLOR_PAIR(4));
	mvprintw(0,16,"Hexdump:");
	attroff(COLOR_PAIR(4));

	// Print multiple lines
	for(int i=0;i<5;++i)
	{
		attron(COLOR_PAIR(3));
		mvprintw(i+1,16,"%04X",cpu->pc+i*8);
		attroff(COLOR_PAIR(3));

		// Hex output
		for(int j=0;j<8;++j)
			mvprintw(i+1,24+j*4,"%02X\n",ram->ram[cpu->pc+i*8+j]);

		// ASCII output
		for(int j=0;j<8;++j)
		{
			char c=ram->ram[cpu->pc+i*8+j];
			mvprintw(i+1,32+24+j,"%c\n",c<33?'.':c);
		}
	}
}

void print_disassembly(cpu_t*cpu,ram_t*ram)
{
	attron(COLOR_PAIR(4));
	mvprintw(7,0,"Disassembly:");
	attroff(COLOR_PAIR(4));
	da_print_disassembly(cpu,ram);
}

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();

	win=initscr();
	curs_set(0);
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_CYAN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_BLUE,COLOR_BLACK);

	mvprintw(20,0,"Welcome! Usage: [s] Step [q] Quit");

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
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=PRG_ROM_OFFSET;
	else
		puterr("%s: No ROM loaded\n",__func__);

	// Render -----
	while(true)
	{

		//clear();
		print_registers(cpu);
		print_hexdump(cpu,ram);
		print_disassembly(cpu,ram);
		refresh();
		// Get keyboard input
		switch(getchar())
		{

		// Single step
		case 's':
			cpu_exec(cpu,ram);
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
