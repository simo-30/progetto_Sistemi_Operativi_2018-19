#include "list_process.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ListProcess* new_ListProcess(const char* name) {
	ListProcess* list_proc=(ListProcess*)malloc(sizeof(ListProcess));
	list_proc->first=NULL;
	list_proc->size=0;
	int s=strlen(name);
	list_proc->name=malloc((s+1)*sizeof(char));
	strcpy(list_proc->name, name);
	return list_proc;
}
