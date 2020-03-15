#include"65.h"
#include"65db.h"
#include"ram.h"
#include"rom.h"
#include"cpu.h"
#include"joy.h"
#include"65db_disasm.h"
#include<ctype.h>
#include<stdbool.h>
#include<unistd.h>

// Internal prototypes
void print_registers(cpu_t*cpu);
void print_memory(cpu_t*cpu,ram_t*ram,uint16_t offset);
void print_disassembly(cpu_t*cpu,ram_t*ram);
uint16_t prompt_address(char*prompt,cpu_t*cpu);
uint16_t linear_search(uint16_t from,ram_t*ram);
uint8_t prompt_byte(char*prompt,uint16_t from,ram_t*ram,char*prev,char*b);

// Entry point
int main(int argc,char**argv)
{
	cpu_t*cpu=cpu_init();
	rom_t*rom=new(rom_t);
	ram_t*ram=ram_init();

	char*title=NULL;

	uint16_t hex_offset=0x8000;	// Where start drawing memory hexdump
	int hex_follow_pc=true;		// Toggle following cpu->pc

	win=initscr();
	curs_set(0);
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_CYAN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_BLUE,COLOR_BLACK);

	// Parse command line arguments
	if(argc>1)
	{
		rom_load_file(rom,argv[1]);
		title=argv[1];
		//rom_print_header_info(rom);
		refresh();

		// Map ROM into $8000 by default
		// TODO: Learn where exactly to map 'PRG-ROM'
		rom_map(rom,ram,PRGROM);
		hex_offset=0x8000;
		refresh();
	}

	// Verify ROM is loaded
	if(rom->rom)
		cpu->pc=PRGROM;
	else
		puterr("%s: No ROM loaded\n",__func__);

	// Render -----
	while(true)
	{

		//clear();
		mvprintw(TOPROWHEIGHT+2,15,"%s",title);
		print_registers(cpu);
		print_memory(cpu,ram,hex_offset);
		print_disassembly(cpu,ram);

		mvprintw(STATUSLINE+1,0,
			"Welcome! [s] Step [q] Quit [g] Goto [G] Follow [p] PC [/] Search");

		// Display if following
		if(hex_follow_pc)
		{
			attron(COLOR_PAIR(2));
			mvprintw(0,30,"F");
			attroff(COLOR_PAIR(2));
		}
		else
			mvprintw(0,30," ");

		refresh();
		// Get keyboard input
		switch(getchar())
		{

		// Single step
		case 's':
			cpu_exec(cpu,ram);
			break;

		// Scroll up/down through memory hexdump
		case 'k': // Up
			hex_follow_pc=false;
			hex_offset= (hex_offset>8) ? (hex_offset-8) : 0;
			break;
		case 'j': // Down
			hex_follow_pc=false;
			hex_offset= (hex_offset<LASTHEXOFFSET-8) ? (hex_offset+8) : LASTHEXOFFSET;
			break;

		// Toggle follow pc on/off
		case 'G':
			hex_follow_pc=!hex_follow_pc;
			mvclr(STATUSLINE,0);
			mvprintw(STATUSLINE,0,"Follow PC: %s                      ",
				hex_follow_pc?
				"true":"false");
			break;
		// Goto (memory hexdump)
		case 'g':
			hex_offset=prompt_address("View offset",cpu);
			hex_follow_pc=false;
			break;

		// Set PC manually
		case 'p':
			cpu->pc=prompt_address("Set PC",cpu);
			break;

		// Linear search for character/byte
		case '/':
			hex_follow_pc=false;
			hex_offset=linear_search(hex_offset,ram);
			break;

		// Set byte at address
		case 'b':
			{
				uint16_t addr=prompt_address("Set byte at address: ",cpu);
				char b[512];
				char prev[8];
				ram->ram[addr]=prompt_byte("Set byte: ",addr,ram,prev,b);
				break;
			}

		// Quit command
		case 'q':
			goto quit;
		}

		if(hex_follow_pc) hex_offset=cpu->pc;
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
	mvprintw(4,0,"sp: $%02X\n",cpu->sp);
	mvprintw(5,0,"pc: $%04X\n",cpu->pc);
	mvprintw(6,0,"sr: $%02X\n",cpu->sr.reg);
	for(int i=0;i<8;++i)
		mvprintw(7,i,"%c",((cpu->sr.reg>>i)&0x1)?("NV-BDIZC"[i]):('-'));
}

// Print memory hexdump
void print_memory(cpu_t*cpu,ram_t*ram,uint16_t offset)
{
	// Print memory hexdump at (16,0)
	attron(COLOR_PAIR(4));
	mvprintw(0,16,"Memory:");
	attroff(COLOR_PAIR(4));

	// Print multiple lines
	for(int i=0;i<TOPROWHEIGHT;++i)
	{
		attron(COLOR_PAIR(3));
		mvprintw(i+1,16,"%04X",offset+i*8);
		attroff(COLOR_PAIR(3));

		// Hex output
		for(int j=0;j<8;++j)
			mvprintw(i+1,24+j*4,"%02X\n",ram->ram[offset+i*8+j]);

		// ASCII output
		for(int j=0;j<8;++j)
		{
			char c=ram->ram[offset+i*8+j];
			mvprintw(i+1,32+24+j,"%c\n",c<33?'.':c);
		}
	}
}

void print_disassembly(cpu_t*cpu,ram_t*ram)
{
	attron(COLOR_PAIR(4));
	mvprintw(TOPROWHEIGHT+2,0,"Disassembly:");
	attroff(COLOR_PAIR(4));
	da_print_disassembly(cpu,ram);
}

uint16_t prompt_address(char*prompt,cpu_t*cpu)
{
	char b[8];
	uint16_t gowh=0;

	// Prompt for desired goto address
	mvclr(STATUSLINE,0);
	mvprintw(STATUSLINE,0,"%s (0000-ffff,G,pc,p#XX): ",
		prompt);
	getnstr(b,4);

	// Special values
	if(strcmp(b,"G")==0) gowh=LASTHEXOFFSET;			// Goto end
	else if(strcmp(b,"pc")==0) gowh=cpu->pc;			// Goto cpu->pc
	else if(strlen(b)==0) gowh=0;						// Goto $0000 if empty
	else if(*b=='p') gowh=0x100*strtol(b+1,NULL,16);	// Goto page
	// Normal case
	else gowh=strtol(b,NULL,16);						// Default: goto abs addr
	// Validate input
	if(gowh>LASTHEXOFFSET) gowh=LASTHEXOFFSET;

	// Display result
	mvclr(STATUSLINE,0);
	mvprintw(STATUSLINE,0,"Goto: $%04x.",
		gowh);

	return gowh;
}

uint8_t prompt_byte(char*prompt,uint16_t from,ram_t*ram,char*prev,char*b)
{
	uint8_t byte=0;

	// Prompt for desired byte to find
	mvclr(STATUSLINE,0);
	mvprintw(STATUSLINE,0,"%s (00-ff,n): ",prompt);
	getnstr(b,2);

	// Special values
	if(strcmp(b,"")==0)
	{
		mvclr(STATUSLINE,0);
		mvprintw(STATUSLINE,0,"Not searching");
		return from;
	}
	// Repeat last search
	else if(strcmp(b,"n")==0)
	{
		mvclr(STATUSLINE,0);
		mvprintw(STATUSLINE,0,"Repeating last search");
		memcpy(b,prev,8);
	}

	// Validate input
	for(int i=0;i<2&&b[i];++i)
	{
		if(!isxdigit(b[i]))
		{
			mvclr(STATUSLINE,0);
			mvprintw(STATUSLINE,0,"Error: Invalid hexadecimal digit");
			memcpy(prev,b,8);
			return from;
		}
	}

	// Convert to integer and notify
	byte=strtol(b,NULL,16);
	mvclr(STATUSLINE,0);
	mvprintw(STATUSLINE,0,"Byte: $%X",
		byte);
	return byte;
}

uint16_t linear_search(uint16_t from,ram_t*ram)
{
	static char prev[8];
	char b[8];
	uint8_t byte=prompt_byte("Search for byte",from,ram,prev,b);

	// Search (linearly, until $ffff) from hex_offset
	for(int i=from+1;i<0xffff;++i)
		if(ram->ram[i]==byte)
		{
			mvclr(STATUSLINE,0);
			mvprintw(STATUSLINE,0,"Found $%X at $%04X (%+d)",
				byte,i,i-from);
			memcpy(prev,b,8);
			return i;
		}

	// Default: did not find byte
	mvclr(STATUSLINE,0);
	mvprintw(STATUSLINE,0,"Can't find $%X",
		byte);
	memcpy(prev,b,8);
	return from;
}
