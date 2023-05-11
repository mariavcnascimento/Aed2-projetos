#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "vordenado.h"

typedef struct elem_lse t_elemento_lse;
struct elem_lse{
    void* cargautil;
    struct elem_lse* prox;
};


t_elemento_lse* criar_elemento_lse(void* cargautil){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->cargautil = cargautil;
    novo->prox = NULL;

    return novo;
}

struct lse{
    t_elemento_lse* inicio; 
    int tamanho;
    t_imprimir_lse impressora; 
    t_comparar_lse comparar;
    int nro_cmp_ins;
    int nro_cmp_pri;
    int nro_cmp_rem;
};

t_lse* criar_vordenado(t_imprimir_lse impressora, t_comparar_lse comparar){
     t_lse* nova;
     
    nova  = malloc(sizeof(t_lse));
    nova->inicio = NULL;
    nova->tamanho = 0;
    nova->impressora = impressora;
    nova->comparar = comparar;
    nova -> nro_cmp_ins = 0;
    nova -> nro_cmp_pri = 0;
    nova -> nro_cmp_rem = 0;

    return nova;
}

void inserir_vordenado(t_lse* lse, void* nova_carga){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant=NULL;

    if(lse->tamanho == 0){
        lse->nro_cmp_pri;
    }else{
        lse->nro_cmp_pri++;
    }
    //lse->nro_cmp_pri++;
    lse->tamanho++;
    t_elemento_lse* novo = criar_elemento_lse(nova_carga);
    if (lse->inicio == NULL){
       lse->inicio = novo;
    }else{
        while( (cam!=NULL) && (lse->comparar(cam->cargautil, nova_carga)<0)){
            ant = cam;
            cam = cam->prox;
            lse -> nro_cmp_ins++;
        }
        
        if(cam == lse->inicio){
            novo->prox = cam;
            lse->inicio = novo;
        }else{
            ant->prox = novo;
            novo->prox = cam;
            
        }
    }
}


void* remover_vordenado(t_lse* lse, void* chave){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant = NULL;
    
    lse->nro_cmp_pri++;
    

    while( (cam!=NULL) && (lse->comparar(cam->cargautil , chave)!=0)){
        ant = cam;
        cam = cam->prox;
        lse -> nro_cmp_rem++;
    }

    void* carga = NULL;
    if (cam != NULL){
        carga = cam->cargautil;
        if (cam == lse->inicio){ 
            lse->inicio = cam->prox;
        }else{
            ant->prox = cam->prox;    
        }
        free(cam);
        lse->tamanho--;
    }
    return carga; 

}

void* menor_vordenado(t_lse* lse){
    t_elemento_lse* cam = lse -> inicio; 
    return cam -> cargautil;
}

void* maior_vordenado(t_lse* lse){
    void* carga = NULL;
    
    if(lse->inicio == NULL){
        return carga;
    }else{
        t_elemento_lse* cam = lse->inicio;
        while(cam->prox!=NULL){
            cam=cam->prox;
        }
        carga = cam -> cargautil;
        return carga;
    }
}

int tamanho_vordenado(t_lse* l){
    return l->tamanho;
}

void estatistica_vordenado(t_lse* lse){
    printf("nro comparacoes insercao:  %d\nnro comparações remocao: %d\nnro comparacoes primeiro: %d\n", lse->nro_cmp_ins,lse->nro_cmp_rem,lse->nro_cmp_pri);
}

