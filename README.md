# Projeto_Final SO

      Aluno: Hériclys Barbosa de Sousa
      Aluno: Samuel Saraiva 

## PROGRAMA ORIGINAL:

      #define _GNU_SOURCE
      #include <stdlib.h>
      #include <malloc.h>
      #include <sys/types.h>
      #include <sys/wait.h>
      #include <signal.h>
      #include <sched.h>
      #include <stdio.h>
      // 64kB stack
      #define FIBER_STACK 1024*64
      struct c {
      int saldo;
      };
      typedef struct c conta;
      conta from, to;
      int valor;
      // The child thread will execute this function
      int transferencia( void *arg)
      {
      if (from.saldo >= valor){ // 2
      from.saldo -= valor;
      to.saldo += valor;
      }
      printf("Transferência concluída com sucesso!\n");
      printf("Saldo de c1: %d\n", from.saldo);
      printf("Saldo de c2: %d\n", to.saldo);
      return 0;
      }
      int main()
      {
      void* stack;
      pid_t pid;
      int i;
      // Allocate the stack
      stack = malloc( FIBER_STACK );
      if ( stack == 0 )
      {
      perror("malloc: could not allocate stack");
      exit(1);
      }
      // Todas as contas começam com saldo 100
      from.saldo = 100;
      to.saldo = 100;
      printf( "Transferindo 10 para a conta c2\n" );
      valor = 10;
      for (i = 0; i < 10; i++) {
      // Call the clone system call to create the child thread
      pid = clone( &transferencia, (char*) stack + FIBER_STACK,
      SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
      if ( pid == -1 )
      {
      perror( "clone" );
      exit(2);
      }
      }
      // Free the stack
      free( stack );
      printf("Transferências concluídas e memória liberada.\n");
      return 0;
      }

##`Modificações inclusas ao projeto:`

## 1: `#include <pthreads.h>` 
Foi incluso por ser uma biblioteca que me permitiria trabalhar com ambas as plataformas, tanto 
em Linux quanto em Windows, já que a forma de criação de threads presente no código 
original não era adequado em Windows.

## 2: `#define NUM_THREADS 100`
Apenas define a quantidade de threads que será gerada ao longo do projeto, poderia ser incluso
logo de no início como foi feito, ou na função maim, por exemplo: const int NUM_THREADS = 100;

## 3: `static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;`
Este trecho do código iniciará o mutex, que será o responsável por fazer a gestão da sessão crítica
do programa (trecho este que só poderá ser executado por apenas uma thread).

## 4: `void *transferencia(void *arg){ `
Na verdade, neste ponto do código a única alteração foi a mudança do tipo
da função, que originalmente era "int transferencia( void *arg){ ", com void
essa função poderia ou não retornar algo, sendo trabalhada mais como um procedimento.

## 5: `pthread_mutex_lock(&mutex); ` 
Aqui se inicia o "ponto crítico" do programa, o qual somente uma thread executará por vez,
este trecho significa que há uma trava, e que só uma thread executará a partir destes ponto,
até que sua operação seja finalizada e assim ela será desbloqueada futuramente.

## 6: `pthread_mutex_unlock(&mutex); `
Aqui é finalizado o "ponto crítico" do programa, ou seja a partir deste ponto a trava será removida.

## 7: `pthread_t newthread[NUM_THREADS]; `
O pthread é um padrão de threads para o POSIX, o qual é capaz de identificar o thread, sendo que 
"newthread" é o nome que a thread trabalhará ao longo do programa, isto consignado ao "[NUM_THREADS]" já
a criará no padrão antes especificado.

## 8: `for (i = 0; i < NUM_THREADS; i++) {`
Ele executará um for que irá de 0 a 100 (valor definido em NUM_THREADS).

## 9: `pid = pthread_create(&newthread[i], NULL, transferencia, NULL);`
Pid pode ser interpretado como a digital de uma pessoa, a qual cada um tem uma distinta das demais.
é criado uma thread a partir desde trecho: "pthread_create" porém necessita de alguns parâmetros como:
o endereço de um pthread_t em específico, a função que ele executará quando for criado, NULL deixa em aberto 
seu resultado, sendo que o mesmo pode ser alterado durante sua execução.

## 10: `printf("A thread %lu foi criada\n", &newthread[i]);`
Aqui ele printará a thread que foi gerada.

## 11: `goto enunciado; / enunciado:`
Goto lhe permite pegar o código em determinado ponto e joga-lo em um distindo, sendo que " goto enuncado; "
sever para atribuir onde ele será enviado para outro ponto e " enunciado: " onde o código voltará a executar.

##`Executar o programa no Linux.`
1- Ao abrir o terminal, coloque " mkdir " o que lhe permitirá criar um diretório. Exemplo: lab/projetofinal;
2- Coloque " cd " e o nome do diretório criado para entrar no mesmo;
3- Ao tentar compilar o programa, como utilizamos <pthread> deve-se incluir " -lpthread ". exemplo: gcc projetoFINAL -lpthread -o teste;
4- Por fim basta escrever " ./teste " ou ./ e o nome acrescentado.
      
## `Executar o programa no Windows.`
1- Aperte a tecla Windows + R, que abrirá o executar do windows;
2- Escreva " cmd " e clique com " OK ";
3- Escreva " c:\ para alterar o diretório. Digite  md c:\simple e então o diretório estará criado e então digite c:\simple
para entrar no diretório criado;
4- Digite simple.c no prompt para compilá0lo;
5- Por fim, digite simple.exe (simple caso este seja o nome que o usuário escolheu).

## `Como saber se funcinou?`
Ao fim do programa, pode-se reparar que uma das contas estará zerada enquanto a outra receberá todo o valor que estava presente
na outra conta (caso o teste seja feito com o valor inicial: 100).

## `Fontes utilizadas ao longo do projeto.`
            https://youtu.be/1ks-oMotUjc
            https://youtu.be/ynCc-v0K-do
            https://www.modernescpp.com/index.php/race-condition-versus-data-race
            https://youtu.be/It0OFCbbTJE
            https://youtu.be/uA8X5zNOGw8
            https://www.youtube.com/watch?v=nVESQQg-Oiw&feature=youtu.be
            https://www.youtube.com/watch?v=nVESQQg-Oiw&feature=youtu.be
            https://docs.microsoft.com/pt-br/cpp/build/walkthrough-compile-a-c-program-on-the-command-line?view=vs-2019
            https://www.bogotobogo.com/cplusplus/RandomNumbers.php

## `Por que esta linguagem?`
Recentemente tivemos oficinas de C, as quais nos permitiram compreender diversas novas formas de programar ou
atribuir termos dentro da programação, embora a linguagem Python fosse a que utilizamos durante todo os nossos
semestres, tivemos interesse em programar em C, embora isso tenha complicado muito o projeto também nós permitiu
estudar muito sobre uma linguagem a qual eu não estavámos acostumados. Por fim, foi escolhida como um desafio pessoal
e também acreditamos que conseguiríamos entregar um trabalho adequado mesmo tendo que estudar praticamente toda as possíveis
aplicações que imaginamos durante o programa.





