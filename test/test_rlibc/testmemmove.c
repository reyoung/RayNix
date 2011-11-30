/* memmove.c
 *
 * Copyright (C) 2005-2008 Guillaume Duranceau
 * This file is part of the CROCOS test suite.
 */

#include "string.h"
extern void exit(int);
#define LOOP 5
/* SIZE should be a multiple of 8 */
#define SIZE (8*10)

int main () {
    char t1[LOOP][SIZE], t2[LOOP][SIZE];
    int i, j;

    for (j = 0; j < LOOP; j++) {
        for (i = 0; i < SIZE; i++) t1[j][i] = i;
        memmove (t2[j], t1[j], SIZE);
        for (i = 0; i < SIZE; i++) if (t1[j][i] != t2[j][i]) exit (1);
        memmove (t2[j], &(t2[j][SIZE/8]), SIZE/4);
        for (i = 0; i < SIZE/4; i++) if (t2[j][i] != (i+SIZE/8)) exit (2); 
        memmove (&(t2[j][SIZE-SIZE/4]), &(t2[j][SIZE-SIZE/4-SIZE/8]), SIZE/4);
        for (i = SIZE-SIZE/4; i < SIZE; i++)
            if (t2[j][i] != (i-SIZE/8)) exit (3);
    }
    return 0;
}

