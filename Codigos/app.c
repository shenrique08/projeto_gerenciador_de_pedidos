#include "usuario.h"
#include "restaurante.h"
#include <stdio.h>
#include <string.h>



int main() {
    Lista *lista_usuarios = criar_lista();
    Usuario usuario[2];

    Lista *lista_restaurante = criar_restaurante();
    Restaurante restaurante;

    insere_adm(lista_usuarios, usuario[0]);
    insere_restaurantes_cadastrados(lista_restaurante, restaurante);

    const char welcomeMessage[] = "\n*************** SEJA BEM VINDO AO NOSSO APLICATIVO ***************\n";
    printLetterByLetter(welcomeMessage, 0.05);
    printf("\n");
    printLetterByLetter("\n               [BAZOOKA DELIVERY]              \n\n", 0.1);

    char tem_cadastro = '0';

    do {
        printLetterByLetter("\nVoce ja tem cadastro no app?\n", 0.1);
        printLetterByLetter("[1] -> SIM\n", 0.1);
        printLetterByLetter("[0] -> NAO\n", 0.1);
        scanf("%c", &tem_cadastro);
        getchar();
        if (tem_cadastro == '1') {
            break;
        }
        else if (tem_cadastro == '0') {
            cadastrar_usuario(lista_usuarios, usuario[1]);
            tem_cadastro = '1';
        } else 
            printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!!!\n", 0.1);
            
    } while (tem_cadastro != '1' && tem_cadastro != '0');
    
    char login[50];
    char senha[50];
    char tentar_novamente;
    int logou = 0;

    if (tem_cadastro == '1') {
        do {
            printLetterByLetter("\nInforme seu [login]: ", 0.1);
            fgets(login, sizeof(login), stdin);

            printLetterByLetter("Informe sua [senha]: ", 0.1);
            fgets(senha, sizeof(senha), stdin);
            
            int v = verifica_login(lista_usuarios, login, senha);
            if (v == 1) {
                printLetterByLetter("\nLogin realizado com sucesso!!!\n\n", 0.1);
                logou = 1;
            }
            else if (v == 0) {
                printLetterByLetter("\nUsuario nao encontrado!!!\n\n", 0.2);
                do {
                    printLetterByLetter("Deseja tentar novamente?\n", 0.2);
                    printLetterByLetter("[1] -> SIM\n", 0.1);
                    printLetterByLetter("[0] -> NAO\n", 0.1);
                    scanf(" %c", &tentar_novamente);
                    getchar();

                    if (tentar_novamente != '0' && tentar_novamente != '1') 
                        printLetterByLetter("\nERRO!!! Informe uma opcao valida!\n", 0.1);
                        
                } while (tentar_novamente != '0' && tentar_novamente != '1');
            }

        } while (tentar_novamente == '1' && verifica_login(lista_usuarios, login, senha) == 0);
        
    }

    if (logou == 1) {
        if (verifica_administrador(lista_usuarios, login, senha) == 1) {
            const char mensagem1[] = "Opa!!! Verificamos que voce eh um usuario [administrador]!!!\nSeja bem vindo!!!";
            printLetterByLetter(mensagem1, 0.1);
            printf("\n\n");
            mostrar_restaurantes(lista_restaurante);
            char opcao;
            int pos_cadastro;
            int pos_remocao;
            do {
                printLetterByLetter("\n[1] -> Adicionar restaurante\n", 0.1);
                printLetterByLetter("[2] -> Remover um restaurante da Lista de Restaurantes\n", 0.1);
                printLetterByLetter("[3] -> Sair\n", 0.1);
                printLetterByLetter("\nInforme a opcao desejada: ", 0.1);
                scanf(" %c", &opcao);
                getchar();
                
                switch (opcao) {
                    case '1':
                        do {
                            printLetterByLetter("\nInforme a [POSICAO] que deseja cadastrar o novo restaurante: ", 0.1);
                            scanf("%d", &pos_cadastro);
                            getchar();
                            
                            if (pos_cadastro < 1 || pos_cadastro > tam_lista(lista_restaurante) + 1) {
                                printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.1);
                                sleep(0.5);
                            }
                        } while (pos_cadastro < 1 || pos_cadastro > tam_lista(lista_restaurante) + 1);
                        
                        cadastrar_restaurante(lista_restaurante, &restaurante, pos_cadastro);
                        printLetterByLetter("\nNova Lista de Restaurantes:\n", 0.1);
                        mostrar_restaurantes(lista_restaurante);
                        break;
                    case '2': {
                        Restaurante restaurante_removido;
                        do {
                            printLetterByLetter("\nInforme a [POSICAO] do restaurante que deseja remover: ", 0.1);
                            printLetterByLetter("\nOBS: A [POSICAO] do restaurante a ser removido deve ser > 0 e <= a quantidade de restaurantes cadastrados!\n", 0.1);
                            scanf("%d", &pos_remocao);
                            getchar();
                            if (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1) 
                                printLetterByLetter("\nERRO!!! Informe uma [POSICAO] valida!\n", 0.1);
                            
                        } while (pos_remocao < 1 || pos_remocao > tam_lista(lista_restaurante) + 1);

                        remove_restaurante_pos(lista_restaurante, &restaurante_removido, pos_remocao);
                        printLetterByLetter("\nNova Lista de Restaurantes:\n", 0.1);
                        mostrar_restaurantes(lista_restaurante);
                        break;
                    }
                    case '3':
                        break;
                    default:
                        printLetterByLetter("\nERRO!!! Informe uma [OPCAO] valida!\n", 0.1);
                        break;
                }
            } while (opcao != '3');
        } else {
            const char mensagem2[] = "Opa!!! Verificamos que voce eh um novo [usuario]!!!\nSeja bem vindo!!!";
            printLetterByLetter(mensagem2, 0.1);
            printf("\n\n");
            menu_restaurante(lista_restaurante);
        }
    }   


    limpar_lista(lista_usuarios);
    limpar_lista(lista_restaurante);

    return 0;
}