#include "usuario.h"
#include <stdio.h>



int main()
{
    Lista *lista = criar_lista();
    
    Usuario usuario;
    char operando;
    char tem_cadastro; 

    printf("\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n");
    sleep(0.6);
    printf("LOADING");

    for (int i = 0; i < 3; i++) {
        sleep(0.6);
        printf(".");
    }

    printf("\n\n========== ~~~~~ APTUS DELIVERIA ~~~~~~ =========\n\n");
    
    
    do {
        printf("\nO/A senhor/senhora ja tem cadastro no app?\n");
        printf("[1] -> SIM\n");
        printf("[0] -> NAO\n");
        scanf("%c", &tem_cadastro);
        getchar();
        if (tem_cadastro == '1') {
            break;
        }
        else if (tem_cadastro == '0') {
            cadastrar_usuario(lista, usuario);
        } else {
            printf("\nERRO!!! Informe uma opcao valida!\n");
            sleep(0.7);
        }
        

    } while (tem_cadastro != '1' && tem_cadastro != '0');
    

    if (tem_cadastro == '1') {
        // if (cadastro == 'adm')....
        // else .....
        // aqui iremos colocar as funções para fazer o pedido no restaurante
    }
    

    return 0;
}