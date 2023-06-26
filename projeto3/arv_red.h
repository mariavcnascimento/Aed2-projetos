
#define MAX(a,b) (a>b?a:b)
typedef struct no TNo;

TNo* criar_no(TNo* ancestral, void* info);

typedef void(*TImprimirABB)(void* info);
typedef int(*TCompararABB)(void* s1, void* s2);

typedef struct t_abb TABB;

TABB* criarABB(TImprimirABB imprimir, TCompararABB comparar);

void rotacaoEsquerda(TABB* abb, TNo* no);

void rotacaoDireita(TABB* abb, TNo* no);

void ajustarInsercao(TABB* abb, TNo* no);

int inserirABB(TABB* abb, void* info);

void ajustarRemocao(TABB* abb, TNo* no);
TNo* obterSucessor(TNo* no);

void balancearRemocao(TABB* abb, TNo* no);

/* TNo* removerABB(TABB* abb, void* info) {
    TNo* no = abb->raiz;
    TNo* pai = NULL;
    TNo* atual = NULL;

    if(no == NULL){
        return NULL;
    }
    if (abb->comparar(info, no->info) == 0) {
        atual = no;
    }
    pai = no;
    if (abb->comparar(info, no->info) < 0) {
        no = no->sae;
        abb->compRemocoes++;
    } else {
        no = no->sad;
        abb->compRemocoes++;
    }
 
    if (atual == NULL)
        return NULL;

    TNo* sucessor = NULL;
    TNo* noFilho = NULL;

    if (atual->sae == NULL || atual->sad == NULL)
        sucessor = atual;
    else
        sucessor = obterSucessor(atual); //pega a sae como sucessor

    if (sucessor->sae != NULL)
        noFilho = sucessor->sae;
    else
        noFilho = sucessor->sad;

    if (noFilho != NULL)
        noFilho->ancestral = sucessor->ancestral;

    if (sucessor->ancestral == NULL)
        abb->raiz = noFilho;
    else if (sucessor == sucessor->ancestral->sae)
        sucessor->ancestral->sae = noFilho;
    else
        sucessor->ancestral->sad = noFilho;

    if (sucessor != atual) {
        atual->info = sucessor->info;
    }

    if (sucessor->cor == 0)
        balancearRemocao(abb, noFilho);

    free(sucessor);
    abb->qtdRemocoes++;
    return no;
}
 */

static void trocar(TNo* no, TNo* no2);

TNo * __removerABB(TNo* raiz, void* removivel, TCompararABB comparar, TABB* abb);
void removerABB(TABB *abb, void* removivel);

TNo* __buscarABB(TNo* raiz, void* buscado, TCompararABB comparar, TABB* abb);

void* buscarABB(TABB *abb, void* buscado);
static int __alturaABB(TNo *raiz);
int alturaABB(TABB *abb);
static int __tamanhoABB(TNo* raiz);
int tamanhoABB(TABB *abb);
void estatisticaRED(TABB* abb);
void imprimirArvoreRubroNegraAux(TNo* no, int nivel);
void imprimirArvoreRubroNegra(TABB* abb);

