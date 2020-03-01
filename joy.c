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
	ram->ram[joy->mem_addr]=(uint8_t)joy->button;
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

		if(*b=='\033')
		{
			read(1,b,2);
			if(b[1]=='A')			x=K_UP;
			else if(b[1]=='B')		x=K_DOWN;
			else if(b[1]=='D')		x=K_RIGHT;
			else if(b[1]=='C')		x=K_LEFT;
			else
				x=0;
		}
		else
			x=*b;

		// Update joy_t information
		pthread_mutex_lock(&(joy->mut));
		joy->button=x;
		pthread_mutex_unlock(&(joy->mut));
	}

	return NULL;
}
