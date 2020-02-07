#include"disasm.h"
#include"stdlib.h"
#include"stdarg.h"

static int oper[8];

// Print instruction helper function
static void pi(cpu_t*cpu,ram_t*ram,int n,const char*fmt,...)
{

	#undef __cpu
	#define __cpu cpu

	//printw("\t(pc:$%04x)\t",cpu->pc);

	// pre calculate operands (because ABI is
	// reversing the evaluation of stack-sensitive
	// values:
	int oper[3];
	oper[0] = ram->ram[ cpu->pc ];

	// Print binary representation
	if(n==1)
	{
		printw( "\t%02x\t\t", oper[0] );
	}
	else if(n==2)
	{
		oper[1]=imm();
		printw( "\t%02x %02x\t\t", oper[0], oper[1] );
	}
	else if(n==3)
	{
		oper[1]=imm();
		oper[2]=imm();
		printw( "\t%02x %02x %02x\t", oper[0], oper[1], oper[2] );
	}
	else if(n==0)
		;

	// Print rest of vararg stuff (insn name, operands)
	va_list list;
	va_start(list,fmt);
	vwprintw(win,fmt,list);
	va_end(list);

	//printw(" (pc:$%04x)\t",cpu->pc);
}

#define p0(...) pi(cpuc,ram,0,__VA_ARGS__)
#define p1(...) pi(cpuc,ram,1,__VA_ARGS__)
#define p2(...) pi(cpuc,ram,2,__VA_ARGS__)
#define p3(...) pi(cpuc,ram,3,__VA_ARGS__)
#define end() goto clear_rest

// Print disassembly
void da_print_disassembly(cpu_t*cpu,ram_t*ram)
{
	// Set 'mode' to this copy of cpu
	#undef __cpu
	#define __cpu cpuc

	int y=8;	// Which line to draw on
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

		// Move/transfer
		// lda
		case 0xA1: p2( "lda ($%02x,x)", imm_pk(1) ); end();
		case 0xA5: p2( "lda zp $%02x", imm_pk(1) ); end();
		case 0xA9: p2( "lda #$%02x", imm_pk(1) ); end();
		case 0xB1: p2( "lda y, zp $%02x", imm_pk(1) ); end();
		case 0xB5: p2( "lda x, zp $%02x", imm_pk(1) ); end();
		case 0xB9: p2( "lda y, abs $%02x", imm_pk(1) ); end();
		case 0xBD: p2( "lda y, abs $%02x", imm_pk(1) ); end();
		// ldy
		case 0xA0: p2( "ldy #$%02x", imm_pk(1) ); end();
		// ldx
		case 0xA2: p2( "ldx #$%02x", imm_pk(1) ); end();
		case 0x4C: p3( "jmp abs $%04x", imm16_pk(1) ); end();
		case 0x6C:
				p3( "jmp ind ($%04x) <%04x>", imm_pk(1),
					ind( imm16_pk(2) ) );
				end();
		case 0xEA: p1( "nop"); end();
		case 0x00: p1( "brk"); end();

		clear_rest:
			printw("                         ");
			break;

		default:
			mvprintw(y,0,"-                                             ");
			//p0("incpc(1)");
			incpc(1);
			//printw("\t(pc:$%04x)\t",cpuc->pc);
		}

		// Next line of disassembly
		//cpuc->pc+=1;
		incpc(1);
		++y;
	}
}
