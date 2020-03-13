#include"joy.h"

// Create joy_t struct
joy_t*joy_init(uint16_t addr,int n)
{
	joy_t*j=malloc(sizeof(joy_t));
	//int*codes=malloc(sizeof(int)*n);

	// Verify memory allocation
	//if(!j||!codes)return NULL;
	if(!j)return NULL;

	j->mem_addr=addr;
	return j;
}

// Delete joy_t information
void joy_del(joy_t*joy)
{
	//if(joy)
		//if(joy->codes)
			//free(joy->codes);
}

// Function to write joypad information to RAM
void joy_update_ram(joy_t*joy,ram_t*ram)
{
	pthread_mutex_lock(&(joy->mut));
	ram->ram[joy->mem_addr]=(uint8_t)joy->buttons.reg;
	pthread_mutex_unlock(&(joy->mut));
}

// pthread callback to do stdin read
// without control flow blocking
void*joy_thread_update(void*d)
{
	joy_t*joy=(joy_t*)d;
	int x;
	char b[2];

	// Get keyboard input
	while(true)
	{
		read(1,b,1);

		// Update joy_t information
		pthread_mutex_lock(&(joy->mut));

		// Get multi-byte codes
		if(*b=='\033')
		{
			read(1,b,2);
			if(b[1]=='A')			joy->buttons.reg=0, joy->buttons.bits.up=1;
			else if(b[1]=='B')		joy->buttons.reg=0, joy->buttons.bits.down=1;
			else if(b[1]=='D')		joy->buttons.reg=0, joy->buttons.bits.left=1;
			else if(b[1]=='C')		joy->buttons.reg=0, joy->buttons.bits.right=1;
			//else
				//x=0;
		}
		else	if(*b==JOY_A)		joy->buttons.reg=0x10; //joy->buttons.bits.a=1;
		else	if(*b==JOY_B)		joy->buttons.reg=0x20; //joy->buttons.bits.b=1;
		else	if(*b==JOY_SELECT)	joy->buttons.reg=0x40; //joy->buttons.bits.start=1;
		else	if(*b==JOY_START)	joy->buttons.reg=0x80; //joy->buttons.bits.select=1;
		else	joy->buttons.reg=0;

		pthread_mutex_unlock(&(joy->mut));
	}

	return NULL;
}
