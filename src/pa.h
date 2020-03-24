#include"65.h"
#include"cpu.h"
#include"ram.h"
#include"rom.h"
#include"joy.h"
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<portaudio.h>

int pa_cb(void*in,void*out,
	unsigned long fc,
	PaStreamCallbackTimeInfo*ti,
	PaStreamCallbackFlags f,
	void*data);

typedef struct pa_t
{
	PaStream*pa;
} pa_t;

pa_t*pa_init(void);
