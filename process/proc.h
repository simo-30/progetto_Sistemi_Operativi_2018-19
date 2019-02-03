//header con le strutture dati di un processo e i prototipi delle funzioni
#pragma once
typedef enum {CPU=0, IO=1} ResourceType;

typedef struct {
	/**
	 * ogni processo avrà i seguenti campi per ogni ciclo di richiesta di CPU/IO:
	 * duration => durata della burst di CPU/IO richiesta
	 * resource => il tipo di risorsa richiesta
	 * 
	 * mentre ogni processo sarà indicato univocamente da:
	 * pid => sarà assegnato dallo scheduler (o dal programma di prova)
	 * 
	 * ci sarà un campo ulteriore, che serve per avere una lista di tutti i processi che arriveranno,
	 * ordianta in base al tempo di arrivo, che entreranno nello scheduler al tempo debito: 
	 * time_arrive => indica il tempo di arrivo allo scheduler (o al programma di prova)
	 **/
	int pid;
	int time_arrive;
	int duration;
	ResourceType resource;
} ProcessType; 

ProcessType create_Process(int pid, int max_time_arrive, int max_duration); 
/* 
 * funzione che crea un processo con pid dato, e con tempo di arrivo casuale, ma minore di
 * max_time_arrive, e con duration casuale, ma minore di max_duration, 
 * e con il tipo di risorsa richiesta (CPU o I/O) generata casualmente
*/

void print_process(ProcessType process);
ProcessType create_Process_fromData(int pid, int timeArrive, int duration, int resource);
/* questa funzione crea un processo dato il pid, il tempo di arrivo, la durata e il tipo di risorsa,
 * verrà chiamata da un'altra funzione che prenderà tali parametri da un file*/ 
