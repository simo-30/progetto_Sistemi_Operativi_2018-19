In questa cartella creero i file per la gestione (simulata) di una lista dei processi.

Questi verranno creati tramite funzioni che genereranno CPU_BURST e IO_BURST in modo
casuale.

Poi verranno inseriti in una lista in modo ordinato, da quello che ha il CPU_BURST minore
a quello che lo ha maggiore.

Questo è un primo passaggio per poi implementare lo scheduler, il quale oltre a gestire le
liste dei processi, potrà anche riceverne altri (essendo simulato, si genereranno ogni periodo 
di tempo, il quale sarà casuale), ma potrà avere un massimo numero di processi (per evitare di 
entrare in un possibile ciclo infinito).
