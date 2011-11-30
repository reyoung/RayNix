/* memcpy.c
 *
 * Copyright (C) 2005-2008 Guillaume Duranceau
 * This file is part of the CROCOS test suite.
 */

#include "string.h"
extern void exit(int );
#define LOOP 5
#define SIZE 80

int main () {
    char t1[LOOP][SIZE], t2[LOOP][SIZE];
    int i, j;
    
    for (j = 0; j < LOOP; j++) {
        for (i = 0; i < SIZE; i++) t1[j][i] = i;
        memcpy (t2[j], t1[j], SIZE);
        for (i = 0; i < SIZE; i++) if (t1[j][i] != t2[j][i]) exit (1);
    }
    return 0;
}

