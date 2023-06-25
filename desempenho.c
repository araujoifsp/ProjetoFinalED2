#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "funcoesAuxiliares.h"
#include "desempenho.h"
#include "arvore.h"

long timer(arvoreLLRB *raiz, int options2, int options){
        struct timeval inicio, fim;

            gettimeofday(&inicio, NULL);
            switch(options2){
                case 1:
                    lerCSVOrdenado(raiz, options);
                    if(vazia_arvBin(raiz)){
                        printf("\nA arvore esta vazia");
                    } else {
                        printf("\nA arvore possui elementos");
                    }
                    printf("\n");
                break;
                case 2:
                    lerCSV(raiz, options);
                    if(vazia_arvBin(raiz)){
                        printf("\nA arvore esta vazia");
                    } else {
                        printf("\nA arvore possui elementos");
                    }
                    printf("\n");
                break;
            }
            gettimeofday(&fim, NULL);

    long s = (fim.tv_sec - inicio.tv_sec) * 1000000L + (fim.tv_usec - inicio.tv_usec);
    return s;
}

