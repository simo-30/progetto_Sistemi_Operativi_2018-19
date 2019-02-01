/*header che consentirà la gestione di uno scheduler simulato con politica SRJF*/
#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#pragma once

//variabili globali 
ListProcess* arriving; //lista dei processi in arrivo
ListProcess* waiting; //lista dei processi che hanno terminato 
					  //e che aspettano di essere passati alla funzione che richiederà nuove risorse
ListProcess* input_output; //lista dei processi in stato di I/O
ListProcess* ready; //lista dei processi in stato di ready che aspettano di essere processati
ProcessItem* running; //processo in esecuzione
unsigned int time; //varibile per tenere traccia a che ciclo dello scheduling si è

#if AUTO_VERSION
void start_scheduler(int maxPid, int maxTime, int maxDuration);
	/**la funzione sopra farà partire lo scheduler, inizializzando le liste dei processi
	 * ed il processo in running, e nella lista dei processi in arrivo verranno creati
	 * i processi, secondo la versione utilizzata**/
#elif FILE_VERSION
void start_scheduler(const char* fileName);
#endif
