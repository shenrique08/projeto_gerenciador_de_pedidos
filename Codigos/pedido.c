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






int inserir_pedido(Fila *fila, char *nome_restaurante, char *nome_prato, Pedido pedido, int quantidade, int status, float valor_pedido) 
{
    if (fila == NULL)
        return -1; // Fila não existe

    No *novo = (No *) calloc(1, sizeof(No));
    if (novo == NULL) 
        return -1; // Falha na alocação de memória
    
    // Copia os dados do restaurante para o pedido
    strcpy(pedido.restaurante.nome, nome_restaurante);

    // Definir os valores do pedido
    pedido.quantidade = quantidade;
    pedido.status = status;
    pedido.valorTotal = valor_pedido;

    novo->pedido = pedido;
    novo->prox = NULL;

    // Insere o novo pedido na fila
    if (fila->inicio == NULL) {
        // A fila está vazia
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // A fila não está vazia
        fila->fim->prox = novo;
        fila->fim = novo;
    }

    fila->qtd++;

    return 1; // Sucesso na inserção do pedido
}





void mostrar_pedido(Fila *fila) 
{
    No *aux = fila->inicio;

    printf("-------------------------------------------------------------------\n");
    printLetterByLetter("*** PROXIMO PEDIDO A SER ENTREGUE ***\n", 0.03);
    
    printf("\nRestaurante: [%s]\n", aux->pedido.restaurante.nome);
    //printf("Prato Principal: [%s]\n", atual->pedido.restaurante.prato.nome);
    printf("Quantidade: [%d]\n", aux->pedido.quantidade);
    printf("Valor Total: [R$%.2f]\n", aux->pedido.valorTotal);
    printf("Status: [%s]\n", aux->pedido.status ? "Entregue" : "Em andamento");
    printf("-------------------------------------------------------------------\n");
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