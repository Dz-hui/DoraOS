#ifndef _FORMAT_H_
#define _FORMAT_H_

#include <dos_def.h>
#include <stdarg.h>

#define FORMAT_BUF_LEN 12

/* Format states */
#define S_DEFAULT   0
#define S_FLAGS     1
#define S_WIDTH     2
#define S_PRECIS    3
#define S_LENGTH    4
#define S_CONV      5

/* Lenght flags */
#define L_CHAR      1
#define L_SHORT     2
#define L_LONG      3
#define L_LLONG     4
#define L_DOUBLE    5

#define F_ALTERNATE 0001    // put 0x infront 16, 0 on octals, b on binary
#define F_ZEROPAD   0002    // value should be zero padded
#define F_LEFT      0004    // left justified if set, otherwise right justified
#define F_SPACE     0010    // place a space before positive number
#define F_PLUS      0020    // show +/- on signed numbers, default only for -
#define F_SIGNED    0040    // is an unsigned number?
#define F_SMALL     0100    // use lowercase for hex?

#define is_digit(c) (c >= '0' && c <= '9')

dos_int32 Dos_FormatNStr(dos_char *buf, dos_size size, const dos_char *fmt, va_list ap);


#endif // !_FORMAT_H_

