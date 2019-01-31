#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#include "scheduler.h"
#pragma once

#define PROC 10
#define DURATION 10
#define ARRIVE_TIME 20

int main() {
	ListProcess* l=generate_new_processes("processi in arrivo", PROC, ARRIVE_TIME, DURATION);
	print_list(l);
	printf("\n\n");
	print_list_onlyPid(l);
	destroy_list(l);
	return 0;
}
