#ifndef CTYPE_H_INCLUDED
#define CTYPE_H_INCLUDED



#define islower(c) \
	(((c)<='z'&&(c)>='a'))

#define isupper(c) \
	(((c)<='Z'&&(c)>='A'))

#define isalpha(c) \
	(islower(c)||isupper(c))

#define isdigit(c) \
	(((c)<='9'&&(c)>='0'))

#define isalnum(c) \
	(isalpha(c)||isdigit(c))
	
#define ispunct(c)                          \
    ((((c) >= 0x21) && ((c) <= 0x2f)) ||    \
     (((c) >= 0x3a) && ((c) <= 0x40)) ||    \
     (((c) >= 0x5b) && ((c) <= 0x60)) ||    \
     (((c) >= 0x7b) && ((c) <= 0x7e)))
#define isgraph(c) (((c) >= 0x21) && ((c) <= 0x7e))
#define isspace(c) ((((c) >= 0x09) && ((c) <= 0x0d)) || ((c) == ' '))
#define isprint(c) (((c) >= 0x20) && ((c) <= 0x7e))
#define iscntrl(c) (((c) <= 0x1f) || ((c) == 0x7f))
#define isxdigit(c)                                     \
    (isdigit (c) || (((c) >= 'a') && ((c) <= 'f')) ||   \
    (((c) >= 'A') && ((c) <= 'F')))

#define tolower(c) (isupper (c) ? (c)+'a'-'A' : (c))
#define toupper(c) (islower (c) ? (c)+'A'-'a' : (c))

#endif