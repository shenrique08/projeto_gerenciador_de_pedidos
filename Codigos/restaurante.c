#include "restaurante.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct no {
    Pedido dados_pedido;
    Restaurante dados_restaurante;
    struct no *prox;

} No;  


typedef struct fila {
    No *inicio;
    No *fim;
    int tam_fila;

} Fila;





Fila *criar_restaurante()
{
    Fila *fila = (Fila *) calloc(1, sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tam_fila = 0;

    return fila;
}




int fila_vazia(Fila *fila)
{
    if (fila->inicio == NULL) {
        return 1;
    }
    return 0;
}




int limpar_fila(Fila *fila)
{
    if (fila == NULL) {
        return -1;
    }

    No *aux = fila->inicio;
    while (aux != NULL) {
        fila->inicio = fila->inicio->prox;
        free(aux);
        aux = fila->inicio;
    }

    free(fila);

    return 0;
}




int imprime_pedidos(Fila *fila)
{
    if (fila == NULL) {
        return -1;
    }

    No *aux = fila->inicio;
    while (aux != NULL) {
        printf("\nRestaurante: [%s]", aux->dados_pedido.restaurante.nome);
        printf("\nPrato: [%s]", aux->dados_pedido.prato.nome);
        printf("\nQuantidade: [%d]", aux->dados_pedido.quantidade);
        printf("\nValor total: [$%.2f]", aux->dados_pedido.valorTotal);
        printf("\nStatus do pedido: [%d]", aux->dados_pedido.status);
        printf("\n\n");
        aux = aux->prox;
    }

    return 0;
}





// agora, iremos fazer uma função para inserir um restaurante na fila
int insere_restaurante(Fila *fila, Restaurante r)
{
    if (fila == NULL) {
        return -1;
    }

    // será o novo usuário
    No *novo_no = (No*) calloc(1, sizeof(No));

    novo_no->dados_restaurante = r;

    if (fila_vazia(fila)) {
        fila->inicio = novo_no;
        fila->fim = novo_no;
    } else {
        fila->fim->prox = novo_no;
        fila->fim = novo_no;
    }

    fila->tam_fila++;

    return 0;
}





int cadastrar_restaurante(Fila *fila, Restaurante restaurante) 
{
    if (fila->inicio == NULL) 
        return -1;

    // será o novo usuário
    No *novo_no = (No*) calloc(1, sizeof(No));

    novo_no->dados_restaurante = restaurante;

    printf("\n=============== SISTEMA DE CADASTRO DE RESTAURANTES ===============\n");
    printf("\nInforme o [NOME] do restaurante: ");
    fgets(novo_no->dados_restaurante.nome, sizeof(novo_no->dados_restaurante.nome), stdin);

    printf("Informe o tipo culinario que o restaurante oferece: ");
    printf("\n[1] - Brasileira");
    printf("\n[2] - Fast Food");
    printf("\n[3] - Japonesa\n");
    scanf("%c", &novo_no->dados_restaurante.categoria);
    getchar();
    do {
        switch (novo_no->dados_restaurante.categoria) 
        {
        case '1':
            strcpy(novo_no->dados_restaurante.tipo_culinaria, "Brasileira");
            strcat(novo_no->dados_restaurante.tipo_culinaria, "\n");

            printf("\nInforme o [nome do prato 'brazuka']: ");
            fgets(novo_no->dados_restaurante.prato.nome, sizeof(novo_no->dados_restaurante.prato.nome), stdin);

            printf("\nInforme a ['bebida' que acompanha o prato]: ");
            fgets(novo_no->dados_restaurante.prato.bebida, sizeof(novo_no->dados_restaurante.prato.bebida), stdin);

            printf("\nInforme o [preco do prato 'brazuka'] em R$: ");
            scanf("%f", &novo_no->dados_restaurante.prato.preco);
            break;
        case '2':
            strcpy(novo_no->dados_restaurante.tipo_culinaria, "Fast Food");
            strcat(novo_no->dados_restaurante.tipo_culinaria, "\n");

            printf("\nInforme o [nome do 'lanche']: ");
            fgets(novo_no->dados_restaurante.prato.nome, sizeof(novo_no->dados_restaurante.prato.nome), stdin);

            printf("\nInforme a ['bebida' que acompanha o prato]: ");
            fgets(novo_no->dados_restaurante.prato.bebida, sizeof(novo_no->dados_restaurante.prato.bebida), stdin);

            printf("\nInforme o [preco do 'lanche'] em R$: ");
            scanf("%f", &novo_no->dados_restaurante.prato.preco);
            break;
        case '3':
            strcpy(novo_no->dados_restaurante.tipo_culinaria, "Japonesa");
            strcat(novo_no->dados_restaurante.tipo_culinaria, "\n");

            printf("\nInforme o [nome do prato 'japones']: ");
            fgets(novo_no->dados_restaurante.prato.nome, sizeof(novo_no->dados_restaurante.prato.nome), stdin);

            printf("\nInforme a ['bebida' que acompanha o prato]: ");
            fgets(novo_no->dados_restaurante.prato.bebida, sizeof(novo_no->dados_restaurante.prato.bebida), stdin);

            printf("\nInforme o [preco do prato 'japones'] em R$: ");
            scanf("%f", &novo_no->dados_restaurante.prato.preco);
            break;
        default:
            printf("\nOpcao invalida! Tente novamente!\n\n");
            break;
        }

    } while (novo_no->dados_restaurante.categoria != '1' && novo_no->dados_restaurante.categoria != '2' && 
    novo_no->dados_restaurante.categoria != '3');

    inserir_restaurante(fila, novo_no->dados_restaurante);

    return 0;
}





// função que "simula uma base de dados de restaurantes", para que, inicialmente, o usuário tenha acesso a vários restaurantes previamente disponíveis
int insere_restaurantes_cadastrados(Fila *fila, Restaurante restaurante)
{
    if (fila->inicio != NULL) {
        int contador = 0;
        while (contador < 1) 
        {
            No *novo_no = (No*) calloc(1, sizeof(No));
            novo_no->dados_restaurante = restaurante;

            strcpy(novo_no->dados_restaurante.nome, "Subway");
            strcpy(novo_no->dados_restaurante.tipo_culinaria, "Fast Food");
            strcpy(novo_no->dados_restaurante.prato.nome, "Baratissimo");

            strcpy(novo_no->dados_restaurante.prato.bebida, "Sprite zero");
            novo_no->dados_restaurante.prato.preco = 19.90;
            
            insere_restaurante(fila, novo_no->dados_restaurante);

            contador++;
        }
    }

}







int mostra_restaurantes(Fila *fila)
{
    if (fila == NULL) {
        return -1;
    }

    No *aux = fila->inicio;
    printf("\n\n=============== RESTAURANTES DISPONIVEIS ===============\n");
    while (aux != NULL) {
        printf("\nRestaurante: [%s]", aux->dados_restaurante.nome);
        printf("\nTipo culinario: [%s]", aux->dados_restaurante.tipo_culinaria);
        printf("\nPrato: [%s]", aux->dados_restaurante.prato.nome);
        printf("\nBebida: [%s]", aux->dados_restaurante.prato.bebida);
        printf("\nPreco: [R$%.2f]", aux->dados_restaurante.prato.preco);
        printf("\n\n");
        aux = aux->prox;
    }

    return 0;
}