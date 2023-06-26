#define MAX(a,b) (a>b?a:b)

//Estruturas
typedef struct avl t_avl;
typedef struct no TNo;

// Funções genéricas
typedef void(*TImprimirAVL)(void* info);
typedef int(*TCompararAVL)(void* s1, void* s2);

//Funções da estrutura
TNo* criar_no(TNo* ascentral, void* info);
t_avl* criarAVL(TImprimirAVL imprimir, TCompararAVL comparar);
int alturaNo(TNo* no);
int fatorBalanceamento(TNo* no);
TNo* rotacaoEsquerda(TNo *r,t_avl* abb);
TNo* rotacaoDireita(TNo *r,t_avl* abb);
TNo* rotacaoEsquerdaDireita(TNo *r,t_avl* abb);
TNo* rotacaoDireitaEsquerda(TNo *r,t_avl* abb);
TNo* balancear(TNo *raiz,t_avl* abb, int chave);
static void conectaRaizSAE(TNo *raiz, TNo* sae);
static void conectaRaizSAD(TNo *raiz, TNo* sad);

// Operações ABB 
static TNo* __inserirAVL(TNo* raiz, void* info, TCompararAVL comparar,t_avl* abb);
void inserirAVL(t_avl *abb, void* info);

TNo* __buscarAVL(TNo* raiz, void* buscado, TCompararAVL comparar,t_avl* abb);
void* buscarAVL(t_avl *abb, void* buscado);

static void trocar(TNo* no, TNo* no2);

TNo * __removerAVL(TNo* raiz, void* removivel, TCompararAVL comparar, t_avl* abb);
void removerAVL(t_avl *abb, void* removivel);

static void __podarABB(TNo* raiz);
void podarABB(t_avl* abb, void* info);

static int __alturaAVL(TNo *raiz);
int alturaAVL(t_avl *abb);
static int __tamanhoAVL(TNo* raiz);
int tamanhoAVL(t_avl *abb);
static void __imprimirAVL(TNo* raiz, TImprimirAVL imprimir);
void imprimirAVL(t_avl* abb);

void estatisticaAVL(t_avl* abb);