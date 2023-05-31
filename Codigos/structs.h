#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct fila Fila;

typedef struct lista Lista_restaurante;



typedef struct {
    char nome[50];
    char bebida[50];
    float preco;
    int qtd_pratos;
    
} Prato;


// Estrutura para armazenar os dados do restaurante
typedef struct restaurante {
    Fila *fila_pedidos;
    char nome[50];
    char categoria;
    int tipo_culinaria;
    int qtd_pratos;
    Prato *prato;
    
    
} Restaurante;



// Estrutura para armazenar os dados do pedido
typedef struct {
    Prato prato;
    int quantidade;
    float valorTotal;
    int status; // 0 - Em andamento, 1 - Entregue
} Pedido;





#endif