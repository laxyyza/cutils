#ifndef _CUTILS_H_
#define _CUTILS_H_

#include "int.h"
#include "array.h"
#include "mmframes.h"
#include <math.h>
#include "cutil_string.h"

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

static inline f64
clampf64(f64 val, f64 min, f64 max)
{
	return fmax(min, fmin(val, max));
}

static inline f32
percent(f32 per, f32 max)
{
	return (per / 100.0) * max;
}

#endif // _CUTILS_H_
