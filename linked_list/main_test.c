#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

//programma di test

int main() {
	printf("programma di test delle funzioni per la gestione della lista...\n");
	#if DEBUG
	printf("\nVersione con stampe di debugging\n\n");
	#endif
	ListHead* lista=list_init();
	ListItem* f=new_item();
	ListItem* g=new_item();
	list_insert_first(lista, f);
	printf("%d = elemento f\n", f);
	printf("%d = elemento g\n", g);
	printf("%d = testa lista\n", lista);
	printf("%d = primo elemento della lista\n", lista->first);
	printf("%d = valore di ritorno della list_find(lista, g)\n", list_find(lista, g));
	list_insert(lista, NULL, f);
	list_insert(lista, lista->first, NULL);
	list_insert(lista, lista->first, g);
	#if DEBUG
	print_ind_lista(lista);
	#endif
	remove_item(lista, g);
	printf("%d = valore di ritorno della list_find(lista, g)\n", list_find(lista, g));
	printf("%d = valore della testa rimossa\n", remove_first(lista));
	printf("%d = testa della lista\n", lista->first);
	#if DEBUG
	print_ind_lista(lista);
	#endif
	return 0;
}
