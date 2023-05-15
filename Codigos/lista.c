#include "lista.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct no {
    Conteudo_Pedido dados_pedido;
    struct no *prox;

} No;



typedef struct lista {
    No *inicio;

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
/*======================================================================================================================*/




int inserir_no_inicio(Lista *lista, Conteudo_Pedido pedido)
{
    // se a lista não existe, retorne 2
    if (lista_existe(lista) == 0)
        return 2;
    No *no = (No *) calloc(1, sizeof(No));

    no->dados_pedido = pedido;
    no->prox = lista->inicio;
    lista->inicio = no;

    return 0;
}





int inserir_no_fim(Lista *lista, Conteudo_Pedido pedido)
{
    if (lista_existe(lista) == 0)
        return 2;
    if (lista_vazia(lista) == 1)
        return inserir_no_inicio(lista, pedido);

    No *noLista = lista->inicio;

    while (noLista->prox != NULL)
        noLista = noLista->prox;

    No *novo_no = (No *) calloc(1, sizeof(No));

    novo_no->dados_pedido = pedido;
    noLista->prox = novo_no;
    novo_no->prox = NULL;

    return 0;
}