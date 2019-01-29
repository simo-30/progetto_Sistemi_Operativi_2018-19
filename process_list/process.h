//header con le strutture dati di un processo e i prototipi delle funzioni

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
