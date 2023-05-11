#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "heap.h"

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

void imprimir_carro(t_carro* c){

    printf("Placa: %s %d:%d\n", c->placa, c->hora, c->min);

}

int main(int argc, char const *argv[])
{
    t_heap* estacionados = criar_heap(-1, compararCarro);

    char placa[9]="placa";
    int hora, min;
    
    scanf("%s", placa);
    while(strcmp(placa,"FIM")!=0){
        scanf("%d",&hora);
        scanf("%d",&min);

        t_carro* novo = criar_carro(placa, hora, min);
        
        inserir_heap(estacionados, novo);
        scanf("%s", placa);
    }

    int qtd_vagas;
    do{
        t_carro* saindo = remover_heap(estacionados);
        t_carro* maior = raiz_heap(estacionados);
    
        imprimir_carro(saindo);
        printf("Ocupacao: %d\n", ocupacao_heap(estacionados));
        
        qtd_vagas = (tamanho_heap(estacionados)-ocupacao_heap(estacionados));

        printf("Quantas vagas?: %d\n",qtd_vagas);

    }while(qtd_vagas!=tamanho_heap(estacionados));

    estatistica_heap(estacionados);

    return 0;
}