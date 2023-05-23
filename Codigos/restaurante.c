#include "restaurante.h"
#include "usuario.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>




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
                ; // o ponto e virgula é necessário para o switch funcionar
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

    return 0;
}



int insere_restaurantes_cadastrados(Fila *fila, Restaurante r)
{
    if (fila == NULL)
        return -1;

    // primeiro restaurante
    strcpy(r.nome, "Delicias BaRUka");
    r.tipo_culinaria = 1;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Frango Xadrez");
    strcpy(r.prato[0].bebida, "Suco de jiloh");
    r.prato[0].preco = 3;

    strcpy(r.prato[1].nome, "Lagarto ao Molho Madeira");
    strcpy(r.prato[1].bebida, "Suco de Quiabo");
    r.prato[1].preco = 3;
    
    
    strcpy(r.prato[2].nome, "Vaca Atolada");
    strcpy(r.prato[2].bebida, "Suco de Cenoura");
    r.prato[2].preco = 3;

    strcpy(r.prato[3].nome, "Arroz Carreteiro");
    strcpy(r.prato[3].bebida, "Suco de Beterraba");
    r.prato[3].preco = 3;

    strcpy(r.prato[4].nome, "Carne Moida com Cenoura");
    strcpy(r.prato[4].bebida, "Suco de Couve");
    r.prato[4].preco = 3;

    insere_restaurante(fila, r);

    // segundo restaurante
    strcpy(r.nome, "Subway");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Baratissimo");
    strcpy(r.prato[0].bebida, "Sprite zero");
    r.prato[0].preco = 11.90;

    strcpy(r.prato[1].nome, "Steak Churrasco");
    strcpy(r.prato[1].bebida, "Coca cola");
    r.prato[1].preco = 20.90;

    
    strcpy(r.prato[2].nome, "Barato do Dia");
    strcpy(r.prato[2].bebida, "Fanta Uva");
    r.prato[2].preco = 13.90;

    strcpy(r.prato[3].nome, "Sub da Quebrada");
    strcpy(r.prato[3].bebida, "Pepsi");
    r.prato[3].preco = 15.50;

    strcpy(r.prato[4].nome, "Carne Supreme");
    strcpy(r.prato[4].bebida, "Guarana Antartica");
    r.prato[4].preco = 25.50;

    insere_restaurante(fila, r);


    // terceiro restaurante
    strcpy(r.nome, "Pizza Hut");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Pepperoni Pizza");
    strcpy(r.prato[0].bebida, "Coca cola");
    r.prato[0].preco = 50.90;

    strcpy(r.prato[1].nome, "Margherita Pizza");
    strcpy(r.prato[1].bebida, "Sprite");
    r.prato[1].preco = 69.90;

    
    strcpy(r.prato[2].nome, "Hawaiian Pizza");
    strcpy(r.prato[2].bebida, "Fanta Uva");
    r.prato[2].preco = 49.90;

    strcpy(r.prato[3].nome, "Mussarella com Calabresa");
    strcpy(r.prato[3].bebida, "Pepsi");
    r.prato[3].preco = 48.80;

    strcpy(r.prato[4].nome, "Portuguesa");
    strcpy(r.prato[4].bebida, "Guarana Antartica");
    r.prato[4].preco = 45.50;

    insere_restaurante(fila, r);

    // quarto restaurante
    strcpy(r.nome, "Burger King");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Whopper");
    strcpy(r.prato[0].bebida, "Coca cola");
    r.prato[0].preco = 17.90;

    strcpy(r.prato[1].nome, "Chicken Royale");
    strcpy(r.prato[1].bebida, "Sprite");
    r.prato[1].preco = 15.50;

    
    strcpy(r.prato[2].nome, "Cheddar Duplo");
    strcpy(r.prato[2].bebida, "Fanta Uva");
    r.prato[2].preco = 19.90;

    strcpy(r.prato[3].nome, "Big King");
    strcpy(r.prato[3].bebida, "Pepsi");
    r.prato[3].preco = 18.80;

    strcpy(r.prato[4].nome, "Rodeio Burguer");
    strcpy(r.prato[4].bebida, "Guarana Antartica");
    r.prato[4].preco = 20.50;

    insere_restaurante(fila, r);

    // quinto restaurante
    strcpy(r.nome, "Sushi House");
    r.tipo_culinaria = 3;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Sashimi Moriawase");
    strcpy(r.prato[0].bebida, "Chá verde");
    r.prato[0].preco = 45.90;

    strcpy(r.prato[1].nome, "Sushi Nigiri");
    strcpy(r.prato[1].bebida, "Saquê");
    r.prato[1].preco = 42.50;

   
    strcpy(r.prato[2].nome, "Temaki");
    strcpy(r.prato[2].bebida, "Coca cola");
    r.prato[2].preco = 40.5;

    strcpy(r.prato[3].nome, "Uramaki");
    strcpy(r.prato[3].bebida, "Sprite");
    r.prato[3].preco = 51.5;

    strcpy(r.prato[4].nome, "Hossomaki");
    strcpy(r.prato[4].bebida, "Fanta Uva");
    r.prato[4].preco = 59.90;

    insere_restaurante(fila, r);

    return 0;
}









void mostra_restaurantes(Fila *fila)
{
    if (fila == NULL) return;

    No *aux = fila->inicio;
    int i = 1;
    int nome_length;

    printf("\n\n=============== RESTAURANTES DISPONIVEIS ===============\n\n");

    while (aux != NULL) {
        // Converter o nome do restaurante para letras maiúsculas
        char nome_restaurante_upper[50];
        strcpy(nome_restaurante_upper, aux->dados_restaurante.nome);
        for (int j = 0; nome_restaurante_upper[j] != '\0'; j++) {
            nome_restaurante_upper[j] = toupper(nome_restaurante_upper[j]);
        }

        // Centralizar o nome do restaurante
        nome_length = strlen(nome_restaurante_upper);
        int espacos_antes = (50 - nome_length) / 2;
        int espacos_depois = 50 - nome_length - espacos_antes;
        printf("%*s%s%*s\n\n", espacos_antes, "", nome_restaurante_upper, espacos_depois, "");

        printf("-> CATEGORIA: ");
        if (aux->dados_restaurante.tipo_culinaria == 1) printf("[BRASILEIRA]\n");
        else if (aux->dados_restaurante.tipo_culinaria == 2) printf("[FAST FOOD]\n");
        else if (aux->dados_restaurante.tipo_culinaria == 3) printf("[JAPONESA]\n");

        printf("-> PRATOS DISPONIVEIS:\n\n");

        for (i = 0; i < aux->dados_restaurante.qtd_pratos; i++) {
            printf("Combo %d:\n", i + 1);
            printf("- Prato: %s\n", aux->dados_restaurante.prato[i].nome);
            printf("- Acompanhamento: %s\n", aux->dados_restaurante.prato[i].bebida);
            printf("- Preco: R$%.2f\n", aux->dados_restaurante.prato[i].preco);
            printf("\n");
            sleep(1);
        }

        printf("\n");
        aux = aux->prox;
        sleep(1); 
    }

    printf("\n");
}


