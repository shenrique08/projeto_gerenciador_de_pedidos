#ifndef RESTAURANTE_H
#define RESTAURANTE_H
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



typedef struct lista Lista_restaurante;



Lista_restaurante *criar_restaurante();
int limpar_lista(Lista_restaurante *lista);


int insere_restaurante_pos(Lista_restaurante *lista, Restaurante r, int pos);
int insere_restaurante_no_final(Lista_restaurante *lista, Restaurante r);
int insere_restaurantes_cadastrados(Lista_restaurante *lista, Restaurante r);
int cadastrar_restaurante(Lista_restaurante *lista, Restaurante *restaurante, int pos_cadastro);


int remove_restaurante_inicio(Lista_restaurante *lista, Restaurante *r);
int remove_restaurante_final(Lista_restaurante *lista, Restaurante *r);
int remove_restaurante_pos(Lista_restaurante *lista, Restaurante *r, int pos);


void menu_restaurante(Lista_restaurante *lista);
void mostrar_restaurantes(Lista_restaurante *lista);
void printLetterByLetter(const char* message, float seconds);


int inserir_pedido(Lista_restaurante *lista, Pedido pedido);
int remover_pedido(Lista_restaurante *lista, Pedido *pedido_removido);

#endif