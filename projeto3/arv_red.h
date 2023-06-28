
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
static void __imprimirRED(TNo* raiz, TImprimirABB imprimir);

void imprimirRED(TABB* abb);


