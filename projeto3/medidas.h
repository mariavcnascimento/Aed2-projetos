typedef struct dado t_dado;

t_dado* criar_medida(int num);
void destroy_medida(void* d);
void imprimir_medida(void* d);
int comparar_medida(void* d1, void* d2);
void* ler_medida();
void* ler_chave_medida(void* chave);
