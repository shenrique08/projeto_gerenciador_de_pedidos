#include "usuario.h"
#include "restaurante.h"
#include <stdio.h>
#include <string.h>



int main()
{
    Lista *lista = criar_lista();
    Usuario usuario;

    Fila *fila = criar_restaurante();
    Restaurante restaurante;
    
    char operando;
    char tem_cadastro; 

    insere_adm(lista, usuario);
    insere_restaurantes_cadastrados(fila, restaurante);
    printf("\n##############################################################################\n");
    imprime(lista);
    printf("\n##############################################################################\n\n\n\n\n\n\n");

    printf("\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n");
    printf("LOADING");

    // simulação de loading
    for (int i = 0; i < 3; i++) {
        sleep(0.5);
        printf(".");
    }

    printf("\n\n========== ~~~~~ BAZOOKA DELIVERY ~~~~~~ =========\n\n");
    
    // precisamos verificar se o usuário já tem cadastro no app
    do {
        printf("\nVoce ja tem cadastro no app?\n");
        printf("[1] -> SIM\n");
        printf("[0] -> NAO\n");
        scanf("%c", &tem_cadastro);
        getchar();
        if (tem_cadastro == '1') {
            break;
        }
        else if (tem_cadastro == '0') {
            cadastrar_usuario(lista, usuario);
            tem_cadastro = '1';
            break;
        } else {
            printf("\nERRO!!! Informe uma opcao valida!\n");
            sleep(0.7);
        }
        
    } while (tem_cadastro != '1' && tem_cadastro != '0');
    
    char login[50];
    char senha[50];
    char tentar_novamente;

    if (tem_cadastro == '1') 
    {
        do {
            printf("\nInforme seu [login]: ");
            fgets(login, sizeof(login), stdin);

            printf("Informe sua [senha]: ");
            fgets(senha, sizeof(senha), stdin);
            
            int v = verifica_login(lista, login, senha);
            if (v == 1)
                printf("\nLogin realizado com sucesso!!!\n\n");
            else if (v == 0) {
                printf("\nUsuario nao encontrado!!!\n\n");
                printf("Deseja tentar novamente?\n");
                printf("[1] -> SIM\n");
                printf("[0] -> NAO\n");
                scanf("%c", &tentar_novamente);
                getchar();
            }

        } while (tentar_novamente == '1' && verifica_login(lista, login, senha) == 0);
    }

    // a partir deste ponto, o usuário já está logado no sistema
    // e pode acessar as funcionalidades do app
    mostra_restaurantes(fila);

    return 0;
}