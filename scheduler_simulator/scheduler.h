/*file header per la gestione delle funzioni di uno scheduler*/
#include "process.h"
#include "list_process.h"
#include "nextBurst.h"
#pragma once

ListProcess* generate_new_processes(const char* nameList, int pidMax, int maxTime, int maxDuration);
	/**questa funzione servirà per generare nuovi pidMax processi casuali, 
	 * con tempo di arrivo massimo maxTime, con durata massima maxDuration
	 * e con il tipo di risorsa richiesta (CPU o I/O) casuale,
	 * questi verranno inseriti ordinatamente (in base al loro tempo di arrivo)
	 * in una nuova lista di processi che avrà per nome nameList**/
	 
ProcessItem* get_process_byTime(ListProcess* list, int time);
	/**questa funzione ritorna il processo con il tempo corrispondente a time
	 * dalla lista dei processi in arrivo list**/

void reduce_duration_running(ProcessItem* proc);
	/**questa funzione serve a ridurre di una unità il tempo di durata di un processo,
	 * viene chiamata ad ogni ciclo dallo scheduler sul processo in running**/

void reduce_duration_io(ListProcess* list);
	/**questa funzione riduce di una unità il tempo di durata di tutti i processi nella lista,
	 * viene chiamata dallo scheduler ad ogni ciclo sulla lista dei processi in stato di I/O**/

void insert_on_IO_list(ListProcess* list, ProcessItem* proc);
	/**questa funzione prende una lista (dei processi in stato di I/O) ed un processo
	 * che richiede la risorsa di I/O e inserisce quest'ultimo in testa alla lista,
	 * la modalità di inserimento in questa lista è per la durata**/

void insert_on_waiting_list(ListProcess* list, ProcessItem* proc);
	/**questa funzione prende una lista (dei processi in stato di waiting, 
	 * ossia che hanno terminato il loro lavoro) e ne inserisce unaltro in lista,
	 * e siccome comunque poi per tutti questi processi verranno generati un nuovo
	 * tempo di arrivo, una nuova durata ed una nuova richiesta di risorsa
	 * non interessa in che ordine vengano inseriti nella lista, per cui per ottimizzare
	 * la funzione verranno inseriti in testa**/
