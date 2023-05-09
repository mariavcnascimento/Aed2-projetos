#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "heap.h"
#include "filacomprioridade.h"
#include "lordenado.h"
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

void imprimir_carro(void* ca){
    t_carro* c = ca;
    printf("Placa: %s %d:%d\n", c->placa, c->hora, c->min);

}

void inserir_estrutura(void* estrutura,int tipo){
   
    char placa[9]="placa";
    int hora, min;
    
    scanf("%s", placa);
    while(strcmp(placa,"FIM")!=0){
        scanf("%d",&hora);
        scanf("%d",&min);

        t_carro* novo = criar_carro(placa, hora, min);
        if(tipo == 1){
            inserir_lseO(estrutura,novo);
        }else if(tipo == 2){
            inserir_inicio_lseNo(estrutura,novo);
        }else if(tipo == 3){
            enfileirarCP(estrutura, novo);
        }
        
        scanf("%s", placa);
    }
}

int apresenta(){
    int op;
    printf("Qual estrutura deseja usar?:\n1 - Lista Ordenada\n2 - Lista nao ordenada\n3 - Heap\n");
    scanf("%d",&op);
    return op;
}

int continuar(){
    int num;
    printf("Deseja analisar outra estrutura?\n1-SIM\n2-NAO\n");
    scanf("%d",&num);
    return num;
}

int main(){
    int op, flag = 0;
    
    t_lse* estacionadosO;
    t_lse* estacionadosNo;
    t_fila_cp* estacionadosH;
    
    while(flag != 2 ){
        op = apresenta();
        switch(op){
            case 1:
                estacionadosO = criar_lseO(imprimir_carro,compararCarro);
                inserir_estrutura(estacionadosO,op);
                imprimir_carro(menor_ordenado(estacionadosO));
                imprimir_carro(maior_ordenado(estacionadosO));
                estatistica_lordenado(estacionadosO);
                flag = continuar();
                break;
            case 2:
                estacionadosNo = criar_lseNo(imprimir_carro, compararCarro);
                inserir_estrutura(estacionadosNo,op);
                imprimir_carro(menor_lse(estacionadosNo));
                imprimir_carro(maior_lse(estacionadosNo));
                estatistica_lnordenado(estacionadosNo);
                flag = continuar();
                break;
            case 3:
                estacionadosH = criar_fila_cp(4,compararCarro);
                inserir_estrutura(estacionadosH,op);
                estatistica_FCP(estacionadosH);
                flag = continuar();
                break;
            
        }
    }
    
    return 0;
}