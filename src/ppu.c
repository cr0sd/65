#include"ppu.h"
#include"sdl.h"
#include"ram.h"
#include<stdlib.h>

void printb(int n,int l);

// Create PPU & state
ppu_t*ppu_init(uint32_t w,uint32_t h)
{
	ppu_t*ppu=malloc(sizeof(ppu_t));

	ppu->pixels=malloc(w*h*4);
	ppu->w=w;
	ppu->h=h;

	ppu->vid=sdl_init(ppu);
	if(!ppu->vid)puts("error: PPU video failed to initialize");

	memset(ppu->pixels,0,ppu->w*ppu->h*4);

	return ppu;
}

// Free PPU state
void ppu_del(ppu_t*ppu)
{
	sdl_del(ppu->vid);
	if(ppu->pixels)free(ppu->pixels);
	if(ppu->vid)free(ppu->vid);
	ppu->pixels=NULL;
}

// Update PPU software pixel buffer
void ppu_update(ppu_t*ppu,ram_t*ram)
{
	for(int t=0;t<16;++t)
	{
		for(int y=0;y<8*2;y+=2)
			for(int x=0;x<8;++x)
				ppu->pixels[(t/32*256+y/2*256)+(t%32*8+x)] = ppu->pal[ ((ram->ram[PPUTILE+t*16+y]>>x)&1) | ((((ram->ram[PPUTILE+t*16+y+1])>>x)<<1)&2) ];
	}
	sdl_update(ppu->vid,ppu);
}

// Print binary digits of num
void printb(int n,int l)
{
	char a[512]={0};
	int i=0;
	int j=0;

	// Check if zero
	//if(!n)
		//a[i++]='0';

	// Calculate digits
	while(n>0||j<l)
	{
		int r=n%2;
		a[i++]=r+'0';
		n/=2;
		++j;
	}

	// Print binary representation
	while(a[--i])
		printf("%c",a[i]);
}
