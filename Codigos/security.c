#include "security.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>




// Verifica se uma senha contém números consecutivos de qualquer tamanho
bool temNumerosConsecutivos(const char *senha) 
{
    int comprimento = strlen(senha);
    int contagemConsecutiva = 1;  // Inicializa a contagem de dígitos consecutivos em 1
    for (int i = 0; i < comprimento - 1; i++) {
        if (isdigit(senha[i]) && isdigit(senha[i + 1])) {
            int primeiroDigito = senha[i] - '0';
            int segundoDigito = senha[i + 1] - '0';
            if (segundoDigito == primeiroDigito + 1) {
                // Encontrou um dígito consecutivo
                contagemConsecutiva++;
                if (contagemConsecutiva >= 3) {
                    // Encontrou uma sequência de números consecutivos de comprimento 3 ou mais
                    return true;
                }
            } else {
                // Reinicia a contagem de dígitos consecutivos
                contagemConsecutiva = 1;
            }
        }
    }
    // Nenhum número consecutivo de comprimento 3 ou mais encontrado
    return false;
}




// Verifica se uma senha contém caracteres especiais
bool temCaracteresEspeciais(const char *senha) 
{
    int comprimento = strlen(senha);
    for (int i = 0; i < comprimento; i++) {
        // isalnum checa se o caractere é alfanumérico (letra ou número) e isspace checa se o caractere é um espaço em branco
        if (!isalnum(senha[i]) && !isspace(senha[i])) {
            // Encontrou um caractere especial
            return true;
        }
    }
    // Nenhum caractere especial encontrado
    return false;
}




// Função para verificar se uma senha contém pelo menos uma letra maiúscula
bool temLetraMaiuscula(const char *senha) 
{
    int comprimento = strlen(senha);
    for (int i = 0; i < comprimento; i++) {
        // isupper é uma função que verifica se há alguma letra maiúscula na string
        if (isupper(senha[i])) {
            // Encontrou uma letra maiúscula
            return true;
        }
    }
    // Nenhuma letra maiúscula encontrada
    return false;
}




// Função para verificar se uma senha contém pelo menos uma letra minúscula
bool temLetraMinuscula(const char *senha) 
{
    int comprimento = strlen(senha);
    for (int i = 0; i < comprimento; i++) {
        // islower é uma função que verifica se há alguma letra minúscula na string
        if (islower(senha[i])) {
            // Encontrou uma letra minúscula
            return true;
        }
    }
    // Nenhuma letra minúscula encontrada
    return false;
}




// Função para verificar se uma senha atende ao requisito de comprimento mínimo
bool temComprimentoMinimo(const char *senha, int comprimentoMinimo) 
{
    int comprimento = strlen(senha);
    return comprimento >= comprimentoMinimo;
}




// Função para verificar se uma senha contém pelo menos um número
bool temNumero(const char *senha)
{
    int comprimento = strlen(senha);
    for (int i = 0; i < comprimento; i++) {
        // isdigit é uma função que verifica se há algum número na string
        if (isdigit(senha[i])) {
            // Encontrou um número
            return true;
        }
    }
    // Nenhum número encontrado
    return false;
}

