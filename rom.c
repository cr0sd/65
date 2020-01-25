#include"65.h"
#include"rom.h"

// Load ROM into host machine memory
// To be mapped into 6502 RAM later
void rom_load_file(rom_t*rom,const char*filepath)
{
	rom->filepath=filepath;
	int fd=open(filepath,O_RDONLY);
	size_t len=0;
	if(fd<0)
	{
		puterr("%s: Failed to load ROM file \"%s\"\n",__func__,filepath);
		return;
	}

	// Allocate memory for and read
	// ROM file contents into rom data
	len=lseek(fd,0,SEEK_END);
	if(len<0)
	{
		puterr("%s: Error detecting ROM file (\"%s\") size\n",__func__,filepath);
		return;
	}

	rom->data=malloc(len);
	if(!rom->data)
	{
		puterr("%s: Error allocating ROM memory for file data (\"%s\")\n",__func__,filepath);
		return;
	}

	lseek(fd,0,SEEK_SET);
	read(fd,rom->data,len);

	//printf("success reading rom \"%s\" (%u B)\n",filepath,len);

	close(fd);
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
	memmove(ram->mem,rom->data,0x10000);
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
