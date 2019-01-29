#include "list_process.h"
#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_DURATION 10
#define MAX_TIME_ARRIVE 20
#define MAX_PROC 10

int main() {
	int i;
	printf("++++ programma di prova per testare le funzioni su una lista di processi ++++\n");
	ListProcess* lista=new_ListProcess("lista ordinata per tempo di arrivo");
	ListProcess* q=new_ListProcess("lista ordinata per durata");
	printf("genero i processi...\n\n");
	for (i=0; i<MAX_PROC; i++) {
		ProcessItem* proc=new_process(i, MAX_TIME_ARRIVE, MAX_DURATION);
		insert_key_time_arrive(lista, proc);
		sleep(1);
	}
	for (i=0; i<MAX_PROC; i++) {
		ProcessItem* proc=new_process(i, MAX_TIME_ARRIVE, MAX_DURATION);
		insert_key_duration(q, proc);
		sleep(1);
	}
	print_list(lista);
	print_list(q);
	//ProcessItem* p=remove_first(lista);
	//print_process(p->process);
	print_list_onFile(lista, "listaProcessiArrivo.txt");
	print_list_onFile(lista, "listaProcessiDurata.txt");
	print_list_onlyPid(lista);
	destroy_list(lista);
	destroy_list(q);
}
