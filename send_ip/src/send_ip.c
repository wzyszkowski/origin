/*
 ============================================================================
 Name        : send_ip.c
 Author      : Wojciech Żyszkowski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i = 0;
    for (i = 0; i < argc; i++) {
        printf("Argument numer %d = %s\n", i, argv[i]);
    }
    return 0;

}
