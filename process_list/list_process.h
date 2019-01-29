//header con strutture dati e funzioni per la gestione di una lista di processi
#include "process.h"

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
