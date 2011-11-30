/* strncpy.c
 *
 * Copyright (C) 2005-2008 Guillaume Duranceau
 * This file is part of the CROCOS test suite.
 */

#include "string.h"
extern void exit(int);
#define MAX_SIZE 80
#define SYMB '#'

#define TEST_STRNCPY(dest, str, n)                                  \
({  strncpy ((dest), (str), n);                                     \
    i = 0;                                                          \
    while ((i<n) && ((str)[i]!=0) && ((str)[i])==(dest)[i]) i++;    \
 })

#define TEST_SHORT_STRNCPY(dest, str, n, error1, error2)    \
({  TEST_STRNCPY (dest, str, n);                            \
    if ((str)[i]!=(dest)[i]) exit (error1);                \
    for (; i<n; i++) if ((dest)[i]!=0) exit (error2);      \
 })

#define TEST_LONG_STRNCPY(dest, str, n, error)  \
({  TEST_STRNCPY (dest, str, n);                \
    if ((dest)[i]!=SYMB) exit (error);         \
 })

int main () {
    char *str1 = "coucou";
    char *str2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char *str3 = "";
    char dest1[MAX_SIZE];
    char dest2[MAX_SIZE];
    char dest3[MAX_SIZE];
    int i;
    
    for (i = 0; i < MAX_SIZE; i++) dest1[i] = dest2[i] = dest3[i] = SYMB;
    
    TEST_SHORT_STRNCPY (dest1, str1, 7,  1, 2);
    TEST_LONG_STRNCPY  (dest2, str2, 26, 3);
    TEST_SHORT_STRNCPY (dest3, str3, 10, 4, 5);
    return 0;    
}

