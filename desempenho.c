#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "funcoesAuxiliares.h"
#include "desempenho.h"
#include "algoritmos.h"

double timer(int *vetor, int tamanho, int arv){
    struct timeval inicio, fim;

    gettimeofday(&inicio, NULL);
    switch(arv){
        case 1:
                arvAVL(vetor, tamanho); // atualizar para o modo de preenchimento
                break;

        case 2:
                arvLLRB(vetor, tamanho); // atualizar para o modo de preenchimento
                break;
    }
    gettimeofday(&fim, NULL);

    double s = (fim.tv_sec + fim.tv_usec/1000000.0) - (inicio.tv_sec + inicio.tv_usec /1000000.0);
    return s;
}


