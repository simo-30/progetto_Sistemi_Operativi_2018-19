//header per gestire la creazione di nuove richieste di risorse da parte dei processi
#include "../process_list/process.h"
#include "../process_list/list_process.h"
#pragma once

/* La soluzione che adotto per poter creare una nuova richiesta di risorse da parte dei processi
 * consiste in una funzione la quale crea in modo casuale la richiesta (per il tipo, CPU o I/O,
 * e per la durata), ma gli viene passato un intero che sta ad indicare il tempo dal quale può
 * arrivare tale processo, ed un altro intero che sta ad indicare il tempo massimo oltre il 
 * quale il processo non può arrivare, quindi il tempo di arrivo effettivo viene calcolato in 
 * modo casuale nel range fra tempo minimo e tempo massimo
*/

int process_next_burst(ProcessType* proc, int time_min, int time_max, int duration_max);
