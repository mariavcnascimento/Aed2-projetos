typedef struct lse t_lse;
typedef void(*t_imprimir_lse)(void*);

typedef int (*t_comparar_lse)(void* carga_na_lista, void* nova_carga);
t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparar);
void* remover_lse(t_lse* lse, void* chave);
void inserir_lse(t_lse* lse, void* carga);
void* maior_vordenado(t_lse* lse);
void* menor_vordenado(t_lse* lse);
void estatistica_vordenado(t_lse* lse);

