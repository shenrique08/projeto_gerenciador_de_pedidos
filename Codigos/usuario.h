#ifndef USUARIO_H
#define USUARIO_H


typedef struct usuario {
    char nome[50];
    char cpf[15];
    char num_telefone[20];
    char login[50];
    char senha[50];
    
} Usuario;


typedef struct lista Lista;



Lista *criar_usuario(); 
int lista_existe(Lista *lista); 
int lista_vazia(Lista *lista); 
int tam_lista(Lista *lista);  

int inserir_no_inicio(Lista *lista, Usuario usuario); 
int inserir_no_fim(Lista *lista, Usuario usuario); 


int remover_usuario(Lista *lista, Usuario usuario); 

int cadastrar_usuario(Lista *lista, Usuario usuario); 

int verifica_login(Lista *lista, char *login, char *senha); 


// verifica se o login e a senha passados como parâmetro são do administrador //(retorna 1 se existir, 0 caso contrário)
int verifica_administrador(Lista *lista, char *login_ins, char *senha_ins);

// insere o adm na lista (retorna 0 se o adm foi cadastrado)
int insere_adm(Lista *lista, Usuario usuario);

// função que ajuda na transição de telas
void sleep(float seconds);

#endif