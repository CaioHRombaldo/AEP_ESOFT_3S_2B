#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>


struct endereco
{
    char estado[256];
    char cidade[256];
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
    char nome[34];
    char email[50];
    char senha[32];
	char cpf[11];
    int avaliacaotot;
    int avaliacaonum;
    char numero_celular[256];
    char sexo[5];
    
    struct endereco endereco_cliente[32];
};

struct usuario_prestador
{
    char nome[34];
    char email[50];
    char senha[32];
    char numero_celular[256];
    char profissao[256];
    char cpf[11];
    char sexo[5];
    int avaliacaotot;
    int avaliacaonum;

    struct servico servicos_prestador[32];
    struct endereco endereco_prestador[32];
    

};

// Declaração de Variaveis Globais:
struct usuario_cliente clientes[256];
int totClientes = 0;

struct usuario_prestador prestadores[256];
int totPrestadores = 0;

char cpf_temp[11];

// Fim Declaração de Variaveis Globais

int BuscaClienteCPF(char* cpf){
    int count = 0;
    for(count = 0; count<totClientes; count++){
        if(strcmp(clientes[count].cpf, cpf) == 0){
            return count;
        }
    }

    return -1;
}

void LeCampo(char* campo, int ini, int fim, char* linha){
    // Separa o campo
    int c = 0;
    for(c = ini; c <= fim; c++){
        campo[c-ini] = linha[c];
    }

    // Remove os caracteres vazios
    int tam = fim - ini;

    while(campo[tam] == '=' || campo[tam] == ' '){
        campo[tam] = '\0';
        tam--;
    }

}

void CargaDeDadosEditaveisClientes(){
    FILE *arq;
    char linha[78];
    char *result;
    int count = 0;
    int cliente_id;

    arq = fopen("Dataclienteedit.txt","r");
    
    if(arq == NULL) {
        printf("Problema ao abrir o arquivo editavel.\n");
        return;

    } else {
        while(!feof(arq)){

            result = fgets(linha, 78, arq);

            if (result){
                LeCampo(cpf_temp, 65, 75, linha);
                cliente_id = BuscaClienteCPF(cpf_temp);
                
                if (cliente_id != -1){
                    LeCampo(clientes[cliente_id].senha, 0, 32, linha);

                }

            }

        }

    }
    
}

void CargaDeDadosClientes(){
    FILE *arq;
    char linha[102];
    char *result;

    arq = fopen("Dataclientes.txt","r");
    
    if(arq == NULL) {
        printf("Problema ao abrir o arquivo.\n");
        return;

    } else {
        while(!feof(arq)){

            result = fgets(linha, 102, arq);

            if (result){
                LeCampo(clientes[totClientes].nome, 0, 32, linha);
                LeCampo(clientes[totClientes].email, 34, 83, linha);
                LeCampo(clientes[totClientes].sexo, 84, 88, linha);
                LeCampo(clientes[totClientes].cpf, 89, 99, linha);
            
            }
            totClientes++;
        }
        CargaDeDadosEditaveisClientes();

    }
}


int main(){
    setlocale (LC_ALL, "");
    setlocale (LC_CTYPE, "pt_BR.UTF-8");
    
    printf("Compilei!!\n");
    CargaDeDadosClientes();
    printf("nome: %s\n", clientes[1].nome);
    printf("email: %s\n", clientes[1].email);
    printf("cpf: %s\n", clientes[1].cpf);
    printf("sexo: %s\n", clientes[1].sexo);
    printf("SENHA: %s\n", clientes[1].senha);

    return 0;
}