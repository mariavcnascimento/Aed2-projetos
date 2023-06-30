#define MAX(a,b) (a>b?a:b)
typedef struct no TNo;

typedef void(*t_imprimir_red)(void* info);
typedef int(*t_comparar_red)(void* s1, void* s2);

typedef struct stat t_stats;
typedef struct red t_red;

t_red* criarRED(t_imprimir_red imprimir, t_comparar_red comparar);

void* buscarRED(t_red* red, void* chave);
void inserirRED(t_red* red, void* info);
void* removerRED(t_red* red, void* info);
void estatisticaRED(t_red* red);
int alturaRED(t_red *red);
int tamanhoRED(t_red *red);
