#include "utf8.h"

#include <alloca.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

static const u_int32_t offsetsFromUTF8[6] = {
	0x00000000UL,
	0x00003080UL,
	0x000E2080UL,
	0x03C82080UL,
	0xFA082080UL,
	0x82082080UL,
};

/* clang-format off */
static const char trailingBytesForUTF8[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
};
/* clang-format on */

int u8_toucs(u_int32_t *dest, int sz, char *src, int srcsz) {
	u_int32_t ch;
	char *	  src_end = src + srcsz;
	int		  nb;
	int		  i = 0;

	while (i < sz - 1) {
		nb = trailingBytesForUTF8[(unsigned char)*src];
		if (srcsz == -1) {
			if (*src == 0) {
				break;
			}
		} else {
			/* stringa troppo piccola per esser utf-8 */
			if (src + nb >= src_end) {
				break;
			}
		}

		ch = 0;
		switch (nb) {
			/* la continuazione tra i diversi case è intenzionale */
		case 3:
			ch += (unsigned char)*src++;
			ch <<= 6;
			/* fall through */
		case 2:
			ch += (unsigned char)*src++;
			ch <<= 6;
			/* fall through */
		case 1:
			ch += (unsigned char)*src++;
			ch <<= 6;
			/* fall through */
		case 0:
			ch += (unsigned char)*src++;
		}
		ch -= offsetsFromUTF8[nb];
		dest[i++] = ch;
	}

	dest[i] = 0;
	return i;
}

int u8_vprintf(const char *fmt, va_list ap) {
	int		   cnt, sz = 0;
	char *	   buf;
	u_int32_t *wcs;

	sz	= 512;
	buf = (char *)alloca(sz);

	while (1) {
		cnt = vsnprintf(buf, sz, fmt, ap);
		if (cnt >= sz) {
			buf = (char *)alloca(cnt - sz + 1);
			sz	= cnt + 1;
		} else {
			break;
		}
	}

	wcs = (u_int32_t *)alloca((cnt + 1) * sizeof(u_int32_t));
	cnt = u8_toucs(wcs, cnt + 1, buf, cnt);
	printf("%ls", (wchar_t *)wcs);
	return cnt;
}

int u8_printf(const char *fmt, ...) {
	int		cnt;
	va_list args;

	va_start(args, fmt);

	cnt = u8_vprintf(fmt, args);

	va_end(args);
	return cnt;
}