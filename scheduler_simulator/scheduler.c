#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#include <stdlib.h>
#include <unistd.h>
#pragma once

ListProcess* generate_new_processes(const char* nameList, int pidMax, int maxTime, int maxDuration) {
	ListProcess* l=new_ListProcess(nameList);
	int i;
	for (i=0; i<pidMax; i++) {
		ProcessItem* p=new_process(i, maxTime, maxDuration);
		insert_key_time_arrive(l, p);
		usleep(10000);
	}
	return l;
}
