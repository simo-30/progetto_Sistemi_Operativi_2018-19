#pragma once
#include "stat.h"
#include "../process_list/list_process.h"
#include "../process_list/process.h"
#include <stdlib.h>
#include <stdio.h>

TypeStat init_TypeStat(int numProcMax) {
	TypeStat ret;
	ret.numProc=numProcMax;
	ret.completingTime=malloc(numProcMax*sizeof(int));
	ret.readyTime=malloc(numProcMax*sizeof(int));
	return ret;
}

void destroy_TypeStat(TypeStat stat) {
	free(stat.completingTime);
	free(stat.readyTime);
	return;
}

float medComplTime(TypeStat stat) {
	int i, som=0;
	for (i=0; i<stat.numProc; i++) {
		som+=stat.completingTime[i];
	}
	return som/stat.numProc;
}

float medReadyTime(TypeStat stat) {
	int i, som=0;
	for (i=0; i<stat.numProc; i++) {
		som+=stat.readyTime[i];
	}
	return som/stat.numProc;
}

void print_TypeStat(TypeStat stat) {
	printf("°°°°°°°°°°°°°°°°°°°°°°°\n");
	printf("statistiche scheduling:\n");
	printf("tempo medio di completamento: %f\n", medComplTime(stat));
	printf("tempo medio di permanenza in stato di ready: %f\n", medReadyTime(stat));
	printf("°°°°°°°°°°°°°°°°°°°°°°°\n");
	return;
}

void insert_completingTime(TypeStat* stat, int pid, int complete) {
	stat->completingTime[pid]=complete;
	return;
}

void adding_readyTime(TypeStat* stat, ListProcess* ready) {
	ProcessItem* aux=ready->first;
	while (aux!=NULL) {
		stat->readyTime[aux->process->pid]+=1;
		aux=aux->next;
	}
	return;
}
