/* strcpy.c
 *
 * Copyright (C) 2005-2008 Guillaume Duranceau
 * This file is part of the CROCOS test suite.
 */

#include "string.h"
extern void exit(int );
#define MAX_SIZE 80

#define TEST_STRCPY(dest, str, error)                                   \
({  strcpy ((dest), (str));                                             \
    i = 0;                                                              \
    while ((i<MAX_SIZE) && ((str)[i]!=0) && ((str)[i])==(dest)[i]) i++; \
    if ((str)[i]!=(dest)[i]) exit (error);                             \
 })

int main () {
    char *str1 = "coucou";
    char *str2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char *str3 = "";
    char dest[MAX_SIZE];
    int i;
    
    TEST_STRCPY (dest, str1, 1);
    TEST_STRCPY (dest, str2, 2);
    TEST_STRCPY (dest, str3, 3);
    return 0;
}

