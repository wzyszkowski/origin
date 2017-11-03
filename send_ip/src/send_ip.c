/*
 ============================================================================
 Name        : send_ip.c
 Author      : Wojciech Żyszkowski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char *argv[])
//{
//    int i = 0;
//    for (i = 0; i < argc; i++) {
//        printf("Argument numer %d = %s\n", i, argv[i]);
//    }
//    return 0;
//
//}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int test, i;

int main(int argc, char* argv[]) {

	char *instrukcja = "--instrukcja";
	char *test = "--test";
	char *portzrodlowy = "--portzrodlowy";
	int portzrodlowyint;
	char *portdocelowy = "--portdocelowy";
	int portdocelowyint;

	for (i = 1; i < argc; i++) { //printf("NUMER:  %d\n",i);
		char *argv1 = argv[i];
		if (0 == strcmp(instrukcja, argv1)) {
			//printf("argv[1] result isaa %s\n", argv[1]);
			printf(
					"Jeżeli chcesz wysłać pakiet IPv4+TCP możesz użyć następujących komend:\n-portzrodlowy [podaj nr portu]\n");
			printf("-portdocelowy [podaj numer portu] \n ");
		}
		if (0 == strcmp(test, argv1)) {
			//printf("argv[1] result isaa %s\n", argv[1]);
			printf("\ntest pomyslny\n");
		}

		if (0 == strcmp(portzrodlowy, argv1)) {

			portzrodlowyint = atoi(argv[i + 1]);
			printf("port zrodlowy %d\n", portzrodlowyint);
		}
		if (0 == strcmp(portdocelowy, argv1)) {

			portdocelowyint = atoi(argv[i + 1]);
			printf("port docelowy %d\n", portdocelowyint);
		}

	}
}

