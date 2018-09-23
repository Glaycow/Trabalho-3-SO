#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){
	int semaforo;
	struct sembuf P,V;

	P.sem_num=0;
	P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;

	if ((semaforo = semget(100, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget");
        exit(0);
	}

    printf("O carro %d chegou!", getpid());	puts(" ");
    semop(semaforo, &P, 1);
    printf("O carro %d estacionou!", getpid()); puts(" ");
}