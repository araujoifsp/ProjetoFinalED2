#define apagaTela system("cls")
#define pula2Linhas printf("\n\n")
#define pula1Linha printf("\n")
#define pausaTela system("pause")
#define decoracao printf("===================================")

typedef struct NO *arvAVL;

typedef struct NO *arvoreLLRB;

void menu();

int resp_menu();

void sub_menu();

int resp_sub_menu();

int opcao_ecolhida(int options2);

int criaVetor(int *vetor, int tamanho);

void preencheVetor(int *vetor, int tamanho);

