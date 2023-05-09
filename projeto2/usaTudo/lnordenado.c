#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lnordenado.h"

/* Tipo elemento da LSE*/
typedef struct elem_lse t_elemento_lse;
struct elem_lse{
    void* cargautil;// carga util
    struct elem_lse* prox;// endereco prox
};

/**
 * cria um elemento da LSE
*/
t_elemento_lse* criar_elemento_lseNo(void* cargautil){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->cargautil = cargautil;
    novo->prox = NULL;

    return novo;
}

/**
 * Definição do tipo Lista Simplesmente Encadeada
*/
struct lse{
    t_elemento_lse* inicio; // Primeiro elemento
    int tamanho;
    t_imprimir_lse impressora; 
    t_comparar_lse comparar;


    int nro_cmp_ins; //comparações na inserção
    int nro_cmp_pri; //comparações para retornar o primeiro
    int nro_cmp_rem; //comparações na remoção
};

t_lse* criar_lseNo(t_imprimir_lse impressora, t_comparar_lse comparar){
     t_lse* nova;
     
    nova  = malloc(sizeof(t_lse));
    nova->inicio = NULL;
    nova->tamanho=0;
    nova->impressora = impressora;
    nova->comparar = comparar;

    nova->nro_cmp_ins = 0;
    nova->nro_cmp_pri = 0;
    nova->nro_cmp_rem = 0;

    return nova;
}

// operacoes baseadas em posicao
void inserir_inicio_lseNo(t_lse* lse, void* carga){
    
    t_elemento_lse* novo = criar_elemento_lseNo(carga);

    novo->prox = lse->inicio;
    lse->inicio = novo;
    lse->tamanho++;
    lse->nro_cmp_ins++;
}

int tamanho_lseNo(t_lse* l){
    return l->tamanho;
}

void* buscar_lseNo(t_lse* lse, void* chave){
    t_elemento_lse* cam=lse->inicio;

    while( (cam!=NULL) && (lse->comparar(cam->cargautil, chave)!=0)){
        cam = cam->prox;
    }
    if (cam != NULL)
        return cam->cargautil;
    else
        return NULL;
}

void* remover_lseNo(t_lse* lse, void* chave){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant = NULL;
    
    while( (cam!=NULL) && (lse->comparar(cam->cargautil , chave)!=0)){
        lse->nro_cmp_rem++;
        ant = cam;
        cam = cam->prox;
    }

    void* carga = NULL;
    if (cam != NULL){
        lse->nro_cmp_rem++;
        carga = cam->cargautil;
        if (cam == lse->inicio){ // inicio?
            lse->inicio = cam->prox;
        }else{
        ant->prox = cam->prox;
        }
        free(cam);
        lse->tamanho--;
    }
    return carga; 

}

void* maior_lse(t_lse* lse){
    if(lse->tamanho == 0){
        return NULL;
    }

    void* maior = lse->inicio->cargautil;
    t_elemento_lse* atual = lse->inicio->prox;
    lse->nro_cmp_pri++;

    while(atual != NULL){
        if(lse->comparar(atual->cargautil,maior)>0){
            maior = atual->cargautil;
        }
        atual = atual->prox;
    }
    return maior;
}

void* menor_lse(t_lse* lse){
    if(lse->tamanho == 0){
        return NULL;
    }

    void* menor = lse->inicio->cargautil;
    t_elemento_lse* atual = lse->inicio->prox;
    lse->nro_cmp_pri++;

    while(atual != NULL){
        if(lse->comparar(atual->cargautil,menor)<0){
            menor = atual->cargautil;
        }
        atual = atual->prox;
    }
    return menor;
}

void estatistica_lnordenado(t_lse* l){
    printf("No. de comparacoes nas insercoes: %d\nNo. de comparacoes nas remocoes: %d\nNo. de comparacoes no acesso ao primeiro elemento: %d\n", l->nro_cmp_ins,l->nro_cmp_rem,l->nro_cmp_pri);
}