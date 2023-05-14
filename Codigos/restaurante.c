#include "restaurante.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct no {
    Conteudo_Pedido dados_pedido;
    struct no *prox;

} No;



typedef struct lista {
    No *inicio;
    No *final;

} Lista;





/*===============================================================================================================================*/

Lista *criar_lista()
{
    Lista *lista_pedidos = (Lista *) calloc(1, sizeof(Lista));
    lista_pedidos->inicio = NULL;

    return lista_pedidos;
}



int lista_vazia(Lista *lista)
{
    if (lista == NULL) return -1;
    if (lista->inicio == NULL)
        return 1;
    else 
        return 0;
}



int tam_lista(Lista *lista)
{
    if (lista == NULL) return -1;

    if (lista->inicio == NULL)
        return 0;
    
    No *no = lista->inicio;
    int contador = 0;
    while (no != NULL) {
        contador ++;
        no = no->prox;
    }

    return contador;
}



int lista_existe(Lista *lista)
{
    if (lista == NULL)
        return 0;
    return 1;
}