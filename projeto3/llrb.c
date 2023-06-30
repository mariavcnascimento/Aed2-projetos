#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef void(*t_imprimir_red)(void* info);
typedef int(*t_comparar_red)(void* s1, void* s2);


typedef struct no TNo;
struct no{
    void* info;
    TNo* sae;
    TNo* sad;
    TNo* ancestral;
    int cor;
};

TNo* criar_no(TNo* ancestral, void* info){
    TNo* novo = malloc(sizeof(TNo));
    novo->info = info;
    novo->sae = NULL;
    novo->sad = NULL;
    novo->ancestral = ancestral;
    novo->cor = 1; // novo nó sempre será vermelho
    return novo;
}

typedef struct t_red{
    TNo* raiz;
    t_imprimir_red imprimir;
    t_comparar_red comparar;

    // Estatísticas
    int qtdBuscas;
    int qtdInsercoes;
    int qtdRemocoes;
    int compBuscas;
    int compInsercoes;
    int compRemocoes;
    int rotInsercao;
    int rotRemocao;
    int rotsae;
    int rotsad;
    int rotTotais;
} t_red;

t_red* criarred(t_imprimir_red imprimir, t_comparar_red comparar){
    t_red* red = malloc(sizeof(t_red));

    red->raiz = NULL;
    red->imprimir = imprimir;
    red->comparar = comparar;

    red->rotsae = 0;
    red->rotsad = 0;
    red->rotTotais = 0;

    red->qtdBuscas = 0;
    red->qtdInsercoes = 0;
    red->qtdRemocoes = 0;

    red->compBuscas = 0;
    red->compInsercoes = 0;
    red->compRemocoes = 0;

    red->rotInsercao = 0;
    red->rotRemocao = 0;

    return red;
}

//implementação de acordo com o artigo
TNo* rotacaoEsq(TNo* no){
    TNo* x;
    x = no->sad;
    no->sad = x->sae;
    x->sae = no;
    x->cor = no->cor;
    no->cor = 1;

    return x;
}

TNo* rotacaoDir(TNo* no){
    TNo* x;
    x = no->sae;
    no->sae = no-> sad;
    x->sad = no;
    x->cor = no->cor;
    no->cor = 1;
    return x;
}

void trocarCor(TNo* no){
    no->cor = !no->cor;
    no->sae->cor = !no->sae->cor;
    no->sad->cor = !no->sad->cor;
}

void* __buscar(TNo* no ,void* chave){
    while (no != NULL)
    {
        int cmp = compara(no->info,chave);
        if(cmp == 0) return no->info;
        else if (cmp<0) return buscar(no->sad, chave);
        else if(cmp>0) return buscar(no->sae,chave);
    }
    return NULL;
}

void* buscar(t_red* red, void* chave){
    TNo* raiz = red->raiz;
    return __buscar(raiz,chave);
}

TNo* __inserirRed(TNo* no, void* info){
    if(no == NULL) return criar_no(NULL, info);
    int corEsq = no->sae->cor;
    int corDir = no->sad->cor;
    if(corEsq == 1 && corDir == 1) trocarCor(no);

    int cmp = compara(no->info,info);
    if(cmp == 0){
        return no;//já existe na árvore
    }
    else if (cmp<0) return __inserirRed(no->sad, info);
    else if(cmp>0) return __inserirRed(no->sae,info);

    int corEsq = no->sae->cor;
    int corDir = no->sad->cor;

    if(corDir == 1 && corEsq == 0){
        no = rotacaoEsq(no);
    }

    if(corEsq == 1 && no->sae->sae->cor == 1){
        no = rotacaoDir(no);
    }

    return no;
}

void inserirRed(t_red* red, void* info){
    TNo* raiz = red->raiz;
    raiz = __inserirRed(raiz, info);
    raiz->cor = 0; // a raiz é sempre preta
}


