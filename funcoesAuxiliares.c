
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesAuxiliares.h"
#include "desempenho.h"
#include "arvore.h"

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

typedef struct FUNC {
    int codigo;
    char nome[50];
    int idade;
    char empresa[50];
    char departamento[50];
    float sal;
}Funcionarios;
/*

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
}*/
/*
void enviarOrdenado(Funcionario *funcionario, int n){
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
*/

void imprimirFuncionario(Funcionarios* func) {
    printf("Código: %d\n", func->codigo);
    printf("Nome: %s\n", func->nome);
    printf("Idade: %d\n", func->idade);
    printf("Empresa: %s\n", func->empresa);
    printf("Departamento: %s\n", func->departamento);
    printf("Salário: %.2f\n", func->sal);
    printf("\n");
}


void lerCSV() {
    FILE *f;
    char linha[200];  // Tamanho máximo de uma linha no f CSV

    // Abre o f CSV em modo de leitura
    f = fopen("massaDados.csv", "r");

    if (f == NULL) {
        printf("Erro ao abrir o f.\n");
        return;
    }

    //Lê cada linha do f e imprime na tela
    while (fgets(linha, 300, f)) {
        Funcionarios func;
        char *texto = linha;
        func.codigo = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.departamento, strtok(NULL, ";"));
        func.sal = atof(strtok(NULL, ";"));
        imprimirFuncionario(&func);
        // Processar os dados do funcionário conforme necessário
    }

    rewind(f);  // Volta ao início do arquivo para ler novamente

      // Tamanho máximo de uma linha no segundo loop


    // Fecha o f
    fclose(f);
}
