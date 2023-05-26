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


int remove_restaurante(Fila *fila, Restaurante *r)
{
    if (fila == NULL || fila_vazia(fila)) {
        return -1;
    }

    No *aux = fila->inicio;
    fila->inicio = fila->inicio->prox;
    *r = aux->dados_restaurante;
    free(aux);

    fila->tam_fila--;

    return 0;
}



int cadastrar_restaurante(Fila *fila, Restaurante *restaurante) {
    if (fila == NULL || restaurante == NULL) 
        return -1;

    int opcao;
    int i;

    printf("\n=============== SISTEMA DE CADASTRO DE RESTAURANTES ===============\n");

    do {
        printf("[1] Cadastrar novo restaurante\n");
        printf("[2] Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao == 2) break;

        switch (opcao) {
            case 1:;
                No *novo_no = (No*) calloc(1, sizeof(No));
                novo_no->dados_restaurante = *restaurante;

                printf("\nInforme o nome do restaurante: ");
                fgets(novo_no->dados_restaurante.nome, sizeof(novo_no->dados_restaurante.nome), stdin);

                printf("Informe a categoria do restaurante:\n");
                printf("\n[1] - Brasileira");
                printf("\n[2] - Fast Food");
                printf("\n[3] - Japonesa\n\n");
                printf("Categoria: ");
                scanf("%d", &novo_no->dados_restaurante.tipo_culinaria);
                getchar();

                printf("Informe a quantidade de pratos: ");
                scanf("%d", &novo_no->dados_restaurante.qtd_pratos);

                novo_no->dados_restaurante.prato = (Prato*) malloc(novo_no->dados_restaurante.qtd_pratos * sizeof(Prato));

                for (i = 0; i < novo_no->dados_restaurante.qtd_pratos; i++) {
                    getchar();
                    printf("Informe o nome do [%do] prato: ", i + 1);
                    fgets(novo_no->dados_restaurante.prato[i].nome, sizeof(novo_no->dados_restaurante.prato[i].nome), stdin);
                    printf("Informe o nome da [%da] bebida que acompanha: ", i + 1);
                    fgets(novo_no->dados_restaurante.prato[i].bebida, sizeof(novo_no->dados_restaurante.prato[i].bebida), stdin);
                    printf("Informe o preco do [%do] prato: ", i + 1);
                    scanf("%f", &novo_no->dados_restaurante.prato[i].preco);
                    printf("\n");
                }

                insere_restaurante(fila, novo_no->dados_restaurante);
                break;

            case 2:
                break;

            default:
                printf("Opcao invalida! Tente Novamente.\n\n");
        }

    } while (opcao != 2);

    fila->tam_fila++;

    return 0;
}






int insere_restaurantes_cadastrados(Fila *fila, Restaurante r)
{
    if (fila == NULL)
        return -1;

    // primeiro restaurante
    strcpy(r.nome, "[DELICIAS BARUKA]");
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
    strcpy(r.nome, "[SUBWAY]");
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
    strcpy(r.nome, "[PIZZA HUT]");
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
    strcpy(r.nome, "[ACAI CASEIRO]");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Acai 300ml");
    strcpy(r.prato[0].bebida, "Banana e Morango");
    r.prato[0].preco = 15.00;

    strcpy(r.prato[1].nome, "Acai 500ml");
    strcpy(r.prato[1].bebida, "Leite em Po");
    r.prato[1].preco = 20.00;

    
    strcpy(r.prato[2].nome, "Acai 700ml");
    strcpy(r.prato[2].bebida, "Granola e Leite em Po");
    r.prato[2].preco = 24.00;

    strcpy(r.prato[3].nome, "Acai 1L");
    strcpy(r.prato[3].bebida, "Granola, Leite em Po e Morango");
    r.prato[3].preco = 30.00;

    strcpy(r.prato[4].nome, "Barca de Acai");
    strcpy(r.prato[4].bebida, "Granola, Leite em Po, Morango e Banana");
    r.prato[4].preco = 40.00;

    insere_restaurante(fila, r);

    // quinto restaurante
    strcpy(r.nome, "[SUSHI HOUSE]");
    r.tipo_culinaria = 3;
    r.qtd_pratos = 5; 

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Sashimi Moriawase");
    strcpy(r.prato[0].bebida, "Cha verde");
    r.prato[0].preco = 45.90;

    strcpy(r.prato[1].nome, "Sushi Nigiri");
    strcpy(r.prato[1].bebida, "Saque");
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

    fila->tam_fila = 5;

    return 0;
}




void mostrar_restaurantes(Fila *fila)
{
    if (fila == NULL)
        return;

    No *aux = fila->inicio;
    int i = 1;

    printf("\n\n=============== RESTAURANTES DISPONIVEIS ===============\n\n");
    sleep(0.3);

    for (; aux != NULL; aux = aux->prox, i++) {
        // Imprimir índice e nome do restaurante
        printf("%d -> ", i);
        fflush(stdout); // Limpa o buffer de saída

        // Imprimir o nome do restaurante letra por letra
        for (int j = 0; aux->dados_restaurante.nome[j] != '\0'; j++) {
            printf("%c", aux->dados_restaurante.nome[j]);
            fflush(stdout);
            sleep(0.1);
        }

        printf("\n");
        sleep(0.3);
    }
}








void menu_restaurante(Fila *fila)
{
    if (fila == NULL)
        return;

    No *aux = fila->inicio;
    int i = 1;
    char opcao_restaurante; // Alteração: Mudança de int para char

    printf("\n\n=============== RESTAURANTES DISPONIVEIS ===============\n\n");
    sleep(0.3);

    for (; aux != NULL; aux = aux->prox, i++) {
        // Imprimir índice e nome do restaurante
        printf("%d -> ", i);
        fflush(stdout); // Limpa o buffer de saída

        // Imprimir o nome do restaurante letra por letra
        for (int j = 0; aux->dados_restaurante.nome[j] != '\0'; j++) {
            printf("%c", aux->dados_restaurante.nome[j]);
            fflush(stdout);
            sleep(0.1);
        }

        printf("\n");
        sleep(0.3);
    }

    printf("\n");
    do {
        printf("Escolha um restaurante (1-%d): ", fila->tam_fila);
        fflush(stdout);
        scanf(" %c", &opcao_restaurante); // Alteração: %d para %c e espaço antes de %c
        if (opcao_restaurante < '1' || opcao_restaurante > ('0' + fila->tam_fila)) // Alteração: Comparação com caracteres
            printf("\nCALMA LA AMIGAO. DIGITE UMA OPCAO VALIDA!!!\n\n");
    } while (opcao_restaurante < '1' || opcao_restaurante > ('0' + fila->tam_fila)); // Alteração: Comparação com caracteres

    int opcao_numero = opcao_restaurante - '0'; // Alteração: Conversão de char para int

    aux = fila->inicio;
    i = 1;

    for (; aux != NULL; aux = aux->prox, i++) {
        if (i == opcao_numero) // Alteração: Comparação com int
        {
            printf("\n\n================= PRATOS DISPONIVEIS =================\n\n");
            sleep(0.5);

            printf("-> CATEGORIA: ");
            fflush(stdout);

            if (aux->dados_restaurante.tipo_culinaria == 1)
                printf("[BRASILEIRA]\n");
            else if (aux->dados_restaurante.tipo_culinaria == 2)
                printf("[FAST FOOD]\n");
            else if (aux->dados_restaurante.tipo_culinaria == 3)
                printf("[JAPONESA]\n");

            printf("-> PRATOS DISPONIVEIS:\n\n");
            sleep(0.3);

            for (int j = 0; j < aux->dados_restaurante.qtd_pratos; j++) {
                printf("Combo %d:\n", j + 1);
                sleep(0.5);

                printf("- Prato: ");
                fflush(stdout); // Limpa o buffer de saída

                // Imprimir o nome do prato letra por letra
                for (int k = 0; aux->dados_restaurante.prato[j].nome[k] != '\0'; k++) {
                    printf("%c", aux->dados_restaurante.prato[j].nome[k]);
                    fflush(stdout); // Limpa o buffer de saída
                    sleep(0.1);
                }

                printf("\n");
                sleep(0.5);
                printf("- Acompanhamento: %s\n", aux->dados_restaurante.prato[j].bebida);
                sleep(0.5);
                printf("- Preco: R$%.2f\n", aux->dados_restaurante.prato[j].preco);
                printf("\n");
                sleep(1);
            }

            break;
        }
    }

    printf("\n");
}




