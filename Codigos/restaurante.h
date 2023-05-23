


// Estrutura para armazenar os dados do prato
typedef struct {
    char nome[100];
    char bebida[100];
    float preco;
    
} Prato;



// Estrutura para armazenar os dados do restaurante
typedef struct {
    char nome[100];
    char categoria;
    char tipo_culinaria[100];
    Prato prato;
    
} Restaurante;







// Estrutura para armazenar os dados do pedido
typedef struct {
    Restaurante restaurante;
    Prato prato;
    int quantidade;
    float valorTotal;
    int status; // 0 - Em andamento, 1 - Entregue
} Pedido;


typedef struct fila Fila;


Fila *criar_restaurante();
int fila_vazia(Fila *fila);
int limpar_fila(Fila *fila);


int insere_restaurante(Fila *fila, Restaurante r);
int insere_restaurantes_cadastrados(Fila *fila, Restaurante restaurante);

int imprime_pedidos(Fila *fila);
int mostra_restaurantes(Fila *fila);

int cadastrar_restaurante(Fila *fila, Restaurante restaurante);

int inserir_pedido(Fila *fila, Pedido pedido);
int remover_pedido(Fila *fila, Pedido *pedido_removido);
