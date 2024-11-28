#ifndef _NANO_TIMER_H_
#define _NANO_TIMER_H_

#include "int.h"

typedef struct 
{
	i64 nsec;
	i64 sec;
} hr_time_t;

typedef struct 
{
	hr_time_t start_time;
	hr_time_t end_time;

	f64 start_time_s;
	f64 end_time_s;
	i64 elapsed_time_ns;
} nano_timer_t;

void nano_timer_init(nano_timer_t* nt);
void nano_start_time(nano_timer_t* nt);
void nano_gettime(hr_time_t* t);
i64  nano_end_time(nano_timer_t* nt);
i64  nano_time_diff_ns(const hr_time_t* start_time, const hr_time_t* end_time);
f32  nano_time_diff_ms(const hr_time_t* start_time, const hr_time_t* end_time);
f64  nano_time_diff_s(const hr_time_t* start_time, const hr_time_t* end_time);

i64 sec_to_ns(f64 s);
f32 sec_to_us(f64 s);
f32 sec_to_ms(f64 s);
f64 ns_to_sec(i64 ns);
f32 ns_to_ms(i64 ns);

f64 nano_time_s(const hr_time_t* time);
u64 nano_time_ns(const hr_time_t* time);

#endif // _NANO_TIMER_H_
