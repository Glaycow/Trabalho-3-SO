
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main(){

	int *soma, x=3, y=3;
	int idMem; /* identificador da memória comum */
    int sem;
	struct sembuf P, V;
	P.sem_num=0;P.sem_op= -1;
	P.sem_flg=0;
	V.sem_num=0;
	V.sem_op=1;
	V.sem_flg=0;


	if ((sem = semget(IPC_PRIVATE, 1, IPC_CREAT|0666)) == -1){
		perror("Erro do semget"); exit(0);
	}

	//Inicia semáforo com 1 (Último parâmetro)

	if (semctl(sem, 0, SETVAL, 1) == -1) {
	perror("Erro ao inicializar semáforo");
	exit(0);
	}

	//Cria uma área de memória compartilhada

	idMem = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666);
	if (idMem == -1) {
		perror("Erro no shmget") ;
		exit(0) ;
	}

	// acoplamento do processo a zona de memória
	soma = shmat(idMem, 0, 0);
	*soma = 10;


	if (fork()==0){
		semop(sem, &P, 1); 
            *soma = *soma + x + y;
            printf("\n\nNo filho1: soma = %d", *soma); puts(" ");
		semop(sem, &V, 1);
		exit(0);
	}

	if (fork()==0){
		semop(sem, &P, 1); 
            x = x + 5;
            *soma = *soma + 10;
            printf("\n\nNo filho2: soma = %d", *soma); puts(" ");
		semop(sem, &V, 1);
		exit(0);
	}
	wait(0); wait(0);
	*soma = *soma + 10;
	printf("\nValor do pai: Soma = %d", *soma); puts(" ");


}