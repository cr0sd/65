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
	ram->mem=malloc(0x10000);
	if(!ram->mem)
	{
		puterr("%s: Failed to allocate memory for RAM\n",__func__);
		//return ram;
	}
	return ram;
}

// Free data belonging to ram object
void ram_del(ram_t*ram)
{
	if(!ram->mem)
	{
		puterr("%s: Attempting to free NULL memory\n",__func__);
		return;
	}
	free(ram->mem);
}
