#pragma once /*direttiva per evitare che il compilatore dia errore nel caso trovi 
			   lo stesso codice in altri file*/

typedef struct ListItem {
	struct ListItem* prev;
	struct ListItem* next;
	//elemento generico della lista
} ListItem;

typedef struct ListHead {
	ListItem* first;
	ListItem* last;
	int size;
	/* testa della lista con puntatore al primo ed all'ultimo elemento
	 * un intero per la dimensione della lista
	 * ed un puntatore a char per il nome della lista
	 */
} ListHead;

//prototipi delle funzioni per la gestione della lista
ListHead* list_init();
ListItem* list_find(ListHead* head, ListItem* item);
ListItem* new_item();
void list_insert(ListItem* prec, ListItem* item);
