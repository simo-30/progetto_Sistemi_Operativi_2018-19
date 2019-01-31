Qui implementerò uno scheduler (simulato), con politica SRJF (shortest remaing job first).

Creerò prima una lista di processi, ordinata per tempo di arrivo dei processi; 
i processi sono creati in modo in casuale (per quanto riguarda la durata del burst richiesto, 
il tempo di arrivo, ed il tipo di risorsa richiesta, CPU o I/O).

Serviranno delle variabili globali per gestire le liste dei processi, in particolare ci saranno le seguenti
liste:

1) lista dei processi in arrivo;
2) lista dei processi in stato di waiting;
3) lista dei processi in stato di ready;
4) lista dei processi in stato di I/O;

Ci sarà un processo alla volta che sarà nello stato di running.

Ad ogni ciclo di tempo viene ridotta di un'unità il valore della durata richiesta dal processo
in running e di tutti i processi in stato di I/O, se un processo ha terminato la sua durata viene
messo nella lista di waiting.

In particolare la lista dei processi in arrivo verrà generata al lancio del programma,
ordinata in modo crescente in base al tempo di arrivo ed ad ogni ciclo se il tempo del ciclo
corrisponde al tempo di arrivo del processo in testa (il quale ha il tempodi arrivo minore della lista)
questo viene rimosso dalla lista dei processi in arrivo e messo direttamente nella lista di ready, 
se la risorsa richiesta è la CPU, quest'ultima lista ordinata in base alla durata del burst richiesto,
altrimenti viene messa nella lista dei processi in stato di I/O.

I processi in stato di waiting vengono passati ad una funzione che genera una nuova richiesta di risorse
e di tempo di arrivo, il quale però non può essere superiore al tempo massimo in cui lo scheduler 
può ricevere nuovi processi, terminato tale tempo lo scheduler procederà a schedulare e completare
tutti i processi in coda.

Essendo questo uno scheduler preemptive se uno processo in stato di waiting richiede una risorsa 
la cui durata è minore del processo in testa, questo verrà sospeso e spostato (sempre in modo ordinato
in base alla durata) nella lista dei processi in stato di ready.
