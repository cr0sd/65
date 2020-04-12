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

	//for(int i=0;i<256;++i)		// Tiles 0-255

	// Draw tile 0 at 0x300
	// for(int y=0;y<16;y+=2)	// Bitplane
		// for(int x=0;x<8;++x)
			// ppu->pixels[y/2*256+x]=*((uint32_t*)(ram->ram+0x3f00+((ram->ram[VRAM+(y*256+x)]<<x)&1)));

	/// for(int i=0;i<16*8;i+=2)
		/// ppu->pixels[(i/8)*256+i%8]=ppu->pal[(ram->ram[PPUTILE+i]|(ram->ram[PPUTILE+i+1]<<1))&3];
		//ppu->pixels[i]=ppu->pal[ram->ram[PPUTILE+i]];

	for(int y=0;y<8*2;y+=2)
	{
		for(int x=0;x<8;++x)
		{
			ppu->pixels[y/2*256+x]=ppu->pal[ ((ram->ram[PPUTILE+y]>>x)&1) | ((((ram->ram[PPUTILE+y+1])>>x)<<1)&2) ];

			printf("[%0p]: (%d,%d):  [%02X/%02X]:(%d %d):  %02X (",
				ram->ram+PPUTILE+y,
				y/2,
				x,
				ram->ram[PPUTILE+y],
				ram->ram[PPUTILE+y+1],
				(ram->ram[PPUTILE+y]>>x)&1,
				( (ram->ram[PPUTILE+y+1]>>x)<<1 )&2,
				( ((ram->ram[PPUTILE+y]>>x) & 1) | ((( ((ram->ram[PPUTILE+y+1])>>x)<<1)&2)) )
				);
			printb(( ((ram->ram[PPUTILE+y]>>x) & 1) | ((( ((ram->ram[PPUTILE+y+1])>>x)<<1)&2)) ),8);
			puts(")");
		}
	}

	/*
	for(int i=0;i<512;++i)
	{
		if(ram->ram[i]>3)continue;

		// Draw one of four palette colors specified in VRAM
		ppu->pixels[i]=*((uint32_t*)(ram->ram+0x3f00+ram->ram[VRAM+i]));
	}
	*/

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
