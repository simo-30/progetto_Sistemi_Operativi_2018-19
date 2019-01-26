#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

//programma di test
#define MAX_ITEM 15

int main() {
	printf("programma di test delle funzioni per la gestione della lista...\n");
	ListHead* lista=list_init();
	ListItem* f=new_item();
	ListItem* g=new_item();
	printf("%d\n", f);
	printf("%d\n", g);
	printf("%d\n", lista);
	lista->first=f;
	printf("%d\n", lista->first);
	printf("%d\n", list_find(lista, g));
	return 0;
}
