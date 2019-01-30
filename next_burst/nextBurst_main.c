#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_TIME 20
#define MAX_DURATION 10

int main() {
	printf("---- programma di prova che calcola le modifiche per le successive richieste di CPU e/o I/O ----\n");
	ProcessType* p=create_Process(0, MAX_TIME, MAX_DURATION);
	print_process(p);
	int res=process_next_burst(p, p->time_arrive, MAX_TIME, MAX_DURATION);
	if (res==-1) {
		printf("tempo minimo oltre il minimo\n");
	}
	print_process(p);
	return 0;
}
