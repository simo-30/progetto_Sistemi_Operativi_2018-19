#include "process.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

ProcessType* create_Process(int pid, int max_time_arrive, int max_duration) {
	//genero un processo in modo casuale, con pid dato
	ProcessType* proc=(ProcessType*)malloc(sizeof(ProcessType));
	proc->pid=pid;
	srand(time(NULL));
	proc->time_arrive=rand() % max_time_arrive;
	proc->duration=1 + rand() % max_duration;
	int ris=rand()%10 +1;
	if (ris<=5) {
		proc->resource=CPU;
	}
	else {
		proc->resource=IO;
	}
	return proc;
}

#if DEBUG
void print_process(ProcessType* process) {
	printf("**** process pid	%d ****\n", process->pid);
	printf("     time arriving	%d     \n", process->time_arrive);
	printf("     duration 		%d     \n", process->duration);
	printf("     resource		%d	   \n", process->resource);
	return;
}
#endif
