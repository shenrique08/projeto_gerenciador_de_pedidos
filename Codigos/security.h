#ifndef security_h
#define security_h


#include <stdbool.h>


// função que verifica se há números consecutivos na senha (ex: 123, 456, 789, 321, 654, 987, etc)
bool temNumerosConsecutivos(const char *senha);
// função que verifica se há caracteres especiais na senha (ex: !@#$%&*()_+) Ou seja, tem que haver pelo menos um caractere especial
bool temCaracteresEspeciais(const char *senha);
// função que verifica se há pelo menos uma letra maiúscula na senha
bool temLetraMaiuscula(const char *senha); 
// função que verifica se há pelo menos uma letra minúscula na senha
bool temLetraMinuscula(const char *senha);
// função que verifica se a senha tem o tamanho mínimo especificado (8 caracteres)
bool temComprimentoMinimo(const char *senha, int comprimentoMinimo);
// função que verifica se há pelo menos um número na senha
bool temNumero(const char *senha);


#endif