#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "medidas.h" 


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
