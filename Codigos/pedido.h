#ifndef PEDIDO_H
#define PEDIDO_H
#include "restaurante.h"
#include "structs.h" // structs.h contém as structs Restaurante e Prato


// cada pedido será armazenado em uma fila para cada restaurante. Ou seja, se o usuário fizer o pedido em um 
// restaurante A, o pedido será armazenado na fila do restaurante A. Ou seja, se já não houver esta fila, então ela será criada
// Se o usuário fizer o pedido em um restaurante B,


Fila *criar_fila();
int fila_vazia(Fila *fila);
int fila_cheia(Fila *fila);
int qtd_pedidos(Fila *fila);


int inserir_pedido(Fila *fila_pedidos, Pedido pedido);



void mostrar_pedido(Fila *fila, int status);
int remover_pedido(Fila *fila);

// função será utilizada caso o usuário queira pagar com cartão de crédito
void pagar_com_cartao();

// função será utilizada caso o usuário queira pagar com dinheiro
int pagar_com_dinheiro(float valor_total);

// função será utilizada caso o usuário queira pagar com pix
void pagar_com_pix();

// menu de pagamento
int mostrar_pagamento(float valor_total);
void mostrar_estimativa_entrega();
void sleep(float seconds);
void mostrar_avaliacao();


#endif