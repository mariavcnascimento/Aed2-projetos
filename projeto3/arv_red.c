#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX(a,b) (a>b?a:b)


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

typedef void(*TImprimirABB)(void* info);
typedef int(*TCompararABB)(void* s1, void* s2);

typedef struct t_abb{
    TNo* raiz;
    TImprimirABB imprimir;
    TCompararABB comparar;

    // Estatísticas
    int qtdBuscas;
    int qtdInsercoes;
    int qtdRemocoes;
    int compBuscas;
    int compInsercoes;
    int compRemocoes;
    int rotInsercao;
    int rotRemocao;
    int rotEsquerda;
    int rotDireita;
    int rotTotais;
} TABB;

TABB* criarABB(TImprimirABB imprimir, TCompararABB comparar){
    TABB* abb = malloc(sizeof(TABB));

    abb->raiz = NULL;
    abb->imprimir = imprimir;
    abb->comparar = comparar;

    abb->rotEsquerda = 0;
    abb->rotDireita = 0;
    abb->rotTotais = 0;

    abb->qtdBuscas = 0;
    abb->qtdInsercoes = 0;
    abb->qtdRemocoes = 0;

    abb->compBuscas = 0;
    abb->compInsercoes = 0;
    abb->compRemocoes = 0;

    abb->rotInsercao = 0;
    abb->rotRemocao = 0;

    return abb;
}

void rotacaoEsquerda(TABB* abb, TNo* no){
    TNo* filhoDireita = no->sad;
    no->sad = filhoDireita->sae;
    if (no->sad != NULL)
        no->sad->ancestral = no;
    filhoDireita->ancestral = no->ancestral;
    if (no->ancestral == NULL)
        abb->raiz = filhoDireita;
    else if (no == no->ancestral->sae)
        no->ancestral->sae = filhoDireita;
    else
        no->ancestral->sad = filhoDireita;
    filhoDireita->sae = no;
    no->ancestral = filhoDireita;

    abb->rotTotais++;
    abb->rotEsquerda++;
}

void rotacaoDireita(TABB* abb, TNo* no){
    TNo* filhoEsquerda = no->sae;
    no->sae = filhoEsquerda->sad;
    if (no->sae != NULL)
        no->sae->ancestral = no;
    filhoEsquerda->ancestral = no->ancestral;
    if (no->ancestral == NULL)
        abb->raiz = filhoEsquerda;
    else if (no == no->ancestral->sae)
        no->ancestral->sae = filhoEsquerda;
    else
        no->ancestral->sad = filhoEsquerda;
    filhoEsquerda->sad = no;
    no->ancestral = filhoEsquerda;

    abb->rotTotais++;
    abb->rotDireita++;
}

void ajustarInsercao(TABB* abb, TNo* no){
    while (no->ancestral != NULL && no->ancestral->cor == 1) {
        if (no->ancestral == no->ancestral->ancestral->sae) {
            TNo* tio = no->ancestral->ancestral->sad;
            if (tio != NULL && tio->cor == 1) {
                no->ancestral->cor = 0;
                tio->cor = 0;
                no->ancestral->ancestral->cor = 1;
                no = no->ancestral->ancestral;
                abb->rotInsercao++;
            } else {
                if (no == no->ancestral->sad) {
                    no = no->ancestral;
                    rotacaoEsquerda(abb, no);
                    abb->rotInsercao++;
                }
                no->ancestral->cor = 0;
                no->ancestral->ancestral->cor = 1;
                rotacaoDireita(abb, no->ancestral->ancestral);
                abb->rotInsercao++;
            }
        } else {
            TNo* tio = no->ancestral->ancestral->sae;
            if (tio != NULL && tio->cor == 1) {
                no->ancestral->cor = 0;
                tio->cor = 0;
                no->ancestral->ancestral->cor = 1;
                no = no->ancestral->ancestral;
                //abb->rotInsercao++;
            } else {
                if (no == no->ancestral->sae) {
                    no = no->ancestral;
                    rotacaoDireita(abb, no);
                }
                no->ancestral->cor = 0;
                no->ancestral->ancestral->cor = 1;
                rotacaoEsquerda(abb, no->ancestral->ancestral);
                abb->rotInsercao++;
            }
        }
    }
    abb->raiz->cor = 0;
}

int inserirABB(TABB* abb, void* info){
    TNo* no = criar_no(NULL, info);
    TNo* atual = abb->raiz;
    TNo* anterior = NULL;
    int cmp = 0;

    abb->qtdInsercoes++;

    while (atual != NULL) {
        cmp = abb->comparar(info, atual->info);
        anterior = atual;
        if (cmp < 0) {
            atual = atual->sae;
            abb->compInsercoes++;
        } else if (cmp > 0) {
            atual = atual->sad;
            abb->compInsercoes++;
        } else {
            free(no);
            return 0; // valor já existe na árvore
        }
    }

    no->ancestral = anterior;
    if (anterior == NULL)
        abb->raiz = no;
    else if (cmp < 0)
        anterior->sae = no;
    else
        anterior->sad = no;

    ajustarInsercao(abb, no);

    return 1;
}

void ajustarRemocao(TABB* abb, TNo* no){
    while (no != abb->raiz && no->cor == 0) {
        if (no == no->ancestral->sae) {
            TNo* irmao = no->ancestral->sad;
            if (irmao->cor == 1) {
                irmao->cor = 0;
                no->ancestral->cor = 1;
                rotacaoEsquerda(abb, no->ancestral);
                irmao = no->ancestral->sad;
                abb->rotRemocao++;
            }
            if (irmao->sae->cor == 0 && irmao->sad->cor == 0) {
                irmao->cor = 1;
                no = no->ancestral;
                //abb->rotRemocao++;
            } else {
                if (irmao->sad->cor == 0) {
                    irmao->sae->cor = 0;
                    irmao->cor = 1;
                    rotacaoDireita(abb, irmao);
                    irmao = no->ancestral->sad;
                    abb->rotRemocao++;
                }
                irmao->cor = no->ancestral->cor;
                no->ancestral->cor = 0;
                irmao->sad->cor = 0;
                rotacaoEsquerda(abb, no->ancestral);
                no = abb->raiz;
                abb->rotRemocao++;
            }
        } else {
            TNo* irmao = no->ancestral->sae;
            if (irmao->cor == 1) {
                irmao->cor = 0;
                no->ancestral->cor = 1;
                rotacaoDireita(abb, no->ancestral);
                irmao = no->ancestral->sae;
                abb->rotRemocao++;
            }
            if (irmao->sad->cor == 0 && irmao->sae->cor == 0) {
                irmao->cor = 1;
                no = no->ancestral;
                //abb->rotRemocao++;
            } else {
                if (irmao->sae->cor == 0) {
                    irmao->sad->cor = 0;
                    irmao->cor = 1;
                    rotacaoEsquerda(abb, irmao);
                    irmao = no->ancestral->sae;
                    abb->rotRemocao++;
                }
                irmao->cor = no->ancestral->cor;
                no->ancestral->cor = 0;
                irmao->sae->cor = 0;
                rotacaoDireita(abb, no->ancestral);
                no = abb->raiz;
                abb->rotRemocao++;
            }
        }
    }
    no->cor = 0;
}

TNo* obterSucessor(TNo* no) {
    TNo* atual = no;
    while (atual->sae != NULL)
        atual = atual->sae;
    return atual;
}

void balancearRemocao(TABB* abb, TNo* no) {
    while (no != abb->raiz && (no == NULL || no->cor == 0)) {
        if (no == no->ancestral->sae) {
            TNo* irmao = no->ancestral->sad;
            if (irmao->cor == 1) {
                irmao->cor = 0;
                no->ancestral->cor = 1;
                rotacaoEsquerda(abb, no->ancestral);
                irmao = no->ancestral->sad;
                abb->rotTotais++;
                abb->rotEsquerda++;
            }

            if ((irmao->sae == NULL || irmao->sae->cor == 0) && (irmao->sad == NULL || irmao->sad->cor == 0)) {
                irmao->cor = 1;
                no = no->ancestral;
            } else {
                if (irmao->sad == NULL || irmao->sad->cor == 0) {
                    irmao->sae->cor = 0;
                    irmao->cor = 1;
                    rotacaoDireita(abb, irmao);
                    irmao = no->ancestral->sad;
                    abb->rotTotais++;
                    abb->rotDireita++;
                }

                irmao->cor = no->ancestral->cor;
                no->ancestral->cor = 0;
                irmao->sad->cor = 0;
                rotacaoEsquerda(abb, no->ancestral);
                no = abb->raiz;
                abb->rotTotais++;
                abb->rotEsquerda++;
            }
        } else {
            TNo* irmao = no->ancestral->sae;
            if (irmao->cor == 1) {
                irmao->cor = 0;
                no->ancestral->cor = 1;
                rotacaoDireita(abb, no->ancestral);
                irmao = no->ancestral->sae;
                abb->rotTotais++;
                abb->rotDireita++;
            }

            if ((irmao->sad == NULL || irmao->sad->cor == 0) && (irmao->sae == NULL || irmao->sae->cor == 0)) {
                irmao->cor = 1;
                no = no->ancestral;
            } else {
                if (irmao->sae == NULL || irmao->sae->cor == 0) {
                    irmao->sad->cor = 0;
                    irmao->cor = 1;
                    rotacaoEsquerda(abb, irmao);
                    irmao = no->ancestral->sae;
                    abb->rotTotais++;
                    abb->rotEsquerda++;
                }

                irmao->cor = no->ancestral->cor;
                no->ancestral->cor = 0;
                irmao->sae->cor = 0;
                rotacaoDireita(abb, no->ancestral);
                no = abb->raiz;
                abb->rotTotais++;
                abb->rotDireita++;
            }
        }
    }

    if (no != NULL)
        no->cor = 0;
}

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

static void trocar(TNo* no, TNo* no2){
    void* aux = no->info;
    no->info = no2->info;
    no2->info = aux;
}

TNo * __removerABB(TNo* raiz, void* removivel, TCompararABB comparar, TABB* abb){
    if (raiz == NULL){ // valor não encontrado 
        abb -> compRemocoes += 1;
        return NULL;
    }else if (comparar(raiz->info, removivel)>0){ // caminha para a SAE
        abb -> compRemocoes += 1;
        raiz->sae = __removerABB(raiz->sae, removivel, comparar,abb);
        return raiz;
    }else if (comparar(raiz->info, removivel)<0){ // caminha para a SAD
        abb -> compRemocoes += 1;
        raiz->sad = __removerABB(raiz->sad, removivel, comparar,abb);
        return raiz;
    }else{ // achou
        if ( (raiz->sae == NULL) &&  (raiz->sad == NULL) ){ // remoção de folhas
            if(raiz->cor == 0){
                abb -> compRemocoes += 1;
                free(raiz->info);
                free(raiz);
                ajustarRemocao(abb,raiz->ancestral);    
            }else{
                abb -> compRemocoes += 1;
                free(raiz->info);
                free(raiz);
            }
            return NULL;
        }else if (raiz->sae == NULL){ // 1 elemento (direito)
                raiz->sad->ancestral = raiz->ancestral;
                TNo* sad = raiz->sad;
            if(raiz->cor == 0){
                free(raiz->info);
                free(raiz);
                abb -> compRemocoes += 1;
                ajustarRemocao(abb,raiz->ancestral);
            }else{
                free(raiz->info);
                free(raiz);
                abb -> compRemocoes += 1;
            }
            return sad;

        }else if (raiz->sad == NULL){ // 1 elemento (esquerdo)
                raiz->sae->ancestral = raiz->ancestral;
                TNo* sae = raiz->sae;
            if(raiz->cor == 0){
                free(raiz->info);
                free(raiz);
                abb -> compRemocoes += 1;
                ajustarRemocao(abb,raiz->ancestral);
            }else{
                free(raiz->info);
                free(raiz);
                abb -> compRemocoes += 1;                
            }
            return sae;
        }else{ // Dois descendentes
            TNo* maior = raiz->sae;
            while(maior->sad!=NULL){
                maior = maior->sad;
            }
            trocar(raiz, maior);
            raiz->sae = __removerABB(raiz->sae, removivel, comparar,abb);
            if(raiz->cor == 0){
                ajustarRemocao(abb,raiz->ancestral);
            }
            return raiz;
        }
        return raiz; 
    }
}

void removerABB(TABB *abb, void* removivel){
   abb->raiz = __removerABB(abb->raiz, removivel, abb->comparar, abb);    
}

TNo* __buscarABB(TNo* raiz, void* buscado, TCompararABB comparar, TABB* abb){
    // base da recursão
    if (raiz == NULL){
        abb -> compBuscas += 1;
        return NULL;
    }
    int status = comparar(raiz->info, buscado);
    
    if (status == 0){
        abb -> compBuscas += 1;
        return raiz;
    }else if(status < 0){
        abb -> compBuscas += 1;
        return __buscarABB(raiz->sad, buscado, comparar,abb); 
    }else{
        abb -> compBuscas += 1;
        return __buscarABB(raiz->sae, buscado, comparar,abb); 
    }

}

void* buscarABB(TABB *abb, void* buscado){
    TNo* no = __buscarABB(abb->raiz, buscado, abb->comparar,abb);
    abb -> qtdBuscas += 1;
    return (no != NULL?no->info:NULL);

}


static int __alturaABB(TNo *raiz){
    if (raiz == NULL)
        return -1;
    return MAX(__alturaABB(raiz->sae), __alturaABB(raiz->sad))+1;
}

int alturaABB(TABB *abb){
    return __alturaABB(abb->raiz);
}

static int __tamanhoABB(TNo* raiz){
    if (raiz == NULL)
        return 0;
    return (__tamanhoABB(raiz->sae)+__tamanhoABB(raiz->sad))+1;
}

int tamanhoABB(TABB *abb){
    return __tamanhoABB(abb->raiz);

}

void estatisticaRED(TABB* abb){
    printf("ESTATISTICAS ARVORE Rubro-Negra\n");
    printf("1) Numero de operacoes\nBuscas: %d\nInsercoes: %d\nRemocoes: %d\n", abb ->qtdBuscas, abb->qtdInsercoes, abb -> qtdRemocoes);
    printf("2) Numero de comparacoes\nComparacoes em Buscas: %d\nComparacoes em Insercoes: %d\nComparacoes em Remocoes: %d\n", abb->compBuscas, abb->compInsercoes, abb->compRemocoes);
    printf("3) Numero de manipulacoes - rotacoes\nRotacoes em insercoes: %d\nRotacoes em remocoes: %d\n", abb->rotInsercao, abb->rotRemocao);
    printf("Rotacoes totais a esquerda: %d\nRotacoes totais a direita: %d\nRotacoes totais: %d\n", abb->rotEsquerda, abb->rotDireita, abb->rotTotais);
    printf("-----------------------------------------\n\n");
}

void imprimirArvoreRubroNegraAux(TNo* no, int nivel) {
    if (no == NULL) {
        printf("\n");
        return;
    }

    imprimirArvoreRubroNegraAux(no->sad, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    if (no->cor == 0) {
        printf("%d(B)\n", *(int*)no->info);
    } else {
        printf("%d(R)\n", *(int*)no->info);
    }

    imprimirArvoreRubroNegraAux(no->sae, nivel + 1);
}


void imprimirArvoreRubroNegra(TABB* abb) {
    imprimirArvoreRubroNegraAux(abb->raiz, 0);
}


/* void percorrerEmOrdem(TABB* abb, TNo* no){
    if (no != NULL) {
        percorrerEmOrdem(abb, no->sae);
        abb->imprimir(no->info);
        percorrerEmOrdem(abb, no->sad);
    }
}

void imprimirABB(TABB* abb){
    percorrerEmOrdem(abb, abb->raiz);
} */

// Função de exemplo para imprimir informações do nó (nesse caso, um número inteiro)
void imprimirInteiro(void* info){
    int* valor = (int*)info;
    printf("%d ", *valor);
}

// Função de exemplo para comparar dois números inteiros
int compararInteiro(void* s1, void* s2){
    int* num1 = (int*)s1;
    int* num2 = (int*)s2;
    return *num1 - *num2;
}

