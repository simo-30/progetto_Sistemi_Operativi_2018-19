#include "proc_vector.h"
#include <stdlib.h>
#include <stdio.h>
#pragma once

#define DURATION 10
#define TIME 30

int main() {
	ProcessType p=create_Process(0, TIME, DURATION);
	print_process(p);
	return 0;
}
