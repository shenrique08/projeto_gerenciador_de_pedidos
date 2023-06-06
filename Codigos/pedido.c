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
        return -1;
    
    novo->pedido = pedido;
    novo->prox = NULL;

    // Insere o novo pedido na fila
    if (fila_pedidos->inicio == NULL) {
        // A fila está vazia
        fila_pedidos->inicio = novo;
        fila_pedidos->fim = novo;
    } else {
        fila_pedidos->fim->prox = novo;
        fila_pedidos->fim = novo;
    }

    fila_pedidos->qtd++;

    return 1;
}





void mostrar_pedido(Fila *fila, int status) 
{
    No *aux = fila->inicio;

    printLetterByLetter("-------------------------------------------------------------------\n", 0.02);
    printf("Prato Principal: [%s]\n", aux->pedido.prato.nome);
    printf("Quantidade: [%d]\n", aux->pedido.quantidade);
    printf("Valor Total: [R$%.2f]\n", aux->pedido.valorTotal);
    if (status == 0) 
        printf("Status: [EM ANDAMENTO]\n");
    else if (status == 1) 
        printf("Status: [ENTREGUE]\n");
    else if (status == -1) 
        printf("Status: [CANCELADO]\n");
    
    printLetterByLetter("-------------------------------------------------------------------\n", 0.02);
}





int remover_pedido(Fila *fila)
{
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






void pagar_com_cartao()
{
    printLetterByLetter("\n\n               ***** SISTEMA DE PAGAMENTO *****               \n", 0.03);
    
    char nome_titular[30];
    char numero_cartao[17];
    char data_validade[6]; // mm/aa
    char codigo_seguranca[4];

    do {
        printLetterByLetter("Digite o [nome do titular do cartao]: ", 0.02);
        fgets(nome_titular, 30, stdin);
    } while (strlen(nome_titular) > 30);
    fflush(stdin);
    do {
        printLetterByLetter("Digite o [numero do cartao]: ", 0.02);
        fgets(numero_cartao, 17, stdin);
    } while (strlen(numero_cartao) > 17);
    fflush(stdin);
    do {
        printLetterByLetter("Digite a [data de validade do cartao]: (mm/aa) ", 0.02);
        fgets(data_validade, 6, stdin);
    } while (strlen(data_validade) > 6);
    fflush(stdin);
    do {
        printLetterByLetter("Digite o [CVV]: ", 0.02);
        fgets(codigo_seguranca, 4, stdin);
    } while (strlen(codigo_seguranca) > 4);

    printLetterByLetter("Processando pagamento...\n", 0.2);

    printLetterByLetter("Pagamento realizado com sucesso!\n", 0.02);
    printLetterByLetter("Agradecemos o pedido! Aguarde a entrega...\n", 0.02);
}






int pagar_com_dinheiro(float valor_total)
{
    printLetterByLetter("\n\n               *** SISTEMA DE PAGAMENTO ***               \n", 0.02);

    float valor_pago;
    char troco = '0';

    do {
        do {
            printLetterByLetter("\nPrecisa de troco?\n [1] -> SIM\n [0] -> NAO: ", 0.02);
            scanf(" %c", &troco);
            getchar();
            if (troco != '1' && troco != '0')
                printLetterByLetter("Opcao invalida. Tente novamente!\n", 0.02);
        } while (troco != '1' && troco != '0');

        // caso precise de troco
        if (troco == '1') {
            printLetterByLetter("Digite o valor total que voce ira dar ao entregador: R$", 0.02);
            scanf("%f", &valor_pago);
        }
        
        if (valor_pago < valor_total)
            printLetterByLetter("Valor insuficiente!\n", 0.02);
        
        else if (valor_pago == valor_total)
            printLetterByLetter("Sem troco necessario!\nAgradecemos o pedido! Aguarde a entrega...\n", 0.02);
        
        else{
            printLetterByLetter("Calculando troco...\n", 0.05);
            printf("Troco: [R$%.2f]\n", valor_pago - valor_total);
            printLetterByLetter("Agradecemos o pedido! Aguarde a entrega...\n", 0.02);
        }

    } while (valor_pago < valor_total);

    return 1; // Sucesso no pagamento
}







void pagar_com_pix()
{
    printLetterByLetter("\n\n               ***** SISTEMA DE PAGAMENTO *****               \n", 0.02);
    
    char codigo_pix[28];
    printLetterByLetter("Gerando codigo pix...\n", 0.08);

    srand(time(NULL));
    const char caracteres[] = "0123456789abcdef";
    const int tamanho_codigo_pix = 27; // ex: a56c-4928-93be-9b7bf14beeab

    for (int i = 0; i < tamanho_codigo_pix; i++) {
        int indice = rand() % (sizeof(caracteres) - 1); // gera um indice aleatorio
        codigo_pix[i] = caracteres[indice]; // pega um caractere aleatorio do vetor de caracteres
        if (i == 4 || i == 9 || i == 14) // adiciona o traco nos indices corretos
            codigo_pix[i] = '-';
    }
    codigo_pix[tamanho_codigo_pix] = '\0'; // adiciona o caractere nulo no final da string
    
    printLetterByLetter("Realize o pagamento pelo codigo Pix copia e cola: ", 0.02);
    printf("[%s]\n", codigo_pix);
    //getchar();
    printLetterByLetter("Digite 'ENTER' quando o pagamento for realizado: ", 0.02);
    getchar();
    
    printLetterByLetter("\nProcessando pagamento...\n", 0.2);
    printLetterByLetter("Pagamento realizado com sucesso!\n", 0.02);
    printLetterByLetter("Agradecemos o pedido! Aguarde a entrega...\n\n", 0.02);
}






int mostrar_pagamento(float valor_total)
{
    printLetterByLetter("\n\n               ***** PAGAMENTO *****               \n\n", 0.03);
    printf("VALOR TOTAL DO PEDIDO: [R$%.2f]\n", valor_total);

    char metodo_pagamento;
    printLetterByLetter("Escolha como deseja pagar:\n", 0.02);
    printLetterByLetter("1. Cartao de credito\n", 0.02);
    printLetterByLetter("2. Pix\n", 0.02);
    printLetterByLetter("3. Dinheiro na entrega\n", 0.02);
    printLetterByLetter("4. Cancelar pedido\n", 0.02);
    do {
        printLetterByLetter("Digite a opcao desejada: ", 0.02);
        scanf(" %c", &metodo_pagamento);
        getchar();

        switch (metodo_pagamento) {
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
                //remover_pedido(fila);
                //printLetterByLetter("Pedido cancelado com sucesso!\n", 0.02);
                //printLetterByLetter("Agradecemos a preferencia!\n", 0.02);
                return 0; // Cancelamento do pedido
                
            default:
                printLetterByLetter("Opcao invalida! Tente novamente\n", 0.02);
                break;
        }
    } while (metodo_pagamento != '1' && metodo_pagamento != '2' && metodo_pagamento != '3' && metodo_pagamento != '4');

    return 1; // Sucesso no pagamento
}




void sleepTeste(float seconds) 
{
    fflush(stdout);  // Flush the output to ensure immediate printing

    struct timespec sleepTime;
    sleepTime.tv_sec = (time_t) seconds;
    sleepTime.tv_nsec = (long) ((seconds - (time_t) seconds) * 1e9);

    nanosleep(&sleepTime, NULL);

}





void mostrar_estimativa_entrega() 
{
    printLetterByLetter("\n-------------------------------------------------------------------\n", 0.02);
    srand(time(NULL));
    float estimativa = rand() % 13 + 3;
    printLetterByLetter("Estimativa de entrega: ", 0.02);
    printf("%.1fs\n", estimativa);
    sleepTeste(estimativa);
}






void mostrar_avaliacao()
{
    printLetterByLetter("\n***********************************************************************\n", 0.02);
    printLetterByLetter("               ***** SISTEMA DE AVALIACAO *****               \n", 0.03);
    printLetterByLetter("Avalie o nosso servico de 0 a 5: ", 0.02);
    int avaliacao;
    
    do {
        scanf("%d", &avaliacao);
        getchar();
        if (avaliacao < 0 || avaliacao > 5)
            printLetterByLetter("Avaliacao invalida! Tente novamente\n", 0.02);
    } while (avaliacao < 0 || avaliacao > 5);
    
    printLetterByLetter("Avalie o prato de 0 a 5: ", 0.02);

    do {
        scanf("%d", &avaliacao);
        getchar();
        if (avaliacao < 0 || avaliacao > 5)
            printLetterByLetter("Avaliacao invalida! Tente novamente\n", 0.02);

    } while (avaliacao < 0 || avaliacao > 5);
    
    printLetterByLetter("Agradecemos a avaliacao! Ate a proxima!\n", 0.02);
}
