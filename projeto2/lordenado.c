#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lordenado.h"

/* Tipo elemento da LSE*/
typedef struct elem_lse t_elemento_lse;
struct elem_lse{
    void* cargautil;// carga util
    struct elem_lse* prox;// endereco prox
};

/**
 * cria um elemento da LSE
*/
t_elemento_lse* criar_elemento_lse(void* cargautil){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->cargautil = cargautil;
    novo->prox = NULL;

    //printf("Criando: %p %p %p\n", novo, novo->cargautil, novo->prox);

    return novo;
}

/**
 * Definição do tipo Lista Simplesmente Encadeada
*/
struct lse{
    t_elemento_lse* inicio; // Primeiro elemento
    t_elemento_lse* fim;
    int tamanho;
    t_imprimir_lse impressora; 
    t_comparar_lse comparar;
    int nro_cmp_ins;
    int nro_cmp_pri;
    int nro_cmp_rem;
};

t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparar){
     t_lse* nova;
     
    nova  = malloc(sizeof(t_lse));
    nova->inicio = NULL;
    nova -> fim = NULL;
    nova->tamanho = 0;
    nova->impressora = impressora;
    nova->comparar = comparar;
    nova -> nro_cmp_ins = 0;
    nova -> nro_cmp_pri = 0;
    nova -> nro_cmp_rem = 0;

    return nova;
}



void inserir_lse(t_lse* lse, void* nova_carga){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant=NULL;

    lse->tamanho++;
    t_elemento_lse* novo = criar_elemento_lse(nova_carga);
    if (lse->inicio == NULL){ // lista vazia
       lse->inicio = novo;
    }else{
        while( (cam!=NULL) && (lse->comparar(cam->cargautil, nova_carga)<0)){
            ant = cam;
            cam = cam->prox;
            lse -> nro_cmp_ins++;
        }
        // inicio
        if(cam == lse->inicio){
            novo->prox = cam;
            lse->inicio = novo;
            lse -> nro_cmp_ins++;
        }else{
            ant->prox = novo;
            novo->prox = cam;
            lse -> nro_cmp_ins++;
        }
    }
}



void* remover_lse(t_lse* lse, void* chave){
    t_elemento_lse* cam = lse->inicio;
    t_elemento_lse* ant = NULL;
    
    while( (cam!=NULL) && (lse->comparar(cam->cargautil , chave)!=0)){
        ant = cam;
        cam = cam->prox;
        lse -> nro_cmp_rem++;
    }

    void* carga = NULL;
    if (cam != NULL){
        carga = cam->cargautil;
        if (cam == lse->inicio){ // inicio?
            lse->inicio = cam->prox;
            lse -> nro_cmp_rem++;
        }else{
            ant->prox = cam->prox;
            lse -> nro_cmp_rem++;
        }
        free(cam);
        lse->tamanho--;
    }
    return carga; 

}

void* menor_ordenado(t_lse* lse){
    t_elemento_lse* cam = lse -> inicio;
    lse->nro_cmp_pri++; 
    return cam -> cargautil;
}

void* maior_ordenado(t_lse* lse){
    int cont = 0;
    void* carga = NULL;
    
    if(lse->inicio == NULL){
        return carga;
    }else{
        t_elemento_lse* cam = lse->inicio;
        while(cam->prox!=NULL){
            cam=cam->prox;
            cont++;
        }
        carga = cam -> cargautil;
        //printf("%d\n",cont);
        return carga;
    }
}

void estatistica_lordenado(t_lse* lse){
    printf("Nmr de comparacoes nas insercoes: %d\n",lse -> nro_cmp_ins);
    printf("Nmr de comparacoes no acesso ao primeiro elemento: %d\n", lse -> nro_cmp_pri);
    printf("Nmr de comparacoes nas remocoes: %d\n", lse -> nro_cmp_rem);
}

/*
int tamanho_lse(t_lse* lse){
   return lse ->tamanho;
}

void* buscar_lse(t_lse* lse, void* chave){
    t_elemento_lse* cam=lse->inicio;

    while( (cam!=NULL) && (lse->comparar(cam->cargautil, chave)!=0)){
        cam = cam->prox;
    }
    if (cam != NULL)
        return cam->cargautil;
    else
        return NULL;
}

void* acessar_lse(t_lse* lse, int pos){
    int i=1;
    void* carga=NULL; // entrada invalida
    if (pos<0){
        pos = (pos % lse->tamanho) + (lse->tamanho+1); 
        pos = (pos==0?1:pos);
    }else if(pos>0){
        pos = pos % lse->tamanho;
        pos = (pos==0?lse->tamanho:pos);
    }else{
        return carga;
    }

    t_elemento_lse* cam = lse->inicio;
    if ((pos<=lse->tamanho)){
        while(i<pos){
            cam = cam->prox;
            i++;
        }
        carga = cam->cargautil;
    }
    return carga;
}

// operacoes baseadas em posicao
void inserir_inicio_lse(t_lse* lse, void* carga){
    
    t_elemento_lse* novo = criar_elemento_lse(carga);

    novo->prox = lse->inicio;
    lse->inicio = novo;
    lse->tamanho++;

}

void* remover_inicio_lse(t_lse* lse){
    void* carga=NULL;
    t_elemento_lse* removivel = lse->inicio;
    if (lse->inicio != NULL){    
        lse->inicio = removivel->prox;
        lse->tamanho--;
        carga = removivel->cargautil;

        free(removivel);
    }
    return carga;
}


void inserir_final_lse(t_lse* lse, void* carga){
    t_elemento_lse* novo = criar_elemento_lse(carga);
    if(lse->tamanho == 0){ // lse->inicio == NULL
        lse->inicio = novo;
    }else{
        t_elemento_lse* cam = lse->inicio;
        while(cam->prox!=NULL){
            cam=cam->prox;
        }
        cam->prox = novo;
    }
    lse->tamanho++;
}

void* remover_final_lse(t_lse* lse){
    void* carga=NULL;

    t_elemento_lse* ant=NULL;
    t_elemento_lse* cam=lse->inicio;
    if (lse->tamanho == 0){
        return carga;
    }else if(lse->tamanho == 1){
        cam = lse->inicio;
        lse->inicio=NULL;
    }else{
        while(cam->prox!=NULL){
            ant = cam;
            cam = cam->prox;
        }
        ant->prox = NULL;
    }
    carga = cam->cargautil;
    free(cam);
    lse->tamanho--;
    return carga;
}

void imprimir_lse(t_lse *lse){
    t_elemento_lse* cam = lse->inicio;
    while(cam!=NULL){
        lse->impressora(cam->cargautil);
        cam = cam->prox;
    } 
}*/