/*file header per la gestione delle funzioni di uno scheduler*/
#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#pragma once

ListProcess* generate_new_processes(const char* nameList, int pidMax, int maxTime, int maxDuration);
	/**questa funzione servirà per generare nuovi pidMax processi casuali, 
	 * con tempo di arrivo massimo maxTime, con durata massima maxDuration
	 * e con il tipo di risorsa richiesta (CPU o I/O) casuale,
	 * questi verranno inseriti ordinatamente (in base al loro tempo di arrivo)
	 * in una nuova lista di processi che avrà per nome nameList**/
