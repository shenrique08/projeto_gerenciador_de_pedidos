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

    No *novo_no = (No*) malloc(sizeof(No));
    novo_no->dados_restaurante = r;
    novo_no->prox = NULL;

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

int cadastrar_restaurante(Fila *fila, Restaurante restaurante) {
    
    if (fila == NULL) {
        return -1;
    }

    int opcao;
    int i;

    printf("\n=============== SISTEMA DE CADASTRO DE RESTAURANTES ===============\n");

    do {

        printf("[1] Cadastrar novo restaurante\n");
        printf("[2] Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                No *novo_no = (No*) malloc(sizeof(No));
                novo_no->dados_restaurante = restaurante;

                printf("\nInforme o nome do restaurante: ");
                fgets(novo_no->dados_restaurante.nome, sizeof(novo_no->dados_restaurante.nome), stdin);

                printf("Informe a categoria do restaurante:\n");
                printf("\n[1] - Brasileira");
                printf("\n[2] - Fast Food");
                printf("\n[3] - Japonesa\n");
                printf("Categoria: ");
                // guardar em int tipo_culinaria na struct restaurante
                scanf("%d", &novo_no->dados_restaurante.tipo_culinaria);
                getchar();

                printf("Informe a quantidade de pratos: ");
                scanf("%d", &novo_no->dados_restaurante.qtd_pratos);

                novo_no->dados_restaurante.prato = (Prato*) malloc(novo_no->dados_restaurante.qtd_pratos * sizeof(Prato));
                
                for (i = 0; i < novo_no->dados_restaurante.qtd_pratos; i++) {
                    getchar();
                    printf("Informe o nome do prato: ");
                    fgets(novo_no->dados_restaurante.prato[i].nome, sizeof(novo_no->dados_restaurante.prato[i].nome), stdin);
                    printf("Informe o nome da bebida que acompanha: ");
                    fgets(novo_no->dados_restaurante.prato[i].bebida, sizeof(novo_no->dados_restaurante.prato[i].bebida), stdin);
                    printf("Informe o preco do prato: ");
                    scanf("%f", &novo_no->dados_restaurante.prato[i].preco);
                }

                insere_restaurante(fila, novo_no->dados_restaurante);
                break;

            case 2:
                break;

            default:
                printf("Opcao invalida!");
            
        }

    } while (opcao != 2);

}





// função que "simula uma base de dados de restaurantes", para que, inicialmente, o usuário tenha acesso a vários restaurantes previamente disponíveis
/*int insere_restaurantes_cadastrados(Fila *fila, Restaurante restaurante)
{
    if (fila->inicio != NULL) {
        int contador = 0;
        while (contador < 1) 
        {
            No *novo_no = (No*) malloc(sizeof(No));
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

}*/

int insere_restaurantes_cadastrados(Fila *fila, Restaurante r)
{
    if (fila == NULL)
        return -1;

    r.prato = (Prato*) malloc(r.qtd_pratos * sizeof(Prato));

    strcpy(r.nome, "Subway");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 2;
    
    strcpy(r.prato[0].nome, "Baratissimo");
    strcpy(r.prato[0].bebida, "Sprite zero");
    r.prato[0].preco = 9.90;

    strcpy(r.prato[1].nome, "Carissimo");
    strcpy(r.prato[1].bebida, "Coca cola");
    r.prato[1].preco = 29.90;

    insere_restaurante(fila, r);

    return 0;
}

void mostra_restaurantes(Fila *fila){
    if (fila == NULL) return;

    No *aux = fila->inicio;
    int i = 1;
    printf("\n\n=============== RESTAURANTES DISPONIVEIS ===============\n");

    while (aux != NULL){
        printf("%d - %s\n", i, aux->dados_restaurante.nome);
        printf("Categoria:");
        if (aux->dados_restaurante.tipo_culinaria == 1) printf(" Brasileira\n");
        else if (aux->dados_restaurante.tipo_culinaria == 2) printf(" Fast Food\n");
        else if (aux->dados_restaurante.tipo_culinaria == 3) printf(" Japonesa\n");

        printf("Pratos disponiveis:\n");
        for (i = 0; i < aux->dados_restaurante.qtd_pratos; i++) {
            printf("Combo %d:\n", i+1);
            printf("- Prato: %s\n", aux->dados_restaurante.prato[i].nome);
            printf("- Acompanhamento: %s\n", aux->dados_restaurante.prato[i].bebida);
            printf("- Preco: R$%.2f\n", aux->dados_restaurante.prato[i].preco);
            printf("\n");
        }
        printf("\n");
        aux = aux->prox;
    }
    printf("\n\n");
}

