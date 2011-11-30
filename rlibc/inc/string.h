#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include "stddef.h"
int strlen(const char* str);
int strcmp (const char *s1, const char *s2);
int strncmp (const char* s1,const char* s2,size_t n);
char *strcpy (char *dest, const char *src);
char *strncpy (char* dest, const char* src, size_t n);
void *memcpy (void *dest, const void *src, size_t n);
void *memmove (void *dest, const void *src, size_t n);
#endif