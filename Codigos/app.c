#include "usuario.h"
#include "restaurante.h"
#include "pedido.h"
#include <stdio.h>
#include <string.h>



int main() 
{
    Lista *lista_usuarios = criar_usuario();
    Usuario usuario;

    Lista *lista_restaurante = criar_restaurante();
    Restaurante restaurante;

    Pedido pedido;

    // insere o administrador na lista de usuarios
    insere_adm(lista_usuarios, usuario);
    // insere restaurantes pré-cadastrados na lista de restaurante
    insere_restaurantes_cadastrados(lista_restaurante, restaurante);

    printLetterByLetter("\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n\n", 0.02);
    printLetterByLetter("\n               [BAZOOKA DELIVERY]              \n\n", 0.02);

    char tem_cadastro = '0';
    char navegar_app = '1';

    //***********************************************************************************************************************
    // esta é a parte da verificação do usário e demais funcionalidades
    //***********************************************************************************************************************
    while (navegar_app == '1') 
    {
        // verifica se o usuário já tem cadastro no app
        // se não tiver, pergunta se ele quer se cadastrar
        // se quiser, cadastra o usuário (chama a função cadastrar_usuario)
        
        do {
            printLetterByLetter("\nVoce ja tem cadastro no app?\n", 0.02);
            printLetterByLetter("[1] -> SIM\n", 0.02);
            printLetterByLetter("[0] -> NAO\n", 0.02);
            scanf("%c", &tem_cadastro);
            getchar();
            if (tem_cadastro == '1') {
                break;
            }
            // se o usuário não tem cadastro, ele pode se cadastrar
            else if (tem_cadastro == '0') {
                cadastrar_usuario(lista_usuarios, usuario);
                tem_cadastro = '1';
            } else 
                printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!!!\n", 0.02);
                
        } while (tem_cadastro != '1' && tem_cadastro != '0');

        char login[50];
        char senha[50];
        char tentar_novamente;
        int logou = 0;

        // após o usuário se cadastrar, pede os dados de login
        if (tem_cadastro == '1') {
            do {
                printLetterByLetter("\nInforme seu [login]: ", 0.02);
                fgets(login, sizeof(login), stdin);

                printLetterByLetter("Informe sua [senha]: ", 0.02);
                fgets(senha, sizeof(senha), stdin);
                
                // verifica se o login e senha informados são válidos
                int v = verifica_login(lista_usuarios, login, senha);
                // se for válido, loga no app
                if (v == 1) {
                    printLetterByLetter("\nLogin realizado com sucesso!!!\n\n", 0.02);
                    logou = 1;
                }
                // se não for válido, pergunta se o usuário quer tentar novamente
                // se quiser, pergunta os dados de login novamente
                else if (v == 0) {
                    printLetterByLetter("\nUsuario nao encontrado!!!\n\n", 0.02);
                    do {
                        printLetterByLetter("Deseja tentar novamente?\n", 0.02);
                        printLetterByLetter("[1] -> SIM\n", 0.02);
                        printLetterByLetter("[0] -> NAO (Sair do app)\n", 0.02);
                        scanf(" %c", &tentar_novamente);
                        getchar();
                        if (tentar_novamente == '0') {
                            printLetterByLetter("\nObrigado por utilizar nosso app. Volte sempre!\n", 0.02);
                            navegar_app = '0';
                            break;
                        }
                        if (tentar_novamente != '0' && tentar_novamente != '1') 
                            printLetterByLetter("\nERRO!!! Informe uma opcao valida!\n", 0.02);
                            
                    } while (tentar_novamente != '0' && tentar_novamente != '1');
                }

            } while (tentar_novamente == '1' && verifica_login(lista_usuarios, login, senha) == 0);
        }


        // ***********************************************************************************************************************
        // esta é a parte da interação do usuário, uma vez logado, com o app
        //***********************************************************************************************************************
        char interagir_como_usuario = '0';
        if (logou == 1) {
            // verifica se o usuário é admin
            if (verifica_administrador(lista_usuarios, login, senha) == 1) 
            {   
                //  se for, libera o menu de administrador
                printLetterByLetter("Verificamos que voce eh um [usuario administrador].\nSeja bem vindo!!!\n", 0.02);
                printLetterByLetter("\nOperacoes disponiveis para administradores:\n", 0.02);
                printLetterByLetter("[1] -> Adicionar restaurante\n", 0.02);
                printLetterByLetter("[2] -> Remover um restaurante da Lista de Restaurantes\n", 0.02);
                printLetterByLetter("[3] -> Interagir com o app como cliente\n", 0.02);
                printLetterByLetter("[4] -> Listar todos os restaurantes cadastrados\n", 0.02);
                printLetterByLetter("[5] -> Sair do app\n", 0.02);
                char opcao;
                do {
                    if (interagir_como_usuario == '1') {
                        break;
                    }
                    printLetterByLetter("\nInforme a opcao desejada: ", 0.02);
                    scanf(" %c", &opcao);
                    getchar();
                    if (opcao == '5') {
                        printLetterByLetter("\nObrigado por utilizar nosso app. Volte sempre!\n", 0.02);
                        navegar_app = '0'; 
                        break;
                    }

                    switch (opcao) {
                        case '1':
                            cadastrar_restaurante(lista_restaurante, &restaurante);
                            printLetterByLetter("\nNova Lista de Restaurantes:\n", 0.02);
                            menu_restaurantes_adm(lista_restaurante);
                            do {
                                printLetterByLetter("\nDeseja interagir com o app como cliente?\n", 0.02);
                                printLetterByLetter("[1] -> SIM\n", 0.02);
                                printLetterByLetter("[0] -> NAO\n", 0.02);
                                scanf(" %c", &interagir_como_usuario);
                                getchar();
                                
                                switch (interagir_como_usuario) {
                                    case '1':
                                        interagir_como_usuario = '1';
                                        break;
                                    case '0':
                                        interagir_como_usuario = '0';
                                        printLetterByLetter("\nObrigado por usar o app!!!\n\n", 0.02);
                                        break;
                                    default:
                                        printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.02);
                                        break;
                                }
                            } while (interagir_como_usuario != '0' && interagir_como_usuario != '1');

                            break;
                        // remover um restaurante
                        case '2': {
                            ; // o ponto e virgula é para não dar erro de compilação
                            Restaurante restaurante_removido;
                            int pos_remocao;
                            menu_restaurantes_adm(lista_restaurante);
                            do {
                                printLetterByLetter("\nInforme a [POSICAO] do restaurante que deseja remover: ", 0.02);
                                printLetterByLetter("\nOBS: A [POSICAO] do restaurante a ser removido deve ser > 0 e <= a quantidade de restaurantes cadastrados!\n", 0.02);
                                scanf("%d", &pos_remocao);
                                getchar();
                                if (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1) 
                                    printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.02);
                                
                            } while (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1);

                            remove_restaurante_pos(lista_restaurante, &restaurante_removido, pos_remocao);
                            printLetterByLetter("\nNova Lista de Restaurantes:\n", 0.02);
                            menu_restaurantes_adm(lista_restaurante);
                            do {
                                printLetterByLetter("\nDeseja interagir com o app como usuario?\n", 0.02);
                                printLetterByLetter("[1] -> SIM\n", 0.02);
                                printLetterByLetter("[0] -> NAO (Sair do App)\n", 0.02);
                                scanf(" %c", &interagir_como_usuario);
                                getchar();
                                
                                switch (interagir_como_usuario) {
                                    case '1':
                                        interagir_como_usuario = '1';
                                        break;
                                    case '0':
                                        printLetterByLetter("\nObrigado por usar o app!!!\n\n", 0.02);
                                        navegar_app = '0';
                                        break;
                                    default:
                                        printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.02);
                                        break;
                                }
                            } while (interagir_como_usuario != '0' && interagir_como_usuario != '1');
                            
                            break;
                        }
                        case '3':
                            interagir_como_usuario = '1';
                            break;
                        case '4':
                            menu_restaurantes_adm(lista_restaurante);
                            break;
                        default:
                            printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.02);
                            break;
                    }
                } while (opcao != '5');
            }
        } 

        // o usuário não é administrador ou ele quer interagir como um usuário padrão
        if (((logou == 1) && (verifica_administrador(lista_usuarios, login, senha) == 0 )) || (interagir_como_usuario == '1')) 
        {
            printLetterByLetter("\nSeja bem vindo! Sou o seu assistente virtual e te ajudarei no que precisar!\n ", 0.02);
            // aqui, o usuário pode interagir com o app como um usuário padrão, tal como um cliente, tendo acesso aos
            // restaurantes e aos pratos disponíveis, podendo fazer pedidos e avaliar os restaurantes etc
            menu_restaurante_usuario(lista_restaurante);
            char fazer_pedido = '0';
            do {
                printLetterByLetter("\nDeseja fazer um pedido?\n[1] -> SIM \n[0] -> NAO\n", 0.02);
                scanf(" %c", &fazer_pedido);
                getchar();
                if (fazer_pedido != '1' && fazer_pedido != '0') 
                    printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.02);
            } while (fazer_pedido != '1' && fazer_pedido != '0');

            // se o cliente desejar fazer o pedido
            if (fazer_pedido == '1') {
                while (fazer_pedido == '1') 
                {
                    char nome_restaurante[50];
                    char nome_prato_princ[50];
                    Restaurante restaurante_escolhido;
                    Prato prato_escolhido;

                    printLetterByLetter("\nInforme o [NOME DO RESTAURANTE] que deseja fazer o pedido: ", 0.02);
                    do {
                        fgets(nome_restaurante, 50, stdin);
                        nome_restaurante[strlen(nome_restaurante) - 1] = '\0';
                        if (buscar_restaurante(lista_restaurante, &restaurante_escolhido, nome_restaurante) == 0) 
                            printLetterByLetter("\nERRO!!! Informe um [NOME DO RESTAURANTE] valido!\n", 0.02);
                        
                    } while (buscar_restaurante(lista_restaurante, &restaurante_escolhido, nome_restaurante) == 0);
                    

                    printLetterByLetter("Informe o [NOME DO PRATO PRINCIPAL] que deseja fazer o pedido: ", 0.02);
                    do {
                        fgets(nome_prato_princ, 50, stdin);
                        nome_prato_princ[strlen(nome_prato_princ) - 1] = '\0';
                        if (buscar_prato_principal(lista_restaurante, nome_prato_princ, &prato_escolhido) == 0) 
                            printLetterByLetter("\nERRO!!! Informe um [NOME DE PRATO PRINCIPAL] valido!\n", 0.02);
                        
                    } while (buscar_prato_principal(lista_restaurante, nome_prato_princ, &prato_escolhido) == 0);

                    printf("Informe a [QUANTIDADE] de '%s' que deseja pedir: ", prato_escolhido.nome);
                    do {
                        scanf("%d", &pedido.quantidade);
                        getchar();
                        if (pedido.quantidade <= 0) 
                            printLetterByLetter("\nERRO!!! Informe uma [QUANTIDADE] valida!\n", 0.02);
                        
                    } while (pedido.quantidade <= 0);

                    pedido.valorTotal = prato_escolhido.preco * pedido.quantidade;
                    pedido.prato = prato_escolhido;
                    int status = 0; // 0 -> pedido em andamento
                    
                    if (inserir_pedido(restaurante_escolhido.fila_pedidos, pedido) == 1) {
                        printLetterByLetter("\nPedido realizado com sucesso!!!\n", 0.02);
                        printLetterByLetter("*** PROXIMO PEDIDO A SER ENTREGUE ***\n\n", 0.03);
                        mostrar_pedido(restaurante_escolhido.fila_pedidos, status);
                    } else 
                        printLetterByLetter("\nERRO!!! Nao foi possivel realizar o pedido!!!\n", 0.02);
                        
                    // fazer o pagamento
                    int fez_pedido = mostrar_pagamento(pedido.valorTotal);
                    if (fez_pedido){
                        mostrar_estimativa_entrega();
                        status = 1; // 1 -> pedido entregue
                        mostrar_pedido(restaurante_escolhido.fila_pedidos, status);
                        printLetterByLetter("\nPedido finalizado com sucesso!!!\n", 0.02);
                        // remover o pedido da fila de pedidos do restaurante
                        remover_pedido(restaurante_escolhido.fila_pedidos);
                        // avaliacao do restaurante
                        mostrar_avaliacao();
                        fazer_pedido = '0';
                    }
                    else {
                        remover_pedido(restaurante_escolhido.fila_pedidos);
                        printLetterByLetter("\nPedido cancelado com sucesso!!!\n", 0.02);
                        fazer_pedido = '0';
                    }
                }

            }

            printLetterByLetter("\nDeseja continuar navegando pelo app?\n[1] -> SIM \n[0] -> NAO\n", 0.02);
            do {
                scanf(" %c", &navegar_app);
                getchar();
                if (navegar_app != '1' && navegar_app != '0') 
                    printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.02);
                if (navegar_app == '0') {
                    printLetterByLetter("\nObrigado por usar o nosso app!!!\n", 0.02);
                    navegar_app = '0';
                    break;
                } else 
                    navegar_app = '1';
            } while (navegar_app != '1' && navegar_app != '0');
        }    
    }

    limpar_lista(lista_usuarios);
    limpar_lista(lista_restaurante);

    return 0;
}
