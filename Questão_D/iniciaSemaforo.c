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
	
	//Inicia semáforo com 20 (Último parâmetro)
	if (semctl(semaforo, 0, SETVAL, 20) == -1) {
		perror("Erro ao inicializar o semáforo");
		exit(0);
	}
    
	puts("Semáforo Inicializado");	
}