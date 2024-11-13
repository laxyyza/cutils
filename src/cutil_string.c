#include "cutil_string.h"
#include "string.h"
#include <stdlib.h>

#ifdef _WIN32
char* 
strndup(const char* src, u64 size)
{
	u64 len = strnlen(src, size);
	len = len < size ? len : size;
	char* dst = malloc(len + 1);
	if (!dst)
		return NULL;
	memcpy(dst, src, len);
	dst[len] = '\0';
	return dst;
}
#endif // _WIN32
