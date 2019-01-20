#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

/**
 * file con le funzioni per la gestione di una lista collegata
 **/

void list_init(ListHead* head, char name[]) {
	//funzione che inizializza la lista
	head->first=0;
	head->last=0;
	head->size=0;
	strcpy(head->name, name);
}

int list_find(ListHead* head, ListItem* item) {
	/*
	 * funzione che tramite una scansione lineare cerca un elemento nella lista,
	 * ritorna 1 se è presente, 0 altrimenti
	 */
	ListItem* aux=head->first;
	while(aux) {
		if (aux==item) {
			return 1;
		}
		aux=aux->next;
	}
	return 0;
}

ListItem* list_insert(ListHead* head, ListItem* prev, ListItem* item) {
	if (prev==NULL || item==NULL) {
		return 0;
	}
	if (list_find(head, prev)==0) {
		return 0;
	}
	ListItem* aux;
	aux->prev=item;
	item->next=aux;
	prev->next=item;
	item->prev=prev;
	return item;
}
