#ifndef PEDIDO_H
#define PEDIDO_H
#include "restaurante.h"
#include "structs.h"





Fila *criar_fila();
int fila_vazia(Fila *fila);
int fila_cheia(Fila *fila);
int qtd_pedidos(Fila *fila);


int inserir_pedido(Fila *fila_pedidos, Pedido pedido);



void mostrar_pedido(Fila *fila);
int remover_pedido(Fila *fila, Pedido *pedido_entregue);

void pagar_com_cartao();
int pagar_com_dinheiro(float valor_total);
void pagar_com_pix();
void mostrar_pagamento(float valor_total);



#endif