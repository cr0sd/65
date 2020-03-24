#include"65.h"
#include"pa.h"

int pa_cb(void*in,void*out,
	unsigned long fc,
	PaStreamCallbackTimeInfo*ti,
	PaStreamCallbackFlags f,
	void*data)
{
	return 0;
}

pa_t*pa_init(void)
{
	pa_t*pa=malloc(sizeof(pa_t));
	if(!pa)return NULL;
	Pa_Initialize();
	Pa_OpenDefaultStream(&pa->pa,0,1,paInt8,8000,64,
		(PaStreamCallback*)pa_cb,NULL);
}

void pa_del(pa_t*pa)
{
	Pa_Terminate();
	free(pa);
}
