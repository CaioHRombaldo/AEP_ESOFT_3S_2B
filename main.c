#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct endereco
{
    char cidade[256];
    char estado[256];
    char rua[256];
    char rua_numero[256];
    char rua_complemento[256];

};

struct servico
{
    char nome[256];
    char categoria[256][256];
    char valor_medio[256];

};

struct usuario_cliente
{
    char nome[256];
    char email[256];
    char senha[256];

    char avaliacao[256];
    
};

struct usuario_prestador
{
    char nome[256];
    char email[256];
    char senha[256];
    char numero_celular[256];
    char profissao[256];
    char cpf[256];
    char sexo;

    char avaliacao[256];

    struct servico servicos_prestador[256];
    struct endereco endereco_prestador[256];
    

};

int main(){

    printf("Hello, World!");

    return 0;
}