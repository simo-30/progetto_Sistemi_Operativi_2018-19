#include <stdio.h>
#include <stdlib.h>
#include "process.h"

#define MAX_DURATION 10
#define MAX_TIME_ARRIVE 20

int main() {
	printf("---- programma di prova per testare le funzioni sui processi ----\n\n");
	ProcessType* proc=create_Process(0, MAX_TIME_ARRIVE, MAX_DURATION);
	#if DEBUG
	print_process(proc);
	#endif
	free(proc);
	return 0;
}
