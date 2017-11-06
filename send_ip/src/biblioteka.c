/*
 * biblioteka.c

 *
 *  Created on: 28-10-2017
 *      Author: wojciech
 */

#include <string.h>
#include <stdio.h>
#include <netinet/ip6.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/tcp.h>



void Ustaw_Interfejs(char * interface, char * interfejschar) {
	strcpy(interface, interfejschar);
}
void Ustaw_IP_Zrodlowe(char * src_ip, char * ipzrodlowychar)
{
strcpy(src_ip,ipzrodlowychar);
}

void Ustaw_IP_Docelowe (char * target, char * ipdocelowychar)
{
strcpy(target,ipdocelowychar);
}

void Ustaw_Port_Zrodlowy(struct tcphdr *tcphdr, int portzrodlowyint)
{

	tcphdr->th_sport = htons(portzrodlowyint);
}

void Ustaw_Port_Docelowy(struct tcphdr *tcphdr, int portdocelowyint)
{
tcphdr->th_dport = htons(portdocelowyint);
}


