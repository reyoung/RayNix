#include "string.h"
extern void exit(int status);
int main () {
    char *str1 = "coucou";
    char *str2 = "cou";
    char *str3 = "coucoucou";
    char *str4 = "abc";
    
    if (strcmp (str1, str1) != 0) exit (1);
    if (strcmp (str2, str2) != 0) exit (2);
    if (strcmp (str3, str3) != 0) exit (3);
    if (strcmp (str4, str4) != 0) exit (4);

    if (strcmp (str1, str2) <= 0) exit (5);
    if (strcmp (str2, str1) >= 0) exit (6);
    if (strcmp (str1, str3) >= 0) exit (7);
    if (strcmp (str3, str1) <= 0) exit (8);
    if (strcmp (str1, str4) <= 0) exit (9);
    if (strcmp (str4, str1) >= 0) exit (10);

    return 0;
}