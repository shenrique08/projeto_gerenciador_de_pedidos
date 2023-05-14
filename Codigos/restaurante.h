


typedef struct conteudo_pedido {
    float preco;
    
} Conteudo_Pedido;


typedef struct lista Lista;


Lista *criar_lista();
int lista_existe(Lista *lista);
int lista_vazia(Lista *lista);
int tam_lista(Lista *lista);



int inserir_no_inicio(Lista *lista, Conteudo_Pedido pedido);
int inserir_no_fim(Lista *lista, Conteudo_Pedido pedido);
