#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
//#include <windows.h>
#define FIBER_STACK 1024*64
#define NUM_THREADS 100


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct c{
	int saldo;
};

typedef struct c conta;

conta from, to;

int valor;

int x;


void *transferencia(void *arg){

	pthread_mutex_lock(&mutex);

        if (from.saldo >= valor){

		printf("Transferindo 10 reais\n");

		x = rand()%2;
		printf("%d",x);

		if (x == 0){
			from.saldo -= valor;
			to.saldo += valor;
		}

		else if (x == 1){
			to.saldo -= valor;
			from.saldo += valor;
		}

        	printf("Transferência concluída com sucesso!");
		printf("\nSaldo da c1: %d ",from.saldo);
		printf("\nSaldo da c2: %d \n\n",to.saldo);
	}

	pthread_mutex_unlock(&mutex);
}


int main(){

	pthread_t newthread[NUM_THREADS];
	void *stack;
    	pid_t pid;
    	int i;
    	void *thread_retorno;

    	from.saldo = 100;
    	to.saldo = 100;
    	valor = 10;

    	stack = malloc( FIBER_STACK );

	if ( stack == 0 ){
		perror("malloc: could not allocate stack");
	    	exit(1);
	}

	for (i = 0; i < NUM_THREADS; i++){

		pid = pthread_create(&newthread[i], NULL, transferencia, NULL);

		if ( pid == -1 ){
			perror( "Erro durante a criação da thread." );
	        	exit(2);
	    	}

		printf("A thread %ld foi criada. \n", newthread[i]);
	}


	for (i = 0; i < NUM_THREADS; i++){

	        pid = pthread_join(newthread[i], &thread_retorno);

		if ( pid == -1 ){
	    	perror( "Erro durante a finalização da thread." );
	        exit(2);
	    }
	}

	free ( stack );
	printf("Transferências concluídas e memória liberada\n");
//	Sleep(100);
	return 0;
}
