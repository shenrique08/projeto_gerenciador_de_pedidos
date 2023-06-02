#include "pedido.h"
#include "restaurante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // srand(time(NULL)) para gerar um código de pix aleatório



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
    if (fila == NULL)
        return -1;
    return 0;
}




int qtd_pedidos(Fila *fila)
{
    if (fila == NULL)
        return -1;
    return fila->qtd;
}






int inserir_pedido(Fila *fila_pedidos, Pedido pedido)
{
    if (fila_pedidos == NULL)
        return -1; // Fila não existe

    No *novo = (No *) calloc(1, sizeof(No));
    if (novo == NULL) 
        return -1; // Falha na alocação de memória
    

    novo->pedido = pedido;
    novo->prox = NULL;

    // Insere o novo pedido na fila
    if (fila_pedidos->inicio == NULL) {
        // A fila está vazia
        fila_pedidos->inicio = novo;
        fila_pedidos->fim = novo;
    } else {
        // A fila não está vazia
        fila_pedidos->fim->prox = novo;
        fila_pedidos->fim = novo;
    }

    fila_pedidos->qtd++;

    return 1; // Sucesso na inserção do pedido
}





void mostrar_pedido(Fila *fila, int status) 
{
    No *aux = fila->inicio;

    printf("-------------------------------------------------------------------\n");
    //printLetterByLetter("*** PROXIMO PEDIDO A SER ENTREGUE ***\n", 0.03);
    
    printf("Prato Principal: [%s]\n", aux->pedido.prato.nome);
    printf("Quantidade: [%d]\n", aux->pedido.quantidade);
    printf("Valor Total: [R$%.2f]\n", aux->pedido.valorTotal);
    printf("Status: [%s]\n", status == 1 ? "Entregue" : "Em andamento");
    printf("-------------------------------------------------------------------\n");
}







/*int remover_pedido(Fila *fila, Pedido *pedido_entregue)
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
}*/

int remover_pedido(Fila *fila){
    if (fila == NULL)
        return -1;
    if (fila_vazia(fila))
        return -2;
    
    No *aux = fila->inicio;
    fila->inicio = aux->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;
    
    free(aux);
    fila->qtd--;

    return 0;
}

void pagar_com_cartao(){
    printf("-------------------------------------------------------------------\n");
    printLetterByLetter("*** PAGAMENTO ***\n", 0.03);
    
    char nome_titular[30];
    char numero_cartao[16];
    char data_validade[6];
    char codigo_seguranca[4];

    printLetterByLetter("Digite o nome do titular do cartao: ", 0.01);
    scanf(" %[^\n]", nome_titular);
    printLetterByLetter("Digite o numero do cartao: ", 0.01);
    scanf(" %[^\n]", numero_cartao);
    printLetterByLetter("Digite a data de validade do cartao: ", 0.01);
    scanf(" %[^\n]", data_validade);
    printLetterByLetter("Digite o codigo de seguranca do cartao: ", 0.01);
    scanf(" %[^\n]", codigo_seguranca);

    printLetterByLetter("Processando pagamento...\n", 0.1);

    printLetterByLetter("Pagamento realizado com sucesso!\n", 0.01);
    printLetterByLetter("Agradecemos o pedido! Aguarde a entrega...\n", 0.01);
    
}

int pagar_com_dinheiro(float valor_total){
    printf("-------------------------------------------------------------------\n");
    printLetterByLetter("*** PAGAMENTO ***\n", 0.03);

    float valor_pago;

    do {
        printLetterByLetter("Digite quanto ira pagar na entrega: ", 0.01);
        scanf("%f", &valor_pago);
        if (valor_pago < valor_total){
            printLetterByLetter("Valor insuficiente!\n", 0.01);
        }
        else if (valor_pago == valor_total){
            printLetterByLetter("Sem troco necessario!\nAgradecemos o pedido! Aguarde a entrega...\n", 0.01);
        }
        else{
            printLetterByLetter("Calculando troco...\n", 0.05);
            printf("Troco: [R$%.2f]\n", valor_pago - valor_total);
            printLetterByLetter("Agradecemos o pedido! Aguarde a entrega...\n", 0.01);
        }

    } while (valor_pago < valor_total);

    return 1; // Sucesso no pagamento
}

void pagar_com_pix(){
    printf("-------------------------------------------------------------------\n");
    printLetterByLetter("*** PAGAMENTO ***\n", 0.03);
    
    char codigo_pix[30];

    printLetterByLetter("Gerando codigo pix...\n", 0.05);

    srand(time(NULL));
    const char caracteres[] = "0123456789abcdef";
    const int tamanho_codigo_pix = 27; // ex: a56c-4928-93be-9b7bf14beeab

    for (int i = 0; i < tamanho_codigo_pix; i++){
        int indice = rand() % (sizeof(caracteres) - 1); // gera um indice aleatorio
        codigo_pix[i] = caracteres[indice]; // pega um caractere aleatorio do vetor de caracteres
        if (i == 4 || i == 9 || i == 14) // adiciona o traco nos indices corretos
            codigo_pix[i] = '-';
    }
    codigo_pix[tamanho_codigo_pix] = '\0'; // adiciona o caractere nulo no final da string
    
    printLetterByLetter("Realize o pagamento pelo Pix copia e cola: ", 0.01);
    printf("[%s]\n", codigo_pix);
    getchar();
    printLetterByLetter("Digite 'ENTER' quando o pagamento for realizado: ", 0.01);
    getchar();
    
    printLetterByLetter("\nProcessando pagamento...\n", 0.1);
    printLetterByLetter("Pagamento realizado com sucesso!\n", 0.01);
    printLetterByLetter("Agradecemos o pedido! Aguarde a entrega...\n", 0.01);
}

void mostrar_pagamento(float valor_total){
    printf("-------------------------------------------------------------------\n");
    printLetterByLetter("*** PAGAMENTO ***\n", 0.03);
    printf("Valor total: [R$%.2f]\n", valor_total);
    printf("-------------------------------------------------------------------\n");

    char metodo_pagamento;
    printf("Escolha como deseja pagar:\n");
    printf("1. Cartao de credito\n");
    printf("2. Pix\n");
    printf("3. Dinheiro na entrega\n");
    printf("4. Cancelar pedido\n");
    printf("Digite a opcao desejada: ");
    scanf(" %c", &metodo_pagamento);

    switch (metodo_pagamento){
        case '1':
            pagar_com_cartao();
            break;
        case '2':
            pagar_com_pix();
            break;
        case '3':
            pagar_com_dinheiro(valor_total);
            break;
        case '4':
            // printar pedido cancelado e remover da fila
            break;
        default:
            printLetterByLetter("Opcao invalida!\n", 0.01);
            break;
    }
}

void sleepTeste(float seconds) 
{
    fflush(stdout);  // Flush the output to ensure immediate printing

    struct timespec sleepTime;
    sleepTime.tv_sec = (time_t) seconds;
    sleepTime.tv_nsec = (long) ((seconds - (time_t) seconds) * 1e9);

    nanosleep(&sleepTime, NULL);
}

void mostrar_estimativa_entrega() {
    printf("-------------------------------------------------------------------\n");
    srand(time(NULL));
    float estimativa = rand() % 13 + 3;
    printf("Estimativa de entrega: %.1fs\n", estimativa);
    //printf("-------------------------------------------------------------------\n");
    sleepTeste(estimativa);
}

void mostrar_avaliacao(){
    printf("-------------------------------------------------------------------\n");
    printLetterByLetter("*** AVALIACAO ***\n", 0.03);
    printf("Avalie o nosso servico de 0 a 5: ");
    int avaliacao;
    scanf("%d", &avaliacao);
    if (avaliacao < 0 || avaliacao > 5){
        printLetterByLetter("Avaliacao invalida!\n", 0.01);
    }
    else{
        printLetterByLetter("Agradecemos a avaliacao!\n", 0.01);
    }

    printLetterByLetter("Avalie o pedido de 0 a 5: ", 0.01);
    scanf("%d", &avaliacao);

    if (avaliacao < 0 || avaliacao > 5){
        printLetterByLetter("Avaliacao invalida!\n", 0.01);
    }
    else{
        printLetterByLetter("Agradecemos a avaliacao! Ate a proxima!\n", 0.01);
    }

    printf("-------------------------------------------------------------------\n");
}
