#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(){

	int temperatura, valor_semaforo;
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
	
	
	//Inicia semáforo com 1 (Último parâmetro)
	if (semctl(semaforo_1, 0, SETVAL, 0) == -1) {
		perror("Erro ao inicializar o Primeiro semáforo");
		exit(0);
	}

	if (semctl(semaforo_2, 0, SETVAL, 0) == -1) {
		perror("Erro ao inicializar o Segundo semáforo");
		exit(0);
	}
	
	//Pega e imprime o valor do semáforo
	if ( ( valor_semaforo = semctl(semaforo_1, 0, GETVAL, 1)) == -1) {
		perror("Erro ao pegar valor do Primeiro semáforo");
		exit(0);
	}

	if ( ( valor_semaforo = semctl(semaforo_2, 0, GETVAL, 1)) == -1) {
		perror("Erro ao pegar valor do do Segundo semáforo");
		exit(0);
	}
	
	

	for(;;){
		printf("\nDigite o valor da temperatura:");
		scanf("%d", &temperatura);
		if (temperatura < 25){
			semop(semaforo_1, &V, 1);
		}
		else{
			semop(semaforo_2, &V, 1);
		}
	}

	

}