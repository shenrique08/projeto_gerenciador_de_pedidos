#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "pedido.h"
#include "structs.h" // structs.h contém as structs Restaurante e Prato



Lista_restaurante *criar_restaurante();
int limpar_lista(Lista_restaurante *lista);
int qtd_restaurantes(Lista_restaurante *lista);


int insere_restaurante_no_final(Lista_restaurante *lista, Restaurante r);

// insere uma "simulação de base de dados" dos restaurantes previamente cadastrados
// função é usada ao inicializar o programa
int insere_restaurantes_cadastrados(Lista_restaurante *lista, Restaurante r);


int cadastrar_restaurante(Lista_restaurante *lista, Restaurante *restaurante);
int buscar_restaurante(Lista_restaurante *lista, Restaurante *restaurante, char *nome_restaurante);
int buscar_prato_principal(Lista_restaurante *lista, char *nome_prato, Prato *prato_escolhido);


int remove_restaurante_inicio(Lista_restaurante *lista, Restaurante *r);
int remove_restaurante_final(Lista_restaurante *lista, Restaurante *r);
int remove_restaurante_pos(Lista_restaurante *lista, Restaurante *r, int pos);


// o menu para o adm e para o usuário são diferentes
void menu_restaurantes_adm(Lista_restaurante *lista);
void menu_restaurante_usuario(Lista_restaurante *lista);

// função que ajuda na transição de telas
void printLetterByLetter(const char* message, float seconds);

#endif