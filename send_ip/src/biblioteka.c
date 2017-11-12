/*
 * biblioteka.c

 *
 *  Created on: 28-10-2017
 *      Author: wojciech
 */

#include <string.h>
#include <stdio.h>
#include <netinet/ip6.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <dlfcn.h>

void Ustaw_Interfejs(char * interface, char * interfejschar) {
	strcpy(interface, interfejschar);
}
void Ustaw_IP_Zrodlowe(char * src_ip, char * ipzrodlowychar) {
	strcpy(src_ip, ipzrodlowychar);
}

void Ustaw_IP_Docelowe(char * target, char * ipdocelowychar) {
	strcpy(target, ipdocelowychar);
}

void Ustaw_Port_Zrodlowy(struct tcphdr *tcphdr, int portzrodlowyint) {

	tcphdr->th_sport = htons(portzrodlowyint);
}

void Ustaw_Port_Docelowy(struct tcphdr *tcphdr, int portdocelowyint) {
	tcphdr->th_dport = htons(portdocelowyint);
}

void Ustaw_Numer_Sekwencyjny(struct tcphdr *tcphdr, int numersekwencyjnyint) {
	tcphdr->th_seq = htonl(numersekwencyjnyint);
}

void Ustaw_Nr_Potw_Bajtu(struct tcphdr *tcphdr, int nrpotwierdzanegobajtuint) {
	tcphdr->th_ack = htonl(nrpotwierdzanegobajtuint);
}
void Ustaw_Zarezerwowane(struct tcphdr *tcphdr, int zarezerwowaneint) {
	tcphdr->th_x2 = zarezerwowaneint;
}

void Data_Offset(struct tcphdr *tcphdr, int TCP_HDRLEN) {
	tcphdr->th_off = TCP_HDRLEN / 4;
}
void Ustaw_Rozmiar_Okna(struct tcphdr * tcphdr, int rozmiaroknaint) {
	tcphdr->th_win = htons(rozmiaroknaint);
}
void Ustaw_Wsk_Danych_Pilnych(struct tcphdr * tcphdr, int wskdanychpilnychint) {
	tcphdr->th_urp = htons(wskdanychpilnychint);

}

