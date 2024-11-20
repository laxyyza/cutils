#include "mmframes.h"
#include <stdlib.h>
#include <stdio.h>

#define FRAME_SIZE 4096

static void
memframe_init(memframe_t* frame, u64 size)
{
	frame->size = (size == 0) ? FRAME_SIZE : size;
	frame->buf = calloc(1, frame->size);
	frame->idx = 0;
}

void  
mmframes_init(mmframes_t* mmf)
{
	array_init(&mmf->frames, sizeof(memframe_t), 1);
	memframe_t* mf = array_add_into(&mmf->frames);
	memframe_init(mf, 0);
}

static void*
mmframes_push(memframe_t* frame, u64 size)
{
	void* ret = NULL;
	if (frame->idx + size < frame->size)
	{
		ret = (u8*)frame->buf + frame->idx;
		frame->idx += size;
	}
	return ret;
}

void* 
mmframes_alloc(mmframes_t* mmf, u64 size)
{
	void* ret;
	memframe_t* frames = (memframe_t*)mmf->frames.buf;
	memframe_t* frame;

	for (u32 i = 0; i < mmf->frames.count; i++)
	{
		frame = frames + i;
		if ((ret = mmframes_push(frame, size)))
			return ret;
	}
	frame = array_add_into(&mmf->frames);
	memframe_init(frame, (size > FRAME_SIZE) ? size : 0);
	ret = mmframes_push(frame, size);
	return ret;
}

void  
mmframes_clear(mmframes_t* mmf)
{
	memframe_t* frames = (memframe_t*)mmf->frames.buf;
	memframe_t* frame;

	for (u32 i = 1; i < mmf->frames.count; i++)
	{
		frame = frames + i;
		free(frame->buf);
	}
	array_clear(&mmf->frames, true);
	mmf->frames.count = 1;
	frame = (memframe_t*)mmf->frames.buf;
	frame->idx = 0;
}

void  
mmframes_free(mmframes_t* mmf)
{
	memframe_t* frames = (memframe_t*)mmf->frames.buf;
	memframe_t* frame;

	for (u32 i = 0; i < mmf->frames.count; i++)
	{
		frame = frames + i;
		free(frame->buf);
	}
	array_del(&mmf->frames);
}
