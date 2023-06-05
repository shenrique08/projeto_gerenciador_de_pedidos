#ifndef RESTAURANTE_H
#define RESTAURANTE_H
// Estrutura para armazenar os dados do prato
#include "pedido.h"
#include "structs.h"



Lista_restaurante *criar_restaurante();
int limpar_lista(Lista_restaurante *lista);
int qtd_restaurantes(Lista_restaurante *lista);


int insere_restaurante_no_final(Lista_restaurante *lista, Restaurante r);
int insere_restaurantes_cadastrados(Lista_restaurante *lista, Restaurante r);
int cadastrar_restaurante(Lista_restaurante *lista, Restaurante *restaurante);
int buscar_restaurante(Lista_restaurante *lista, Restaurante *restaurante, char *nome_restaurante);
int buscar_prato_principal(Lista_restaurante *lista, char *nome_prato, Prato *prato_escolhido);


int remove_restaurante_inicio(Lista_restaurante *lista, Restaurante *r);
int remove_restaurante_final(Lista_restaurante *lista, Restaurante *r);
int remove_restaurante_pos(Lista_restaurante *lista, Restaurante *r, int pos);


/*void menu_restaurante(Lista_restaurante *lista, char opcao_restaurante, char opcao_combo);*/
void menu_restaurantes_adm(Lista_restaurante *lista);
void menu_restaurante_usuario(Lista_restaurante *lista);
void printLetterByLetter(const char* message, float seconds);





#endif