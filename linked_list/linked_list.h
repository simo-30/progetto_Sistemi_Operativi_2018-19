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
	char name[64];
	/* 
	 * testa della lista con puntatore al primo ed all'ultimo elemento
	 * un intero per la dimensione della lista
	 * ed un puntatore a char per il nome della lista
	 */
} ListHead;

//prototipi delle funzioni per la gestione della lista
void list_init(ListHead* head, char name[]);
int list_find(ListHead* head, ListItem* item); 
ListItem* list_insert(ListHead* head, ListItem* prev, ListItem* item);
ListItem* list_remove_item(ListHead* head, ListItem* item);
ListItem* list_insert_front(ListHead* head, ListItem* item);
ListItem* list_insert_last(ListHead* head, ListItem* item);
ListItem* list_remove_first(ListHead* head, ListItem* item);
