#include "proc.h"
#pragma once

typedef struct {
	char* name;
	int size;
	int used;
	ProcessType processes[size];
} VectorProcess;

VectorProcess new_vector(char* name, int size);
void insert_key_time(VectorProcess vec, ProcessType p);
void insert_key_duration(VectorProcess vec, ProcessType p);
void print_vector(VectorProcess vec);
ProcessType remove_first(VectorProcess vec);
void print_vector_onlyPid(VectorProcess vec);
void print_vector_onFile(VectorProcess vec, char* fileName);
void print_vector_onFile_onlyPid(VectorProcess vec, char* fileName);
