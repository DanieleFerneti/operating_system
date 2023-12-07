#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define N_RECORDS 10


struct record {
	int a;
	int b;
	int c;
};

/*FUNZIONE DI ORDINAMENTO*/
int compara(const void *x, const void *y) {
	struct record *a = (struct record*) x;
	struct record *b = (struct record*) y;
	return a->a - b->a;
}

/*FUNZIONE CHE GENERA IN MODO RANDOM UN NUMERO ARBITRARIO DI RECORDS
* input n : numero di record che voglio generare
* output records : puntatore ad un array di record generati
*/
struct record* genera(int n) {
	struct record* records = (struct record*) calloc(n, sizeof(struct record)); //calloc(numero di elem da allocare, dimensione degli elementi)
	for (int i=0; i<n; i++) {
		//do 4 byte a ciascun campo del singolo record
		records[i].a = rand(); //*records
		records[i].b = rand();
		records[i].c = rand();
	}
	return records;
}

/*FUNZIONE SALVATAGGIO SU DISCO DI ARRAY DI RECORDS*/
* char* path = identifica il percorso del file da creare
* int n = numero di elementi del mio array
*/
void scrivi(char* path, struct record* records, int n) {
	int fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	if (fd == -1) {
		perror("Errore nella open: ");
		exit(-1);
	}
	for (int i=0; i<n; i++) {
		int written = 0;
		while (written < sizeof(struct record)) {
			written+=write(fd, (char*)&records[i]+written, sizeof(struct record)-written);
			/*secondo parametro: da dove devo iniziare a scrivere(char* utilizzato per ingannare l'aritmetica dei puntatori
			* terzo paramentro : quanto devo scrivere
   			*/
		}
	}
	close(fd);
}

void stampa_records(struct record* records, int n) {
	for (int i=0; i<n; i++) {
		printf("%d:\t %d\t%d\t%d\n", i, records[i].a, records[i].b, records[i].c);
	}
}

/*FUNZIONE LETTURA DA DISCO DI ARRAY DI RECORDS*/
struct record* leggi(char* path) {
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Errore nella open: ");
		exit(-1);
	}
	struct stat stats;//definisco la struct dove andranno le statistiche
	fstat(fd, &stats);//secondo parametro: puntatore ad una struct dove verranno messe tutte le statistiche all'interno del file
	struct record* records = (struct record*) malloc(stats.st_size); //st_size : total size in byte del file
	int n_records = stats.st_size/sizeof(struct record);//calcolo il numero dei records
	for (int i=0; i<n_records; i++) {
		read(fd, &records[i], sizeof(struct record));
	}
	close(fd);
	return records;	 
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Mi spiace, ma devi passare un argomento");
		exit(-1);
	}
	char* path = argv[1];

	struct record* records = genera(N_RECORDS);
	stampa_records(records, N_RECORDS); //stampa dei numeri appena generati
	scrivi(path, records, N_RECORDS);
	free(records);
	records=leggi(path); //abbiamo ricaricato i records
	printf("\n\n\n\n");
	stampa_records(records, N_RECORDS); //stampa dei records per verificare che sono gli stessi della prima stampa
	qsort(records, N_RECORDS, sizeof(struct record), compara);
	printf("\n\n\n\n");
	stampa_records(records, N_RECORDS);// stampa dei records per vedere se ordinamento è andato a buon fine
}

