#pragma once
#include "linked_list.h"

typedef enum {CPU=0, IO=1} TypeResource; 
//tipo enum per specificare il tipo di risorsa che il processo utilizza

typedef struct {
	//evento del processo
	ListItem list;
	TypeResource type;
	int duration;
} My_Event;

typedef struct {
	//struttura che simula un processo
	ListItem list;
	int pid; //assegnato dal programma di prova
	int arrival_time;
	ListHead events;
} My_Process;
