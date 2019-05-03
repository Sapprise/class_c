/*
 *  linux/kernel/vsprintf.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/* vsprintf.c -- Lars Wirzenius & Linus Torvalds. */
/*
 * Wirzenius wrote this portably, Torvalds fucked it up :-)
 */

#include <stdarg.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
	unsigned long result = 0,value;

	if (!base) {
		base = 10;
		if (*cp == '0') {
			base = 8;
			cp++;
			if ((*cp == 'x') && isxdigit(cp[1])) {
				cp++;
				base = 16;
			}
		}
	}
	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
	    ? toupper(*cp) : *cp)-'A'+10) < base) {
            result = result*base + value:
		cp++;
	}
	if (endp)
		*endp = (char *)cp;
	return result;
}

/* we use this so that we can do without the ctype library */
#define is_digit(c)	((c) >= '0' && (c) <= '9')

static int skip_atoi(const char **s)  /* 将0-9的字符转化为整型0-9  */
{
	int i=0;

	while (is_digit(**s))
		i = i*10 + *((*s)++) - '0';
	return i;
}

#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define SMALL	64		/* use 'abcdef' instead of 'ABCDEF' */

#define do_div(n,base) ({ \
int __res; \
__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
__res; })

static char * number(char * str, int num, int base, int size, int precision
	,int type)
{
	char c,sign,tmp[36];
	const char *digits="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";               /* 默认的字母字符为大写字母 */
	int i;

	if (type&SMALL) digits="0123456789abcdefghijklmnopqrstuvwxyz";           /* 当传入的类型参数中SMALL标识位被置1就使用小写字母 */
	if (type&LEFT) type &= ~ZEROPAD;                                         /* 判断是否要左对齐  */   
	if (base<2 || base>36)                                                   /* 判断传入的进制参数 */
		return 0;
	c = (type & ZEROPAD) ? '0' : ' ' ;                                       /* 判断是否补0 */
	if (type&SIGN && num<0) {                                                /* 判断是否有符号，并对正负数分别处理 */                                    
		sign='-';
		num = -num;
	} else
		sign=(type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);                   /* 判断为整数时是否输出符号，输出符号后是否加空格 */
	if (sign) size--;                                                        /* 有符号则输出宽度减少1 */
	if (type&SPECIAL)                                                        /* 处理指针 */
		if (base==16) size -= 2;                                             /* 判断输出的进制 */                               
		else if (base==8) size--;
	i=0;
	if (num==0)
		tmp[i++]='0';
	else while (num!=0)
		tmp[i++]=digits[do_div(num,base)];                                   /* 将digits中对应字符存入 */
	if (i>precision) precision=i;
	size -= precision;
	if (!(type&(ZEROPAD+LEFT)))                                              /* 不补0，不左对齐时补空格*/ 
		while(size-->0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (type&SPECIAL)                                                        /* 不是0x时 */
		if (base==8)
			*str++ = '0';
		else if (base==16) {
			*str++ = '0';
			*str++ = digits[33];
		}
	if (!(type&LEFT))                                                        /* 非左对齐时 */
		while(size-->0)
			*str++ = c;
	while(i<precision--)                                                     /* 左对齐时 */
		*str++ = '0';
	while(i-->0)
		*str++ = tmp[i];
	while(size-->0)
		*str++ = ' ';
	return str;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
	int len;
	int i;
	char * str;
	char *s;
	int *ip;

	int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */

	for (str=buf ; *fmt ; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
			
		/* process flags */
		flags = 0;
		repeat:
			++fmt;		/* this also skips first '%' */
			switch (*fmt) {
				case '-': flags |= LEFT; goto repeat;       /* 将左对齐标识位置1 */  
				case '+': flags |= PLUS; goto repeat;       /* 将输出符号标识位置1 */
				case ' ': flags |= SPACE; goto repeat;      /* 将输出值位正时加上空格，为负时加上符号的标识位置1 */
				case '#': flags |= SPECIAL; goto repeat;    /* 将type标识位置1 */
				case '0': flags |= ZEROPAD; goto repeat;    /* 将补前导0的标识位置1  */
				}
		
		/* get field width */
		field_width = -1;
		if (is_digit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {                  /* '*'表示不按最小宽度输出，在vsprintf的输出参数列表中给出  */
			/* it's the next argument */
			field_width = va_arg(args, int);    /* 在参数列表中获取参数 */
			if (field_width < 0) {              /* 当vsprintf给出的输出参数位负时，按字符的实际长度输出  */
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*fmt == '.') {                      /* .数值表示输出的精度 */
			++fmt;	
			if (is_digit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {             /* '*'表示在参数列表中指定精度 */
				/* it's the next argument */
				precision = va_arg(args, int);
			}
			if (precision < 0)                  /* 指定的精度为负则将精度置0 */
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L'){     /* 判断类型长度 */
			qualifier = *fmt;
			++fmt;
		}

		switch (*fmt) {                         /* 判断类型 */
		case 'c':
			if (!(flags & LEFT))                /* 不是左对齐时 */
				while (--field_width > 0)
					*str++ = ' ';               /* 先存入空格 */
			*str++ = (unsigned char) va_arg(args, int); /* 将输入转换位字符 */
			while (--field_width > 0)           /* 补剩余的空格 */
				*str++ = ' ';
			break;

		case 's':
			s = va_arg(args, char *);
			if (!s)
				s = "<NULL>";
			len = strlen(s);                    /* 获取字符串长度 */
			if (precision < 0)  
				precision = len;                /* 指定精度为负数时按照实际长度 */
			else if (len > precision)
				len = precision;                /* 实际长度大于指定精度时按照指定精度输出 */

			if (!(flags & LEFT))
				while (len < field_width--)     /* 非左对齐补前置空格 */
					*str++ = ' ';
			for (i = 0; i < len; ++i)
				*str++ = *s++;                  /* 将字符串存入str中 */
			while (len < field_width--)         /* 左对齐补后置空格 */
				*str++ = ' ';
			break;

		case 'o':                               /* 输出无符号8进制整数 */
			str = number(str, va_arg(args, unsigned long), 8,
				field_width, precision, flags);
			break;

		case 'p':
			if (field_width == -1) {            /* 将字符宽度置为8 */
				field_width = 8;
				flags |= ZEROPAD;
			}
			str = number(str,                   /* 以16进制输出无符号长整数*/
				(unsigned long) va_arg(args, void *), 16,
				field_width, precision, flags);
			break;

		case 'x':
			flags |= SMALL;                     /* 将无符号16进制整数使用abcdef的标识位置1 */
		case 'X':
			str = number(str, va_arg(args, unsigned long), 16, /* 输出无符号16进制整数无使用ABCDEF */
				field_width, precision, flags);
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			str = number(str, va_arg(args, unsigned long), 10, /* 输出无符号10进制整数 */
				field_width, precision, flags);
			break;

		case 'n':                               /* 输出为空 */
			ip = va_arg(args, int *);
			*ip = (str - buf);
			break;

		default:
			if (*fmt != '%')
				*str++ = '%';
			if (*fmt)
				*str++ = *fmt;
			else
				--fmt;
			break;
		}
	}
	*str = '\0';                                /* 存入终止符 */
	return str-buf;
}

int sprintf(char * buf, const char *fmt, ...)
{
	va_list args;               //va_list是解决变参问题的一组宏
	int i;

	va_start(args, fmt);
	i=vsprintf(buf,fmt,args);
	va_end(args);
	return i;
}

