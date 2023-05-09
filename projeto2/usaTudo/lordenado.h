typedef struct lse t_lse;
typedef void(*t_imprimir_lse)(void*);

typedef int (*t_comparar_lse)(void* carga_na_lista, void* nova_carga);
t_lse* criar_lseO(t_imprimir_lse impressora, t_comparar_lse comparar);
void* remover_lseO(t_lse* lse, void* chave);
void inserir_lseO(t_lse* lse, void* carga);
void* maior_ordenado(t_lse* lse);
void* menor_ordenado(t_lse* lse);
void estatistica_lordenado(t_lse* lse);
void imprimir_lseO(t_lse* lse);
/*
void inserir_inicio_lse(t_lse* lse, void* carga);
void* remover_inicio_lse(t_lse* lse);
void* acessar_lse(t_lse* lse, int pos);
void inserir_final_lse(t_lse* lse, void* carga);
void* remover_final_lse(t_lse* lse);
void imprimir_lse(t_lse* lse);
int tamanho_lse(t_lse* lse);
void* buscar_lse(t_lse* lse, void* chave);*/