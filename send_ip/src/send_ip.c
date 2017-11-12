/*
 ============================================================================
 Name        : send_ip.c
 Author      : Wojciech Żyszkowski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()
#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t, uint32_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_RAW, IPPROTO_IP, IPPROTO_TCP, INET_ADDRSTRLEN
#include <netinet/ip.h>       // struct ip and IP_MAXPACKET (which is 65535)
#define __FAVOR_BSD           // Use BSD format of tcp header
#include <netinet/tcp.h>      // struct tcphdr
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <errno.h>            // errno, perror()
// Define some constants.
#define IP4_HDRLEN 20         // IPv4 header length
#define TCP_HDRLEN 20         // TCP header length, excludes options data
// Function prototypes
uint16_t checksum(uint16_t *, int);
uint16_t tcp4_checksum(struct ip, struct tcphdr);
char *allocate_strmem(int);
uint8_t *allocate_ustrmem(int);
int *allocate_intmem(int);

//wskaźniki na funkcje
void (*IF)(char *, char *);
void (*IPZ)(char *, char*);
void (*IPD)(char *, char*);
void (*PZ)(struct tcphdr *, int);
void (*PD)(struct tcphdr *, int);
void (*SN)(struct tcphdr *, int);
void (*NP)(struct tcphdr *, int);
void (*RE)(struct tcphdr*, int);
void (*DO)(struct tcphdr*, int);
void (*UDO)(struct tcphdr*, int);
void (*WDP)(struct tcphdr*, int);

char *instrukcja = "--instrukcja";
char *portzrodlowy = "--portzrodlowy";
int portzrodlowyint = 667;
char *portdocelowy = "--portdocelowy";
int portdocelowyint = 666;
char *numersekwencyjny = "--numersekwencyjny";
int numersekwencyjnyint = 0;
char *nrpotwierdzanegobajtu = "--nrpotwierdzanegobajtu";
int nrpotwierdzanegobajtuint = 0;
char *zarezerwowane = "--zarezerwowane";
int zarezerwowaneint = 0;
char *znacznikFIN = "--znacznikFIN";
int znacznikFINint = 0;
char *znacznikSYN = "--znacznikSYN";
int znacznikSYNint = 1;
char *znacznikRST = "--znacznikRST";
int znacznikRSTint = 0;
char *znacznikPSH = "--znacznikPSH";
int znacznikPSHint = 0;
char *znacznikACK = "--znacznikACK";
int znacznikACKint = 0;
char *znacznikURG = "--znacznikURG";
int znacznikURGint = 0;
char *znacznikECE = "--znacznikECE";
int znacznikECEint = 0;
char *znacznikCWR = "--znacznikCWR";
int znacznikCWRint = 0;
char *rozmiarokna = "--rozmiarokna";
int rozmiaroknaint = 65535;
char *wskdanychpilnych = "--wskdanychpilnych";
int wskdanychpilnychint = 0;
char *interfejs = "--interfejs";
//char *interfejschar="wlp3s0";
char *interfejschar = "lo";
char *ipzrodlowy = "--ipzrodlowy";
char ipzrodlowychar[] = "192.168.0.227";
char *ipdocelowy = "--ipdocelowy";
char ipdocelowychar[] = "127.0.0.1";
char *ttl = "--ttl";
int ttlint = 255;
char *typuslugi = "--typuslugi";
int typuslugiint = 0;
char *sumaktcp = "--sumatcp";
int sumaktcpint = 1;
int sumatcp = 0;

int i;

int main(int argc, char* argv[]) {

	puts("USTAWIONO PARAMETRY:");
	puts("===================================");

	void *Biblioteka; // wskaznik do bilbioteki

	Biblioteka = dlopen(
			"/home/wojciech/Pulpit/Projekt/origin/send_ip/src/biblioteka.so",
			RTLD_LAZY);

	for (i = 1; i < argc; i++) {
		char *argv1 = argv[i];
		if (0 == strcmp(instrukcja, argv1)) {

			printf(
					"Jeżeli chcesz wysłać pakiet IPv4+TCP możesz użyć następujących komend:\n--ipzrodlowy [podaj adres IP] \n--ipdocelowy [podaj adres IP] \n--interfejs [nazwa interfejsu] \n--portzrodlowy [podaj nr portu]\n");
			printf(
					"--portdocelowy [podaj numer portu] \n--numersekwencyjny [podaj numer] \n--nrpotwierdzanegobajtu [podaj numer] \n--zarezerwowane [podaj numer] \n--znacznikFIN [podaj numer] \n--znacznikSYN [podaj numer] \n--znacznikRST [podaj numer] \n--znacznikPSH [podaj numer] \n--znacznikACK [podaj numer] \n--znacznikURG [podaj numer] \n--znacznikECE [podaj numer] \n--znacznikCWR [podaj numer] \n--rozmiarokna [podaj rozmiar] \n--wskdanychpilnych [podaj numer]\n--typuslugi [podaj numer]\n--ttl [podaj numer]\n--sumatcp [podaj numer]\nPrzykładowa linijka zmieniająca wszystkie pola: sudo ./send_ip --portdocelowy 777 --ipzrodlowy 123.232.121.111 --ipdocelowy 197.187.145.126 --rozmiarokna 12 --wskdanychpilnych22\n ");
			exit(0);
		}

		if (0 == strcmp(numersekwencyjny, argv1)) {
			numersekwencyjnyint = (argv1[i + 1]);

			printf("numer sekwencyjny %d\n", numersekwencyjnyint);
		}

		if (0 == strcmp(portzrodlowy, argv1)) {

			portzrodlowyint = atoi(argv[i + 1]);
			printf("port zrodlowy %d\n", portzrodlowyint);
		}
		if (0 == strcmp(portdocelowy, argv1)) {

			portdocelowyint = atoi(argv[i + 1]);
			printf("port docelowy %d\n", portdocelowyint);
		}
		if (0 == strcmp(nrpotwierdzanegobajtu, argv1)) {

			nrpotwierdzanegobajtuint = atoi(argv[i + 1]);
			printf("numer potwierdzanego bajtu %d\n", nrpotwierdzanegobajtuint);

		}
		if (0 == strcmp(zarezerwowane, argv1)) {

			zarezerwowaneint = atoi(argv[i + 1]);
			printf("zarezerwowane %d\n", zarezerwowaneint);
		}

		if (0 == strcmp(znacznikFIN, argv1)) {

			znacznikFINint = atoi(argv[i + 1]);
			printf("znacznik FIN %d\n", znacznikFINint);
		}
		if (0 == strcmp(znacznikSYN, argv1)) {

			znacznikSYNint = atoi(argv[i + 1]);
			printf("znaczik SYN %d\n", znacznikSYNint);
		}
		if (0 == strcmp(znacznikRST, argv1)) {

			znacznikRSTint = atoi(argv[i + 1]);
			printf("znacznik RST %d\n", znacznikRSTint);
		}
		if (0 == strcmp(znacznikPSH, argv1)) {

			znacznikPSHint = atoi(argv[i + 1]);
			printf("znacznik PSH %d\n", znacznikPSHint);
		}
		if (0 == strcmp(znacznikACK, argv1)) {

			znacznikACKint = atoi(argv[i + 1]);
			printf("znacznik ACK %d\n", znacznikACKint);

		}
		if (0 == strcmp(znacznikURG, argv1)) {

			znacznikURGint = atoi(argv[i + 1]);
			printf("znacznik URG %d\n", znacznikURGint);
		}
		if (0 == strcmp(znacznikECE, argv1)) {

			znacznikECEint = atoi(argv[i + 1]);
			printf("znacznik ECE %d\n", znacznikECEint);
		}
		if (0 == strcmp(znacznikURG, argv1)) {

			znacznikURGint = atoi(argv[i + 1]);
			printf("znacznik URG %d\n", znacznikURGint);
		}
		if (0 == strcmp(znacznikCWR, argv1)) {

			znacznikCWRint = atoi(argv[i + 1]);
			printf("znacznik CWR %d\n", znacznikCWRint);
		}
		if (0 == strcmp(rozmiarokna, argv1)) {

			rozmiaroknaint = atoi(argv[i + 1]);
			printf("rozmiar okna %d\n", rozmiaroknaint);
		}
		if (0 == strcmp(wskdanychpilnych, argv1)) {

			wskdanychpilnychint = atoi(argv[i + 1]);
			printf("wskaznik danych pilnych %d\n", wskdanychpilnychint);
		}
		if (0 == strcmp(interfejs, argv1)) {

			interfejschar = argv[i + 1];
			printf("interfejs %s\n", interfejschar);
		}
		if (0 == strcmp(ipzrodlowy, argv1)) {

			strcpy(ipzrodlowychar, argv[i + 1]);

			printf("IP źródłowy %s\n", ipzrodlowychar);
		}
		if (0 == strcmp(ipdocelowy, argv1)) {

			strcpy(ipdocelowychar, argv[i + 1]);

			printf("IP docelowy %s\n", ipdocelowychar);
		}
		if (0 == strcmp(ttl, argv1)) {

			ttlint = atoi(argv[i + 1]);

			printf("Time to live  %d\n", ttlint);
		}
		if (0 == strcmp(typuslugi, argv1)) {

			typuslugiint = atoi(argv[i + 1]);

			printf("Typ usługi  %d\n", typuslugiint);
		}

		if (0 == strcmp(sumaktcp, argv1)) {

			sumaktcpint = atoi(argv[i + 1]);

			printf("Suma Kontrolna TCP  %d\n", sumaktcpint);
		}

	}

	int i, status, sd, *ip_flags, *tcp_flags;
	const int on = 1;
	char *interface, *target, *src_ip, *dst_ip;
	struct ip iphdr;
	struct tcphdr tcphdr;
	uint8_t *packet;
	struct addrinfo hints, *res;
	struct sockaddr_in *ipv4, sin;
	struct ifreq ifr;
	void *tmp;

	// rezerwacja pamieci dla tablic
	packet = allocate_ustrmem(IP_MAXPACKET);
	interface = allocate_strmem(40);
	target = allocate_strmem(40);
	src_ip = allocate_strmem(INET_ADDRSTRLEN);
	dst_ip = allocate_strmem(INET_ADDRSTRLEN);
	ip_flags = allocate_intmem(4);
	tcp_flags = allocate_intmem(8);

	// skonfigurowanie interfejsu

	IF = dlsym(Biblioteka, "Ustaw_Interfejs");
	IF(interface, interfejschar);

	// Wysłanie zadania abu sprawdzic deskryptor soketa
	if ((sd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("socket() failed to get socket descriptor for using ioctl() ");
		exit(EXIT_FAILURE);
	}

	//sprawdzenie numeru interfejsu i bindowanie
	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", interface);
	if (ioctl(sd, SIOCGIFINDEX, &ifr) < 0) {
		perror("ioctl() failed to find interface ");
		return (EXIT_FAILURE);
	}
	close(sd);

	// Adres zrodlowy
	IPZ = dlsym(Biblioteka, "Ustaw_IP_Zrodlowe");
	IPZ(src_ip, ipzrodlowychar);

	// adres docelowy
	IPD = dlsym(Biblioteka, "Ustaw_IP_Docelowe");
	IPD(target, ipdocelowychar);

	// wypelnienie hints dla getaddrinfo().
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = hints.ai_flags | AI_CANONNAME;

	if ((status = getaddrinfo(target, NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	ipv4 = (struct sockaddr_in *) res->ai_addr;
	tmp = &(ipv4->sin_addr);
	if (inet_ntop(AF_INET, tmp, dst_ip, INET_ADDRSTRLEN) == NULL ) {
		status = errno;
		fprintf(stderr, "inet_ntop() failed.\nError message: %s",
				strerror(status));
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

	// naglowek ipv4

	// dlugosc naglowka ipv4
	iphdr.ip_hl = IP4_HDRLEN / sizeof(uint32_t);

	// wersja ip
	iphdr.ip_v = 4;

	// Typ usługi
	iphdr.ip_tos = typuslugiint;

	// długość datagramu czyli IP header + TCP header
	iphdr.ip_len = htons(IP4_HDRLEN + TCP_HDRLEN);

	//numer sekwencyjny- brak przy jednym datagramie
	iphdr.ip_id = htons(0);

	// Fragmentacja

	// Zero (1 bit)
	ip_flags[0] = 0;

	// Do not fragment flag (1 bit)
	ip_flags[1] = 0;

	// More fragments following flag (1 bit)
	ip_flags[2] = 0;

	// Fragmentation offset (13 bits)
	ip_flags[3] = 0;

	iphdr.ip_off = htons(
			(ip_flags[0] << 15) + (ip_flags[1] << 14) + (ip_flags[2] << 13)
					+ ip_flags[3]);

	// Time-to-Live (8 bits): default to maximum value
	iphdr.ip_ttl = ttlint;

	// Transport layer protocol (8 bits): 6 for TCP
	iphdr.ip_p = IPPROTO_TCP;

	// Source IPv4 address (32 bits)
	if ((status = inet_pton(AF_INET, src_ip, &(iphdr.ip_src))) != 1) {
		fprintf(stderr, "inet_pton() failed.\nError message: %s",
				strerror(status));
		exit(EXIT_FAILURE);
	}

	// Destination IPv4 address (32 bits)
	if ((status = inet_pton(AF_INET, dst_ip, &(iphdr.ip_dst))) != 1) {
		fprintf(stderr, "inet_pton() failed.\nError message: %s",
				strerror(status));
		exit(EXIT_FAILURE);
	}

	// IPv4 header checksum (16 bits): set to 0 when calculating checksum
	iphdr.ip_sum = 0;
	iphdr.ip_sum = checksum((uint16_t *) &iphdr, IP4_HDRLEN);

	// TCP header

	// Source port number (16 bits)

	PZ = dlsym(Biblioteka, "Ustaw_Port_Zrodlowy");
	PZ(&tcphdr, portzrodlowyint);

	// Destination port number (16 bits)

	PD = dlsym(Biblioteka, "Ustaw_Port_Docelowy");
	PD(&tcphdr, portdocelowyint);

	// Sequence number (32 bits)

	SN = dlsym(Biblioteka, "Ustaw_Numer_Sekwencyjny");
	SN(&tcphdr, numersekwencyjnyint);

	// Acknowledgement number (32 bits): 0 in first packet of SYN/ACK process
	NP = dlsym(Biblioteka, "Ustaw_Nr_Potw_Bajtu");
	NP(&tcphdr, nrpotwierdzanegobajtuint);

	// Reserved (4 bits): should be 0
	RE = dlsym(Biblioteka, "Ustaw_Zarezerwowane");
	RE(&tcphdr, zarezerwowaneint);

	// Data offset (4 bits): size of TCP header in 32-bit words
	DO = dlsym(Biblioteka, "Data_Offset");
	DO(&tcphdr, TCP_HDRLEN);

	// Flags (8 bits)

	// FIN flag (1 bit)

	tcp_flags[0] = znacznikFINint;

	// SYN flag (1 bit): set to 1
	tcp_flags[1] = znacznikSYNint;

	// RST flag (1 bit)
	tcp_flags[2] = znacznikRSTint;

	// PSH flag (1 bit)
	tcp_flags[3] = znacznikPSHint;

	// ACK flag (1 bit)
	tcp_flags[4] = znacznikACKint;

	// URG flag (1 bit)
	tcp_flags[5] = znacznikURGint;

	// ECE flag (1 bit)
	tcp_flags[6] = znacznikECEint;

	// CWR flag (1 bit)
	tcp_flags[7] = znacznikCWRint;

	tcphdr.th_flags = 0;
	for (i = 0; i < 8; i++) {
		tcphdr.th_flags += (tcp_flags[i] << i);
	}

	// Window size (16 bits)
	UDO = dlsym(Biblioteka, "Ustaw_Rozmiar_Okna");
	UDO(&tcphdr, rozmiaroknaint);

	// Urgent pointer (16 bits): 0 (only valid if URG flag is set)
	WDP = dlsym(Biblioteka, "Ustaw_Wsk_Danych_Pilnych");
	WDP(&tcphdr, wskdanychpilnychint);

	// TCP checksum (16 bits)

	if (sumaktcpint != 1) {
		tcphdr.th_sum = sumaktcpint;
	}
	if (sumaktcpint == 1) {
		tcphdr.th_sum = tcp4_checksum(iphdr, tcphdr);
		;
	}

	// Prepare packet.

	// Naglowek IPv4
	memcpy(packet, &iphdr, IP4_HDRLEN * sizeof(uint8_t));

	// Naglowek protokolu warstwy wyzszej
	memcpy((packet + IP4_HDRLEN), &tcphdr, TCP_HDRLEN * sizeof(uint8_t));

	// przygotowanie naglowka ethernet-podajemy docelowy adres zeby wiedziec gdzie wyslac datagram i do sendto()
	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = iphdr.ip_dst.s_addr;

	// żadanie deskryptora socketa
	if ((sd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("socket() failed ");
		exit(EXIT_FAILURE);
	}

	//ustawienie flagi socketa na naglowek ipv4
	if (setsockopt(sd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		perror("setsockopt() failed to set IP_HDRINCL ");
		exit(EXIT_FAILURE);
	}

	//zbidnowanie socketa na interfejs
	if (setsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr)) < 0) {
		perror("setsockopt() failed to bind to interface ");
		exit(EXIT_FAILURE);
	}

	// funkcja wysylajaca pakiet
	if (sendto(sd, packet, IP4_HDRLEN + TCP_HDRLEN, 0, (struct sockaddr *) &sin,
			sizeof(struct sockaddr)) < 0) {
		perror("sendto() failed ");
		exit(EXIT_FAILURE);
	}

	// zamkniecie socketa deskryptor
	close(sd);

	// zwolnienie pamieci
	free(packet);
	free(interface);
	free(target);
	free(src_ip);
	free(dst_ip);
	free(ip_flags);
	free(tcp_flags);

}

// Computing the internet checksum (RFC 1071).
uint16_t checksum(uint16_t *addr, int len) {
	int count = len;
	register uint32_t sum = 0;
	uint16_t answer = 0;

	// Sum up 2-byte values until none or only one byte left.
	while (count > 1) {
		sum += *(addr++);
		count -= 2;
	}

	// Add left-over byte, if any.
	if (count > 0) {
		sum += *(uint8_t *) addr;
	}

	// Fold 32-bit sum into 16 bits; we lose information by doing this,
	// increasing the chances of a collision.
	// sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
	while (sum >> 16) {
		sum = (sum & 0xffff) + (sum >> 16);
	}

	// Checksum is one's compliment of sum.
	answer = ~sum;

	return (answer);
}

// Build IPv4 TCP pseudo-header and call checksum function.
uint16_t tcp4_checksum(struct ip iphdr, struct tcphdr tcphdr) {
	uint16_t svalue;
	char buf[IP_MAXPACKET], cvalue;
	char *ptr;
	int chksumlen = 0;

	// ptr points to beginning of buffer buf
	ptr = &buf[0];

	// Copy source IP address into buf (32 bits)
	memcpy(ptr, &iphdr.ip_src.s_addr, sizeof(iphdr.ip_src.s_addr));
	ptr += sizeof(iphdr.ip_src.s_addr);
	chksumlen += sizeof(iphdr.ip_src.s_addr);

	// Copy destination IP address into buf (32 bits)
	memcpy(ptr, &iphdr.ip_dst.s_addr, sizeof(iphdr.ip_dst.s_addr));
	ptr += sizeof(iphdr.ip_dst.s_addr);
	chksumlen += sizeof(iphdr.ip_dst.s_addr);

	// Copy zero field to buf (8 bits)
	*ptr = 0;
	ptr++;
	chksumlen += 1;

	// Copy transport layer protocol to buf (8 bits)
	memcpy(ptr, &iphdr.ip_p, sizeof(iphdr.ip_p));
	ptr += sizeof(iphdr.ip_p);
	chksumlen += sizeof(iphdr.ip_p);

	// Copy TCP length to buf (16 bits)
	svalue = htons(sizeof(tcphdr));
	memcpy(ptr, &svalue, sizeof(svalue));
	ptr += sizeof(svalue);
	chksumlen += sizeof(svalue);

	// Copy TCP source port to buf (16 bits)
	memcpy(ptr, &tcphdr.th_sport, sizeof(tcphdr.th_sport));
	ptr += sizeof(tcphdr.th_sport);
	chksumlen += sizeof(tcphdr.th_sport);

	// Copy TCP destination port to buf (16 bits)
	memcpy(ptr, &tcphdr.th_dport, sizeof(tcphdr.th_dport));
	ptr += sizeof(tcphdr.th_dport);
	chksumlen += sizeof(tcphdr.th_dport);

	// Copy sequence number to buf (32 bits)
	memcpy(ptr, &tcphdr.th_seq, sizeof(tcphdr.th_seq));
	ptr += sizeof(tcphdr.th_seq);
	chksumlen += sizeof(tcphdr.th_seq);

	// Copy acknowledgement number to buf (32 bits)
	memcpy(ptr, &tcphdr.th_ack, sizeof(tcphdr.th_ack));
	ptr += sizeof(tcphdr.th_ack);
	chksumlen += sizeof(tcphdr.th_ack);

	// Copy data offset to buf (4 bits) and
	// copy reserved bits to buf (4 bits)
	cvalue = (tcphdr.th_off << 4) + tcphdr.th_x2;
	memcpy(ptr, &cvalue, sizeof(cvalue));
	ptr += sizeof(cvalue);
	chksumlen += sizeof(cvalue);

	// Copy TCP flags to buf (8 bits)
	memcpy(ptr, &tcphdr.th_flags, sizeof(tcphdr.th_flags));
	ptr += sizeof(tcphdr.th_flags);
	chksumlen += sizeof(tcphdr.th_flags);

	// Copy TCP window size to buf (16 bits)
	memcpy(ptr, &tcphdr.th_win, sizeof(tcphdr.th_win));
	ptr += sizeof(tcphdr.th_win);
	chksumlen += sizeof(tcphdr.th_win);

	// Copy TCP checksum to buf (16 bits)
	// Zero, since we don't know it yet
	*ptr = 0;
	ptr++;
	*ptr = 0;
	ptr++;
	chksumlen += 2;

	// Copy urgent pointer to buf (16 bits)
	memcpy(ptr, &tcphdr.th_urp, sizeof(tcphdr.th_urp));
	ptr += sizeof(tcphdr.th_urp);
	chksumlen += sizeof(tcphdr.th_urp);

	return checksum((uint16_t *) buf, chksumlen);
}

//Alokacja pamięci na tablicę charów
char *
allocate_strmem(int len) {
	void *tmp;

	if (len <= 0) {
		fprintf(stderr,
				"ERROR: Cannot allocate memory because len = %i in allocate_strmem().\n",
				len);
		exit(EXIT_FAILURE);
	}

	tmp = (char *) malloc(len * sizeof(char));
	if (tmp != NULL ) {
		memset(tmp, 0, len * sizeof(char));
		return (tmp);
	} else {
		fprintf(stderr,
				"ERROR: Cannot allocate memory for array allocate_strmem().\n");
		exit(EXIT_FAILURE);
	}
}

//Alokacja pamięci na tablicę ucharów
uint8_t *
allocate_ustrmem(int len) {
	void *tmp;

	if (len <= 0) {
		fprintf(stderr,
				"ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n",
				len);
		exit(EXIT_FAILURE);
	}

	tmp = (uint8_t *) malloc(len * sizeof(uint8_t));
	if (tmp != NULL ) {
		memset(tmp, 0, len * sizeof(uint8_t));
		return (tmp);
	} else {
		fprintf(stderr,
				"ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
		exit(EXIT_FAILURE);
	}
}

//Alokacja pamięci na tablice intów
int *
allocate_intmem(int len) {
	void *tmp;

	if (len <= 0) {
		fprintf(stderr,
				"ERROR: Cannot allocate memory because len = %i in allocate_intmem().\n",
				len);
		exit(EXIT_FAILURE);
	}

	tmp = (int *) malloc(len * sizeof(int));
	if (tmp != NULL ) {
		memset(tmp, 0, len * sizeof(int));
		return (tmp);
	} else {
		fprintf(stderr,
				"ERROR: Cannot allocate memory for array allocate_intmem().\n");
		exit(EXIT_FAILURE);
	}
}
