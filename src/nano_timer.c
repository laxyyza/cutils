#define _GNU_SOURCE
#include "nano_timer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#ifdef _WIN32
static LARGE_INTEGER freq = { 0 };

void
nano_gettime(hr_time_t* t)
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	i64 total_sec = (counter.QuadPart * 1e9) / freq.QuadPart;
	t->sec = total_sec / 1e9;
	t->nsec = total_sec % (i64)1e9;
}
#endif // _WIN32

#ifdef __linux__
void
nano_gettime(hr_time_t* t)
{
	struct timespec timespec;
	clock_gettime(CLOCK_MONOTONIC, &timespec);
	t->sec = timespec.tv_sec;
	t->nsec = timespec.tv_nsec;
}
#endif // __linux__

void 
nano_timer_init(nano_timer_t* nt)
{
#ifdef _WIN32
	QueryPerformanceFrequency(&freq);
#endif

	nano_start_time(nt);
}

void 
nano_start_time(nano_timer_t* nt)
{
	nano_gettime(&nt->start_time);
	nt->start_time_s = (nt->start_time.nsec / 1e9) + nt->start_time.sec;
}

i64
nano_end_time(nano_timer_t* nt)
{
	nano_gettime(&nt->end_time);
	nt->end_time_s = (nt->end_time.nsec / 1e9) + nt->end_time.sec;
	nt->elapsed_time_ns = nano_time_diff_ns(&nt->start_time, &nt->end_time);
	return nt->elapsed_time_ns;
}

f64  
nano_time_diff(const hr_time_t* start_time, const hr_time_t* end_time)
{
	return  (end_time->sec - start_time->sec) +
			((end_time->nsec - start_time->nsec) * 1e9);
}

i64  
nano_time_diff_ns(const hr_time_t* start_time, const hr_time_t* end_time)
{
	return  ((end_time->sec - start_time->sec) * 1e9) + 
			(end_time->nsec - start_time->nsec);
}

f32  
nano_time_diff_ms(const hr_time_t* start_time, const hr_time_t* end_time)
{
	return	((end_time->sec - start_time->sec) * 1e3) + 
			((end_time->nsec - start_time->nsec) / 1e6);
}

f64  
nano_time_diff_s(const hr_time_t* start_time, const hr_time_t* end_time)
{
	return	(end_time->sec - start_time->sec) +
			((end_time->nsec - start_time->nsec) / 1e9);
}

i64 
sec_to_ns(f64 s)
{
	return s * 1e9;
}

f32
sec_to_us(f64 s)
{
	return s * 1e6;
}

f32
sec_to_ms(f64 s)
{
	return s * 1e3;
}

f64
ns_to_sec(i64 ns)
{
	return ns / 1e9;
}

f32
ns_to_ms(i64 ns)
{
	return ns / 1e6;
}

f64 
nano_time_s(const hr_time_t* time)
{
	return (time->nsec / 1e9) + time->sec;
}

u64 
nano_time_ns(const hr_time_t* time)
{
	return time->nsec + (time->sec * 1e9);
}
