#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	
    int *sanduiche;
	int idMem;
	int semaforo_1, semaforo_2;
	struct sembuf P,V;

	P.sem_num=0;
	P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;


	if ((semaforo_1 = semget(100, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget"); exit(0);
	}

	if ((semaforo_2 = semget(200, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget"); exit(0);
	}
	
	//Se liga a uma área de memória compartilhada existente
	if ((idMem = shmget(100, sizeof(int), 0666)) == -1) {
		perror("Erro no shmget") ;
		exit(0) ;
	}
	
	// acoplamento do processo a zona de memória
	sanduiche = (int *)shmat(idMem, 0, 0);
	
	for(;;){
		if(*sanduiche == 0){
			puts("\nAcabaram os biscoitos, acorda a conzinheira é avisa aos outros alunos");
			semop(semaforo_2, &V, 1);
			sleep(2);
		}
		else{
			semop(semaforo_1, &V, 1);
			puts("\nRetirei um biscoito da travasse");
			*sanduiche = *sanduiche - 1;
			printf("Sanduiche Restantes na travessa: %d\n", *sanduiche);
			semop(semaforo_1, &P, 1);
		}		
		sleep(1);
	}
}