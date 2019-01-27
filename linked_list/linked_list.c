#include <stdlib.h>
#include <stdio.h>
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

void list_insert(ListHead* head, ListItem* prec, ListItem* item) {
	/** 
	 * il controllo su quale lista stiamo aggiungendo l'elemento
	 * verrà fatto a monte, ossia quando dovremo inserire l'elemento
	 * si cercherà la posizione in cui inserirlo, per cui, si starà
	 * lavorando già in una lista;
	 * serve avere la testa della lista, va aumentato il campo il size
	 **/
	if (item==NULL) {
		//l'elemento da inserire non può essere nullo
		#if DEBUG
		printf("Elemento da inserire nullo, non valido\n");
		#endif
		return;
	}
	if (prec==NULL) {
		#if DEBUG
		printf("Elemento precedente nullo, non valido\n");
		#endif
		return;
	}
	item->next=prec->next;
	if (prec->next!=NULL) {
		prec->next->prev=item;
	}
	item->prev=prec;
	prec->next=item;
	head->size+=1;
	return;
}
