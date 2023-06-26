#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "AVL.h"
#include "funcoesAuxiliares.h"
#include "arvore.h"
#include "desempenho.h"

typedef struct No {
    int info;
    struct No* esq;
    struct No* dir;
    int altura;
}NoAVL;

typedef struct{
    NoAVL *raiz;
}arvB;

int altura(NoAVL *No) {
    if (No == NULL) {
        return -1;
    }
    return No->altura;
}

void atualizarAltura(NoAVL *No) {
    int alturaEsq = altura(No->esq);
    int alturaDir = altura(No->dir);
    No->altura = (alturaEsq > alturaDir ? alturaEsq : alturaDir) + 1;
}

NoAVL* rotacaoDireita(NoAVL *No) {
    NoAVL *novaRaiz = No->esq;
    No->esq = novaRaiz->dir;
    novaRaiz->dir = No;
    atualizarAltura(No);
    atualizarAltura(novaRaiz);
    return novaRaiz;
}

NoAVL* rotacaoEsquerda(NoAVL *No) {
    NoAVL *novaRaiz = No->dir;
    No->dir = novaRaiz->esq;
    novaRaiz->esq = No;
    atualizarAltura(No);
    atualizarAltura(novaRaiz);
    return novaRaiz;
}

NoAVL* balancear(NoAVL *No) {
    if (altura(No->esq) - altura(No->dir) > 1) {
        if (altura(No->esq->dir) > altura(No->esq->esq)) {
            No->esq = rotacaoEsquerda(No->esq);
        }
        No = rotacaoDireita(No);
    } else if (altura(No->dir) - altura(No->esq) > 1) {
        if (altura(No->dir->esq) > altura(No->dir->dir)) {
            No->dir = rotacaoDireita(No->dir);
        }
        No = rotacaoEsquerda(No);
    }
    return No;
}
NoAVL* inserirDireita(NoAVL* No, int dado);

NoAVL* inserirEsquerda(NoAVL *No, int dado) {
    if (No == NULL) {
        NoAVL *novo = (NoAVL*)malloc(sizeof(NoAVL));
        novo->info = dado;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }
    if (dado < No->info) {
        No->esq = inserirEsquerda(No->esq, dado);
    } else {
        No->dir = inserirDireita(No->dir, dado);
    }
    atualizarAltura(No);
    return balancear(No);
}

NoAVL* inserirDireita(NoAVL *No, int dado) {
    if (No == NULL) {
        NoAVL *novo = (NoAVL*)malloc(sizeof(NoAVL));
        novo->info = dado;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }
    if (dado < No->info) {
        No->esq = inserirEsquerda(No->esq, dado);
    } else {
        No->dir = inserirDireita(No->dir, dado);
    }
    atualizarAltura(No);
    return balancear(No);
}

void inserir(arvB *arv, int dado) {
    arv->raiz = inserirEsquerda(arv->raiz, dado);
}

int consulta_arvAVL(arvAVL *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }

    struct NO *atual = *raiz;

    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info){
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return 0;
}

void libera_arvAVL(struct No *NoAVL) {
    if(NoAVL == NULL){
        return;
    }
    libera_arvAVL(NoAVL->esq);
    libera_arvAVL(NoAVL->dir);
    free(NoAVL);
    NoAVL = NULL;
}

