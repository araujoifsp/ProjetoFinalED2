//Arquivo main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoesAuxiliares.h"

int main()
{
    arvoreLLRB *raiz;

    printf("**** Projeto: Desempenho AVL x Rubro-Negra ****");
    pula2Linhas;
    printf("**** Alunos: ****");
    pula1Linha;
    printf("Alicia Lopes - GU3026558");
    pula1Linha;
    printf("Gabriel de Araujo - GU3027261");
    pula1Linha;
    printf("Guilherme Correa Monteiro - GU3026647");
    pula1Linha;
    printf("J�ssica de Medeiros Corr�a - GU3027252");
    pula1Linha;
    printf("Leonardo dos Reis - GU3027287");
    pula1Linha;
    printf("Lucas Knupp - GU3026787");
    pula1Linha;
    pula2Linhas;

    printf("**** Menu ****");
    pula1Linha;

    while(1) {

        int x;

        //int *vetor;
        int i = 0;
        //double *tempo;
        int arquivo = 0;
        //tempo = malloc(10 * sizeof(double));

        int options, options2;
        menu();
        options = resp_menu();

        switch(options){
        case 1 : ;
            //apagaTela;
            //printf("\nVoce escolheu a arvore -> AVL\n");
            //pausaTela;
            //sub_menu();
            //options2 = resp_sub_menu();
            //arquivo = opcao_ecolhida(options2);
            break;
        case 2 : ;
            apagaTela;
           printf("\nVoce escolheu a arvore -> Rubro-Negra\n");
            pausaTela;
           sub_menu();
           options2 = resp_sub_menu();
           arquivo = opcao_ecolhida(options2);

            raiz = cria_arvBin();
            switch(options2){
                case 1:
                    lerCSVOrdenado(raiz, options);
                    if(vazia_arvBin(raiz)){
                        printf("A arvore esta vazia");
                    } else {
                        printf("A arvore possui elementos");
                    }
                    printf("\n");
                break;
                case 2:
                    lerCSV(raiz, options);
                    if(vazia_arvBin(raiz)){
                        printf("A arvore esta vazia");
                    } else {
                        printf("A arvore possui elementos");
                    }
                    printf("\n");
                break;
            }
            liberar_arvBin(raiz);
            break;
        case 3 : ;
            apagaTela;
            printf("\nVoce escolheu a opcao 3 -> Sair do programa!\n");
            pula2Linhas;
            pausaTela;
            return 0;
            break;
        default:
            apagaTela;
            printf("ERRO!!!!! \nPreencha o menu corretamente");
            pula2Linhas;
            break;
        }

        //tempo = timer(vetor,tam,options); //atualizar de acordo com o formato das arvores
        //printf("Tempo de ordena��o: %f segundos\n",tempo[i]);
        pula2Linhas;

        //radixSort_lsd(vetor, tam);


    }
}


