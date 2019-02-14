#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#pragma once

/*NOTA: ci sono alcune funzioni dello scheduler che richiamano direttamente una funzione in list_process.h
 * 		questa è una scelta per poter offrire un'interfaccia allo sviluppatore di uno scheduler
 * 		portabile, simulando un'architettura a strati fra i vari header*/

ListProcess* generate_new_processes(const char* nameList, int pidMax, int maxTime, int maxDuration) {
	ListProcess* l=new_ListProcess(nameList);
	int i;
	for (i=0; i<pidMax; i++) {
		ProcessItem* p=new_process(i, maxTime, maxDuration);
		insert_key_time_arrive(l, p);
		usleep(10000);
	}
	return l;
}

ProcessItem* get_process_byTime(ListProcess* list, int time) {
	if (list->first->process->time_arrive == time) {
		return remove_first(list);
	}
	else {
		return NULL;
	}
}

void reduce_duration_running(ProcessItem* proc) {
	proc->process->duration-=1;
	return;
}

void reduce_duration_io(ListProcess* list) {
	ProcessItem* aux=list->first;
	while (aux) {
		aux->process->duration-=1;
		aux=aux->next;
	}
	return;
}

void insert_on_IO_list(ListProcess* list, ProcessItem* proc) {
	insert_key_duration(list, proc);
	return;
}

void insert_on_waiting_list(ListProcess* list, ProcessItem* proc) {
	insert_key_duration(list, proc);
	return;
}

void insert_on_ready_list(ListProcess* list, ProcessItem* proc) {
	insert_key_duration(list, proc);
	return;
}

void insert_on_arriving_list(ListProcess* list, ProcessItem* proc) {
	insert_key_time_arrive(list, proc);
	return;
}

void request_new_resources(ListProcess* waiting, ListProcess* arriving, int minTime, int maxTime, int maxDuration) {
	while (waiting->first!=NULL) {
		ProcessItem* aux=remove_first(waiting);
		if (process_next_burst(aux->process, minTime, maxTime, maxDuration)==0) {
			insert_on_arriving_list(arriving, aux);
		}
	}
	return;
}

void switching_process(ListProcess* ready, ListProcess* io, ProcessItem* proc) {
	if (proc->process->resource==CPU) {
		insert_on_ready_list(ready, proc);
		return;
	}
	if (proc->process->resource==IO) {
		insert_on_IO_list(io, proc);
		return;
	}
	return;
}

ListProcess* generate_new_processes_fromFile(const char* nameFile) {
	/* MODALITÀ DI SALVATAGGIO NEL FILE:
	 * 		"nome lista"
	 * 		PID (int) (int) (int) (int)
	 * 		...
	 * 1° int => numero di pid
	 * 2° int => tempo di arrivo
	 * 3° int => durata
	 * 4° int => tipo di risorsa*/
	FILE* fd=fopen(nameFile, "r");
	if (fd==NULL) {
		printf("Non è stato possibile aprire il file '%s'\n", nameFile);
		return NULL;
	}
	char* buffer=NULL;
	size_t line_len=0;
	if (getline(&buffer, &line_len, fd) <= 0) {
		printf("errore di lettura dal file %s\n", nameFile);
		return NULL;
	}
	ListProcess* l=new_ListProcess(buffer);
	while (getline(&buffer, &line_len, fd) > 0) {
		int pid, time, dur, res;
		res=-1;
		int num_tokens=0;
		num_tokens=sscanf(buffer, "PID %d %d %d %d", &pid, &time, &dur, &res);
		if (res==0 || res==1) {
			ProcessItem* p=new_process_fromData(pid, time, dur, res);
			insert_key_time_arrive(l, p);
		}
		else {
			printf("tipo di risorsa richiesta dal processo #%d non valida\n", pid);
		}
	}
	fclose(fd);
	return l;
}

void print_scheduler_onFile(const char* nameFile, int timing, ListProcess* arriving, ListProcess* ready, ListProcess* input_output, ListProcess* waiting, ProcessItem* running) {
	FILE* fd=fopen(nameFile, "a");
	fprintf(fd,"---- Time %d ----\n", timing);
	fclose(fd);
	print_list_onlyPid_onFileMode(arriving, nameFile, "a");
	print_list_onlyPid_onFileMode(ready, nameFile, "a");
	print_list_onlyPid_onFileMode(input_output, nameFile, "a");
	print_list_onlyPid_onFileMode(waiting, nameFile, "a");
	if (running->process->pid!=-1) {
		//il processo running deve essere valido
		append_process_onFile(running->process, nameFile);
	}
	fd=fopen(nameFile, "a");
	fprintf(fd,"----------------\n\n");
	fclose(fd);
}
