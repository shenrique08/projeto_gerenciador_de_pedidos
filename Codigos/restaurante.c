#include "restaurante.h"
#include "usuario.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>




typedef struct no {
    
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



int qtd_restaurantes(Lista_restaurante *lista)
{
    if (lista == NULL) {
        return -1;
    }

    return lista->tam_lista;
}





// agora, iremos fazer uma função para inserir um restaurante na lista
int insere_restaurante_no_final(Lista_restaurante *lista, Restaurante r)
{
    if (lista == NULL) 
        return -1;
    
    r.fila_pedidos = criar_fila();

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

    novo_no->dados_restaurante.qtd_pratos = r.qtd_pratos;
    lista->tam_lista++;

    return 0;
}




int remove_restaurante_inicio(Lista_restaurante *lista, Restaurante *r)
{
    if (lista == NULL || lista_vazia(lista)) 
        return -1;
    
    No *aux = lista->inicio;
    lista->inicio = lista->inicio->prox;
    *r = aux->dados_restaurante;
    aux->dados_restaurante.qtd_pratos = r->qtd_pratos;
    free(aux);

    lista->tam_lista--;
    
    return 0;
}





int insere_restaurante_no_inicio(Lista_restaurante *lista, Restaurante r)
{
    if (lista == NULL) 
        return -1;
    r.fila_pedidos = criar_fila();

    No *novo_no = (No*) calloc(1, sizeof(No));
    novo_no->dados_restaurante = r;
    novo_no->prox = lista->inicio;
    lista->inicio = novo_no;

    if (lista->fim == NULL) 
        lista->fim = novo_no;
    
    lista->tam_lista++;
    novo_no->dados_restaurante.qtd_pratos = r.qtd_pratos;

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

    aux->dados_restaurante.qtd_pratos = r->qtd_pratos;
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

    aux->dados_restaurante.qtd_pratos = r->qtd_pratos;
    anterior->prox = aux->prox;
    *r = aux->dados_restaurante;
    free(aux);

    lista->tam_lista--;

    return 0;
}





int cadastrar_restaurante(Lista_restaurante *lista, Restaurante *restaurante) 
{
    if (lista == NULL || restaurante == NULL) 
        return -1;

    int opcao;
    int i, qtd_cadastros = 0;

    printf("\n=============== SISTEMA DE CADASTRO DE RESTAURANTES ===============\n");

    do {
        if (qtd_cadastros > 0)
            printf("[1] Cadastrar outro restaurante\n");
        else
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
                printf("Informe o tipo culinario do restaurante:\n");
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
                    printf("\nInforme o nome do [%do] prato: ", i + 1);
                    fgets(novo_no->dados_restaurante.prato[i].nome, sizeof(novo_no->dados_restaurante.prato[i].nome), stdin);
                    novo_no->dados_restaurante.prato[i].nome[strcspn(novo_no->dados_restaurante.prato[i].nome, "\n")] = '\0';
                    // iremos colocar o nome do restaurante em uppercase para facilitar a busca
                    for (int j = 0; novo_no->dados_restaurante.prato[i].nome[j] != '\0'; j++) {
                        novo_no->dados_restaurante.prato[i].nome[j] = toupper(novo_no->dados_restaurante.prato[i].nome[j]);
                    }

                    printf("Informe o nome da [%da] bebida que acompanha: ", i + 1);
                    fgets(novo_no->dados_restaurante.prato[i].bebida, sizeof(novo_no->dados_restaurante.prato[i].bebida), stdin);
                    novo_no->dados_restaurante.prato[i].bebida[strcspn(novo_no->dados_restaurante.prato[i].bebida, "\n")] = '\0';
                    printf("Informe o preco do [%do] prato: R$", i + 1);
                    scanf("%f", &novo_no->dados_restaurante.prato[i].preco);
                }

                insere_restaurante_no_final(lista, novo_no->dados_restaurante);
                qtd_cadastros++;
                break;

            case 2:
                break;

            default:
                printf("Opcao invalida! Tente Novamente.\n\n");
                sleep(1);
        }

    } while (opcao != 2);

    return 0;
}





int buscar_restaurante(Lista_restaurante *lista, Restaurante *restaurante, char *nome_restaurante)
{
    if (lista == NULL || restaurante == NULL || lista_vazia(lista)) 
        return -1;

    No *aux = lista->inicio;
    // precisamos verificar o nome sem contar as letras maiusculas e minusculas
    for (int i = 0; nome_restaurante[i] != '\0'; i++) {
        nome_restaurante[i] = toupper(nome_restaurante[i]);
    }
    
    while (aux != NULL) {
        if (strcmp(aux->dados_restaurante.nome, nome_restaurante) == 0) 
        {
            restaurante->qtd_pratos = aux->dados_restaurante.qtd_pratos;
            restaurante->prato = (Prato*) calloc(restaurante->qtd_pratos, sizeof(Prato));
            *restaurante = aux->dados_restaurante;
            return 1;
        }
        aux = aux->prox;
    }

    return 0;
}






int buscar_prato_principal(Lista_restaurante *lista, char *nome_prato, Prato *prato_escolhido)
{
    if (lista == NULL || lista->tam_lista == 0)
        return -1;

    No *aux = lista->inicio;

    // Convertendo o nome do prato para maiúsculas
    for (int i = 0; nome_prato[i] != '\0'; i++) {
        nome_prato[i] = toupper((unsigned char)nome_prato[i]);
    }

    while (aux != NULL) {
        for (int i = 0; i < aux->dados_restaurante.qtd_pratos; i++) {
            // Convertendo o nome do prato atual para maiúsculas
            char prato_atual_upper[50];
            strcpy(prato_atual_upper, aux->dados_restaurante.prato[i].nome);
            for (int j = 0; prato_atual_upper[j] != '\0'; j++) {
                prato_atual_upper[j] = toupper((unsigned char)prato_atual_upper[j]);
            }

            if (strcmp(prato_atual_upper, nome_prato) == 0) {
                *prato_escolhido = aux->dados_restaurante.prato[i];
                return 1;
            }
        }
        aux = aux->prox;
    }

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

    // sexto restaurante
    strcpy(r.nome, "MADERO");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 3;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Madero Burger");
    strcpy(r.prato[0].bebida, "Coca cola");
    r.prato[0].preco = 45.90;

    strcpy(r.prato[1].nome, "Madero Veggie");
    strcpy(r.prato[1].bebida, "Sprite");
    r.prato[1].preco = 42.50;

    strcpy(r.prato[2].nome, "Madero Bacon Super");
    strcpy(r.prato[2].bebida, "Fanta Uva");
    r.prato[2].preco = 59.90;

    insere_restaurante_no_final(lista, r);

    // sétimo restaurante
    strcpy(r.nome, "Comida Mineira");
    r.tipo_culinaria = 1;
    r.qtd_pratos = 4;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Feijao Tropeiro");
    strcpy(r.prato[0].bebida, "Coca cola");
    r.prato[0].preco = 45.90;

    strcpy(r.prato[1].nome, "Frango com Quiabo");
    strcpy(r.prato[1].bebida, "Sprite");
    r.prato[1].preco = 42.50;

    strcpy(r.prato[2].nome, "Feijoada");
    strcpy(r.prato[2].bebida, "Suco de Laranja");
    r.prato[2].preco = 59.90;

    strcpy(r.prato[3].nome, "Tutu de Feijao");
    strcpy(r.prato[3].bebida, "Pepsi");
    r.prato[3].preco = 55.90;

    insere_restaurante_no_final(lista, r);

    // oitavo restaurante
    strcpy(r.nome, "Sorveteria Gelato");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 5;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Napolitano");
    strcpy(r.prato[0].bebida, "Nutella");
    r.prato[0].preco = 15.90;

    strcpy(r.prato[1].nome, "Chocolate");
    strcpy(r.prato[1].bebida, "Leite condensado");
    r.prato[1].preco = 12.50;

    strcpy(r.prato[2].nome, "Morango");
    strcpy(r.prato[2].bebida, "Leite Ninho");
    r.prato[2].preco = 14.90;

    strcpy(r.prato[3].nome, "Creme");
    strcpy(r.prato[3].bebida, "Paçoca");
    r.prato[3].preco = 12.90;

    strcpy(r.prato[4].nome, "Limao");
    strcpy(r.prato[4].bebida, "Ovomaltine");
    r.prato[4].preco = 12.90;

    insere_restaurante_no_final(lista, r);

    // nono restaurante

    strcpy(r.nome, "Burritos");
    r.tipo_culinaria = 2;
    r.qtd_pratos = 3;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Burritos de Frango");
    strcpy(r.prato[0].bebida, "Coca cola");
    r.prato[0].preco = 37.90;

    strcpy(r.prato[1].nome, "Burritos de Carne");
    strcpy(r.prato[1].bebida, "Sprite");
    r.prato[1].preco = 42.50;

    strcpy(r.prato[2].nome, "Burritos de Queijo");
    strcpy(r.prato[2].bebida, "Fanta Uva");
    r.prato[2].preco = 39.90;

    insere_restaurante_no_final(lista, r);

    // décimo restaurante
    strcpy(r.nome, "Casa do Pao de Queijo");
    r.tipo_culinaria = 1;
    r.qtd_pratos = 4;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Pao de Queijo Tradicional");
    strcpy(r.prato[0].bebida, "Cafe");
    r.prato[0].preco = 5.90;

    strcpy(r.prato[1].nome, "Pao de Queijo com Requeijao");
    strcpy(r.prato[1].bebida, "Cafe com Leite");
    r.prato[1].preco = 7.50;

    strcpy(r.prato[2].nome, "Pao de Queijo com Presunto e Queijo");
    strcpy(r.prato[2].bebida, "Cappuccino");
    r.prato[2].preco = 9.90;

    strcpy(r.prato[3].nome, "Pao de Queijo com Calabresa");
    strcpy(r.prato[3].bebida, "Chocolate Quente");
    r.prato[3].preco = 9.90;

    insere_restaurante_no_final(lista, r);

    // décimo primeiro restaurante
    strcpy(r.nome, "Casa do Bolo");
    r.tipo_culinaria = 1;
    r.qtd_pratos = 3;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Bolo de Chocolate");
    strcpy(r.prato[0].bebida, "Leite Caramelado");
    r.prato[0].preco = 15.90;

    strcpy(r.prato[1].nome, "Bolo de Cenoura");
    strcpy(r.prato[1].bebida, "Cafe com Leite");
    r.prato[1].preco = 12.50;

    strcpy(r.prato[2].nome, "Bolo de Milho");
    strcpy(r.prato[2].bebida, "Cappuccino");
    r.prato[2].preco = 14.90;

    insere_restaurante_no_final(lista, r);

    // décimo segundo restaurante

    strcpy(r.nome, "China in Box");
    r.tipo_culinaria = 3;
    r.qtd_pratos = 4;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Yakissoba Tradicional");
    strcpy(r.prato[0].bebida, "Coca Zero");
    r.prato[0].preco = 37.90;

    strcpy(r.prato[1].nome, "Yakissoba de Frango");
    strcpy(r.prato[1].bebida, "Fanta Laranja");
    r.prato[1].preco = 42.50;

    strcpy(r.prato[2].nome, "Yakissoba de Carne");
    strcpy(r.prato[2].bebida, "Fanta Uva");
    r.prato[2].preco = 39.90;

    strcpy(r.prato[3].nome, "Yakissoba de Camarao");
    strcpy(r.prato[3].bebida, "Suco natural de Laranja");
    r.prato[3].preco = 42.50;

    insere_restaurante_no_final(lista, r);

    // décimo terceiro restaurante

    strcpy(r.nome, "Temakeria e Cia");
    r.tipo_culinaria = 3;
    r.qtd_pratos = 4;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Temaki de Salmao");
    strcpy(r.prato[0].bebida, "Cha Gelado");
    r.prato[0].preco = 37.90;

    strcpy(r.prato[1].nome, "Temaki de Atum");
    strcpy(r.prato[1].bebida, "Cha de Limao");
    r.prato[1].preco = 42.50;

    strcpy(r.prato[2].nome, "Temaki de Camarao");
    strcpy(r.prato[2].bebida, "Cha de Hibisco");
    r.prato[2].preco = 39.90;

    strcpy(r.prato[3].nome, "Temaki de Kani");
    strcpy(r.prato[3].bebida, "Cha de Erva Doce");
    r.prato[3].preco = 42.50;

    insere_restaurante_no_final(lista, r);

    // décimo quarto restaurante

    strcpy(r.nome, "Coco Bambu");
    r.tipo_culinaria = 1;
    r.qtd_pratos = 3;

    r.prato = (Prato*) calloc(r.qtd_pratos, sizeof(Prato));

    strcpy(r.prato[0].nome, "Camarao Internacional");
    strcpy(r.prato[0].bebida, "Caipirinha");
    r.prato[0].preco = 89.90;

    strcpy(r.prato[1].nome, "Muqueca de Camarao");
    strcpy(r.prato[1].bebida, "Mojito");
    r.prato[1].preco = 79.90;

    strcpy(r.prato[2].nome, "Polvo ao Coco Bambu");
    strcpy(r.prato[2].bebida, "Caipiroska");
    r.prato[2].preco = 89.90;

    insere_restaurante_no_final(lista, r);


    return 0;
}






void menu_restaurantes_adm(Lista_restaurante *lista) 
{
    if (lista == NULL)
        return;

    int opcao_restaurante;
    char opcao, ver_pratos;
    int i;

    while (1) {
        No *aux = lista->inicio;
        i = 1;

        // primeiro, iremos mostrar todos os restaurantes cadastrados
        printLetterByLetter("\n\n================= RESTAURANTES =================\n\n", 0.02);
        while (aux != NULL) {
            // Converter o nome para letras maiúsculas
            for (int j = 0; aux->dados_restaurante.nome[j] != '\0'; j++) 
                aux->dados_restaurante.nome[j] = toupper(aux->dados_restaurante.nome[j]);
            
            printf("%d. ", i);
            printf("[");
            printLetterByLetter(aux->dados_restaurante.nome, 0.05); 
            printf("]\n");
            sleep(0.2);

            aux = aux->prox;
            i++;
        }

        do {
            printf("\nDeseja ver os pratos de algum restaurante? (S/N): ");
            fflush(stdout);
            scanf(" %c", &ver_pratos);
            getchar();
            if (ver_pratos != 'S' && ver_pratos != 's' && ver_pratos != 'N' && ver_pratos != 'n')
                printf("Opcao invalida! Tente novamente\n");
        } while (ver_pratos != 'S' && ver_pratos != 's' && ver_pratos != 'N' && ver_pratos != 'n');

        if (ver_pratos == 'N' || ver_pratos == 'n')
            break;

        // agora, iremos mostrar as opções de cada restaurante
        do {
            printf("\nEscolha um restaurante para mostrar os pratos disponiveis (1-%d): ", lista->tam_lista);
            fflush(stdout);
            scanf("%d", &opcao_restaurante);
            getchar();
        } while (opcao_restaurante < 1 || opcao_restaurante > lista->tam_lista);

        aux = lista->inicio;
        i = 1;
        while (aux != NULL && i < opcao_restaurante) {
            aux = aux->prox;
            i++;
        }

        if (aux != NULL) {
            const char headerMessage[] = "\n\n================= PRATOS DISPONIVEIS =================\n\n";
            printLetterByLetter(headerMessage, 0.02);

            printLetterByLetter("-> TIPO CULINARIO: ", 0.03);
            if (aux->dados_restaurante.tipo_culinaria == 1)
                printLetterByLetter("*** BRASILEIRA ***\n\n", 0.03);
            else if (aux->dados_restaurante.tipo_culinaria == 2)
                printLetterByLetter("*** FAST FOOD ***\n\n", 0.03);
            else if (aux->dados_restaurante.tipo_culinaria == 3)
                printLetterByLetter("*** ASIATICA ***\n\n", 0.03);


            for (int j = 0; j < aux->dados_restaurante.qtd_pratos; j++) 
            {
                printf("[COMBO] %d:\n", j + 1);
                printLetterByLetter("- Prato Principal: ", 0.03);
                fflush(stdout);

                const char *pratoNome = aux->dados_restaurante.prato[j].nome;
                printLetterByLetter(pratoNome, 0.03);
                printf("\n");

                printLetterByLetter("- Acompanhamento: ", 0.03);
                fflush(stdout);

                const char *acompanhamento = aux->dados_restaurante.prato[j].bebida;
                printLetterByLetter(acompanhamento, 0.03);
                printf("\n");

                printLetterByLetter("- Preco: ", 0.03);
                fflush(stdout);
                printf("R$%.2f\n", aux->dados_restaurante.prato[j].preco);
                printf("\n");
                sleep(1.4);
            }
        }
        
        do {
            printLetterByLetter("Deseja ver o cardapio de outro restaurante?\n", 0.02);
            printLetterByLetter("[1] - Sim\n", 0.02);
            printLetterByLetter("[0] - Nao\n", 0.02);
            scanf(" %c", &opcao);
            getchar();
            if (opcao != '1' && opcao != '0')
                printLetterByLetter("Opcao invalida! Tente novamente\n", 0.02);
        } while (opcao != '1' && opcao != '0');

        if (opcao == '0')
            break;
    }
}





void menu_restaurante_usuario(Lista_restaurante *lista) 
{
    if (lista == NULL)
        return;

    int opcao_culinaria;
    char opcao;
    int i;

    while (1) {
        // Mostrar os tipos de culinária disponíveis
        printLetterByLetter("\n\n================= TIPOS CULINARIOS =================\n\n", 0.02);
        printLetterByLetter("[1] - Brasileira\n", 0.02);
        printLetterByLetter("[2] - Fast Food\n", 0.02);
        printLetterByLetter("[3] - Japonesa\n", 0.02);

        do {
            printLetterByLetter("\nEscolha um tipo de culinaria para mostrar os restaurantes disponiveis (1-3): ", 0.02);
            fflush(stdout);
            scanf("%d", &opcao_culinaria);
            getchar();

            if (opcao_culinaria < 1 || opcao_culinaria > 3)
                printLetterByLetter("Opcao invalida! Tente novamente\n", 0.02);
        } while (opcao_culinaria < 1 || opcao_culinaria > 3);

        // Filtrar e mostrar os restaurantes do tipo culinária escolhido
        No *aux = lista->inicio;
        i = 1;
        int encontrados = 0;

        while (aux != NULL) {
            if (aux->dados_restaurante.tipo_culinaria == opcao_culinaria) {
                if (encontrados == 0) {
                    const char headerMessage[] = "\n\n================= RESTAURANTES DO TIPO CULINARIO ESCOLHIDO =================\n\n";
                    printLetterByLetter(headerMessage, 0.02);
                }

                // Converter o nome para letras maiúsculas
                for (int j = 0; aux->dados_restaurante.nome[j] != '\0'; j++) 
                    aux->dados_restaurante.nome[j] = toupper(aux->dados_restaurante.nome[j]);
                
                printLetterByLetter("-> [", 0.02);
                printLetterByLetter(aux->dados_restaurante.nome, 0.05); 
                printLetterByLetter("]\n", 0.02);
                sleep(0.2);

                encontrados++;
            }

            aux = aux->prox;
            i++;
        }

        if (encontrados == 0) {
            printLetterByLetter("\nNenhum restaurante encontrado para o tipo de culinária selecionado.\n", 0.02);
            continue;
        }

        // Perguntar ao usuário qual restaurante ele deseja ver os pratos disponíveis
        char nome_restaurante[100];
        int restaurante_encontrado = 0;
        printLetterByLetter("\nDigite o [nome do restaurante] para mostrar os pratos disponiveis: ", 0.02);
        fflush(stdout);

        do {
            fgets(nome_restaurante, sizeof(nome_restaurante), stdin);
            nome_restaurante[strcspn(nome_restaurante, "\n")] = '\0'; // remover o caractere de nova linha

            // Converter o nome do restaurante para letras maiúsculas
            for (int j = 0; nome_restaurante[j] != '\0'; j++)
                nome_restaurante[j] = toupper(nome_restaurante[j]);

            aux = lista->inicio;
            i = 1;

            while (aux != NULL) {
                // Comparar o nome do restaurante com o nome digitado pelo usuário
                if (strcmp(aux->dados_restaurante.nome, nome_restaurante) == 0) {
                    restaurante_encontrado = 1;
                    break;
                }

                aux = aux->prox;
                i++;
            }

            if (!restaurante_encontrado)
                printLetterByLetter("\nRestaurante nao encontrado. Digite novamente.\n", 0.02);

        } while (!restaurante_encontrado);

        // Mostrar os pratos disponíveis do restaurante escolhido
        const char headerMessage[] = "\n\n====================== PRATOS DISPONIVEIS PARA O RESTAURANTE ESCOLHIDO ======================\n\n";
        printLetterByLetter(headerMessage, 0.02);

        // Mostrar os pratos disponíveis do restaurante escolhido
        printLetterByLetter("-> TIPO CULINARIO: ", 0.03);
        if (aux->dados_restaurante.tipo_culinaria == 1)
            printLetterByLetter("*** BRASILEIRA ***\n\n", 0.03);
        else if (aux->dados_restaurante.tipo_culinaria == 2)
            printLetterByLetter("*** FAST FOOD ***\n\n", 0.03);
        else if (aux->dados_restaurante.tipo_culinaria == 3)
            printLetterByLetter("*** JAPONESA ***\n\n", 0.03);

        for (int j = 0; j < aux->dados_restaurante.qtd_pratos; j++) {
            printf("[COMBO] %d:\n", j + 1);
            printLetterByLetter("- Prato Principal: ", 0.03);
            fflush(stdout);

            const char *pratoNome = aux->dados_restaurante.prato[j].nome;
            printLetterByLetter(pratoNome, 0.03);
            printf("\n");

            printLetterByLetter("- Acompanhamento: ", 0.03);
            fflush(stdout);

            const char *acompanhamento = aux->dados_restaurante.prato[j].bebida;
            printLetterByLetter(acompanhamento, 0.03);
            printf("\n");

            printLetterByLetter("- Preco: ", 0.03);
            fflush(stdout);
            printf("R$%.2f\n", aux->dados_restaurante.prato[j].preco);
            printf("\n");
            sleep(1.3);
        }

        do {
            printLetterByLetter("Deseja ver o cardapio de outro restaurante?\n", 0.02);
            printLetterByLetter("[1] - Sim\n", 0.02);
            printLetterByLetter("[0] - Nao\n", 0.02);
            scanf(" %c", &opcao);
            getchar();

            if (opcao != '1' && opcao != '0')
                printLetterByLetter("\nOpcao invalida. Digite novamente.\n", 0.02);

        } while (opcao != '1' && opcao != '0');

        if (opcao == '0')
            break;
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
