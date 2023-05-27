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



typedef struct lista {
    No *inicio;
    No *fim;
    int tam_lista;

} Lista_restaurante;





Lista_restaurante *criar_restaurante()
{
    Lista_restaurante *lista = (Lista_restaurante *) calloc(1, sizeof(Lista_restaurante));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam_lista = 0;

    return lista;
}





int limpar_lista(Lista_restaurante *lista)
{
    if (lista == NULL) {
        return -1;
    }

    No *aux = lista->inicio;
    while (aux != NULL) {
        No *proximo = aux->prox;
        free(aux);
        aux = proximo;
        aux = NULL;
    }

    lista->inicio = NULL;
    free(lista);

    return 0;
}






// agora, iremos fazer uma função para inserir um restaurante na lista
int insere_restaurante_no_final(Lista_restaurante *lista, Restaurante r)
{
    if (lista == NULL) {
        return -1;
    }

    No *novo_no = (No*) malloc(sizeof(No));
    novo_no->dados_restaurante = r;
    novo_no->prox = NULL;

    if (lista_vazia(lista)) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        lista->fim->prox = novo_no;
        lista->fim = novo_no;
    }

    lista->tam_lista++;

    return 0;
}




int remove_restaurante_inicio(Lista_restaurante *lista, Restaurante *r)
{
    if (lista == NULL || lista_vazia(lista)) {
        return -1;
    }

    No *aux = lista->inicio;
    lista->inicio = lista->inicio->prox;
    *r = aux->dados_restaurante;
    free(aux);

    lista->tam_lista--;

    return 0;
}





int insere_restaurante_no_inicio(Lista_restaurante *lista, Restaurante r)
{
    if (lista == NULL) 
        return -1;

    No *novo_no = (No*) calloc(1, sizeof(No));
    novo_no->dados_restaurante = r;
    novo_no->prox = lista->inicio;
    lista->inicio = novo_no;

    if (lista->fim == NULL) {
        lista->fim = novo_no;
    }

    lista->tam_lista++;

    return 0;
}



int insere_restaurante_pos(Lista_restaurante *lista, Restaurante r, int pos)
{
    if (lista == NULL || pos <= 0 || pos > lista->tam_lista + 1) 
        return -1;
    
    if (pos == 1) 
        return insere_restaurante_no_inicio(lista, r);
    else if (pos == lista->tam_lista + 1) 
        return insere_restaurante_no_final(lista, r);

    No *novo_no = (No*) calloc(1, sizeof(No));
    novo_no->dados_restaurante = r;

    No *aux = lista->inicio;
    int cont = 1;
    while (cont < pos - 1) {
        aux = aux->prox;
        cont++;
    }

    novo_no->prox = aux->prox;
    aux->prox = novo_no;

    lista->tam_lista++;

    return 0;
}




int remove_restaurante_final(Lista_restaurante *lista, Restaurante *r)
{
    if (lista == NULL || lista_vazia(lista)) {
        return -1;
    }

    No *aux = lista->inicio;
    No *anterior = NULL;

    while (aux->prox != NULL) {
        anterior = aux;
        aux = aux->prox;
    }

    if (anterior == NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
    } else {
        anterior->prox = NULL;
        lista->fim = anterior;
    }

    *r = aux->dados_restaurante;
    free(aux);

    lista->tam_lista--;

    return 0;
    
}





int remove_restaurante_pos(Lista_restaurante *lista, Restaurante *r, int pos)
{
    if (lista == NULL || lista_vazia(lista) || pos <= 0 || pos > lista->tam_lista) 
        return -1;
    
    if (pos == 1) 
        return remove_restaurante_inicio(lista, r);
    else if (pos == lista->tam_lista) 
        return remove_restaurante_final(lista, r);
    
    No *aux = lista->inicio;
    No *anterior = NULL;

    int i = 1;
    while (i < pos) {
        anterior = aux;
        aux = aux->prox;
        i++;
    }

    anterior->prox = aux->prox;
    *r = aux->dados_restaurante;
    free(aux);

    lista->tam_lista--;

    return 0;
}




int cadastrar_restaurante(Lista_restaurante *lista, Restaurante *restaurante, int pos_cadastro) 
{
    if (lista == NULL || restaurante == NULL) 
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
                // linha abaixo usada para que o fgets não deixe o \n no final da string e atrapalhe a impressão da lista
                novo_no->dados_restaurante.nome[strcspn(novo_no->dados_restaurante.nome, "\n")] = '\0';
                sleep(0.5);
                printf("Informe a categoria do restaurante:\n");
                sleep(0.5);
                printf("\n[1] - Brasileira");
                sleep(0.5);
                printf("\n[2] - Fast Food");
                sleep(0.5);
                printf("\n[3] - Japonesa\n\n");
                sleep(0.5);
                printf("Categoria: ");
                scanf("%d", &novo_no->dados_restaurante.tipo_culinaria);
                getchar();

                sleep(0.5);
                printf("Informe a quantidade de pratos: ");
                scanf("%d", &novo_no->dados_restaurante.qtd_pratos);

                novo_no->dados_restaurante.prato = (Prato*) malloc(novo_no->dados_restaurante.qtd_pratos * sizeof(Prato));

                for (i = 0; i < novo_no->dados_restaurante.qtd_pratos; i++) {
                    getchar();
                    printf("\nInforme o nome do [%do] prato: ", i + 1);
                    fgets(novo_no->dados_restaurante.prato[i].nome, sizeof(novo_no->dados_restaurante.prato[i].nome), stdin);
                    sleep(0.5);
                    printf("Informe o nome da [%da] bebida que acompanha: ", i + 1);
                    fgets(novo_no->dados_restaurante.prato[i].bebida, sizeof(novo_no->dados_restaurante.prato[i].bebida), stdin);
                    sleep(0.5);
                    printf("Informe o preco do [%do] prato: ", i + 1);
                    scanf("%f", &novo_no->dados_restaurante.prato[i].preco);
                    sleep(0.5);
                    printf("\n");
                }

                insere_restaurante_pos(lista, novo_no->dados_restaurante, pos_cadastro);
                break;

            case 2:
                break;

            default:
                printf("Opcao invalida! Tente Novamente.\n\n");
                sleep(1);
        }

    } while (opcao != 2);

    lista->tam_lista++;

    return 0;
}






int insere_restaurantes_cadastrados(Lista_restaurante *lista, Restaurante r)
{
    if (lista == NULL)
        return -1;

    // primeiro restaurante
    strcpy(r.nome, "DELICIAS BARUKA");
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

    insere_restaurante_no_final(lista, r);

    // segundo restaurante
    strcpy(r.nome, "SUBWAY");
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

    insere_restaurante_no_final(lista, r);


    // terceiro restaurante
    strcpy(r.nome, "PIZZA HUT");
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

    insere_restaurante_no_final(lista, r);

    // quarto restaurante
    strcpy(r.nome, "ACAI CASEIRO");
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

    insere_restaurante_no_final(lista, r);

    // quinto restaurante
    strcpy(r.nome, "SUSHI HOUSE");
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

    insere_restaurante_no_final(lista, r);

    lista->tam_lista = 5;

    return 0;
}






void mostrar_restaurantes(Lista_restaurante *lista) 
{
    if (lista == NULL)
        return;

    No *aux = lista->inicio;
    int i = 1;

    const char headerMessage[] = "\n\n=============== RESTAURANTES DISPONIVEIS ===============\n\n";
    printLetterByLetter(headerMessage, 0.1);

    for (; aux != NULL; aux = aux->prox, i++) {
        printf("%d -> [", i);
        fflush(stdout);

        char *restauranteNome = aux->dados_restaurante.nome;

        // Converter os caracteres para maiúsculas
        for (int j = 0; restauranteNome[j] != '\0'; j++) {
            restauranteNome[j] = toupper(restauranteNome[j]);
        }

        printLetterByLetter(restauranteNome, 0.1);

        printf("]\n");
        sleep(0.3);
    }
}





void printLetterByLetter(const char* message, float seconds) 
{
    for (int i = 0; message[i] != '\0'; i++) {
        putchar(message[i]);
        fflush(stdout);
        sleep(seconds);
    }
}





void menu_restaurante(Lista_restaurante *lista) 
{
    if (lista == NULL)
        return;

    mostrar_restaurantes(lista);

    int opcao_numero;

    printf("\n");
    do {
        printf("Escolha um restaurante (1-%d): ", lista->tam_lista);
        fflush(stdout);
        scanf("%d", &opcao_numero);
        if (opcao_numero < 1 || opcao_numero > lista->tam_lista)
            printLetterByLetter("\nCALMA LA AMIGAO. DIGITE UMA OPCAO VALIDA!!!\n\n", 0.05);
    } while (opcao_numero < 1 || opcao_numero > lista->tam_lista);

    No *aux = lista->inicio;
    int i = 1;

    for (; aux != NULL; aux = aux->prox, i++) {
        if (i == opcao_numero)
        {
            const char headerMessage[] = "\n\n================= PRATOS DISPONIVEIS =================\n\n";
            printLetterByLetter(headerMessage, 0.1);

            printf("-> CATEGORIA: ");
            fflush(stdout);

            if (aux->dados_restaurante.tipo_culinaria == 1)
                printLetterByLetter("[BRASILEIRA]\n", 0.1);
            else if (aux->dados_restaurante.tipo_culinaria == 2)
                printLetterByLetter("[FAST FOOD]\n", 0.1);
            else if (aux->dados_restaurante.tipo_culinaria == 3)
                printLetterByLetter("[JAPONESA]\n", 0.1);

            printLetterByLetter("-> PRATOS DISPONIVEIS:\n\n", 0.1);
            

            for (int j = 0; j < aux->dados_restaurante.qtd_pratos; j++) {
                printf("Combo %d:\n", j + 1);
                printLetterByLetter("- Prato: ", 0.1);
                fflush(stdout);

                const char *pratoNome = aux->dados_restaurante.prato[j].nome;
                printLetterByLetter(pratoNome, 0.1);

                printf("\n");
                sleep(0.5);

                printLetterByLetter("- Acompanhamento: ", 0.1);
                fflush(stdout);

                const char *acompanhamento = aux->dados_restaurante.prato[j].bebida;
                printLetterByLetter(acompanhamento, 0.1);

                printf("\n");

                printLetterByLetter("- Preco: ", 0.1);
                fflush(stdout);
                printf("R$%.2f\n", aux->dados_restaurante.prato[j].preco);

                printf("\n");
            }
       }
    }
}
