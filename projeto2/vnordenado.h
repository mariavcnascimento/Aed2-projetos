typedef struct lse t_lse;
typedef void(*t_imprimir_lse)(void*);

typedef int (*t_comparar_lse)(void* carga_na_lista, void* nova_carga);
t_lse* criar_vnordenado(t_imprimir_lse impressora, t_comparar_lse comparar);

// operacoes baseadas em posicao
void inserir_vnordenado(t_lse* lse, void* carga);
int tamanho_vnordenado(t_lse* l);
void* remover_vnordenado(t_lse* lse, void* chave);
void estatistica_vnordenado(t_lse* l);
void* maior_vnordenado(t_lse* lse);
void* menor_vnordenado(t_lse* lse);
/* void inserir_lse(t_lse* lse, void* carga);
void inserir_final_lse(t_lse* lse, void* carga);
void* remover_final_lse(t_lse* lse);
void imprimir_lse(t_lse* lse);
void* remover_inicio_lse(t_lse* lse);
void* acessar_lse(t_lse* lse, int pos);
void* acessar_prim_lse(t_lse* l); */