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
void Ustaw_Numer_Sekwencyjny(struct tcphdr *tcphdr, int numersekwencyjnyint);
void Ustaw_Nr_Potw_Bajtu(struct tcphdr *tcphdr, int nrpotwierdzanegobajtuint);
void Ustaw_Zarezerwowane(struct tcphdr *tcphdr, int zarezerwowaneint);
void Data_Offset(struct tcphdr *tcphdr, int TCP_HDRLEN);
void Ustaw_Rozmiar_Okna(struct tcphdr * tcphdr,int rozmiaroknaint);
void Ustaw_Wsk_Danych_Pilnych(struct tcphdr * tcphdr,int rozmiaroknaint);

#endif /* BIBLIOTEKA_H_ */
