#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
	printf("programma di test delle funzioni per la gestione della lista...\n");
	ListHead lista;
	list_init(&lista, "prima lista");
	printf("%s\n", lista.name);
	return 0;
}
