#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

/**
 * file con le funzioni per la gestione di una lista collegata
 **/

ListHead* list_init() {
	//funzione che inizializza la lista
	ListHead* head=(ListHead*)malloc(sizeof(ListHead));
	head->first=NULL;
	head->last=NULL;
	head->size=0;
	return head;
}

ListItem* list_find(ListHead* head, ListItem* item) {
	/*
	 * funzione che tramite una scansione lineare cerca un elemento nella lista,
	 * ritorna 1 se è presente, 0 altrimenti
	 */
	ListItem* aux=head->first;
	while(aux) {
		if (aux==item) {
			return aux;
		}
		aux=aux->next;
	}
	return NULL;
}

ListItem* new_item() {
	/* funzione per la creazione di un nuovo elemento */
	ListItem* item=(ListItem*)malloc(sizeof(ListItem));
	item->next=NULL;
	item->prev=NULL;
	return item;
}

