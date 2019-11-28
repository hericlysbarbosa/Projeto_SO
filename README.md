# Projeto_Final SO

Aluno: Hériclys Barbosa de Sousa

Modificações inclusas ao projeto:

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

## 8: 






