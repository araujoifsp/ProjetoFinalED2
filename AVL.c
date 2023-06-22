
#include <stdio.h>
#include <stdlib.h>
#include "funcoesAuxiliares.h"
#include "arvore.h"
#include "AVL.h"
#include "desempenho.h"

/*
typedef struct ArvoreAVL {
    struct Funcionarios* dado;
    struct ArvoreAVL* esquerda;
    struct ArvoreAVL* direita;
    int altura;
} ArvoreAVL;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(ArvoreAVL* node) {
    if (node == NULL)
        return 0;
    return node->altura;
}

int fatorBalanceamento(ArvoreAVL* node) {
    if (node == NULL)
        return 0;
    return altura(node->esquerda) - altura(node->direita);
}

ArvoreAVL* criarNo(Funcionarios* funcionario) {
    ArvoreAVL* novoNo = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
    novoNo->dado = funcionario;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 1;
    return novoNo;
}

ArvoreAVL* rotacaoDireita(ArvoreAVL* y) {
    ArvoreAVL* x = y->esquerda;
    ArvoreAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

ArvoreAVL* rotacaoEsquerda(ArvoreAVL* x) {
    ArvoreAVL* y = x->direita;
    ArvoreAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

ArvoreAVL* inserir(ArvoreAVL* node, Funcionarios* funcionario) {
    if (node == NULL){
        return criarNo(funcionario);
    }

    if (funcionario->codigo < node->dado.codigo) {
        node->esquerda = inserir(node->esquerda, funcionario);
    } else if (funcionario.codigo > node->dado.codigo) {
        node->direita = inserir(node->direita, funcionario);
    } else {
        // O funcion�rio j� existe na �rvore (caso queira evitar duplicatas)
        return node;
    }

    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    int balanceamento = fatorBalanceamento(node);

    // Casos de rota��o AVL
    if (balanceamento > 1 && funcionario.codigo < node->esquerda->dado.codigo) {
        return rotacaoDireita(node);
    }

    if (balanceamento < -1 && funcionario.codigo > node->direita->dado.codigo) {
        return rotacaoEsquerda(node);
    }

    if (balanceamento > 1 && funcionario.codigo > node->esquerda->dado.codigo) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }

    if (balanceamento < -1 && funcionario.codigo < node->direita->dado.codigo) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }

    return node;
}

// Fun��o de exemplo para percorrer a �rvore em ordem
void percorrerEmOrdem(ArvoreAVL* root) {
    if (root != NULL) {
        percorrerEmOrdem(root->esquerda);
        // Fa�a algo com os dados do funcion�rio, por exemplo, imprimir
        printf("%s\n", root->dado->nome);
        percorrerEmOrdem(root->direita);
    }
}

/*
int main() {
    id* raiz = NULL;

    raiz = //vir aqui a lista de func

    printf("Percurso em ordem da �rvore AVL: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    return 0;
}
*/
