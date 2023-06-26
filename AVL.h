typedef struct NO *arvoreAVL;

typedef struct NO {
    int info;
    struct NoAVL* esq;
    struct NoAVL* dir;
    int altura;
} NOAVL;

arvoreAVL* criar_arvAVL();
int altura_arvAVL(arvoreAVL* raiz);
int insere_arvAVL(arvoreAVL* raiz, int valor);
int removearvAVL(arvoreAVL *raiz, int valor);

void rotacaoLL(arvoreAVL* raiz);
void rotacaoRR(arvoreAVL* raiz);
void rotacaoLR(arvoreAVL* raiz);
void rotacaoRL(arvoreAVL* raiz);


void liberar_arvBin(arvoreAVL *raiz);
int consulta_arvBin(arvoreAVL* raiz, int valor);
int busca_arvAVL(arvoreAVL* raiz, int codigo);




