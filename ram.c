#include"ram.h"

// Allocate RAM for read/write
ram_t*ram_init(void)
{
	ram_t*ram=malloc(sizeof(ram_t));
	if(!ram)
	{
		puterr("%s: Failed to allocate RAM\n",__func__);
		return NULL;
	}
	ram->ram=malloc(0x10000);
	if(!ram->ram)
	{
		puterr("%s: Failed to allocate memory for RAM\n",__func__);
		//return ram;
	}
	return ram;
}

// Free data belonging to ram object
void ram_del(ram_t*ram)
{
	if(!ram->ram)
	{
		puterr("%s: Attempting to free NULL memory\n",__func__);
		return;
	}
	free(ram->ram);
}

uint16_t ram_indirect_address(ram_t*ram,uint16_t src)
{
	return *(uint16_t*)(ram->ram+src);
}
