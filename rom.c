#include"65.h"
#include"rom.h"

// Load ROM into host machine memory
// To be mapped into 6502 RAM later
void rom_load(rom_t*rom,const char*filepath)
{
	rom->fd=open(filepath,O_RDONLY);
	if(rom->fd<0)
		puterr("%s: Failed to load ROM file \"%s\"\n",__func__,filepath);
}
