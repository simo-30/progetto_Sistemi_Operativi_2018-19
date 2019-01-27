#pragma once /*direttiva per evitare che il compilatore dia errore nel caso trovi 
			   lo stesso codice in altri file*/

typedef struct ListItem {
	struct ListItem* prev;
	struct ListItem* next;
	//elemento generico della lista
} ListItem;

typedef struct ListHead {
	ListItem* first;
	int size;
	/* testa della lista con puntatore al primo elemento
	 * un intero per la dimensione della lista
	 */
} ListHead;

//prototipi delle funzioni per la gestione della lista
ListHead* list_init();
ListItem* list_find(ListHead* head, ListItem* item);
ListItem* new_item();
void list_insert(ListHead* head, ListItem* prec, ListItem* item);
void list_insert_first(ListHead* head, ListItem* item);
ListItem* remove_first(ListHead* head);
ListItem* remove_item(ListHead* head, ListItem* item);
#if DEBUG
void print_ind_lista(ListHead* head);
#endif
