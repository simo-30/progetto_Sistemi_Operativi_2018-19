/**header per la gestione di una struttura dati per la creazione
 * e gestione delle statistiche relative allo scheduler**/
#pragma once
#include "../process_list/list_process.h"

typedef struct {
	//struttura dati statistiche
	int numProc; //numero di processi totali
	int* completingTime; //puntatore ad un array di int, che sono il tempo di completamento di ogni processo
						 //anche se è un puntatore la sua gestione avverrà come fosse un vettore
						 //sapendo quanti elementi ("numProc") sono presenti
	int* readyTime; //questo array memorizza il tempo per cui ogni processo è in stato di ready
					//anche se è un puntatore la sua gestione avverrà come fosse un vettore
					//sapendo quanti elementi ("numProc") sono presenti
} TypeStat;

TypeStat init_TypeStat(int numProcMax);
void destroy_TypeStat(TypeStat stat);
float medComplTime(TypeStat stat); //calcola il tempo medio di completamento dei processi
float medReadyTime(TypeStat stat); //calcola il tempo medio di attesa dei processi
void print_TypeStat(TypeStat stat);
void insert_completingTime(TypeStat* stat, int pid, int complete); //inserisce nel vettore dei tempi di completamento
																   //un nuovo tempo di completamento, il pid del processo
																   //corrisponde all'indice del vettore
void adding_readyTime(TypeStat* stat, ListProcess* ready); //aggiunge un'unità a tutti i processi in stato di ready
void writeStatOnFile(TypeStat stat, const char* nameFile); //scrive alla fine del file le statistiche
