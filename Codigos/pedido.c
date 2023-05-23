#include "usuario.h"
#include "pedido.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct no {
    Pedido dados;
    struct no *prox;

} No;



typedef struct fila {
    No *inicio;
    No *fim;
    int tam_fila;

} Fila;



/*=============================================================================================================*/

Fila *criar_fila()
{
    Fila *fila = (Fila *) calloc(1, sizeof(Fila));

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tam_fila = 0;

    return fila;
}





int fila_vazia(Fila *fila)
{
    if (fila == NULL)
        return -1;
    if (fila->tam_fila == 0)
        return 1;
    return 0;
}





int limpar_fila(Fila *fila)
{
    if (fila == NULL)
        return -1;
    while (fila_vazia(fila) != 1)
        remover(fila, NULL);

    free(fila);
    fila = NULL;

    return 0;
}





int inserir_pedido(Fila *fila, Pedido pedido)
{
    if (fila == NULL)
        return -1;
    
    No *novo_no = (No*) calloc(1, sizeof(No));
    novo_no->dados = paciente;
    novo_no->prox = NULL; // o prox do novo nó sempre será NULL, uma vez que a inserção em uma fila sempre será em seu final

    // se a fila estiver vazia, então aponte o início da fila para o novo_no
    if (fila_vazia(fila) == 1)  
        fila->inicio = novo_no;
    // caso contrário, aponte o que, anteriormente era o último nó, para o novo_no
    else 
        fila->fim->prox = novo_no;
    
    // em ambos os casos, o novo_no será o fim da fila
    fila->fim = novo_no;
    fila->tam_fila += 1;

    return 0;
}





int cadastrar_pedido(Fila *fila, Pedido pedido)
{
    if (fila == NULL)
        return -1;

    // será o novo paciente
    No *novo_no = (No*) calloc(1, sizeof(No));
    novo_no->dados = paciente;
    
    printf("\n=============== SISTEMA DE CADASTRO ===============\n");
    printf("\nInforme seu [NOME]: ");
    fgets(novo_no->dados_usuario.nome, sizeof(novo_no->dados_usuario.nome), stdin);

    printf("Informe seu [CPF]: ");
    fgets(novo_no->dados_usuario.cpf, sizeof(novo_no->dados_usuario.cpf), stdin);

    printf("Informe seu [NUMERO DE TELEFONE]: (+55) ");
    fgets(novo_no->dados_usuario.num_telefone, sizeof(novo_no->dados_usuario.num_telefone), stdin);

    printf("\nAgora, crie seu [LOGIN] e sua [SENHA]: \n");
    printf("[LOGIN]: ");
    fgets(novo_no->dados_usuario.login, sizeof(novo_no->dados_usuario.login), stdin);

    printf("[SENHA]: ");
    fgets(novo_no->dados_usuario.senha, sizeof(novo_no->dados_usuario.senha), stdin);

    inserir_no_fim(lista, novo_no->dados_usuario);

    return 0;
}





int remover(Fila *fila, Pedido *pedido_removido)
{
    if (fila == NULL)
        return -1;
    if (fila_vazia(fila) == 1)
        return -2;
    
    No *no_aux = fila->inicio;
    *pedido_removido = no_aux->dados; // como a remoção sempre acontece no início da fila, este será o elemento retornado
    // o início agora apontará para, anteriormente, segundo elemento
    fila->inicio = no_aux->prox;
    free(no_aux);

    // caso, após a remoção, a lista fique vazia, temos que atualizar o ponteiro fim
    if (fila->inicio == NULL)
        fila->fim = NULL;

    fila->tam_fila -= 1;

    return 0;
}





void imprime_pedidos(Fila *fila)
{
    if (fila != NULL) {
        No *no = fila->inicio;
        while (no != NULL) {
            printf("\nNOME: %s ",no->dados.nome);
            printf("Senha: %s \n",no->dados.senha);
            
            no = no->prox;
        }
    }
}


char menu()
{
    char operando;
    do {
        printf("\n========== RESTAURANTES =========\n\n");
        printf("[1] ;;;;;;\n");
        printf("[2] ;;;;;;\n");
        printf("[3] ;;;;;;\n");
        printf("[4] ;;;;;;\n");
        scanf("%c", &operando);
        getchar();

        if (operando == '4')
            break;

        switch (operando) {
            case '1':
            case '2':
            case '3':
            case '4':
            default:
                break;
                
        }

    } while (operando != '4');


    return operando;
}