#include "usuario.h"
#include "restaurante.h"
#include <stdio.h>
#include <string.h>



int main()
{
    Lista *lista = criar_lista();
    Usuario usuario[2];

    Fila *fila = criar_restaurante();
    Restaurante restaurante;
    //char operando;
    //char tem_cadastro; 
    insere_adm(lista, usuario[0]);
    insere_restaurantes_cadastrados(fila, restaurante);
    
    printf("\n########################################################################################################################################\n");
    const char* welcomeMessage = "\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n";
    const char* loadingMessage = "LOADING...";

    // Exibir mensagem de boas-vindas letra por letra
    for (int i = 0; welcomeMessage[i] != '\0'; i++) {
        putchar(welcomeMessage[i]);
        fflush(stdout);
        sleep(0.05); 
    }

    printf("\n");

    // Exibir mensagem de carregamento letra por letra
    fflush(stdout);
    for (int i = 0; loadingMessage[i] != '\0'; i++) {
        putchar(loadingMessage[i]);
        sleep(0.25);
        fflush(stdout);
    }
    
    

    
    
    printf("\n\n========== ~~~~~ BAZOOKA DELIVERY ~~~~~~ =========\n\n");
    char tem_cadastro = '0';
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
            cadastrar_usuario(lista, usuario[1]);
                tem_cadastro = '1';

        } else {
            printf("\nERRO!!! Informe uma opcao valida!\n");
            sleep(0.7);
        }
        
    } while (tem_cadastro != '1' && tem_cadastro != '0');
    
    char login[50];
    char senha[50];
    char tentar_novamente;
    int logou = 0;

    if (tem_cadastro == '1') 
    {
        do {
            printf("\nInforme seu [login]: ");
            fgets(login, sizeof(login), stdin);

            printf("Informe sua [senha]: ");
            fgets(senha, sizeof(senha), stdin);
            
            int v = verifica_login(lista, login, senha);
            if (v == 1) {
                printf("\nLogin realizado com sucesso!\n\n");
                logou = 1;
            }
            else if (v == 0) {
                printf("\nUsuario nao encontrado!\n\n");
                do {
                    printf("Deseja tentar novamente?\n");
                    printf("[1] -> SIM\n");
                    printf("[0] -> NAO\n");
                    scanf(" %c", &tentar_novamente);
                    getchar();

                    if (tentar_novamente != '0' && tentar_novamente != '1') {
                        printf("\nERRO!!! Informe uma opcao valida!\n");
                        sleep(0.5);
                    }
                } while (tentar_novamente != '0' && tentar_novamente != '1');
            }

        } while (tentar_novamente == '1' && verifica_login(lista, login, senha) == 0);
        
    }
    // a partir deste ponto, o usuário já está logado no sistema
    // e pode acessar as funcionalidades do app
    if (logou == 1) {
    // agora, verifico se o login e senha que o usuário logou são o login e senha admin
    // consideremos que o login e senha fazem parte do primeiro elemento da lista de usuário inserida na função "insere_adm"
        if (verifica_administrador(lista, login, senha) == 1) {
            printf("\n\n========== ~~~~~ BEM VINDO [ADMINISTRADOR] ~~~~~~ =========\n\n");
            mostrar_restaurantes(fila);
            char opcao;
            do {
                printf("\n[1] -> Adicionar restaurante\n");
                printf("[2] -> Remover um restaurante da fila\n");
                printf("[3] -> Sair\n");
                printf("\nInforme a opcao desejada: ");
                scanf(" %c", &opcao);
                getchar();
                
                switch (opcao) {
                    case '1':
                        cadastrar_restaurante(fila, &restaurante);
                        printf("\nNova fila de restaurantes:\n");
                        mostrar_restaurantes(fila);
                        break;
                    case '2': {
                        Restaurante restaurante_removido;
                        remove_restaurante(fila, &restaurante_removido);
                        printf("\nNova fila de restaurantes:\n");
                        mostrar_restaurantes(fila);
                        break;
                    }
                    case '3':
                        break;
                    default:
                        printf("\nERRO!!! Informe uma opção valida!\n");
                        sleep(0.5);
                        break;
                }
            } while (opcao != '3');
        } else {
            printf("\n\n========== ~~~~~ BEM VINDO [USUÁRIO] ~~~~~~ =========\n\n");
            menu_restaurante(fila);
        }
    }   

    
    
   printf("\n########################################################################################################################################\n\n\n\n");
    return 0;
}