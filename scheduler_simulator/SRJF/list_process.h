//header con strutture dati e funzioni per la gestione di una lista di processi
#include "process.h"
#pragma once

typedef struct item {
	struct item* next;
	ProcessType* process;
} ProcessItem;

typedef struct {
	ProcessItem* first;
	int size;
	char* name;
} ListProcess;

ListProcess* new_ListProcess(const char* name);
void insert_key_time_arrive(ListProcess* list, ProcessItem* proc);
/*
 * la funzione soprà prototipata inserisce un processo in una lista,
 * in base al tempo di arrivo dal minore al maggiore (nel caso di tempo uguali confronterà il pid),
 * servirà per gestirà la prima lista con i processi appena creati, che verranno poi schedulati
*/
ProcessItem* new_process(int pid, int max_time_arrive, int max_duration);
void print_list(ListProcess* list);
void destroy_list(ListProcess* list);
ProcessItem* remove_first(ListProcess* list);
void print_list_onFile(ListProcess* list, const char* nameFile);
void insert_key_duration(ListProcess* list, ProcessItem* proc);
void print_list_onlyPid(ListProcess* list);
void print_list_onlyPid_onFile(ListProcess* list, const char* nameFile);
ProcessItem* new_process_fromData(int pid, int arriveTime, int duration, int resource);
