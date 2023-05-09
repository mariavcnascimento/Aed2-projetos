#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "lordenado.h"

typedef struct carro{
    char placa[9];
    int hora, min;
}t_carro;

t_carro* criar_carro(char placa[], int hora, int min){
    t_carro *c = malloc(sizeof(t_carro));
    strcpy(c->placa,placa);
    c->hora = hora;
    c->min = min;
    return c;
}

int compararCarro(void* c1, void* c2){
    t_carro* cc1 = c1;
    t_carro* cc2 = c2;
    return strcmp(cc1->placa, cc2->placa);
}

void destroy_carro(t_carro *c){
    free(c);
}

void imprimir_carro(void* ca){
    t_carro* c = ca;
    printf("Placa: %s %d:%d\n", c->placa, c->hora, c->min);
}

int main(){

    t_lse* estacionados = criar_lse(imprimir_carro, compararCarro);
    char placa[9]="placa";
    int hora, min;
    
    scanf("%s", placa);
    while(strcmp(placa,"FIM")!=0){
        scanf("%d",&hora);
        scanf("%d",&min);

        t_carro* novo = criar_carro(placa, hora, min);
        
        //inserir_final_lse(estacionados, novo);
        inserir_lse(estacionados,novo);
        scanf("%s", placa);
    }

    imprimir_lse(estacionados);
    imprimir_carro(menor_ordenado(estacionados));
    imprimir_carro(maior_ordenado(estacionados));
    remover_lse(estacionados,"p3");
    estatistica_lordenado(estacionados);

    
    return 0;
}