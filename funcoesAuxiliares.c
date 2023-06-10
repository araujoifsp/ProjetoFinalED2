
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

Funcionario* lerCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Funcionario* raiz = NULL;
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Funcionario* novoFuncionario = (Funcionario*)malloc(sizeof(Funcionario));

        char* token = strtok(linha, ";");
        novoFuncionario->codigo = atoi(token);

        token = strtok(NULL, ";");
        strcpy(novoFuncionario->nome, token);

        token = strtok(NULL, ";");
        novoFuncionario->idade = atoi(token);

        token = strtok(NULL, ";");
        strcpy(novoFuncionario->empresa, token);

        token = strtok(NULL, ";");
        strcpy(novoFuncionario->departamento, token);

        token = strtok(NULL, ";");
        novoFuncionario->salario = atof(token);

        novoFuncionario->esquerda = NULL;
        novoFuncionario->direita = NULL;

        raiz = inserirFuncionario(raiz, novoFuncionario);
    }

    fclose(arquivo);
    return raiz;
}

typedef struct Funcionario {
    int codigo;
    char nome[50];
    int idade;
    char empresa[50];
    char departamento[50];
    float salario;
    struct Funcionario* esquerda;
    struct Funcionario* direita;
} Funcionario;

Funcionario* criarFuncionario(int codigo, const char* nome, int idade, const char* empresa, const char* departamento, float salario) {
    Funcionario* novoFuncionario = (Funcionario*)malloc(sizeof(Funcionario));
    novoFuncionario->codigo = codigo;
    strcpy(novoFuncionario->nome, nome);
    novoFuncionario->idade = idade;
    strcpy(novoFuncionario->empresa, empresa);
    strcpy(novoFuncionario->departamento, departamento);
    novoFuncionario->salario = salario;
    novoFuncionario->esquerda = NULL;
    novoFuncionario->direita = NULL;
    return novoFuncionario;
}

Funcionario* inserirFuncionario(Funcionario* raiz, Funcionario* novoFuncionario) {
    if (raiz == NULL) {
        return novoFuncionario;
    }

    if (novoFuncionario->codigo < raiz->codigo) {
        raiz->esquerda = inserirFuncionario(raiz->esquerda, novoFuncionario);
    } else {
        raiz->direita = inserirFuncionario(raiz->direita, novoFuncionario);
    }

    return raiz;
}
void salvarCSV(int* vetor, int tamanho, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d;", vetor[i]);
    }

    fclose(arquivo);
}



void radixSort_lsd(int* vetor, int n) {
    int i;
    int max = vetor[0];

    for (i = 1; i < n; i++) {
        if (vetor[i] > max) {
            max = vetor[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[n];
        int count[10] = {0};

        for (i = 0; i < n; i++) {
            count[(vetor[i] / exp) % 10]++;
        }

        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (i = n - 1; i >= 0; i--) {
            output[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
            count[(vetor[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++) {
            vetor[i] = output[i];
        }
    }
}

void enviarOrdenado(Funcionario *funcionarios, int n){
    FILE *arq;
    arq = fopen("ordenado.csv", "w");
    if(arq == NULL){
        printf("Erro ao criar o arquivo\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char funcStr[250];
        sprintf(funcStr, "%d;%s;%d;%s;%s;%f\n", funcionarios[i].codigo, funcionarios[i].nome,funcionarios[i].idade, funcionarios[i].empresa, funcionarios[i].departamento, funcionarios[i].salario);
        fprintf(arq, funcStr);
    }

    fclose(arq);
}

