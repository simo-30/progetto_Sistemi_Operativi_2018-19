#include "../../process_list/process.h"
#include "../../process_list/list_process.h"
#include "../../next_burst/nextBurst.h"
#include "../scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#pragma once

//variabili globali che però possono essere modificate passandogli i parametri al lancio del programma
#define PROC 20
#define TIME 50
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
 * +) VERSION=0 (automatica) -> <maxPid> <maxTime> <maxDuration> <fileNameOut>
 * +) VERSION=1 (da file) -> <maxTime> <maxDuration> <fileNameIn> */
int main(int argc, char** argv) {
	int maxPid, maxTime, maxDuration;
	maxPid=PROC;
	maxTime=TIME;
	maxDuration=DURATION;
	char* nameFileIn;
	char* nameFileOut;
	nameFileOut=(char*)malloc(strlen(NAME_FILE)*sizeof(char)+1);
	strcpy(nameFileOut, NAME_FILE);
	#if VERSION==0
	if (argc==2) {
		int s=strlen(argv[1]);
		nameFileOut=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFileOut, argv[1]);
	}
	else if (argc==4) {
		maxPid=atoi(argv[1]);
		maxTime=atoi(argv[2]);
		maxDuration=atoi(argv[3]);
	}
	else if (argc==5) {
		maxPid=atoi(argv[1]);
		maxTime=atoi(argv[2]);
		maxDuration=atoi(argv[3]);
		int s=strlen(argv[4]);
		nameFileOut=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFileOut, argv[4]);
	}
	#elif VERSION==1
	if (argc==4) {
		maxTime=atoi(argv[1]);
		maxDuration=atoi(argv[2]);
		int s=strlen(argv[3]);
		nameFileIn=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFileIn, argv[3]);
	}
	else if (argc==2) {
		int s=strlen(argv[1]);
		nameFileIn=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFileIn, argv[1]);
	}
	else if (argc==3) {
		int s=strlen(argv[1]);
		nameFileIn=(char*)malloc(s*sizeof(char)+1);
		strcpy(nameFileIn, argv[1]);
		nameFileOut=(char*)malloc(strlen(argv[2])*sizeof(char)+1);
		strcpy(nameFileOut, argv[2]);
	}
	else {
		printf("usage:\n executable <maxTime> <maxDuration> <fileNameIn>\n or\n executable <fileNameIn>\n or executable <fileNameIn> <fileNameOut>");
		exit(1);
	}
	#endif
	FILE* fd=fopen(nameFileOut, "w");
	fprintf(fd, "STARTING SCHEDULER\n\n");
	fclose(fd);
	printf("Starting scheduler\n");
	srand(time(NULL));
	#if VERSION==0
	arriving=generate_new_processes("arriving processes", maxPid, maxTime, maxDuration);
	#elif VERSION==1
	arriving=generate_new_processes_fromFile(nameFileIn);
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
		if (running->process->pid!=-1) {
			printf("\nrunning process\n");
			print_process(running->process);
		}
		print_scheduler_onFile(nameFileOut, timing, arriving, ready, input_output, waiting, running);
		while (arriving->first!=NULL && arriving->first->process->time_arrive == timing) {
			pr=remove_first(arriving); /**prendo il primo elemento della lista dei processi in arrivo**/
			if (pr->process->resource==CPU) { //il processo pr deve richiedere la CPU
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
						}
						else if (pr->process->duration == running->process->duration && pr->process->pid < running->process->pid) {
							ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
							aux=running;
							running=pr;
							pr=aux;
						}
					}
					else {
						/* non ci sono processi in ready
						* quindi pr sarà in running*/
						running=new_process_fromData(pr->process->pid, pr->process->time_arrive, pr->process->duration, pr->process->resource);
						/**per evitare conflitti successivamente con l'inserimento del processo nella lista
						* giusta, quello in running avrà i campi data uguali a pr, e pr avrà come pid -1,
						* ad indicare che NON deve essere inserito in nessuna lista**/
						pr->process->pid=-1;
					}
				}
				else {
					/* è già presente un processo in running valido
					* devo confrontare il lavoro rimanente con il processo appena
					* rimosso dalla lista dei processi in arrivo*/
					if (pr->process->duration < running->process->duration) {
						ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
						aux=running;
						running=pr;
						pr=aux;
					}
					else if (pr->process->duration == running->process->duration && pr->process->pid < running->process->pid) {
						ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
						aux=running;
						running=pr;
						pr=aux;
					}
				}
			}
			/**fatti i confronti per determinare quale processo deve rimanere in running
			 * ora devo inserire il processo pr nella lista giusta, verificando prima tramite 
			 * il pid se sia un processo valido o no**/
			if (pr!=NULL && pr->process!=NULL && pr->process->pid > -1) {
				//il processo pr è valido quindi posso inserirlo nella lista giusta in base al tipo di risorsa richiesta
				if (pr->process->resource==CPU) {
					insert_on_ready_list(ready, pr);
				}
				else if (pr->process->resource==IO) {
					insert_on_IO_list(input_output, pr);
				}
			}
		}
		//ho preso il processo in arrivo e messo nella lista in base al tipo di risorsa richiesta
		//ora devo diminuire di un'unità il lavoro rimanente al processo running
		if (running->process->pid != -1) {
			//il processo deve essere valido
			reduce_duration_running(running);
			if (running->process->duration==0) {
				ProcessItem* aux=new_process_fromData(running->process->pid, running->process->time_arrive, running->process->resource, running->process->resource);
				insert_on_waiting_list(waiting, aux);
				if (ready->first!=NULL) {
					running=remove_first(ready); 
					/**essendo presente almeno un processo nella lista ready,
					 * il primo di essi viene messo in running**/
				}
				else {
					/*non ci sono processi in ready, quindi l'attuale processo in running non è più valido*/
					running->process->pid=-1; //il processo running non è più valido
				}
			}
		}
		else {
			if (ready->first!=NULL) {
				//se è presente un processo in ready sarà il prossimo ad essere in running
				running=remove_first(ready);
			}
		}
		/**ora devo dimuire il lavoro dei processi in I/O**/
		reduce_duration_io(input_output); //riduco di un'unità il lavoro rimanente ai processi in I/O
		while (input_output->first!=NULL && input_output->first->process->duration==0) {
			//il primo processo in I/O ha finito di lavorare 
			//quindi lo inserisco nella lista di waiting
			ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem));
			aux=remove_first(input_output);
			insert_on_waiting_list(waiting, aux);
		}
		/* ora per tutti i processi in waiting devo calcolare una nuova richiesta
		 * e poi inserirli nella lista dei processi in arrivo per poterli di nuovo
		 * schedulare quando arriveranno allo scheduler*/
		request_new_resources(waiting, arriving, timing, maxTime, maxDuration);
		printf("------\n\n");
	}
	/**ho schedulato tutti i processi iniziali
	 * ora devo schedulare tutti i processi rimasti in arrivo, ready ed I/O
	 * ma senza creare nuove risorse**/
	while (arriving->first!=NULL || ready->first!=NULL || input_output->first!=NULL || running->process->pid!=-1) {
		printf("--- Tempo %d ---\n", timing);
		print_list_onlyPid(arriving);
		print_list_onlyPid(ready);
		print_list_onlyPid(input_output);
		print_list_onlyPid(waiting);
		if (running->process->pid!=-1) {
			printf("\nrunning process\n");
			print_process(running->process);
		}
		print_scheduler_onFile(nameFileOut, timing, arriving, ready, input_output, waiting, running);
		while (arriving->first!=NULL && arriving->first->process->time_arrive == timing) {
			pr=remove_first(arriving); /**prendo il primo elemento della lista dei processi in arrivo**/
			if (pr->process->resource==CPU) { //il processo pr deve richiedere la CPU
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
						}
						else if (pr->process->duration == running->process->duration && pr->process->pid < running->process->pid) {
							ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
							aux=running;
							running=pr;
							pr=aux;
						}
					}
					else {
						/* non ci sono processi in ready
						* quindi pr sarà in running*/
						running=new_process_fromData(pr->process->pid, pr->process->time_arrive, pr->process->duration, pr->process->resource);
						/**per evitare conflitti successivamente con l'inserimento del processo nella lista
						* giusta, quello in running avrà i campi data uguali a pr, e pr avrà come pid -1,
						* ad indicare che NON deve essere inserito in nessuna lista**/
						pr->process->pid=-1;
					}
				}
				else {
					/* è già presente un processo in running valido
					* devo confrontare il lavoro rimanente con il processo appena
					* rimosso dalla lista dei processi in arrivo*/
					if (pr->process->duration < running->process->duration) {
						ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
						aux=running;
						running=pr;
						pr=aux;
					}
					else if (pr->process->duration == running->process->duration && pr->process->pid < running->process->pid) {
						ProcessItem* aux=(ProcessItem*)malloc(sizeof(ProcessItem)); //processo di appoggio per lo swap dei processi
						aux=running;
						running=pr;
						pr=aux;
					}
				}
			}
			/**fatti i confronti per determinare quale processo deve rimanere in running
			 * ora devo inserire il processo pr nella lista giusta, verificando prima tramite 
			 * il pid se sia un processo valido o no**/
			if (pr!=NULL && pr->process!=NULL && pr->process->pid > -1) {
				//il processo pr è valido quindi posso inserirlo nella lista giusta in base al tipo di risorsa richiesta
				if (pr->process->resource==CPU) {
					insert_on_ready_list(ready, pr);
				}
				else if (pr->process->resource==IO) {
					insert_on_IO_list(input_output, pr);
				}
			}
		}
		//ho preso il processo in arrivo e messo nella lista in base al tipo di risorsa richiesta
		//ora devo diminuire di un'unità il lavoro rimanente al processo running
		if (running->process->pid != -1) {
			//il processo deve essere valido
			reduce_duration_running(running);
			if (running->process->duration==0) {
				if (ready->first!=NULL) {
					running=remove_first(ready); 
					/**essendo presente almeno un processo nella lista ready,
					 * il primo di essi viene messo in running**/
				}
				else {
					/*non ci sono processi in ready, quindi l'attuale processo in running non è più valido*/
					running->process->pid=-1; //il processo running non è più valido
				}
			}
		}
		else {
			if (ready->first!=NULL) {
				//se è presente un processo in ready sarà il prossimo ad essere in running
				running=remove_first(ready);
			}
		}
		/**ora devo dimuire il lavoro dei processi in I/O**/
		reduce_duration_io(input_output); //riduco di un'unità il lavoro rimanente ai processi in I/O
		while (input_output->first!=NULL && input_output->first->process->duration==0) {
			//il primo processo in I/O ha finito di lavorare 
			//quindi lo rimuovo dallo scheduler
			remove_first(input_output);
		}
		timing+=1; //ad ogni ciclo devo aumentare il clock
		printf("------\n\n");
	}
	fd=fopen(nameFileOut, "a");
	fprintf(fd, "\nEND SCHEDULER");
	fclose(fd);
	printf("\nEND SCHEDULER\n");
	//libero la memoria
	destroy_list(arriving);
	destroy_list(ready);
	destroy_list(input_output);
	destroy_list(waiting);
	return(0);
}
