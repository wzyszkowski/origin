/*
 * biblioteka.h
 *
 *  Created on: 05-11-2017
 *      Author: wojciech
 */

#ifndef BIBLIOTEKA_H_
#define BIBLIOTEKA_H_
void Ustaw_Interfejs(char * interface, char * interfejschar);
void Ustaw_IP_Zrodlowe(char * src_ip, char  *ipzrodlowychar);
void Ustaw_IP_Docelowe (char * target, char * ipdocelowychar);
void Ustaw_Port_Zrodlowy(struct tcphdr * tcphdr, int portzrodlowyint);
void Ustaw_Port_Docelowy(struct tcphdr *tcphdr, int portdocelowyint);

#endif /* BIBLIOTEKA_H_ */
