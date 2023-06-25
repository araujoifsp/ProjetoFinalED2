#define apagaTela system("cls")
#define pula2Linhas printf("\n\n")
#define pula1Linha printf("\n")
#define pausaTela system("pause")
#define decoracao printf("===================================")

typedef struct NO *arvAVL;

typedef struct NO *arvoreLLRB;

typedef struct FUNC {
    int codigo;
    char nome[50];
    int idade;
    char empresa[50];
    char departamento[50];
    float sal;
}Funcionarios;

void menu();

int resp_menu();

void sub_menu();

int resp_sub_menu();

int opcao_ecolhida(int options2);

int criaVetor(int *vetor, int tamanho);

void preencheVetor(int *vetor, int tamanho);

void salvarCSV(int* vetor, int tamanho, const char* nomeArquivo);

void radixSort_lsd(int arr[], int n);

void lerCSV(arvoreLLRB *raiz);

void exportToCSV(Funcionarios arr[], int n);

int cor(struct NO *H);
void trocaCor(struct NO *H);
void insere_arvoreLLRB(arvoreLLRB *raiz, Funcionarios vetorFuncionarios[], int tamanho);
void insere_arvoreLLRB(arvoreLLRB *raiz, Funcionarios vetorFuncionarios[], int tamanho);
int remove_arvoreLLRB(arvoreLLRB *raiz, int valor);
void liberar_arvBin(arvoreLLRB *raiz);
void libera_NO(struct NO *no);
int vazia_arvBin(arvoreLLRB *raiz);
arvoreLLRB *cria_arvBin();
void lerCSVOrdenado(arvoreLLRB *raiz);


//enviarOrdenado(FUNC *Funcionario, int n);


