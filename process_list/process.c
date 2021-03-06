#include "process.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#pragma once

ProcessType* create_Process(int pid, int max_time_arrive, int max_duration) {
	//genero un processo in modo casuale, con pid dato
	ProcessType* proc=(ProcessType*)malloc(sizeof(ProcessType));
	proc->pid=pid;
	//srand(time(NULL));
	proc->time_arrive=rand() % max_time_arrive;
	proc->duration=1 + rand() % max_duration;
	int ris=rand()%1000;
	if (ris<=500) {
		proc->resource=CPU;
	}
	else {
		proc->resource=IO;
	}
	return proc;
}

void print_process(ProcessType* process) {
	printf("**** process pid	%d ****\n", process->pid);
	printf("     time arriving	%d\n", process->time_arrive);
	printf("     duration		%d\n", process->duration);
	printf("     resource		%d\n", process->resource);
	printf("******************************\n");
	return;
}

void destroy_process(ProcessType* process) {
	free(process);
	return;
}

ProcessType* create_Process_fromData(int pid, int timeArrive, int duration, int resource) {
	ProcessType* proc=(ProcessType*)malloc(sizeof(ProcessType));
	if (resource==0 || resource==1) {
		proc->pid=pid;
		proc->time_arrive=timeArrive;
		proc->duration=duration;
		proc->resource=resource;
		return proc;
	}
	return NULL;
}

void append_process_onFile(ProcessType* process, const char* nameFile) {
	FILE* fd=fopen(nameFile, "a");
	if (fd==NULL) {
		perror("Errore nell'apertura del file\n");
		return;
	}
	fprintf(fd, "\nRunning process\n");
	fprintf(fd, "**** process pid	%d ****\n", process->pid);
	fprintf(fd, "     time arriving	%d\n", process->time_arrive);
	fprintf(fd, "     duration		%d\n", process->duration);
	fprintf(fd, "     resource		%d\n", process->resource);
	fprintf(fd, "******************************\n");
	fclose(fd);
	return;
}
