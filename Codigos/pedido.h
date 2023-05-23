


typedef struct pedido {
    int quantidade;
    float preco;

} Pedido;


typedef struct fila Fila;


Fila *criar_fila();
int fila_vazia(Fila *fila);
int limpar_fila(Fila *fila);

void imprime_pedidos(Fila *fila);
int cadastrar_pedido(Fila *fila, Pedido pedido);

int inserir_pedido(Fila *fila, Pedido pedido);
int remover_pedido(Fila *fila, Pedido *pedido_removido);

char menu();