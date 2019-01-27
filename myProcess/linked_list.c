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
	if (list_find(head, prec)==NULL) {
		#if DEBUG
		printf("Elemento precedente non nella lista, non valido\n");
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
	#if DEBUG
	printf("Elemento inserito con successo\n");
	#endif
	return;
}

void list_insert_first(ListHead* head, ListItem* item) {
	//funzione per inserimento in testa
	if (head->first!=NULL) {
		item->next=head->first->next;
		item->prev=head->first->prev;
	}
	head->first=item;
	head->size+=1;
	#if DEBUG
	printf("Testa della lista aggiornata con successo\n");
	#endif
	return;
}

ListItem* remove_first(ListHead* head) {
	//funzione per la rimozione della testa
	ListItem* ret=head->first;
	if (head->first->next!=NULL) {
		head->first=ret->next;
		#if DEBUG
		printf("aggiornamento della testa con l'elemento successivo\n");
		#endif
	}
	else {
		head->first=NULL;
		#if DEBUG
		printf("la testa è null\n");
		#endif
	}
	head->size-=1;
	#if DEBUG
	printf("rimozione della testa avvenuta con successo\n");
	#endif
	return ret;
}

ListItem* remove_item(ListHead* head, ListItem* item) {
	//funzione per la rimozione di un elemento
	ListItem* aux=head->first;
	while (aux) {
		if (aux==item) {
			aux->prev->next=aux->next;
			#if DEBUG
			printf("Elemento trovato: %d\n", aux);
			#endif
			return aux;
		}
		aux=aux->next;
	}
	head->size-=1;
	#if DEBUG
	printf("L'elemento non è nella lista\n");
	#endif
	return NULL;
}

#if DEBUG
void print_ind_lista(ListHead* head) {
	ListItem* aux=head->first;
	while (aux) {
		printf("--- #%d ---\n", aux);
		aux=aux->next;
	}
	return;
}
#endif
