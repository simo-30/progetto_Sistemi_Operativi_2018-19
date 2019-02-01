#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#include "srjf.h"
#include <stdlib.h>
#include <stdio.h>
#pragma once

/* ci saranno 2 versioni dello scheduler:
 * +) la versione che prende i processi in arrivo da file, FILE_VERSION
 * +) la versione che li genera in automatico, AUTO_VERSION
 * entrambe le versioni poi salveranno su file il loro sviluppo*/

//versioni per inizializare lo scheduler
#if AUTO_VERSION
void start_scheduler(int maxPid, int maxTime, int maxDuration) {
	arriving=generate_new_processes("arriving processes", maxPid, maxTime, maxDuration);
	ready=new_ListProcess("arriving processes");
	waiting=new_ListProcess("waiting processes");
	ready=new_ListProcess("ready processes");
	running=new_process_fromData(INT_MAX, INT_MAX, INT_MAX, -1);
	return;
}
#elif FILE_VERSION
void start_scheduler(const char* fileName) {
	arriving=generate_new_processes_fromFile(fileName);
	ready=new_ListProcess("arriving processes");
	waiting=new_ListProcess("waiting processes");
	ready=new_ListProcess("ready processes");
	running=new_process_fromData(INT_MAX, INT_MAX, INT_MAX, -1);
	return;
}
#endif
