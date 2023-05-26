// Estrutura para armazenar os dados do prato
typedef struct {
    char nome[100];
    char bebida[100];
    float preco;
    
} Prato;



// Estrutura para armazenar os dados do restaurante
typedef struct restaurante{
    char nome[100];
    char categoria;
    int tipo_culinaria;
    int qtd_pratos;
    Prato *prato;
    
} Restaurante;



// Estrutura para armazenar os dados do pedido
typedef struct {
    Restaurante restaurante;
    int quantidade;
    float valorTotal;
    char status; // 0 - Em andamento, 1 - Entregue
} Pedido;



typedef struct fila Fila;

Fila *criar_restaurante();
int fila_vazia(Fila *fila);
int limpar_fila(Fila *fila);

int insere_restaurante(Fila *fila, Restaurante r);
int insere_restaurantes_cadastrados(Fila *fila, Restaurante r);
int remove_restaurante(Fila *fila, Restaurante *r);

void menu_restaurante(Fila *fila);
void mostrar_restaurantes(Fila *fila);

int cadastrar_restaurante(Fila *fila, Restaurante *restaurante);

int inserir_pedido(Fila *fila, Pedido pedido);
int remover_pedido(Fila *fila, Pedido *pedido_removido);