

#include <stdio.h>
#include <stdlib.h>
#include "RN.h"

//codigo rubro negra
#define RED 1
#define BLACK 0

struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
};

int cor(struct NO *H){
    if(H == NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void trocaCor(struct NO *H){
    H->cor = !H->cor;

    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }

    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *rotacionaEsquerda(struct NO *A){
    struct NO *B = A->dir;

    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *rotacionaDireita(struct NO *A){
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *move2EsqRED(struct NO *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NO *move2DirRED(struct NO *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NO *balancear(struct NO *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}

struct NO *insereNO(struct NO *H, int valor, int *resp){
    if(H == NULL){
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));

        if(novo == NULL){
            *resp = 0;
            return NULL;
        }

        novo->info = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }

    if(valor == H->info){
        *resp = 0;
    }else{
        if(valor < H->info){
            H->esq = insereNO(H->esq, valor, resp);
        }else{
            H->dir = insereNO(H->dir, valor, resp);
        }
    }

    if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
    }

    if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }

    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }

    return H;
}

int insere_arvoreLLRB(arvoreLLRB *raiz, int valor){
    int resp;

    //funcao resp pela busca do local de inser��o do n�
    *raiz = insereNO(*raiz, valor, &resp);

    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }

    return resp;
}

struct NO *procuraMenor(struct NO *atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;

    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }

    return no1;
}

struct NO *removeNO(struct NO *H, int valor){
    if(valor < H->info){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, valor);
    }else{
        if(cor(H->esq) == RED){
            H = rotacionaDireita(H);
        }
        if(valor == H->info && (H->dir == NULL)){
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK){
            H = move2DirRED(H);
        }
        if(valor == H->info){
            struct NO *x = procuraMenor(H->dir);
            H->info = x->info;
            H->dir = removeNO(H->dir, valor);
        }else{
            H->dir = removeNO(H->dir, valor);
        }
    }
    return balancear(H);
}

struct NO *removeMenor(struct NO *H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
        H = move2EsqRED(H);
    }

    H->esq = removeMenor(H->esq);
    return balancear(H);
}

int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor){
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

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor){
    if(consulta_arvoreLLRB(raiz, valor)) {
        struct NO *H = *raiz;

        //funcao resp pela busca do no a ser removido
        *raiz = removeNO(H, valor);
        if(*raiz != NULL){
            (*raiz)->cor = BLACK;
        }
        return 1;
    }else{
        return 0;
    }
}




// fim rubro negra

/* calcula a altura de um no
int alt_no(struct NO *no){
    if(no == NULL){
        return -1;
    } else {
        return no->alt;
    }
}

// calcula o fator de balanceamento de um no
int fatorBalanceamento_NO(struct NO *no){
    return labs(alt_no(no->esq) - alt_no(no->dir));
}
// a funcao labs(), arredonda valores em modulo

// calcula maior valor
int maior(int x, int y){
    if(x >y){
        return(x);
    } else {
        return(y);
    }
}

void rotacaoLL(arvAVL *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), (*raiz)->alt + 1);
    *raiz = no;
}

void rotacaoRR(arvAVL *raiz){
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->dir), (*raiz)->alt + 1);
    (*raiz) = no;
}

void rotacaoLR(arvAVL *raiz){
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(arvAVL *raiz){
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

// fim cod avl aula 1

int insere_arvAVL(arvAVL *raiz, int valor) {
    int res; // pega resposta das chamadas de funcao
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            return 0;
        }
        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_arvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info){
                    rotacaoLL(raiz);
                } else {
                    rotacaoLR(raiz);
                }
            }
        }
    }else {
        if(valor > atual->info){
            if((res = insere_arvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        rotacaoRR(raiz);
                    } else {
                        rotacaoRL(raiz);
                    }
                }
            }
        }else {
            printf("Valor duplicado.\n");
            return 0;
        }
    }
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
}

struct NO *procuramenor(struct NO *atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_arvAVL(arvAVL *raiz, int valor) {
    if(*raiz == NULL){
        return 0;
    }
    int res;

    if(valor < (*raiz)->info){
        if((res = remove_arvAVL(&(*raiz)->esq, valor)) ==  1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir)){
                    rotacaoRR(raiz);
                }else{
                    rotacaoRL(raiz);
                }
            }
        }
    }

    if((*raiz)->info < valor){
        if((res = remove_arvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2) {
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
    }

    if((*raiz)->info == valor) {
        if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
            struct NO *no_velho = (*raiz);
            if((*raiz)->esq != NULL){
                *raiz = (*raiz)->esq;
            }else{
                *raiz = (*raiz)->dir;
            }
            free(no_velho);
        }else{
            struct NO *temp = procuramenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            remove_arvAVL((*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
        if(*raiz != NULL){
            (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)-> dir)) + 1;
        }
        return 1;
    }

    if(*raiz != NULL){
        (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    }
    return res;
}


// fim

*/
arvoreLLRB *cria_arvBin() {
    arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof(arvoreLLRB));
    if(raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvBin(arvoreLLRB *raiz) {
    if(raiz == NULL) {
        return;
    }

    libera_NO(*raiz);
    free(raiz);
}


void libera_NO(struct NO *no) {
    if(no == NULL){
        return;
    }

    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

int vazia_arvBin(arvoreLLRB *raiz) {
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

/*
int altura_arvBin(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }

    int alt_esq = altura_arvBin(&((*raiz)->esq));
    int alt_dir = altura_arvBin(&((*raiz)->dir));

    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    } else {
        return(alt_dir + 1);
    }
}

int totalNO_arvBin(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }

    int alt_esq = totalNO_arvBin(&((*raiz)->esq));
    int alt_dir = totalNO_arvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void preOrdem_arvBin(arvoreLLRB *raiz) {
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        preOrdem_arvBin(&((*raiz)->esq));
        preOrdem_arvBin(&((*raiz)->dir));
    }
}

void emOrdem_arvBin(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdem_arvBin(&((*raiz)->dir));
    }
}

void posOrdem_arvBin(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOrdem_arvBin(&((*raiz)->esq));
        posOrdem_arvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}

*/




