#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lnordenado.h"

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

void imprimir_carro(void* cc){
    t_carro* c = cc;

    printf("Placa: %s %d:%d\n", c->placa, c->hora, c->min);

}

int main(int argc, char const *argv[])
{
    t_lse* estacionados = criar_lseNo(imprimir_carro, compararCarro);

    char placa[9]="placa";
    int hora, min;
    
    scanf("%s", placa);
    while(strcmp(placa,"FIM")!=0){
        scanf("%d",&hora);
        scanf("%d",&min);

        t_carro* novo = criar_carro(placa, hora, min);
        
        inserir_inicio_lseNo(estacionados, novo);
        scanf("%s", placa);
    }
    int ocupacao = tamanho_lse(estacionados);

    int qtd_vagas;
    /* do{

        qtd_vagas = tamanho_lse(estacionados) - ocupacao;
        ocupacao--;

        printf("Carro maior da lista:\n");
        t_carro* maior = maior_lse(estacionados);
        imprimir_carro(maior);

        printf("Carro menor da lista:\n");
        t_carro* menor = menor_lse(estacionados);
        imprimir_carro(menor);

        printf("Digite a placa do carro que quer retirar:\n");
        scanf("%s",placa);
        t_carro* saindo = remover_lse(estacionados,placa);

    }while(qtd_vagas!=tamanho_lse(estacionados));
    */
   
    imprimir_carro(maior_lse(estacionados));
    imprimir_carro(menor_lse(estacionados));
    remover_lse(estacionados, "p4");
    estatistica_lnordenado(estacionados);
    
    return 0;
}