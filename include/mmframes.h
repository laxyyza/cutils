#ifndef _SERVER_MMFRAMES_H_
#define _SERVER_MMFRAMES_H_

/**
 * The "mmframes" (Memory Management Frames) is a custom data structure 
 * designed for efficient temporary memory storage, resembling a stack with 
 * `allocate` and `clear` operations. It consists of an array of "memory frames," 
 * which by default contains a single frame.
 *
 * Each memory frame includes:
 *	A buffer,
 *	A default size of 4096 bytes,
 *	An index to track the allocation point within the buffer.
 *
 * When allocating memory, mmframes returns a pointer to `frame->buffer + index`
 * and increments the index by the requested allocation size. If a frame 
 * lacks sufficient space, a new frame is allocated. For allocations larger than 
 * the default frame size of 4096 bytes, a new frame sized specifically 
 * for the allocation is created.
 *
 * The `clear` operation reclaims memory by reducing mmframes to a single frame 
 * and resetting the index of that frame to zero. This design allows for 
 * temporary data storage that can be quickly allocated each frame, used, 
 * and then discarded, making it ideal for short-lived data within high-frequency operations.
 */

#include "array.h"

typedef struct 
{
	void*	buf;
	u64		size;
	u64		idx;
} memframe_t;

typedef struct 
{
	array_t frames;
} mmframes_t;

void  mmframes_init(mmframes_t* mmf);
void* mmframes_alloc(mmframes_t* mmf, u64 size);
void* mmframes_zalloc(mmframes_t* mmf, u64 size);
void  mmframes_clear(mmframes_t* mmf);
void  mmframes_free(mmframes_t* mmf);

#endif // _SERVER_MMFRAMES_H_
