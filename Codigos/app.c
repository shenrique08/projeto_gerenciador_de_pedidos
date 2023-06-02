#include "usuario.h"
#include "restaurante.h"
#include "pedido.h"
#include <stdio.h>
#include <string.h>



int main() 
{
    Lista *lista_usuarios = criar_usuario();
    Usuario usuario[2];

    Lista *lista_restaurante = criar_restaurante();
    Restaurante restaurante;

    Pedido pedido;


    insere_adm(lista_usuarios, usuario[0]);
    insere_restaurantes_cadastrados(lista_restaurante, restaurante);

    const char welcomeMessage[] = "\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n";
    printLetterByLetter(welcomeMessage, 0.01);
    printf("\n");
    printLetterByLetter("\n               [BAZOOKA DELIVERY]              \n\n", 0.01);

    char tem_cadastro = '0';

    //***********************************************************************************************************************
    // esta é a parte da verificação do usário e demais funcionalidades
    //***********************************************************************************************************************
    do {
        printLetterByLetter("\nVoce ja tem cadastro no app?\n", 0.01);
        printLetterByLetter("[1] -> SIM\n", 0.01);
        printLetterByLetter("[0] -> NAO\n", 0.01);
        scanf("%c", &tem_cadastro);
        getchar();
        if (tem_cadastro == '1') {
            break;
        }
        else if (tem_cadastro == '0') {
            cadastrar_usuario(lista_usuarios, usuario[1]);
            tem_cadastro = '1';
        } else 
            printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!!!\n", 0.01);
            
    } while (tem_cadastro != '1' && tem_cadastro != '0');

    char login[50];
    char senha[50];
    char tentar_novamente;
    int logou = 0;

    if (tem_cadastro == '1') {
        do {
            printLetterByLetter("\nInforme seu [login]: ", 0.01);
            fgets(login, sizeof(login), stdin);

            printLetterByLetter("Informe sua [senha]: ", 0.01);
            fgets(senha, sizeof(senha), stdin);
            
            int v = verifica_login(lista_usuarios, login, senha);
            if (v == 1) {
                printLetterByLetter("\nLogin realizado com sucesso!!!\n\n", 0.01);
                logou = 1;
            }
            else if (v == 0) {
                printLetterByLetter("\nUsuario nao encontrado!!!\n\n", 0.01);
                do {
                    printLetterByLetter("Deseja tentar novamente?\n", 0.01);
                    printLetterByLetter("[1] -> SIM\n", 0.01);
                    printLetterByLetter("[0] -> NAO\n", 0.01);
                    scanf(" %c", &tentar_novamente);
                    getchar();

                    if (tentar_novamente != '0' && tentar_novamente != '1') 
                        printLetterByLetter("\nERRO!!! Informe uma opcao valida!\n", 0.01);
                        
                } while (tentar_novamente != '0' && tentar_novamente != '1');
            }

        } while (tentar_novamente == '1' && verifica_login(lista_usuarios, login, senha) == 0);
        
    }



    // ***********************************************************************************************************************
    // esta é a parte da interação do usuário, uma vez logado, com o app
    //***********************************************************************************************************************
    char interagir_como_usuario = '0';
    if (logou == 1) {
        if (verifica_administrador(lista_usuarios, login, senha) == 1) 
        {
            const char mensagem1[] = "Verificamos que voce eh um usuario [administrador]!!!\nSeja bem vindo!!!";
            printLetterByLetter(mensagem1, 0.01);
            printf("\n");
            char opcao;
            int pos_cadastro, pos_remocao;
            
            do {
                if (interagir_como_usuario == '1') {
                    break;
                }
                printLetterByLetter("\nOperacoes disponiveis para administradores:\n", 0.01);
                printLetterByLetter("[1] -> Adicionar restaurante\n", 0.01);
                printLetterByLetter("[2] -> Remover um restaurante da Lista de Restaurantes\n", 0.01);
                printLetterByLetter("[3] -> Interagir com o app como cliente\n", 0.01);
                printLetterByLetter("[4] -> Listar todos os restaurantes cadastrados\n", 0.01);
                printLetterByLetter("[5] -> Sair do app\n", 0.01);
                printLetterByLetter("\nInforme a opcao desejada: ", 0.01);
                scanf(" %c", &opcao);
                getchar();
                if (opcao == '5') {
                    printLetterByLetter("\nObrigado por utilizar nosso app. Volte sempre!\n", 0.01); 
                    break;
                }

                switch (opcao) {
                    case '1':
                        do {
                            printLetterByLetter("\nInforme a [POSICAO] que deseja cadastrar o novo restaurante: ", 0.01);
                            scanf("%d", &pos_cadastro);
                            getchar();
                            
                            if (pos_cadastro < 1 || pos_cadastro > tam_lista(lista_restaurante) + 1) {
                                printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.01);
                                sleep(0.5);
                            }
                        } while (pos_cadastro < 1 || pos_cadastro > tam_lista(lista_restaurante) + 1);
                        
                        cadastrar_restaurante(lista_restaurante, &restaurante, pos_cadastro);
                        printLetterByLetter("\nRestaurante cadastrado com sucesso!!!\n", 0.01);
                        do {
                            printLetterByLetter("\nDeseja interagir com o app como cliente?\n", 0.01);
                            printLetterByLetter("[1] -> SIM\n", 0.01);
                            printLetterByLetter("[0] -> NAO\n", 0.01);
                            scanf(" %c", &interagir_como_usuario);
                            getchar();
                            
                            switch (interagir_como_usuario) {
                                case '1':
                                    interagir_como_usuario = '1';
                                    break;
                                case '0':
                                    printLetterByLetter("\nObrigado por usar o app!!!\n\n", 0.01);
                                    break;
                                default:
                                    printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.01);
                                    break;
                            }
                        } while (interagir_como_usuario != '0' && interagir_como_usuario != '1');

                        break;
                    case '2': {
                        ; // o ponto e virgula é para não dar erro de compilação
                        Restaurante restaurante_removido;
                        do {
                            printLetterByLetter("\nInforme a [POSICAO] do restaurante que deseja remover: ", 0.01);
                            printLetterByLetter("\nOBS: A [POSICAO] do restaurante a ser removido deve ser > 0 e <= a quantidade de restaurantes cadastrados!\n", 0.01);
                            scanf("%d", &pos_remocao);
                            getchar();
                            if (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1) 
                                printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.01);
                            
                        } while (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1);

                        remove_restaurante_pos(lista_restaurante, &restaurante_removido, pos_remocao);
                        printLetterByLetter("\nNova Lista de Restaurantes:\n", 0.01);
                        menu_restaurantes(lista_restaurante);
                        do {
                            printLetterByLetter("\nDeseja interagir com o app como usuario?\n", 0.01);
                            printLetterByLetter("[1] -> SIM\n", 0.01);
                            printLetterByLetter("[0] -> NAO\n", 0.01);
                            scanf(" %c", &interagir_como_usuario);
                            getchar();
                            
                            switch (interagir_como_usuario) {
                                case '1':
                                    interagir_como_usuario = '1';
                                    break;
                                case '0':
                                    printLetterByLetter("\nObrigado por usar o app!!!\n\n", 0.01);
                                    break;
                                default:
                                    printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.01);
                                    break;
                            }
                        } while (interagir_como_usuario != '0' && interagir_como_usuario != '1');
                        
                        break;
                    }
                    case '3':
                        interagir_como_usuario = '1';
                        break;
                    case '4':
                        menu_restaurantes(lista_restaurante);
                        break;
                    default:
                        printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.01);
                        break;
                }
            } while (opcao != '5');
        }
    } 

    // o usuário não é administrador ou ele quer interagir como um usuário padrão
    if (((logou == 1) && (verifica_administrador(lista_usuarios, login, senha) == 0 )) || (interagir_como_usuario == '1')) 
    {
        
        const char mensagem2[] = "\nSeja bem vindo";
        printLetterByLetter(mensagem2, 0.01);
        char nome[50];
        strcpy(nome, usuario[0].nome);
        // tirar o \n do nome
        nome[strlen(nome) - 1] = '\0';
        printf("[%s]", nome);
        printLetterByLetter("Sou o seu assistente virtual e te ajudarei no que voce precisar!\n", 0.01);


        // aqui, o usuário pode interagir com o app como um usuário padrão, tal como um cliente, tendo acesso aos
        // restaurantes e aos pratos disponíveis, podendo fazer pedidos e avaliar os restaurantes etc
        menu_restaurantes(lista_restaurante);
        char fazer_pedido = '0';
        printLetterByLetter("\nDeseja fazer um pedido?\n[1] -> SIM \n[0] -> NAO\n", 0.01);
        do {
            scanf(" %c", &fazer_pedido);
            getchar();
            if (fazer_pedido != '1' && fazer_pedido != '0') {
                printf("\nERRO!!! Informe uma [OPCAO] valida!\n");
            }
        } while (fazer_pedido != '1' && fazer_pedido != '0');

        // se o cliente desejar fazer o pedido
        if (fazer_pedido == '1') {
            while (fazer_pedido == '1') 
            {
                char nome_restaurante[50];
                char nome_prato_princ[50];
                Restaurante restaurante_escolhido;
                Prato prato_escolhido;
                //int qtd_pedidos = 1;
                
                //float valor_total = 0;
                printLetterByLetter("\nInforme o [NOME] do restaurante que deseja fazer o pedido: ", 0.01);
                do {
                    fgets(nome_restaurante, 50, stdin);
                    nome_restaurante[strlen(nome_restaurante) - 1] = '\0';
                    if (buscar_restaurante(lista_restaurante, &restaurante_escolhido, nome_restaurante) == 0) {
                        printLetterByLetter("\nERRO!!! Informe um [NOME] de restaurante valido!\n", 0.01);
                    }
                } while (buscar_restaurante(lista_restaurante, &restaurante_escolhido, nome_restaurante) == 0);
                
                
                printLetterByLetter("Informe o [NOME] do combo que deseja fazer o pedido: ", 0.01);
                do {
                    fgets(nome_prato_princ, 50, stdin);
                    nome_prato_princ[strlen(nome_prato_princ) - 1] = '\0';
                    if (buscar_prato_principal(lista_restaurante, nome_prato_princ, &prato_escolhido) == 0) {
                        printLetterByLetter("\nERRO!!! Informe um [NOME] de combo valido!\n", 0.01);
                    }
                } while (buscar_prato_principal(lista_restaurante, nome_prato_princ, &prato_escolhido) == 0);

                printLetterByLetter("Informe a [QUANTIDADE] de combos que deseja pedir: ", 0.01);
                do {
                    scanf("%d", &pedido.quantidade);
                    getchar();
                    if (pedido.quantidade <= 0) {
                        printLetterByLetter("\nERRO!!! Informe uma [QUANTIDADE] valida!\n", 0.01);
                    }
                } while (pedido.quantidade <= 0);

                pedido.valorTotal = prato_escolhido.preco * pedido.quantidade;
                pedido.prato = prato_escolhido;
                //pedido.quantidade = 1;
                int status = 0; // 0 -> pedido em andamento
                
                if (inserir_pedido(restaurante_escolhido.fila_pedidos, pedido) == 1) {
                    printLetterByLetter("\nPedido realizado com sucesso!!!\n", 0.01);
                    printLetterByLetter("*** PROXIMO PEDIDO A SER ENTREGUE ***\n", 0.03);
                    mostrar_pedido(restaurante_escolhido.fila_pedidos, status);
                } else {
                    printLetterByLetter("\nERRO!!! Nao foi possivel realizar o pedido!!!\n", 0.01);
                }
                
                /*printLetterByLetter("\nDeseja fazer outro pedido? \n[1] -> SIM \n[0] -> NAO\n", 0.01);
                char fazer_outro_pedido = '0';
                do {
                    scanf(" %c", &fazer_outro_pedido);
                    getchar();
                    if (fazer_outro_pedido != '1' && fazer_outro_pedido != '0') {
                        printf("\nERRO!!! Informe uma [OPCAO] valida!\n");
                    }
                } while (fazer_outro_pedido == '1');*/

                    
                // fazer o pagamento
                mostrar_pagamento(pedido.valorTotal);
                mostrar_estimativa_entrega();
                // a funcao acima tem sleep para simular o tempo de entrega
                // alterar o status para entregue
                status = 1; // 1 -> pedido entregue
                mostrar_pedido(restaurante_escolhido.fila_pedidos, status);
                printLetterByLetter("\nPedido finalizado com sucesso!!!\n", 0.01);
                // remover o pedido da fila de pedidos do restaurante
                remover_pedido(restaurante_escolhido.fila_pedidos);
                //mostrar_pedido(restaurante_escolhido.fila_pedidos, status);
                // avaliacao do restaurante
                fazer_pedido = '0';

            }

        }

        else {
            printLetterByLetter("\nObrigado por usar o aplicativo!te a proxima!\n", 0.01);
        }
    }    
    

    // caso não tenha logado, o usuário não pode interagir com o app

    limpar_lista(lista_usuarios);
    limpar_lista(lista_restaurante);

    return 0;
}
