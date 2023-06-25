#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesAuxiliares.h"
#include "desempenho.h"
#include "arvore.h"

#define RED 1
#define BLACK 0

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

                break;
            case 2:
                printf("\nVoce escolheu a opcao do arquivo desordenado\n");
                pausaTela;

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


void imprimirFuncionario(Funcionarios* func) {
    printf("Codigo: %d\n", func->codigo);
    printf("Nome: %s\n", func->nome);
    printf("Idade: %d\n", func->idade);
    printf("Empresa: %s\n", func->empresa);
    printf("Departamento: %s\n", func->departamento);
    printf("Salario: %.2f\n", func->sal);
    printf("\n");
}

void lerCSV(arvoreLLRB *raiz, int options) {
    FILE *f;
    char linha[200];

    f = fopen("massaDados.csv", "r");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int numFuncionarios = 0;
    while (fgets(linha, sizeof(linha), f)) {
        numFuncionarios++;
    }
    rewind(f);

    Funcionarios* vetorFuncionarios = (Funcionarios*) malloc(numFuncionarios * sizeof(Funcionarios));
    int i = 0;
    while (fgets(linha, sizeof(linha), f)) {
        Funcionarios func;
        char *texto = linha;
        func.codigo = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.departamento, strtok(NULL, ";"));
        func.sal = atof(strtok(NULL, ";"));
        vetorFuncionarios[i++] = func;
    }

    fclose(f);
    /*
    for (int j = 0; j < numFuncionarios; j++) {
        imprimirFuncionario(&vetorFuncionarios[j]);
    }
    */
    if(options == 2) {
        insere_arvoreLLRB(raiz, vetorFuncionarios, numFuncionarios);
        printf("Realizada a insercao com arvore rubro negra\n");
    }
    //aqui coloca a do arvore AVL

    free(vetorFuncionarios);
}

void exportToCSV(Funcionarios arr[], int n) {
    FILE* f = fopen("ordenado.csv", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    fprintf(f, "Código;Nome;Idade;Empresa;Departamento;Salário\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%d;%s;%s;%.2f\n", arr[i].codigo, arr[i].nome, arr[i].idade,
                arr[i].empresa, arr[i].departamento, arr[i].sal);
    }

    fclose(f);
    printf("Dados exportados para o arquivo");
}

void lerCSVOrdenado(arvoreLLRB *raiz, int options) {
    FILE *f;
    char linha[200];

    f = fopen("ordenado.csv", "r");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int numFuncionarios = 0;
    while (fgets(linha, sizeof(linha), f)) {
        numFuncionarios++;
    }
    rewind(f);

    Funcionarios* vetorFuncionarios = (Funcionarios*) malloc(numFuncionarios * sizeof(Funcionarios));
    int i = 0;
    while (fgets(linha, sizeof(linha), f)) {
        Funcionarios func;
        char *texto = linha;
        func.codigo = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.departamento, strtok(NULL, ";"));
        func.sal = atof(strtok(NULL, ";"));
        vetorFuncionarios[i++] = func;
    }

    fclose(f);

    /*
    for (int j = 0; j < numFuncionarios; j++) {
        imprimirFuncionario(&vetorFuncionarios[j]);
    }*/

    if(options == 2) {
        insere_arvoreLLRB(raiz, vetorFuncionarios, numFuncionarios);
        printf("Realizada a insercao com arvore rubro negra\n");
    }
    //aqui coloca a do arvore AVL

    free(vetorFuncionarios);
}

struct NO {
    Funcionarios *funcionario;
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

struct NO *insereNO(struct NO *H, Funcionarios *funcionario, int *resp) {
    if (H == NULL) {
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));

        if (novo == NULL) {
            *resp = 0;
            return NULL;
        }

        novo->funcionario = funcionario;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }

    if (funcionario->codigo == H->funcionario->codigo) {
        *resp = 0;
    } else {
        if (funcionario->codigo < H->funcionario->codigo) {
            H->esq = insereNO(H->esq, funcionario, resp);
        } else {
            H->dir = insereNO(H->dir, funcionario, resp);
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

void insere_arvoreLLRB(arvoreLLRB *raiz, Funcionarios vetorFuncionarios[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        int resp;
        *raiz = insereNO(*raiz, &vetorFuncionarios[i], &resp);
    }

    if (*raiz != NULL) {
        (*raiz)->cor = BLACK;
    }
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
    if(valor < H->funcionario){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, valor);
    }else{
        if(cor(H->esq) == RED){
            H = rotacionaDireita(H);
        }
        if(valor == H->funcionario && (H->dir == NULL)){
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK){
            H = move2DirRED(H);
        }
        if(valor == H->funcionario){
            struct NO *x = procuraMenor(H->dir);
            H->funcionario = x->funcionario;
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

int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    }

    struct NO *atual = *raiz;

    while (atual != NULL) {
        if (valor == atual->funcionario->codigo) {
            return 1;
        }
        if (valor > atual->funcionario->codigo) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return 0;
}

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor) {
    if(consulta_arvoreLLRB(raiz, valor)) {
        struct NO *H = *raiz;

        *raiz = removeNO(H, valor);
        if(*raiz != NULL) {
            (*raiz)->cor = BLACK;
        }
        return 1;
    } else {
        return 0;
    }
}

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

