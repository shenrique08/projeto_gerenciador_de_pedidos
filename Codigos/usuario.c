#include "usuario.h"
#include "restaurante.h"
#include "security.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct no {
    Usuario dados_usuario;
    struct no *prox;

} No;



typedef struct lista {
    No *inicio;
    int tam_lista;

} Lista;





/*===============================================================================================================================*/

Lista *criar_usuario()
{
    Lista *usuario = (Lista *) calloc(1, sizeof(Lista));
    usuario->inicio = NULL;
    usuario->tam_lista = 0;

    return usuario;
}





int lista_existe(Lista *lista)
{
    if (lista == NULL)
        return 0;
    return 1;
}





int lista_vazia(Lista *lista)
{
    if (lista == NULL) return -1;
    if (lista->inicio == NULL)
        return 1;
    else 
        return 0;
}





int tam_lista(Lista *lista)
{
    if (lista == NULL) return -1;

    if (lista->inicio == NULL)
        return 0;
    
    return lista->tam_lista;
}





int mostra_usuarios(Lista *lista)
{
    if (lista == NULL) 
        return -1;
    if (lista_vazia(lista) == 1) 
        return -2;
    No *noLista = lista->inicio;

    while (noLista != NULL) {
        printf("\nNOME: %s\n", noLista->dados_usuario.nome);
        printf("CPF: %s\n", noLista->dados_usuario.cpf);
        printf("NUMERO DE TELEFONE: %s\n", noLista->dados_usuario.num_telefone);
        printf("LOGIN: %s", noLista->dados_usuario.login);
        printf("SENHA: %s\n", noLista->dados_usuario.senha);

        noLista = noLista->prox;
    }

    return 0;
}





/*======================================================================================================================*/

int inserir_no_inicio(Lista *lista, Usuario usuario)
{
    // se a lista não existe, retorne 2
    if (lista_existe(lista) == 0)
        return 2;
    No *no = (No *) calloc(1, sizeof(No));

    no->dados_usuario = usuario;
    no->prox = lista->inicio;
    lista->inicio = no;

    lista->tam_lista++;

    return 0;
}





int inserir_no_fim(Lista *lista, Usuario usuario)
{
    if (lista_existe(lista) == 0)
        return -1;
    if (lista_vazia(lista) == 1)
        return inserir_no_inicio(lista, usuario);

    No *noLista = lista->inicio;

    while (noLista->prox != NULL)
        noLista = noLista->prox;

    No *novo_no = (No *) calloc(1, sizeof(No));

    novo_no->dados_usuario = usuario;
    noLista->prox = novo_no;
    novo_no->prox = NULL;

    lista->tam_lista++;

    return 0;
}





int remover_usuario(Lista *lista, Usuario usuario)
{
    if (lista_existe(lista) == 0)
        return -1;
    if (lista_vazia(lista) == 1)
        return -2;
    
    No *anterior = NULL;
    No *atual = lista->inicio;

    // percorrendo a lista até encontrar o aluno
    while (atual != NULL && strcmp(atual->dados_usuario.nome, usuario.nome) != 0) {
        anterior = atual;
        atual = atual ->prox;
    }

    // se o elemento não foi encontrado
    if (atual == NULL)
        return -1;
    
    // remove o elemento encontrado
    if (anterior == NULL) // é o primeiro elemento
        lista->inicio = atual->prox;
    else 
        anterior->prox = atual->prox;

    lista->tam_lista--;
    free(atual);

    return 0;
}





int cadastrar_usuario(Lista* lista, Usuario usuario) {
    if (lista_existe(lista) == 0)
        return -1;

    No* novo_no = (No*)calloc(1, sizeof(No));
    novo_no->dados_usuario = usuario;

    printLetterByLetter("\n=============== SISTEMA DE CADASTRO DE USUARIO ===============\n", 0.02);
    printLetterByLetter("\nInforme seu [NOME]: ", 0.02);
    fgets(novo_no->dados_usuario.nome, sizeof(novo_no->dados_usuario.nome), stdin);

    printLetterByLetter("Informe seu [CPF]: ", 0.02);
    fgets(novo_no->dados_usuario.cpf, sizeof(novo_no->dados_usuario.cpf), stdin);

    printLetterByLetter("Informe seu [NUMERO DE TELEFONE]: (+55) ", 0.02);
    fgets(novo_no->dados_usuario.num_telefone, sizeof(novo_no->dados_usuario.num_telefone), stdin);

    printLetterByLetter("\nAgora, crie seu [LOGIN] e sua [SENHA]:\nOBS: Escolha seu [LOGIN] e sua [SENHA] de forma segura!\n", 0.02);
    printLetterByLetter("\n[LOGIN]: ", 0.02);
    fgets(novo_no->dados_usuario.login, sizeof(novo_no->dados_usuario.login), stdin);

    bool isPasswordSecure = false;
    while (!isPasswordSecure) {
        printLetterByLetter("[SENHA]: ", 0.02);

        fgets(novo_no->dados_usuario.senha, sizeof(novo_no->dados_usuario.senha), stdin);

        // Keep track of password errors
        bool tem_erro = false;

        if (hasConsecutiveNumbers(novo_no->dados_usuario.senha)) {
            printLetterByLetter("A senha [NAO PODE conter sequencia de numeros consecutivos].\n", 0.02);
            tem_erro = true;
        }

        if (!hasSpecialCharacters(novo_no->dados_usuario.senha)) {
            printLetterByLetter("A senha [DEVE conter caracteres especiais].\n", 0.02);
            tem_erro = true;
        }

        if (!hasUppercaseLetter(novo_no->dados_usuario.senha)) {
            printLetterByLetter("A senha [DEVE conter pelo menos uma letra maiuscula].\n", 0.02);
            tem_erro = true;
        }

        if (!hasLowercaseLetter(novo_no->dados_usuario.senha)) {
            printLetterByLetter("A senha [DEVE conter pelo menos uma letra minuscula].\n", 0.02);
            tem_erro = true;
        }

        if (!hasMinimumLength(novo_no->dados_usuario.senha, 8)) {
            printLetterByLetter("A senha [DEVE ter no minimo 8 caracteres].\n", 0.02);
            tem_erro = true;
        }

        if (!hasNumber(novo_no->dados_usuario.senha)) {
            printLetterByLetter("A senha [DEVE conter pelo menos um numero].\n", 0.02);
            tem_erro = true;
        }

        if (tem_erro) {
            printLetterByLetter("TENTE NOVAMENTE.\n\n", 0.02);
            continue;
        }

        isPasswordSecure = true;
        printLetterByLetter("\nLOGIN E SENHA CADASTRADOS COM SUCESSO!\n", 0.02);
    }

    inserir_no_fim(lista, novo_no->dados_usuario);

    return 0;
}







int verifica_login(Lista *lista, char *login, char *senha)
{
    if (lista == NULL) 
        return -1;  
    
    if (lista_vazia(lista) == 1) 
        return -2;  
    
    No *atual = lista->inicio;
    
    while (atual != NULL) {
        if (strcmp(atual->dados_usuario.login, login) == 0 && strcmp(atual->dados_usuario.senha, senha) == 0) 
            return 1;  // Login válido
        atual = atual->prox;
    }

    return 0;  // Login inválido
}




int verifica_administrador(Lista *lista, char *login_ins, char *senha_ins)
{
    if (lista == NULL) 
        return -1;  
    
    if (lista_vazia(lista) == 1) 
        return -2;  
    
    No *atual = lista->inicio;
    
    // verificaremos o primeiro usuário da lista, que é o administrador
    if (strcmp(atual->dados_usuario.login, login_ins) == 0 && strcmp(atual->dados_usuario.senha, senha_ins) == 0) 
        return 1;  // é administrador

    return 0;  // não é administrador
}





int insere_adm(Lista *lista, Usuario usuario)
{
    if (lista_existe(lista) != 0) {
        No *novo_no = (No*) calloc(1, sizeof(No));
        novo_no->dados_usuario = usuario;

        strcpy(novo_no->dados_usuario.cpf, "adm");
        strcpy(novo_no->dados_usuario.nome, "adm");
        strcpy(novo_no->dados_usuario.num_telefone, "666");

        strcpy(novo_no->dados_usuario.login, "bazooka");
        strcat(novo_no->dados_usuario.login, "\n"); // Adiciona '\n' ao final da string login
        strcpy(novo_no->dados_usuario.senha, "delas");
        strcat(novo_no->dados_usuario.senha, "\n"); // Adiciona '\n' ao final da string senha

        inserir_no_inicio(lista, novo_no->dados_usuario);
    }

    return 0;
}






void sleep(float seconds) 
{
    fflush(stdout);  // Flush the output to ensure immediate printing

    struct timespec sleepTime;
    sleepTime.tv_sec = (time_t) seconds;
    sleepTime.tv_nsec = (long) ((seconds - (time_t) seconds) * 1e9);

    nanosleep(&sleepTime, NULL);
}
