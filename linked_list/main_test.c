#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

//programma di test

int main() {
	printf("programma di test delle funzioni per la gestione della lista...\n");
	ListHead* lista=list_init();
	ListItem* f=new_item();
	ListItem* g=new_item();
	printf("%d = elemento f\n", f);
	printf("%d = elemento g\n", g);
	printf("%d = testa lista\n", lista);
	lista->first=f;
	printf("%d = primo elemento della lista\n", lista->first);
	printf("%d = valore di ritorno della list_find(lista, g)\n", list_find(lista, g));
	list_insert(lista, NULL, f);
	list_insert(lista, lista->first, NULL);
	list_insert(lista, lista->first, g);
	printf("%d = valore di ritorno della list_find(lista, g)\n", list_find(lista, g));
	return 0;
}
