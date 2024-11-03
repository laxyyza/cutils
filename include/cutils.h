#ifndef _CUTILS_H_
#define _CUTILS_H_

#include "int.h"
#include "array.h"
#include "mmframes.h"
#include <math.h>

static inline i32 
clampi(i32 val, i32 min, i32 max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

static inline f32
clampf(f32 val, f32 min, f32 max)
{
	return fmaxf(min, fminf(val, max));
}

#endif // _CUTILS_H_
