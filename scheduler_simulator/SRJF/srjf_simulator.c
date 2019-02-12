#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#pragma once

//variabili globali che però possono essere modificate passandogli i parametri al lancio del programma
#define PROC 20
#define TIME 100
#define DURATION 10
#define NAME_FILE "file_processes/scheduler.txt"

ListProcess* arriving; //lista dei processi in arrivo
ListProcess* waiting; //lista dei processi che hanno terminato 
					  //e che aspettano di essere passati alla funzione che richiederà nuove risorse
ListProcess* input_output; //lista dei processi in stato di I/O
ListProcess* ready; //lista dei processi in stato di ready che aspettano di essere processati
ProcessItem* running; //processo in esecuzione
ProcessItem* pr; //variabile per il processo che viene preso dalla lista arriving
int timing; //varibile per tenere traccia a che ciclo dello scheduling si è

/* i parametri possono essere così passati in base alla versione:
 * +) VERSION=0 (automatica) -> <maxPid> <maxTime> <maxDuration>
 * +) VERSION=1 (da file) -> <maxTime> <maxDuration> <fileName>*/
int main(int argc, char** argv) {
	int maxPid, maxTime, maxDuration;
	maxPid=PROC;
	maxTime=TIME;
	maxDuration=DURATION;
	char* nameFile;
	#if VERSION==0
	if (argc==4) {
		maxPid=atoi(argv[1]);
		maxTime=atoi(argv[2]);
		maxDuration=atoi(argv[3]);
	}
	#elif VERSION==1
	if (argc==4) {
		maxTime=atoi(argv[1]);
		maxDuration=atoi(argv[2]);
		int s=strlen(argv[3]);
		nameFile=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFile, argv[3]);
	}
	if (argc==2) {
		int s=strlen(argv[1]);
		nameFile=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFile, argv[1]);
	}
	else {
		printf("usage:\n executable <maxTime> <maxDuration> <fileName>\n or\n executable <fileName>\n");
		exit(1);
	}
	#endif
	FILE* fd=fopen(NAME_FILE, "w");
	fprintf(fd, "STARTING SCHEDULER\n\n");
	fclose(fd);
	printf("Starting scheduler\n");
	srand(time(NULL));
	#if VERSION==0
	arriving=generate_new_processes("arriving processes", maxPid, maxTime, maxDuration);
	#elif VERSION==1
	arriving=generate_new_processes_fromFile(nameFile);
	#endif
	waiting=new_ListProcess("waiting processes");
	ready=new_ListProcess("ready processes");
	input_output=new_ListProcess("I/O processes");
	running=(ProcessItem*)malloc(sizeof(ProcessItem));
	running->process=(ProcessType*)malloc(sizeof(ProcessType));
	running->process->pid=-1; /**imposto il pid a -1 così da poter controllare dopo se il processo puntato
							   * da questa variabile è valido o meno; se il pid==-1 non è valido**/
	pr=(ProcessItem*)malloc(sizeof(ProcessItem));
	for (timing=0; timing<maxTime; timing++) {
		//ciclo principale dove si svolgerà tutto il lavoro dello scheduler
		printf("--- Tempo %d ---\n", timing);
		print_list_onlyPid(arriving);
		print_list_onlyPid(ready);
		print_list_onlyPid(input_output);
		print_list_onlyPid(waiting);
		print_scheduler_onFile(NAME_FILE, timing, arriving, ready, input_output, waiting);
		while (arriving->first!=NULL && arriving->first->process->time_arrive == timing) {
			pr=remove_first(arriving); /**prendo il primo elemento della lista dei processi in arrivo**/
			if (running->process->pid==-1) {
				/* processo running non valido,
				 * quindi l'ultimo processo in running ha finito il suo lavoro
				 * ne devo prendere un altro dalla lista di ready 
				 * e poi confrontare il job rimanente con il processo appena 
				 * rimosso dalla lista dei processi in arrivo*/
				if (ready->first!=NULL) {
					//è presente almeno un processo nella lista dei processi in ready
					running=remove_first(ready);
					//ora devo confrontare il job rimanente fra running e pr, dando priorità in caso siano uguali al pid minore
					if (pr->process->duration < running->process->duration) {
						ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
						aux=running;
						running=pr;
						pr=aux;
						free(aux);
					}
					else if (pr->process->duration == running->process->duration && pr->process->pid < running->process->pid) {
						ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
						aux=running;
						running=pr;
						pr=aux;
						free(aux);
					}
				}
				else {
					/* non ci sono processi in ready
					 * quindi pr sarà in running*/
					running=new_process_fromData(pr->process->pid, pr->process->time_arrive, pr->process->duration, pr->process->resource);
					/**per evitare conflitti successivamente con l'inserimento del processo nella lista
					 * giusta, quello in running avrà i campi data uguali a pr, e pr avrà come pid -1,
					 * ad indicare che NON deve essere inserito in nessuna lista**/
				}
			}
			else {
				/* è già presente un processo in running valido
				* devo confrontare il lavoro rimanente con il processo appena
				* rimosso dalla lista dei processi in arrivo*/
			}
		}
		//manca ancora l'inserimento di altri processi in running 
		//e togliere quelli che finiscono dallo stato di I/O
		printf("------\n\n");
	}
	fd=fopen(NAME_FILE, "a");
	fprintf(fd, "\nEND SCHEDULER");
	fclose(fd);
}
