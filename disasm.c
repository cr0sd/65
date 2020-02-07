#include"disasm.h"
#include"stdlib.h"

// Print instruction helper function
static void pi(cpu_t*cpu,ram_t*ram,int n,const char*fmt,...)
{

	// Print binary hexdump
	if(n==1)
		printw( "\t%02x\t\t", ram->ram[cpu->pc] );
	else if(n==2)
		printw( "\t%02x %02x\t\t", ram->ram[cpu->pc],
			ram->ram[cpu->pc+1] );
	else if(n==3)
		printw( "\t%02x %02x %02x\t", ram->ram[cpu->pc],
			ram->ram[cpu->pc+1], ram->ram[cpu->pc+2] );

	// Print rest of vararg stuff (insn name, operands)
	va_list list;
	va_start(list,fmt);
	vwprintw(win,fmt,list);
	va_end(list);
}

#define p1(...) pi(cpu,ram,1,__VA_ARGS__)
#define p2(...) pi(cpu,ram,2,__VA_ARGS__)
#define p3(...) pi(cpu,ram,3,__VA_ARGS__)

// Print disassembly
void da_print_disassembly(cpu_t*cpu,ram_t*ram)
{
	// Set 'mode' to this copy of cpu
	#define __cpu cpuc

	int y=8;
	cpu_t*cpuc=alloca(sizeof(cpu_t));

	// Create copy of cpu
	if(!cpuc)
	{
		puterr("%s: Failed to allocate copy of CPU\n",__func__);
		return;
	}
	memcpy(cpuc,cpu,sizeof(cpu_t));

	// Disassemble 12 lines
	for(int i=0; i<12; ++i)
	{

		// Print offset
		attron(COLOR_PAIR(5));
		mvprintw(y,0,"%04x",cpuc->pc);
		attroff(COLOR_PAIR(5));

		// Opcodes
		switch(ram->ram[cpuc->pc])
		{

		case 0xA0: p2( "ldy #$%02x", imm() );
			goto clear_rest;

		case 0xA5: p2( "lda zp $%02x", imm() );
			goto clear_rest;

		case 0xA9: p2( "lda #$%02x", imm() );
			goto clear_rest;

		case 0xB1: p2( "lda y, zp $%02x", zp( imm() ) );
			goto clear_rest;

		case 0xB5: p2( "lda x, zp $%02x", zp( imm() ) );
			goto clear_rest;

		case 0xB9: p2( "lda y, abs $%02x", ab( imm() ) );
			goto clear_rest;

		case 0xBD: p2( "lda y, abs $%02x", ab( imm() ) );
			goto clear_rest;

		case 0xA2: p2( "ldx #$%02x", imm() );
			goto clear_rest;

		case 0x4C: p3( "jmp abs $%04x", imm() | (imm()<<8) );
			goto clear_rest;

		case 0x6C:
			{
				int tmp = imm() | (imm()<<8);
				p3( "jmp ind (%04x) <%04x>", tmp, ind( tmp ) );
			}
			goto clear_rest;

		case 0xEA: // nop
			p1( "nop");
			goto clear_rest;

		case 0x00: // brk
			p1( "brk");
			goto clear_rest;

		clear_rest:
			printw("                     ");
			break;

		default:
			mvprintw(y,0,"-                                         ");
		}

		// Next line of disassembly
		cpuc->pc+=1;
		++y;
	}
}
