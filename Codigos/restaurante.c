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
    novo_no->dados_restaurante.qtd_pratos = r.qtd_pratos;

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
    aux->dados_restaurante.qtd_pratos = r->qtd_pratos;
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
    novo_no->dados_restaurante.qtd_pratos = r.qtd_pratos;

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

    novo_no->dados_restaurante.qtd_pratos = r.qtd_pratos;
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




int cadastrar_restaurante(Lista_restaurante *lista, Restaurante *restaurante, int pos_cadastro) 
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

                insere_restaurante_pos(lista, novo_no->dados_restaurante, pos_cadastro);
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

    lista->tam_lista = 5;

    return 0;
}






void menu_restaurantes(Lista_restaurante *lista) 
{
    if (lista == NULL)
        return;

    char opcao_restaurante;
    char opcao;
    int i;

    while (1) {
        No *aux = lista->inicio;
        i = 1;

        // primeiro, iremos mostrar todos os restaurantes cadastrados
        printLetterByLetter("\n\n================= RESTAURANTES =================\n\n", 0.04);
        while (aux != NULL) {
            // Converter o nome para letras maiúsculas
            int j;
            for (j = 0; aux->dados_restaurante.nome[j] != '\0'; j++) 
                aux->dados_restaurante.nome[j] = toupper(aux->dados_restaurante.nome[j]);
            
            printf("%d. ", i);
            printLetterByLetter(aux->dados_restaurante.nome, 0.1); // Atraso de 0.1 segundos por letra
            putchar('\n');

            aux = aux->prox;
            i++;
        }

        // agora, iremos mostrar as opções de cada restaurante
        do {
            printf("\nEscolha um restaurante para mostrar os pratos disponiveis (1-%d): ", lista->tam_lista);
            fflush(stdout);
            scanf(" %c", &opcao_restaurante);
            getchar();
        } while (opcao_restaurante < '1' || opcao_restaurante > '1' + lista->tam_lista - 1);

        aux = lista->inicio;
        i = 1;
        while (aux != NULL && i < opcao_restaurante - '0') {
            aux = aux->prox;
            i++;
        }

        if (aux != NULL) {
            const char headerMessage[] = "\n\n================= PRATOS DISPONIVEIS =================\n\n";
            printLetterByLetter(headerMessage, 0.04);

            printLetterByLetter("-> CATEGORIA: ", 0.07);
            if (aux->dados_restaurante.tipo_culinaria == 1)
                printLetterByLetter("*** BRASILEIRA ***\n\n", 0.07);
            else if (aux->dados_restaurante.tipo_culinaria == 2)
                printLetterByLetter("*** FAST FOOD ***\n\n", 0.07);
            else if (aux->dados_restaurante.tipo_culinaria == 3)
                printLetterByLetter("*** JAPONESA ***\n\n", 0.07);


            for (int j = 0; j < aux->dados_restaurante.qtd_pratos; j++) 
            {
                printf("[COMBO] %d:\n", j + 1);
                printLetterByLetter("- Prato Principal: ", 0.07);
                fflush(stdout);

                const char *pratoNome = aux->dados_restaurante.prato[j].nome;
                printLetterByLetter(pratoNome, 0.07);
                printf("\n");

                printLetterByLetter("- Acompanhamento: ", 0.07);
                fflush(stdout);

                const char *acompanhamento = aux->dados_restaurante.prato[j].bebida;
                printLetterByLetter(acompanhamento, 0.07);
                printf("\n");

                printLetterByLetter("- Preco: ", 0.07);
                fflush(stdout);
                printf("R$%.2f\n", aux->dados_restaurante.prato[j].preco);
                printf("\n");
            }
        }
        
        printLetterByLetter("Deseja ver outro restaurante?\n", 0.05);
        do {
            printLetterByLetter("[1] - Sim\n", 0.05);
            printLetterByLetter("[0] - Nao\n", 0.05);
            scanf(" %c", &opcao);
            getchar();
            if (opcao != '1' && opcao != '0')
                printLetterByLetter("Opcao invalida! Tente novamente\n", 0.05);
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

