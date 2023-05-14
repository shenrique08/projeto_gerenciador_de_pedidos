#include "restaurante.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct no {
    Conteudo_Pedido dados_pedido;
    struct no *prox;

} No;


typedef struct lista {
    No *inicio

} Lista;


Lista *criar_lista()
{
    Lista *lista_pedidos = (Lista *) calloc(1, sizeof(Lista));
    lista_pedidos->inicio = NULL;

    return lista_pedidos;
}