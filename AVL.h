typedef struct NO *arvAVL;

//codigo avl
int alt_no(struct NO *no);
int fatorBalanceamento_NO(struct NO *no);
int maior(int x, int y);

void rotacaoLL(arvAVL *raiz);
void rotacaoRR(arvAVL *raiz);
void rotacaoLR(arvAVL *raiz);
void rotacaoRL(arvAVL *raiz);

// fim cod avl aula 1
int insere_arvAVL(arvAVL *raiz, int valor);
int remove_arvAVL(arvAVL *raiz, int valor);
// fim


arvAVL *cria_arvBin();

void liberar_arvBin(arvAVL *raiz);

int vazia_arvBin(arvAVL *raiz);

int altura_arvBin(arvAVL *raiz);

int totalNO_arvBin(arvAVL *raiz);

void preOrdem_arvBin(arvAVL *raiz);

void emOrdem_arvBin(arvAVL *raiz);

void posOrdem_arvBin(arvAVL *raiz);

int consulta_arvBin(arvAVL *raiz, int valor);

