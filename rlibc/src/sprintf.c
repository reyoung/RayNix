#include "sprintf.h"
#include "stddef.h"
#include "string.h"
#include "ctype.h"
#define LEFT	0x01
#define PLUS	0x02
#define SPACE	0x04
#define SPECIAL	0x08
#define ZERO	0x10
#define SIGN	0x20
#define SMALL	0x40

#ifdef i386
#define LONG_STRSIZE_BASE_2 32
#else
#define LONG_STRSIZE_BASE_2 64
#endif


static int _GetWide(const char** fmt);
static void number_to_string (long num, int base, int flags, int wide,
        int precision, char **s) {
    char sign;  /* sign printed : '+', '-', ' ', or 0 (no sign) */
    int num_cpy = num;
    unsigned long ul_num = (unsigned long) num; /* for unsigned format */

    /* string representation of num (reversed) */
    char tmp[LONG_STRSIZE_BASE_2];
    int i = 0; /* number of figures in tmp */

    const char *digits = "0123456789ABCDEF";
    if (flags & SMALL) digits = "0123456789abcdef";

    if ((base < 2) || (base > 16)) return;

    if ((flags & SIGN) && (num < 0)) { sign = '-'; num = -num; }
    else sign = (flags & PLUS) ? '+' : ((flags & SPACE) ? ' ' : 0);
    if (sign) wide--;

    if (flags & SPECIAL) {
        if ((base == 16) && (num != 0)) wide -= 2;  /* '0x' or '0X' */
        if (base == 8) { wide--; precision--; }     /* '0' */
    }
    
    if (num == 0) tmp[i++] = '0';
    /* signed format */
    if (flags & SIGN) {
        while (num != 0) {
            tmp[i++] = digits[num % base];
            num = num / base;
        } 
    }
    /* unsigned format */
    else {
        while (ul_num != 0) {
            tmp[i++] = digits[ul_num % base];
            ul_num = ul_num / base;
        } 
    }

    if (i > precision) precision = i;
    wide -= precision;

    /* wide = number of padding chars */
    /* precision = number of figures after the sign and the special chars */

    /* right justified and no zeropad : pad with spaces */
    if (!(flags & (LEFT + ZERO))) while (wide-- > 0) *((*s)++) = ' ';

    if (sign) *((*s)++) = sign;
    if ((flags & SPECIAL) && (num_cpy != 0)) {
        if (base == 8) *((*s)++) = '0';
        if (base == 16) {
            *((*s)++) = '0';
            if (flags & SMALL) *((*s)++) = 'x';
            else *((*s)++) = 'X';
        }
    }

    /* rigth justified and zeropad : pad with 0 */
    if (!(flags & LEFT)) while (wide-- > 0) *((*s)++) = '0';

    /* print num */
    while (i < precision--) *((*s)++) = '0';
    while (i-- > 0) *((*s)++) = tmp[i];

    /* left justfied : pad with spaces */
    while (wide-- > 0) *((*s)++) = ' ';
}




int sprintf(char* str, const char* fmt , ...){
	va_list args;
	int res;
	va_start(args,fmt);
	res = vsprintf(str,fmt,args);
	va_end(args);
	return res;
}

int vsprintf(char* str,const char* fmt,va_list args){
	char ch;
	char* start = str;
	int flags=0;
	int wide;
	int precision;
	char qualifier;
	char *s;
	int i, len, base;
	va_list ap = args;
	while((ch=*fmt++)!=0){
		if(ch!='%'){
			*str++=ch;
		} else {
			// Get Flag
			while(True){
				if(*fmt=='-'){
					flags|=LEFT;
					++fmt;
				} else if (*fmt=='+'){
					flags|=PLUS;
					++fmt;
				} else if (*fmt==' '){
					flags|=SPACE;
					++fmt;
				} else if (*fmt=='#'){
					flags|=SPECIAL;
					++fmt;
				} else if (*fmt=='0'){
					flags|=ZERO;
					++fmt;
				} else {
					break;
				}
			}		
			// Get Width
			wide = -1;
			if(isdigit(*fmt)){
				wide = _GetWide(&fmt);
			} else if(*fmt=='*'){
				wide = va_arg(args,int);
				++fmt;
			}
			// Get Precision
			precision = -1;
			if(*fmt=='.'){
				++fmt;
				if(isdigit(*fmt)){
					precision = _GetWide(&fmt);
				} else if (*fmt=='*'){
					++fmt;
					precision = va_arg(args,int);
				} else {
					precision = 0;
				}
			}
			qualifier = -1;
			if((*fmt)=='h'||(*fmt)=='l') qualifier=*fmt++;
			
			// TODO Complete Special Chars.
		        switch (*fmt++) {
		            case 'i':
		            case 'd':
		                flags |= SIGN;
		                if (precision != -1) flags &= ~ZERO;
                		switch (qualifier) {
		                    case 'h':
                		        number_to_string ((short) va_arg (ap, int), 10, flags,
		                            wide, precision, &str);
                		        break;
		                    case 'l':
		                        number_to_string (va_arg (ap, long), 10, flags,
		                            wide, precision, &str);
                		        break;
		                    default:
                		        number_to_string (va_arg (ap, int), 10, flags,
		                            wide, precision, &str);
                		        break;
                		}
		                break;
		            case 'u':
                		base = 10;
		                goto num_to_str_without_sign;
		            case 'o':
		                base = 8;
                		goto num_to_str_without_sign;
		            case 'x':
                		flags |= SMALL;
		            case 'X':
		                base = 16;
  		              num_to_str_without_sign:
		                flags &= (~PLUS & ~SPACE);
                		if (precision != -1) flags &= ~ZERO;
		                switch (qualifier) {
                		    case 'h':
		                        number_to_string ((unsigned short) va_arg (ap, int),
		                            base, flags, wide, precision, &str);
                		        break;
		                    case 'l':
                		        number_to_string ((unsigned long) va_arg (ap, long),
		                            base, flags, wide, precision, &str);
                		        break;
		                    default:
                		        number_to_string ((unsigned int) va_arg (ap, int),
		                            base, flags, wide, precision, &str);
                		        break;
		                }
                		break;
		            case 's':
                		s = va_arg (ap, char *);
		                len = strlen (s);
                		if ((precision >= 0) && (len > precision)) len = precision;
           		     /* rigth justified : pad with spaces */
		                if (!(flags & LEFT)) while (len < wide--) *str++ = ' ';
                		for (i = 0; i < len; i++) *str++ = *s++;
          		      /* left justified : pad with spaces */
        		        while (len < wide--) *str++ = ' ';
                		break;
            		case 'c':
                		/* rigth justified : pad with spaces */
		                if (!(flags & LEFT)) while (1 < wide--) *str++ = ' ';
                		*str++ = (unsigned char) va_arg (ap, int);
		                /* left justified : pad with spaces */
                		while (1 < wide--) *str++ = ' ';
		                break;
		            default:
                		return -1;
		        }	
		}
	}
	*str=0;
	return (int)(str-start);
}
static int _GetWide(const char** fmt){
	int retv;
	while(isdigit(**fmt)){
		retv*=10;
		retv+=**fmt;
		++(*fmt);
	}
	return retv;
}


