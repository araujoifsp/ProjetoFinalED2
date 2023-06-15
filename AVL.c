
#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreAVL {
    int dado;
    struct ArvoreAVL* esquerda;
    struct ArvoreAVL* direita;
    int altura;
} id;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getAltura(id* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

id* criarNo(int dado) {
    id* novoNo = (id*)malloc(sizeof(id));
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 1;
    return novoNo;
}

id* rotacionarDireita(id* y) {
    id* x = y->esquerda;
    id* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;

    return x;
}

id* rotacionarEsquerda(id* x) {
    id* y = x->direita;
    id* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;

    return y;
}

int getBalanceamento(id* no) {
    if (no == NULL)
        return 0;
    return getAltura(no->esquerda) - getAltura(no->direita);
}

id* inserir(id* no, int dado) {
    if (no == NULL)
        return criarNo(dado);

    if (dado < no->dado)
        no->esquerda = inserir(no->esquerda, dado);
    else if (dado > no->dado)
        no->direita = inserir(no->direita, dado);
    else
        return no;

    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));

    int balanceamento = getBalanceamento(no);

    if (balanceamento > 1 && dado < no->esquerda->dado)
        return rotacionarDireita(no);

    if (balanceamento < -1 && dado > no->direita->dado)
        return rotacionarEsquerda(no);

    if (balanceamento > 1 && dado > no->esquerda->dado) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (balanceamento < -1 && dado < no->direita->dado) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}

void percorrerEmOrdem(id* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        percorrerEmOrdem(raiz->direita);
    }
}
/*
int main() {
    id* raiz = NULL;

    raiz = //vir aqui a lista de func

    printf("Percurso em ordem da árvore AVL: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    return 0;
}
*/
