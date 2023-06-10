#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesAuxiliares.h"
#include "desempenho.h"
#include "algoritmos.h"

#define RED 1
#define BLACK 0

struct NOavl {
    int info;
    int alt; //altura
    struct NOavl *esq;
    struct NOavl *dir;
};

struct NOrb {
    int info;
    struct NOrb *esq;
    struct NOrb *dir;
    int cor;
};

void menu() {
    pula1Linha;
    printf("Escolha o tipo de arvore: \n");
    printf("1. Arvore AVL\n");
    printf("2. Arvore Rubro-Negra\n");
    printf("3. Sair do programa\n");
}

int resp_menu() {
    int x;
    pula2Linhas;
    printf("Digite a opcao desejada: \n");
    scanf("%d", &x);

    return x;
}

void sub_menu() {
    pula1Linha;
    printf("Escolha a forma de preenchimento da arvore: \n");
    printf("1. Arquivo Ordenado\n");
    printf("2. Arquivo Desordenado\n");
}

int opcao_ecolhida(int options2){
    switch(options2){
            case 1:
                printf("\nVoce escolheu a opcao do arquivo ordenado\n");
                pausaTela;
                // return arquivo ordenado;
                break;
            case 2:
                printf("\nVoce escolheu a opcao do arquivo desordenado\n");
                pausaTela;
                // return arquivo desordenado;
                break;
            default:
                printf("ERRO!!!!! \nPreencha o menu corretamente\n");
                pausaTela;
                break;
    }
}

int resp_sub_menu() {
    int x;
    pula2Linhas;
    printf("Digite a opcao desejada: \n");
    scanf("%d", &x);

    return x;
}



