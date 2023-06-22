typedef struct NO *arvoreLLRB;

//codigo rubro negra
int insere_arvoreLLRB(arvoreLLRB *raiz, int valor);

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor);

// fim



//codigo avl
int alt_no(struct NO *no);
int fatorBalanceamento_NO(struct NO *no);
int maior(int x, int y);

void rotacaoLL(arvoreLLRB *raiz);
void rotacaoRR(arvoreLLRB *raiz);
void rotacaoLR(arvoreLLRB *raiz);
void rotacaoRL(arvoreLLRB *raiz);

// fim cod avl aula 1
int insere_arvAVL(arvoreLLRB *raiz, int valor);
int remove_arvAVL(arvoreLLRB *raiz, int valor);
// fim




arvoreLLRB *cria_arvBin();

void liberar_arvBin(arvoreLLRB *raiz);

int vazia_arvBin(arvoreLLRB *raiz);

int altura_arvBin(arvoreLLRB *raiz);

int totalNO_arvBin(arvoreLLRB *raiz);

void preOrdem_arvBin(arvoreLLRB *raiz);

void emOrdem_arvBin(arvoreLLRB *raiz);

void posOrdem_arvBin(arvoreLLRB *raiz);

int consulta_arvBin(arvoreLLRB *raiz, int valor);

