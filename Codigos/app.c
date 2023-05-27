#include "usuario.h"
#include "restaurante.h"
#include <stdio.h>
#include <string.h>



int main() 
{
    Lista *lista_usuarios = criar_lista();
    Usuario usuario[2];

    Lista *lista_restaurante = criar_restaurante();
    Restaurante restaurante;

    insere_adm(lista_usuarios, usuario[0]);
    insere_restaurantes_cadastrados(lista_restaurante, restaurante);

    const char welcomeMessage[] = "\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n";
    printLetterByLetter(welcomeMessage, 0.05);
    printf("\n");
    printLetterByLetter("\n               [BAZOOKA DELIVERY]              \n\n", 0.05);

    char tem_cadastro = '0';

    //***********************************************************************************************************************
    // esta é a parte da verificação do usário e demais funcionalidades
    //***********************************************************************************************************************
    do {
        printLetterByLetter("\nVoce ja tem cadastro no app?\n", 0.05);
        printLetterByLetter("[1] -> SIM\n", 0.05);
        printLetterByLetter("[0] -> NAO\n", 0.05);
        scanf("%c", &tem_cadastro);
        getchar();
        if (tem_cadastro == '1') {
            break;
        }
        else if (tem_cadastro == '0') {
            cadastrar_usuario(lista_usuarios, usuario[1]);
            tem_cadastro = '1';
        } else 
            printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!!!\n", 0.05);
            
    } while (tem_cadastro != '1' && tem_cadastro != '0');

    char login[50];
    char senha[50];
    char tentar_novamente;
    int logou = 0;

    if (tem_cadastro == '1') {
        do {
            printLetterByLetter("\nInforme seu [login]: ", 0.05);
            fgets(login, sizeof(login), stdin);

            printLetterByLetter("Informe sua [senha]: ", 0.05);
            fgets(senha, sizeof(senha), stdin);
            
            int v = verifica_login(lista_usuarios, login, senha);
            if (v == 1) {
                printLetterByLetter("\nLogin realizado com sucesso!!!\n\n", 0.05);
                logou = 1;
            }
            else if (v == 0) {
                printLetterByLetter("\nUsuario nao encontrado!!!\n\n", 0.05);
                do {
                    printLetterByLetter("Deseja tentar novamente?\n", 0.05);
                    printLetterByLetter("[1] -> SIM\n", 0.05);
                    printLetterByLetter("[0] -> NAO\n", 0.05);
                    scanf(" %c", &tentar_novamente);
                    getchar();

                    if (tentar_novamente != '0' && tentar_novamente != '1') 
                        printLetterByLetter("\nERRO!!! Informe uma opcao valida!\n", 0.05);
                        
                } while (tentar_novamente != '0' && tentar_novamente != '1');
            }

        } while (tentar_novamente == '1' && verifica_login(lista_usuarios, login, senha) == 0);
        
    }



    // ***********************************************************************************************************************
    // esta é a parte da interação do usuário, uma vez logado, com o app
    //***********************************************************************************************************************
    char interagir_como_usuario = '0';
    if (logou == 1) {
        if (verifica_administrador(lista_usuarios, login, senha) == 1) {
            const char mensagem1[] = "Verificamos que voce eh um usuario [administrador]!!!\nSeja bem vindo!!!";
            printLetterByLetter(mensagem1, 0.05);
            printf("\n");
            mostrar_restaurantes(lista_restaurante);
            char opcao;
            int pos_cadastro, pos_remocao;
            
            do {
                if (interagir_como_usuario == '1') break;
                printLetterByLetter("\nOperacoes disponiveis para administradores:\n", 0.05);
                printLetterByLetter("[1] -> Adicionar restaurante\n", 0.05);
                printLetterByLetter("[2] -> Remover um restaurante da Lista de Restaurantes\n", 0.05);
                printLetterByLetter("[3] -> Sair do app\n", 0.05);
                printLetterByLetter("\nInforme a opcao desejada: ", 0.05);
                scanf(" %c", &opcao);
                getchar();
                if (opcao == '3') {
                    printLetterByLetter("\nObrigado por utilizar nosso app. Volte sempre!\n", 0.05);
                    break;
                }
                
                switch (opcao) {
                    case '1':
                        do {
                            printLetterByLetter("\nInforme a [POSICAO] que deseja cadastrar o novo restaurante: ", 0.05);
                            scanf("%d", &pos_cadastro);
                            getchar();
                            
                            if (pos_cadastro < 1 || pos_cadastro > tam_lista(lista_restaurante) + 1) {
                                printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.05);
                                sleep(0.5);
                            }
                        } while (pos_cadastro < 1 || pos_cadastro > tam_lista(lista_restaurante) + 1);
                        
                        cadastrar_restaurante(lista_restaurante, &restaurante, pos_cadastro);
                        printLetterByLetter("\nRestaurante cadastrado com sucesso!!!\n", 0.05);
                        do {
                            printLetterByLetter("\nDeseja interagir com o app como usuario?\n", 0.05);
                            printLetterByLetter("[1] -> SIM\n", 0.05);
                            printLetterByLetter("[0] -> NAO\n", 0.05);
                            scanf(" %c", &interagir_como_usuario);
                            getchar();
                            
                            switch (interagir_como_usuario) {
                                case '1':
                                    interagir_como_usuario = '1';
                                    break;
                                case '0':
                                    printLetterByLetter("\nObrigado por usar o app!!!\n\n", 0.05);
                                    break;
                                default:
                                    printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.05);
                                    break;
                            }
                        } while (interagir_como_usuario != '0' && interagir_como_usuario != '1');

                        break;
                    case '2': {
                        ; // o ponto e virgula é para não dar erro de compilação
                        Restaurante restaurante_removido;
                        do {
                            printLetterByLetter("\nInforme a [POSICAO] do restaurante que deseja remover: ", 0.05);
                            printLetterByLetter("\nOBS: A [POSICAO] do restaurante a ser removido deve ser > 0 e <= a quantidade de restaurantes cadastrados!\n", 0.05);
                            scanf("%d", &pos_remocao);
                            getchar();
                            if (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1) 
                                printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.05);
                            
                        } while (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1);

                        remove_restaurante_pos(lista_restaurante, &restaurante_removido, pos_remocao);
                        printLetterByLetter("\nNova Lista de Restaurantes:\n", 0.05);
                        mostrar_restaurantes(lista_restaurante);
                        do {
                            printLetterByLetter("\nDeseja interagir com o app como usuario?\n", 0.05);
                            printLetterByLetter("[1] -> SIM\n", 0.05);
                            printLetterByLetter("[0] -> NAO\n", 0.05);
                            scanf(" %c", &interagir_como_usuario);
                            getchar();
                            
                            switch (interagir_como_usuario) {
                                case '1':
                                    interagir_como_usuario = '1';
                                    break;
                                case '0':
                                    printLetterByLetter("\nObrigado por usar o app!!!\n\n", 0.05);
                                    break;
                                default:
                                    printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.05);
                                    break;
                            }
                        } while (interagir_como_usuario != '0' && interagir_como_usuario != '1');
                        
                        break;
                    }
                    default:
                        printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.05);
                        break;
                }
            } while (opcao != '3');
        }
    // o usuário não é administrador ou ele quer interagir como um usuário padrão
    } 
    if (((logou == 1) && (verifica_administrador(lista_usuarios, login, senha) == 0 )) || (interagir_como_usuario == '1')) {
            const char mensagem2[] = "Verificamos que voce eh um [usuario]!!!\nSeja bem vindo!!!";
            printLetterByLetter(mensagem2, 0.05);
            printf("\n");
            // aqui, o usuário pode interagir com o app como um usuário padrão, tal como um cliente, tendo acesso aos
            // restaurantes e aos pratos disponíveis, podendo fazer pedidos e avaliar os restaurantes etc
            menu_restaurante(lista_restaurante);
    }    
    

    // caso não tenha logado, o usuário não pode interagir com o app

    limpar_lista(lista_usuarios);
    limpar_lista(lista_restaurante);

    return 0;
}
