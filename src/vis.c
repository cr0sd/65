#include<ncurses.h>
#include"65.h"
#include"vis.h"

// Display information stored in VRAM
int vis_display(cpu_t*cpu,ram_t*ram)
{
	int w=VIS_WIDTH;
	int h=VIS_HEIGHT;

	for(int i=0;i<w*h;++i)
	{
		int b=ram->ram[VRAM+i];
		move(i/w,i%w);
		clrtoeol();
		
		if(b==0xff)
			addch(b?(ACS_CKBOARD):(' '));
		else if(b==0x21)
			addch('@');

		//mvprintw(i/w,i%w,"%c",b?(ACS_CKBOARD):(' '));
		//mvprintw(i/w,i%w,"%c",b);
		//mvprintw(i/w,i%w,"%c",(b<0x20)?('.'):(b));
	}
}
