#include "list_process.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma once

ListProcess* new_ListProcess(const char* name) {
	ListProcess* list_proc=(ListProcess*)malloc(sizeof(ListProcess));
	list_proc->first=NULL;
	list_proc->size=0;
	int s=strlen(name);
	list_proc->name=malloc((s+1)*sizeof(char));
	strcpy(list_proc->name, name);
	return list_proc;
}

void insert_key_time_arrive(ListProcess* list, ProcessItem* proc) {
	ListProcess* auxList=list;
	if (auxList->first==NULL) {
		auxList->first=proc;
		list->size+=1;
		return;
	}
	ProcessItem* aux=auxList->first;
	if (proc->process->time_arrive < aux->process->time_arrive) {
		proc->next=aux;
		auxList->first=proc;
		list->size+=1;
		return;
	}
	if (proc->process->time_arrive == aux->process->time_arrive && proc->process->pid < aux->process->pid) {
		proc->next=aux;
		auxList->first=proc;
		list->size+=1;
		return;
	}
	while (aux->next!=NULL) {
		if (proc->process->time_arrive < aux->next->process->time_arrive) {
			ProcessItem* pross=aux->next;
			proc->next=pross;
			aux->next=proc;
			list->size+=1;
			return;
		}
		if (proc->process->time_arrive == aux->next->process->time_arrive && proc->process->pid < aux->next->process->pid) {
			ProcessItem* pross=aux->next;
			proc->next=pross;
			aux->next=proc;
			list->size+=1;
			return;
		}
		aux=aux->next;
	}
	aux->next=proc;
	list->size+=1;
	return;
}

ProcessItem* new_process(int pid, int max_time_arrive, int max_duration) {
	ProcessItem* proc=(ProcessItem*)malloc(sizeof(ProcessItem));
	proc->process=create_Process(pid, max_time_arrive, max_duration);
	proc->next=NULL;
	return proc;
}

void print_list(ListProcess* list) {
	ListProcess* aux=list;
	printf("%s\n\n", list->name);
	ProcessItem* p=aux->first;
	int i;
	for (i=0; i<list->size; i++) {
		print_process(p->process);
		p=p->next;
	}
	return;
}

void destroy_list(ListProcess* list) {
	ProcessItem* aux=list->first;
	while (aux) {
		destroy_process(aux->process);
		aux=aux->next;
	}
	free(aux);
	free(list);
	return;
}

ProcessItem* remove_first(ListProcess* list) {
	if (list->first==NULL) {
		return NULL;
	}
	ProcessItem* ret=list->first;
	list->first=list->first->next;
	list->size-=1;
	return ret;
}

void print_list_onFile(ListProcess* list, const char* nameFile) {
	FILE* fd=fopen(nameFile, "w");
	if (fd==NULL) {
		printf("errore di apertura del file\n");
		return;
	}
	int i;
	fprintf(fd, "%s\n\n", list->name);
	ProcessItem* aux=list->first;
	for (i=0; i<list->size; i++) {
		fprintf(fd, "**** process pid	%d ****\n", aux->process->pid);
		fprintf(fd, "     time arriving	%d     \n", aux->process->time_arrive);
		fprintf(fd, "     duration 		%d     \n", aux->process->duration);
		fprintf(fd, "     resource		%d	   \n", aux->process->resource);
		fprintf(fd, "******************************\n");
		aux=aux->next;
	}
	fclose(fd);
	return;
}
