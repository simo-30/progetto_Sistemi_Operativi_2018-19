#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#include <stdlib.h>
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
	proc->next=list->first;
	list->first=proc;
	list->size+=1;
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
	ProcessItem* aux=waiting->first;
	while (aux) {
		process_next_burst(aux->process, minTime, maxTime, maxDuration);
		insert_on_arriving_list(arriving, aux);
		aux=aux->next;
	}
	return;
}
