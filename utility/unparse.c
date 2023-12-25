

#include <stdio.h>

#include "uuidP.h"

static char const hexdigits_lower[16] = "0123456789abcdef";
static char const hexdigits_upper[16] = "0123456789ABCDEF";

static void uuid_fmt(const uuid_t uuid, char *buf, char const *restrict fmt)
{
	char *p = buf;
	int i;

	for (i = 0; i < 16; i++) {
		if (i == 4 || i == 6 || i == 8 || i == 10) {
			*p++ = '-';
		}
		size_t tmp = uuid[i];
		*p++ = fmt[tmp >> 4];
		*p++ = fmt[tmp & 15];
	}
	*p = '\0';
}

void uuid_unparse_lower(const uuid_t uu, char *out)
{
	uuid_fmt(uu, out, hexdigits_lower);
}

void uuid_unparse_upper(const uuid_t uu, char *out)
{
	uuid_fmt(uu, out, hexdigits_upper);
}

void uuid_unparse(const uuid_t uu, char *out)
{
#ifdef UUID_UNPARSE_DEFAULT_UPPER
	uuid_fmt(uu, out, hexdigits_upper);
#else
	uuid_fmt(uu, out, hexdigits_lower);
#endif
}
