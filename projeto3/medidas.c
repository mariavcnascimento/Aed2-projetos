#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "time.h"
#include "medidas.h" 
//#include "arv_avl.h"

//Funções especialistas
typedef struct dado{
    int valor;
} t_dado;

t_dado* criar_medida(int num){
    t_dado* dado = malloc(sizeof(t_dado));
    dado -> valor = num;
    return dado;
}

void destroy_medida(void* d){
    t_dado* d1 = d;
    free(d1);
}

void imprimir_medida(void* d){
    t_dado* d1 = d;
    if(d1){
        printf("%d\n", d1 -> valor);
    }
}

int comparar_medida(void* d1, void* d2){ //d1 está na lista, d2 é a carga nova
    t_dado* dado1 = d1;
    t_dado* dado2 = d2;

    if(dado1 -> valor > dado2 -> valor){
        return 1;
    } else if (dado1 -> valor == dado2 -> valor){
        return 0;
    } else {
        return -1;
    }
}

void* ler_medida(){
   
    int* num = (int*)malloc(sizeof(int));
    scanf("%d", num);
    if(*num == -3){
        return NULL;
    }
    return num;
}

void* ler_chave_medida(void* chave){
    int* num = (int*)malloc(sizeof(int));
    scanf("%d", num);
    if(*num == -3){
        return NULL;
    }
    return num;
    
}

/*
int main(){
    int num;
    int buscado, removivel;
    int* chave;

    t_ab* valores = criarABB(imprimirDado, compararDado);
    scanf("%d",&num);
    do{
        
        t_dado* novo = criarDado(num);
        inserirABB(valores, novo);

        scanf("%d",&num); 
    }while(num != -3);

    imprimirABB(valores);
    buscado = 27;
    chave = &buscado;
    buscarABB(valores, chave);

    buscado = 11;
    chave = &buscado;
    buscarABB(valores, chave);

    estatisticaAVL(valores);

    removivel = 11;
    chave = &removivel;
    removerABB(valores, chave);
    removivel = 10;
    chave = &removivel;
    removerABB(valores, chave);
    removivel = 17;
    chave = &removivel;
    removerABB(valores, chave);
    
    printf("\n---------POS REMOCAO----------\n");
    //imprimirABB(valores);
    estatisticaAVL(valores);
    
    return 0;
}*/