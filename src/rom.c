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
	len=lseek(fd,0,SEEK_END);
	if(len<=16)
	{
		puterr("%s: ROM size was less than 16 bytes\n",__func__);
		return;
	}
	len-=16;
	rom->data_len=len;

	// Allocate memory for ROM data
	rom->rom=malloc(len);
	if(!rom->rom)
	{
		puterr("%s: Error allocating ROM memory for file data (\"%s\")\n",__func__,filepath);
		return;
	}

	// Read ROM data into rom_t struct
	lseek(fd,0,SEEK_SET);
	read(fd,rom->header,16);	// iNes header

	// Verify valid NES header
	if(strncmp("NES",rom->header,3)!=0)
	{
		puterr("%s: \"%s\" is not a valid NES file\n",__func__,filepath);
		return;
	}

	// Read trainer section of iNes file if it exists
	if(rom->header[6]&0x3)		// .nes file contains trainer section
	{
		read(fd,rom->trainer,512);
		//printw("has trainer!");
	}

	//lseek(fd,16,SEEK_SET);
	//printw("data_len: %d\n",rom->data_len);
	read(fd,rom->rom,len);		// ROM data

	//printw("success reading rom \"%s\" (%u B)\n",filepath,len);
	close(fd);
}

//void rom_print_header_info(rom_t*rom)
//{
	//#ifndef DO_NOT_USE_CURSES
	//attron(COLOR_PAIR(3));
	//#endif
	//printw("ROM info:\n");
	//printw("Reading ROM file \"%s\"\n",rom->filepath);
	//printw("ROM banks (16k): %u\n",rom->header[4]);
	//printw("VROM banks (8k): %u\n",rom->header[5]);

	//printw("Vertical mirroring: %s\n",rom->header[6]&0x01?"true":"false");
	//printw("Battery-backed RAM at $6000-$7FFF: %s\n",rom->header[6]&0x01?"true":"false");
	//printw("Contains trainer section: %s\n",rom->header[6]&0x03?"true":"false");
	//printw("Four-screen VRAM: %s\n",rom->header[6]&0x04?"true":"false");

	//printw("VS System cartridge: %s\n",rom->header[7]&0x01?"true":"false");
	//printw("ROM Mapper type: %u\n",rom->header[6]&0xf0|rom->header[7]&0x0f);
	//printw("RAM banks (8k): %u (if 0, counted as 1)\n",rom->header[8]);
	//printw("Cartridge: %s\n",(rom->header[9]&0x1)==1?"PAL":"NTSC");

	//printw("Rom data length: %d\n",rom->data_len);
	//#ifndef DO_NOT_USE_CURSES
	//attron(COLOR_PAIR(1));
	//#endif
	//printw("_______________\n");
//}

// Map ROM information into CPU RAM for fetch-decode-execute
// offset used to determine where in RAM said ROM data will be mapped
void rom_map(rom_t*rom,ram_t*ram,size_t offset)
{
	if(!rom || !rom->rom)
	{
		puterr("%s: Attempting to map NULL ROM data into RAM memory\n",__func__);
		return;
	}
	if(!ram || !ram->ram)
	{
		puterr("%s: Attempting to map ROM data into NULL RAM memory\n",__func__);
		return;
	}

	// Copy rom data into ram memory
	// Put NES file header parsing here <---
	//printw("copying %u bytes into RAM from ROM\n",rom->data_len);

	// NOTE: Substitution of copying entire data_len with copying
	// a smaller 'chunk' at a time was necessary on ArchLinux to prevent
	// SIGSEGV crashing the program
	const size_t DATA_CHUNK=2048;
	for(size_t len=rom->data_len;len>0;len-=(len>DATA_CHUNK)?DATA_CHUNK:len)
		memmove(ram->ram+offset,rom->rom,(len>DATA_CHUNK)?DATA_CHUNK:len);
	//memmove(ram->ram,rom->rom,rom->data_len);
}

// Free memory allocated to ROM object
void rom_del(rom_t*rom)
{
	if(!rom->rom)
	{
		puterr("%s: Attempting to free NULL memory\n",__func__);
		return;
	}
	free(rom->rom);
}
