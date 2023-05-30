#ifndef PEDIDO_H
#define PEDIDO_H
#include "restaurante.h"


// Estrutura para armazenar os dados do pedido
typedef struct {
    Restaurante restaurante;
    int quantidade;
    float valorTotal;
    int status; // 0 - Em andamento, 1 - Entregue
} Pedido;



typedef struct fila Fila;



Fila *criar_fila();
int fila_vazia(Fila *fila);
int fila_cheia(Fila *fila);
int qtd_pedidos(Fila *fila);


int inserir_pedido(Fila *fila, char *nome_restaurante, char *nome_prato, Pedido pedido, int quantidade, int status, float valor_pedido);



void mostrar_pedido(Fila *fila);
int remover_pedido(Fila *fila, Pedido *pedido_entregue);

int pagamento(Fila *fila);



#endif