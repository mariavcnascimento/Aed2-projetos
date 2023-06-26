#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "arv_avl.h"

/*typedef struct estatisticas {
    // 1 - operações 
    int qtdBuscas;
    int qtdInsercoes;
    int qtdRemocoes;
    // 2 - comparações por operação
    int compBuscas;
    int compInsercoes;
    int compRemocoes;
    // 3 - manipulacoes (rotacoes)
    int rotEsquerdaInsercao;
    int rotDireitaInsercao;
    int rotEsquerdaRemocao;
    int rotDireitaRemocao;
    //3.1 rotacoes 2 
    int rotEsquerda;
    int rotDireita;
    int rotTotais;
} stats; */

typedef struct no TNo;
struct no{
    int altura;
    void* info;
    TNo* sae;
    TNo* sad;
    TNo* ancestral;
};

TNo* criar_no(TNo* ascentral, void* info){
    TNo* novo = malloc(sizeof(TNo));
    novo->info = info;
    novo->sae = NULL;
    novo->sad = NULL;
    novo->ancestral = ascentral;
    novo -> altura = 0;
    return novo;
}

typedef void(*TImprimirAVL)(void* info);
typedef int(*TCompararAVL)(void* s1, void* s2);
typedef struct avl{
    TNo* raiz;
    TImprimirAVL imprimir;
    TCompararAVL comparar;

     // 1 - operações 
    int qtdBuscas;
    int qtdInsercoes;
    int qtdRemocoes;
    // 2 - comparações por operação
    int compBuscas;
    int compInsercoes;
    int compRemocoes;
    // 3 - manipulacoes (rotacoes)
    int rotInsercao;
    //int rotDireitaInsercao;
    //int rotEsquerdaRemocao;
    int rotRemocao;
    //3.1 rotacoes 2 
    int rotEsquerda;
    int rotDireita;
    int rotTotais;

    
} t_avl;

t_avl* criarAVL(TImprimirAVL imprimir, TCompararAVL comparar){
    t_avl* abb = malloc(sizeof(t_avl));

    abb->raiz = NULL;
    abb->imprimir = imprimir;
    abb->comparar = comparar;
    abb->rotEsquerda = 0;
    abb->rotDireita = 0;
    abb->rotTotais = 0;
    //1 
    abb->qtdBuscas = 0;
    abb->qtdInsercoes = 0;
    abb->qtdRemocoes = 0;
    //2
    abb->compBuscas = 0;
    abb->compInsercoes =0;
    abb->compRemocoes =0;
    //3
    abb->rotInsercao = 0;
    //abb->rotDireitaInsercao = 0;
    //abb->rotEsquerdaRemocao = 0;
    abb->rotRemocao = 0;
    
    return abb;
}

// FUNÇÕES ESPECÍFICAS PARA A AVL

int alturaDoNo(TNo* no){ // altura do nó
    if(no == NULL){
        return -1;
    } else {
        return no -> altura;
    }
}

int fatorDeBalanceamento(TNo* no){
    if(no){
        return (alturaDoNo(no -> sae) - alturaDoNo(no -> sad));
    }
    return 0;
}

TNo* rotacaoEsquerda(TNo *r, t_avl* abb){
    TNo *y, *f;

    y = r->sad;
    f = y->sae;

    y->sae = r;
    r->sad = f;

    r->altura = MAX(alturaDoNo(r->sae), alturaDoNo(r->sad)) + 1;
    y->altura = MAX(alturaDoNo(y->sae), alturaDoNo(y->sad)) + 1;

    abb -> rotEsquerda += 1;
    abb -> rotTotais += 1;
    return y;
}

TNo* rotacaoDireita(TNo *r, t_avl* abb){
    TNo *y, *f;

    y = r->sae;
    f = y->sad;

    y->sad = r;
    r->sae = f;

    r->altura = MAX(alturaDoNo(r->sae), alturaDoNo(r->sad)) + 1;
    y->altura = MAX(alturaDoNo(y->sae), alturaDoNo(y->sad)) + 1;

    abb -> rotDireita += 1;
    abb -> rotTotais += 1;
    return y;
}

TNo* rotacaoEsquerdaDireita(TNo *r, t_avl* abb){
    r->sae = rotacaoEsquerda(r->sae,abb);
    return rotacaoDireita(r,abb);
}

TNo* rotacaoDireitaEsquerda(TNo *r, t_avl* abb){
    r->sad = rotacaoDireita(r->sad,abb);
    return rotacaoEsquerda(r,abb);
}

TNo* balancear(TNo *raiz, t_avl* abb, int chave){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->sad) <= 0){
        raiz = rotacaoEsquerda(raiz,abb);
        if(chave == 1){
            abb -> rotInsercao += 1;
        } else {
            abb -> rotRemocao += 1;
        }   
    }    
    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->sae) >= 0){
        raiz = rotacaoDireita(raiz,abb);
        if(chave == 1){
            abb -> rotInsercao += 1;
        } else {
            abb -> rotRemocao += 1;
        }
    }    
    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->sae) < 0){
        raiz = rotacaoEsquerdaDireita(raiz, abb);
        if(chave == 1){
            abb -> rotInsercao += 2;
        } else {
            abb -> rotRemocao += 2;
        }
    }
    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->sad) > 0){
        raiz = rotacaoDireitaEsquerda(raiz, abb);
        if(chave == 1){
            abb -> rotInsercao += 2;
        } else {
            abb -> rotRemocao += 2;
        }
    }
   
    return raiz;
}

static void conectaRaizSAE(TNo *raiz, TNo* sae){
    raiz->sae = sae;
    sae->ancestral = raiz;
}

static void conectaRaizSAD(TNo *raiz, TNo* sad){
    raiz->sad = sad;
    sad->ancestral = raiz;
}

static TNo* __inserirAVL(TNo* raiz, void* info, TCompararAVL comparar, t_avl* abb){
    //printf("Iniciou insercao \n");
    if (raiz == NULL){
        //printf("Inseriu no \n");
        TNo* novo = criar_no(raiz,info);
        //printf("Insercao raiz\n");
        abb ->compInsercoes += 1;
        
        return novo;
    }
    if (comparar(raiz->info, info) > 0){ // uso da propriedade ordem
        abb -> compInsercoes += 1;
        TNo* sae = __inserirAVL(raiz->sae, info, comparar,abb);
        conectaRaizSAE(raiz, sae);
    }else{
        abb -> compInsercoes += 1;
        TNo* sad = __inserirAVL(raiz->sad, info, comparar,abb);
        conectaRaizSAD(raiz, sad);
    }

    raiz->altura = MAX(alturaDoNo(raiz->sae), alturaDoNo(raiz->sad)) + 1;

    raiz = balancear(raiz,abb, 1);
    //printf("Insercao feita\n");
    return raiz;
}

void inserirAVL(t_avl *abb, void* info){

    abb->raiz = __inserirAVL(abb->raiz, info, abb->comparar,abb);
    abb -> qtdInsercoes += 1;
    //printf("Terminou insercao\n");

}

TNo* __buscarAVL(TNo* raiz, void* buscado, TCompararAVL comparar, t_avl* abb){
    // base da recursão
    if (raiz == NULL){
        abb -> compBuscas += 1;
        return NULL;
    }
    int status = comparar(raiz->info, buscado);
    //abb -> compBuscas += 1;
    if (status == 0){
        abb -> compBuscas += 1;
        return raiz;
    }else if(status < 0){
        abb -> compBuscas += 1;
        return __buscarAVL(raiz->sad, buscado, comparar,abb); 
    }else{
        abb -> compBuscas += 1;
        return __buscarAVL(raiz->sae, buscado, comparar,abb); 
    }

}

void* buscarAVL(t_avl *abb, void* buscado){
    TNo* no = __buscarAVL(abb->raiz, buscado, abb->comparar,abb);
    abb -> qtdBuscas += 1;
    return (no != NULL?no->info:NULL);

}

static void trocar(TNo* no, TNo* no2){
    void* aux = no->info;
    no->info = no2->info;
    no2->info = aux;
}

 TNo * __removerAVL(TNo* raiz, void* removivel, TCompararAVL comparar, t_avl* abb){
    if (raiz == NULL){ // valor não encontrado 
        abb -> compRemocoes += 1;
        return NULL;
    }else if (comparar(raiz->info, removivel)>0){ // caminha para a SAE
        abb -> compRemocoes += 1;
        raiz->sae = __removerAVL(raiz->sae, removivel, comparar, abb);
        return raiz;
    }else if (comparar(raiz->info, removivel)<0){ // caminha para a SAD
        abb -> compRemocoes += 1;
        raiz->sad = __removerAVL(raiz->sad, removivel, comparar,abb);
        return raiz;
    }else{ // achou
        if ( (raiz->sae == NULL) &&  (raiz->sad == NULL) ){ // remoção de folhas
            abb -> compRemocoes += 1;
            /*abb -> rotEsquerda += 1;
            abb -> rotTotais += 1;
            abb -> rotRemocao += 1;*/
            free(raiz->info);
            free(raiz);
            balancear(raiz, abb, 0);
            return NULL;
        }else if (raiz->sae == NULL){ // 1 elemento (direito)
            raiz->sad->ancestral = raiz->ancestral;
            TNo* sad = raiz->sad;
            free(raiz->info);
            free(raiz);
            abb -> compRemocoes += 1;
            balancear(raiz, abb, 0);
            return sad;

        }else if (raiz->sad == NULL){ // 1 elemento (esquerdo)
            raiz->sae->ancestral = raiz->ancestral;
            TNo* sae = raiz->sae;
            free(raiz->info);
            free(raiz);
            abb -> compRemocoes += 1;
            balancear(raiz, abb, 0);
            return sae;
        }else{ // Dois descendentes
            TNo* maior = raiz->sae;
            while(maior->sad!=NULL){
                maior = maior->sad;
            }
            trocar(raiz, maior);
            raiz->sae = __removerAVL(raiz->sae, removivel, comparar,abb);
            balancear(raiz, abb, 0);
            return raiz;
        }
        
        raiz -> altura = MAX(alturaDoNo(raiz->sae), alturaDoNo(raiz->sad)) + 1;
        return raiz; 
    }
 }

void removerAVL(t_avl *abb, void* removivel){
   abb->raiz = __removerAVL(abb->raiz, removivel, abb->comparar,abb);   
   abb -> qtdRemocoes += 1; 
}

#define MAX(a,b) (a>b?a:b)

static int __alturaAVL(TNo *raiz){
    if (raiz == NULL)
        return -1;
    return MAX(__alturaAVL(raiz->sae), __alturaAVL(raiz->sad))+1;
}

int alturaAVL(t_avl *abb){
    return __alturaAVL(abb->raiz);
}

static int __tamanhoAVL(TNo* raiz){
    if (raiz == NULL)
        return 0;
    return (__tamanhoAVL(raiz->sae)+__tamanhoAVL(raiz->sad))+1;
}

int tamanhoAVL(t_avl *abb){
    return __tamanhoAVL(abb->raiz);

}

static void __imprimirAVL(TNo* raiz, TImprimirAVL imprimir){
    if (raiz == NULL)
        return;

    __imprimirAVL(raiz->sae, imprimir);
    imprimir(raiz->info);
    __imprimirAVL(raiz->sad, imprimir);
}

void imprimirAVL(t_avl* abb){
    __imprimirAVL(abb->raiz, abb->imprimir);
}

void estatisticaAVL(t_avl* abb){
    printf("ESTATISTICAS ARVORE AVL\n");
    printf("1) Numero de operacoes\nBuscas: %d\nInsercoes: %d\nRemocoes: %d\n", abb ->qtdBuscas, abb->qtdInsercoes, abb -> qtdRemocoes);
    printf("2) Numero de comparacoes\nComparacoes em Buscas: %d\nComparacoes em Insercoes: %d\nComparacoes em Remocoes: %d\n", abb->compBuscas, abb->compInsercoes, abb->compRemocoes);
    printf("3) Numero de manipulacoes - rotacoes\nRotacoes em insercoes: %d\nRotacoes em remocoes: %d\n", abb->rotInsercao, abb->rotRemocao);
    printf("Rotacoes totais a esquerda: %d\nRotacoes totais a direita: %d\nRotacoes totais: %d\n", abb->rotEsquerda, abb->rotDireita, abb->rotTotais);
    printf("-----------------------------------------\n\n");
}
