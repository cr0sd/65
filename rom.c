#include"65.h"
#include"rom.h"
#include"ram.h"

// Load ROM into host machine memory
// To be mapped into 6502 RAM later
void rom_load_file(rom_t*rom,const char*filepath)
{
	// Open specified file
	rom->filepath=filepath;
	int fd=open(filepath,O_RDONLY);
	size_t len=0;
	if(fd<0)
	{
		puterr("%s: Failed to load ROM file \"%s\"\n",__func__,filepath);
		return;
	}

	// Determine ROM size
	// TODO: Calculate actual ROM size based on iNes header
	len=lseek(fd,0,SEEK_END)-16;
	if(len<0)
	{
		puterr("%s: Error detecting ROM file (\"%s\") size\n",__func__,filepath);
		return;
	}

	// Allocate memory for ROM data
	rom->data=malloc(len);
	if(!rom->data)
	{
		puterr("%s: Error allocating ROM memory for file data (\"%s\")\n",__func__,filepath);
		return;
	}

	// Read ROM data into rom_t struct
	lseek(fd,0,SEEK_SET);

	read(fd,rom->header,16);	// iNes header

	// Read trainer section of iNes file if it exists
	if(rom->header[6]&0x3)		// .nes file contains trainer section
	{
		read(fd,rom->trainer,512);
		//puts("has trainer!");
	}

	read(fd,rom->data,len-16);		// ROM data

	//printf("success reading rom \"%s\" (%u B)\n",filepath,len);

	close(fd);
}

void rom_print_header_info(rom_t*rom)
{
	printf("Reading ROM file \"%s\"\n",rom->filepath);
	printf("ROM banks (16k): %u\n",rom->header[4]);
	printf("VROM banks (8k): %u\n",rom->header[5]);

	printf("Vertical mirroring: %s\n",rom->header[6]&0x01?"true":"false");
	printf("Battery-backed RAM at $6000-$7FFF: %s\n",rom->header[6]&0x01?"true":"false");
	printf("Contains trainer section: %s\n",rom->header[6]&0x03?"true":"false");
	printf("Four-screen VRAM: %s\n",rom->header[6]&0x04?"true":"false");

	printf("VS System cartridge: %s\n",rom->header[7]&0x01?"true":"false");
	printf("ROM Mapper type: %u\n",rom->header[6]&0xf0|rom->header[7]&0x0f);
	printf("RAM banks (8k): %u (if 0, counted as 1)\n",rom->header[8]);
	printf("Cartridge: %s\n",(rom->header[9]&0x1)==1?"PAL":"NTSC");
	puts("_______________");
}

void rom_map(rom_t*rom,ram_t*ram)
{
	if(!rom || !rom->data)
	{
		puterr("%s: Attempting to map NULL ROM data into RAM memory\n",__func__);
		return;
	}
	if(!ram || !ram->mem)
	{
		puterr("%s: Attempting to map ROM data into NULL RAM memory\n",__func__);
		return;
	}

	// Copy rom data into ram memory
	// Put NES file header parsing here <---
	memmove(ram->mem,rom->data,rom->data_len);
}

// Free memory allocated to ROM object
void rom_del(rom_t*rom)
{
	if(!rom->data)
	{
		puterr("%s: Attempting to free NULL memory\n",__func__);
		return;
	}
	free(rom->data);
}
