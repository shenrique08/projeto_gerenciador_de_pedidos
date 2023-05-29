#include "pedido.h"
#include "restaurante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no {
    Pedido pedido;
    struct no *prox;
} No;



typedef struct fila {
    No *inicio;
    No *fim;
    int qtd;
} Fila;



/*#########################################################################################################################*/


Fila *criar_fila() 
{
    Fila *f = (Fila*) calloc(1, sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;

    return f;
}



int fila_vazia(Fila *fila)
{
    if (fila == NULL)
        return -1;
    return (fila->qtd == 0);
}




int fila_cheia(Fila *fila)
{
    return 0;
}




int qtd_pedidos(Fila *fila)
{
    if (fila == NULL)
        return -1;
    return fila->qtd;
}





int inserir_pedido(Fila *fila, Pedido pedido)
{
    if (fila == NULL)
        return -1;

    No *novo = (No*) calloc(1, sizeof(No));
    novo->pedido = pedido;
    novo->prox = NULL;

    if (fila->inicio == NULL)
        fila->inicio = novo;
    else
        fila->fim->prox = novo;
    fila->fim = novo;
    fila->qtd++;

    return 0;
}



int realizar_pedido(Fila *fila, char *nome_restaurante, char *nome_prato, Pedido pedido)
{
    if (fila == NULL)
        return -1;

    // Find the desired restaurant and dish in the queue
    No *atual = fila->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->pedido.restaurante.nome, nome_restaurante) == 0 &&
            strcmp(atual->pedido.restaurante.prato->nome, nome_prato) == 0)
        {
            // Update pedido details
            atual->pedido.quantidade = pedido.quantidade;
            atual->pedido.valorTotal = pedido.valorTotal;
            atual->pedido.status = pedido.status;
            return 0;  // Pedido updated successfully
        }
        atual = atual->prox;
    }

    return -2;  // Restaurant or dish not found in the queue
}








int mostrar_pedidos(Fila *fila)
{
    if (fila == NULL || fila_vazia(fila))
        return -1;

    No *aux = fila->inicio;
    int cont = 1;
    while (aux != NULL) {
        printf("\n[%do] pedido\n", cont);
        printf("Restaurante: [%s]\n", aux->pedido.restaurante.nome);
        printf("Quantidade: [%d]\n", aux->pedido.quantidade);
        printf("Valor total: [R$%.2f]\n", aux->pedido.valorTotal);
        printf("Status: [%s]\n\n", (aux->pedido.status == 0) ? "Em andamento" : "Entregue");
        aux = aux->prox;
        cont++;
    }

    return 0;
}





int remover_pedido(Fila *fila, Pedido *pedido_entregue)
{
    if (fila == NULL)
        return -1;
    if (fila_vazia(fila))
        return -2;

    No *aux = fila->inicio;
    fila->inicio = aux->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;
    *pedido_entregue = aux->pedido;

    free(aux);
    fila->qtd--;

    return 0;
}





int pagamento(Fila *fila)
{
    if (fila == NULL)
        return -1;
    if (fila_vazia(fila))
        return -2;

    Pedido pedido_entregue;
    remover_pedido(fila, &pedido_entregue);

    return 0;
}