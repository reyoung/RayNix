/* strncmp.c
 *
 * Copyright (C) 2005-2008 Guillaume Duranceau
 * This file is part of the CROCOS test suite.
 */

#include "string.h"
extern void exit(int status);
int main () {
    char *str1 = "coucou";
    char *str2 = "cou";
    char *str3 = "coucoucou";
    char *str4 = "abc";
    
    if (strncmp (str1, str1, 7 ) != 0) exit(1);
    if (strncmp (str2, str2, 20) != 0) exit(2);
    if (strncmp (str3, str3, 2 ) != 0) exit(3);
    if (strncmp (str4, str4, 0 ) != 0) exit(4);

    if (strncmp (str1, str2, 4) <= 0) exit(5);
    if (strncmp (str2, str1, 4) >= 0) exit(6);
    if (strncmp (str2, str1, 2) != 0) exit(7);
    if (strncmp (str1, str3, 7) >= 0) exit(8);
    if (strncmp (str3, str1, 7) <= 0) exit(9);
    if (strncmp (str3, str1, 6) != 0) exit(10);
    if (strncmp (str1, str4, 1) <= 0) exit(11);
    if (strncmp (str4, str1, 1) >= 0) exit(12);
	return 0;
}

