


typedef struct usuario {
    char nome[50];
    char cpf[15];
    char num_telefone[30];
    char login[50];
    char senha[50];
    
} Usuario;


typedef struct lista Lista;



Lista *criar_lista();
int lista_existe(Lista *lista);
int lista_vazia(Lista *lista);
int tam_lista(Lista *lista);

int imprime(Lista *lista);

int inserir_no_inicio(Lista *lista, Usuario usuario);
int inserir_no_fim(Lista *lista, Usuario usuario);

int remover_usuario(Lista *lista, Usuario usuario);

int cadastrar_usuario(Lista *lista, Usuario usuario);
int verifica_login(Lista *lista, char *nome, char *senha);
int insere_adm(Lista *lista, Usuario usuario);


void sleep(float seconds);