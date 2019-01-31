#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include <time.h>
#include <stdlib.h>
#pragma once

int process_next_burst(ProcessType* proc, int time_min, int time_max, int duration_max) {
	/**
	 * in questa funzione calcolo una nuova richiesta di risorse effettuata dal processo;
	 * in caso di errore ritorna -1
	 * in caso di successo ritorna 0
	 **/
	if (time_min==time_max) {
		//il tempo minimo e massimo coincidono, quindi lo scheduler (o il programma di prova)
		//ha finito il tempo in cui può accettare altri processi
		return -1;
	}
	srand(time(NULL)+(time_min*time_max));
	int ris=rand()%1000;
	if (ris<=500) {
		proc->resource=CPU;
	}
	else {
		proc->resource=IO;
	}
	int range=time_max - time_min +1; //range di tempo nel quale il processo può arrivare
	proc->time_arrive=1+time_min + rand() % range;
	proc->duration=1 + rand() % duration_max;
	return 0;
}
