#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a,b) (a>b?a:b)

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

typedef struct stat{
  int i_nro;
  int b_nro;
  int r_nro;  
  int b_cmps;
  int i_cmps;
  int r_cmps;
  int i_rot;
  int b_rot;
  int r_rot;
  int rot_totais;
} t_stats;

typedef struct red{
    TNo* raiz;
    t_imprimir_red imprimir;
    t_comparar_red comparar;

    t_stats stats;
} t_red;

t_red* criarRED(t_imprimir_red imprimir, t_comparar_red comparar){
    t_red* red = malloc(sizeof(t_red));

    red->raiz = NULL;
    red->imprimir = imprimir;
    red->comparar = comparar;

    red->stats = (t_stats){.b_cmps=0,.i_cmps=0,.r_cmps=0,.i_nro=0,.b_nro=0,.r_nro=0,.i_rot=0,.b_rot=0,.r_rot=0,.rot_totais=0};

    return red;
}

void estatisticaRED(t_red* red){
    t_stats* stats = &(red->stats);
    printf("Estatísticas:\n");
    double i_media = (double)(stats->i_cmps)/(stats->i_nro);
    printf("Inserções: %d\n", stats->i_nro);
    printf("cmps nas inserções: %d media: %.2lf\n", stats->i_cmps, i_media);
    

    double b_media = (double)(stats->b_cmps)/(stats->b_nro);
    printf("Buscas: %d\n", stats->b_nro);
    printf("cmps nas buscas: %d media: %.2lf\n", stats->b_cmps, b_media);
    
    
    double r_media = (double)(stats->r_cmps)/(stats->r_nro);
    printf("Remoções: %d\n", stats->r_nro);
    printf("cmps nas remoções: %d media: %.2lf\n", stats->r_cmps, r_media);
    

    printf("Remoções totais: %d\n", stats->rot_totais);
    printf("rotações nas inserções: %d\n", stats->i_rot);
    printf("rotações nas buscas: %d\n", stats->b_rot);
    printf("rotações nas remoções: %d\n", stats->r_rot);
}

//implementação de acordo com o artigo
TNo* rotacaoEsq(TNo* no, t_stats* stats){
    TNo* x;
    x = no->sad;
    no->sad = x->sae;
    x->sae = no;
    x->cor = no->cor;
    no->cor = 1;

    stats->rot_totais++;
    return x;
}

TNo* rotacaoDir(TNo* no,t_stats* stats){
    TNo* x;
    x = no->sae;
    no->sae = no-> sad;
    x->sad = no;
    x->cor = no->cor;
    no->cor = 1;

    stats->rot_totais++;
    return x;
}

void trocarCor(TNo* no){
    no->cor = !no->cor;
    no->sae->cor = !no->sae->cor;
    no->sad->cor = !no->sad->cor;
}

bool isRed(TNo* no){
    int cor = no->cor;
    if(cor == 1) return true;
    else if (cor == 0) return false;
}

void* __buscar(TNo* no ,void* chave, t_comparar_red compara, t_stats* stats){
    while (no != NULL)
    {
        int cmp = compara(no->info,chave);
        if(cmp == 0){
            stats->b_cmps+=1;
            return no->info;
        }
        else if (cmp<0){
            stats->b_cmps+=2;
            return __buscar(no->sad, chave,compara,stats);
        }
        else if(cmp>0){
            stats->b_cmps+=3;
            return __buscar(no->sae,chave,compara,stats);
        }
    }
    return NULL;
}

void* buscarRED(t_red* red, void* chave){
    t_stats* stats = &(red->stats);
    stats->b_nro++;

    TNo* no = __buscar(red->raiz,chave,red->comparar,stats);
    return (no != NULL?no->info:NULL);
}

TNo* __inserirRed(TNo* no, void* info, t_comparar_red compara, t_stats* stats){
    if(no == NULL) {
        stats->i_cmps++;
        return criar_no(no,info);
    }

    if(isRed(no->sae) && isRed(no->sad)){
        trocarCor(no);
    }

    int cmp = compara(no->info,info);
    if(cmp == 0){
        return no;//já existe na árvore
    }
    else if (cmp<0){
        stats->i_cmps+=2;
        return __inserirRed(no->sad, info, compara, stats);
    }
    else if(cmp>0){
        stats->i_cmps+=3;
        return __inserirRed(no->sae,info, compara, stats);
    }

    if(isRed(no->sad) && !isRed(no->sae)){
        no = rotacaoEsq(no,stats);
        stats->rot_totais++;
        stats->i_rot++;
    }

    if(isRed(no->sae) && isRed(no->sae->sae)){
        no = rotacaoDir(no,stats);
        stats->rot_totais++;
        stats->i_rot++;
    }

    return no;
}

void inserirRED(t_red* red, void* info){
    TNo* raiz = red->raiz;
    t_stats* stats = &(red->stats);
    stats->i_nro++;
    raiz = __inserirRed(raiz, info, red->comparar,stats);
    raiz->cor = 0; // a raiz é sempre preta
}

TNo* moverRedEsq(TNo* no, t_stats* stats){
    trocarCor(no);
    if(isRed(no->sad->sae)){
        no->sad = rotacaoDir(no->sad,stats);
        no = rotacaoEsq(no,stats);
        stats->rot_totais+= 2;
        stats->r_rot+= 2;
        trocarCor(no);
    }
    return no;
}

TNo* moverRedDir(TNo* no, t_stats* stats){
    trocarCor(no);
    if(isRed(no->sae->sae)){
        no = rotacaoDir(no,stats);
        stats->rot_totais++;
        stats->r_rot++;
        trocarCor(no);
    }
    return no;
}

TNo* min(TNo* no){
    if (no == NULL);
        return NULL;
    while(no->sae != NULL)
        no = no->sae;
    
    return no;
}

TNo* fixUp(TNo* no, t_stats* stats) {

	if (isRed(no->sad)){
		no = rotacaoEsq(no,stats);
        stats->rot_totais++;
        stats->r_rot++;
	}
	if (no->sae && isRed(no->sae) && isRed(no->sae->sae) ){
		no = rotacaoDir(no,stats);
        stats->rot_totais++;
        stats->r_rot++;
	}
	if ( isRed(no->sae) && isRed(no->sad) ){
		trocarCor(no);
	}

	return no;
}

TNo* __deleteMin(TNo* no,t_stats* stats){
    if(no == NULL)
        return NULL;
    else if (!isRed(no->sae) && !isRed(no->sae->sae))
        no = moverRedEsq(no,stats);
    
    no->sae = __deleteMin(no->sae,stats);

    return fixUp(no,stats);
} 

/* void* deleteMin(t_red* red){
    TNo* raiz = red->raiz;
    raiz = __deleteMin(raiz);
    raiz->cor = 0; 
} */

TNo* __removerRed(TNo* no, void* info, t_comparar_red compara, t_stats* stats){
    int cmp = compara(no->info, info);
    if(cmp > 0){ //infor menor que o valor no nó
        if(!isRed(no->sae) && !isRed(no->sae->sae)){
            no = moverRedEsq(no,stats);
        }
        no->sae = __removerRed(no->sae,info,compara,stats);
    }else{
        if(isRed(no->sae)){
            no = rotacaoDir(no,stats);
            stats->rot_totais++;
            stats->r_rot++;
        }else if (cmp == 0 && no->sad == NULL){
            return NULL;
        }else if (!isRed(no->sad) && isRed(no->sad->sae)){
            return moverRedDir(no,stats);
        }else if(cmp == 0){
            no->info = __buscar(no->sad,min(no->sad)->info,compara,stats);
            no = min(no->sad);
            no->sad = __deleteMin(no->sad,stats);
        }else{
            no->sad = __removerRed(no->sad, info,compara,stats);
        }

        return fixUp(no,stats);
    }
}

void* removerRED(t_red* red, void* info){
    t_stats* stats = &(red->stats);
    TNo* raiz = red->raiz;
    raiz = __removerRed(raiz, info, red->comparar, stats);
    raiz->cor = 0; //raiz sempre preta
}

static int __alturaRED(TNo *raiz){
    if (raiz == NULL)
        return -1;
    return MAX(__alturaRED(raiz->sae), __alturaRED(raiz->sad))+1;
}

int alturaRED(t_red *red){
    return __alturaRED(red->raiz);
}

static int __tamanhoRED(TNo* raiz){
    if (raiz == NULL)
        return 0;
    return (__tamanhoRED(raiz->sae)+__tamanhoRED(raiz->sad))+1;
}

int tamanhoRED(t_red *red){
    return __tamanhoRED(red->raiz);

}

