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
	ListProcess* lista=new_ListProcess("prima lista");
	printf("genero i processi...\n\n");
	for (i=0; i<MAX_PROC; i++) {
		ProcessItem* proc=new_process(i, MAX_TIME_ARRIVE, MAX_DURATION);
		insert_key_time_arrive(lista, proc);
		sleep(1);
	}
	print_list(lista);
	ProcessItem* p=remove_first(lista);
	print_process(p->process);
	print_list_onFile(lista, "listaProcessi.txt");
	destroy_list(lista);
}
