#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

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
    char avaliacaotot[7];
    char avaliacaonum[7];
    char numero_celular[14];
    char sexo[5];

    struct endereco endereco_cliente[32];
};

struct usuario_prestador
{
    char nome[34];
    char email[50];
    char senha[32];
    char numero_celular[14];
    char profissao[256];
    char cpf[11];
    char sexo[5];
    char avaliacaotot[7];
    char avaliacaonum[7];

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

bool verificaemail(char str1[]){
	int tam = strlen(str1);
	int arbpos,arbverify = 0,dotverify;
	for(int i=0;i<tam;i++){ // procura pela existencia de um @ na string do email.
		if(str1[i] == '@'){
			arbverify++;
			arbpos = i+1;
		}
	}
	if(arbverify == 1 && str1[arbpos] != '.'){ //caso exista apenas um @ e o mesmo não seja seguido de pontuação.
		while(arbpos < tam){
			if(str1[arbpos] == '.'){ //caso exista uma pontuação apos a detecção de um @ e a mesma não seja seguida
				if(str1[arbpos+1] != '\0'){ // de um '\0', retorne true.
					return true;
				}
			}
			arbpos++;
		}
		return false;
	}
	else{
		return false;
	}
}

bool verificasenha(char str1[]){
	//int verify = 0;
	int tam = strlen(str1);
	//Verifica se o tamanho da senha é superior ou igual a 8 caracteres, caso contrário retorna falso.
	if (tam >= 8 && tam <=32){
		//Verifica se existe algum caracter especial na senha.
		for(int i=0;i<tam;i++){
			if((str1[i] > 32 && str1[i] < 48) || str1[i] > 57 && str1[i] < 65){
				verify++;
				i = tam;
			}
		}
		//Verifica se existe alguma letra minúscula na senha.
		for(int i=0;i<tam;i++){
			if(str1[i]>96 && str1[i]<123){
				verify++;
				i = tam;
			}
		}
		//Verifica se existe alguma letra maiúscula na senha.
		for(int i=0;i<tam;i++){
			if(str1[i]>64 && str1[i] < 91){
				verify++;
				i = tam;
			}
		}
		//Verifica se existe algum número na senha.
		for(int i=0;i<tam;i++){
			if(str1[i]>47 && str1[i] < 58){
				verify++;
				i = tam;
			}
		}
		/*Caso todas as verificações sejam positivas, verify será igual a 4 e retornará
		true, caso contrário retornará false.*/
		if (verify == 4){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

int BuscaClienteCPF(char *cpf)
{
    int count = 0;
    for (count = 0; count < totClientes; count++)
    {
        if (strcmp(clientes[count].cpf, cpf) == 0)
        {
            return count;
        }
    }

    return -1;
}

void LeCampo(char *campo, int ini, int fim, char *linha)
{
    // Separa o campo
    int c = 0;
    for (c = ini; c <= fim; c++)
    {
        campo[c - ini] = linha[c];
    }

    // Remove os caracteres vazios
    int tam = fim - ini;

    while (campo[tam] == '=' || campo[tam] == ' ')
    {
        campo[tam] = '\0';
        tam--;
    }
}

void CargaDeDadosEditaveisClientes()
{
    FILE *arq;
    char linha[78];
    char *result;
    int count = 0;
    int cliente_id;

    arq = fopen("Dataclienteedit.txt", "r");

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo editavel.\n");
        return;
    }
    else
    {
        while (!feof(arq))
        {

            result = fgets(linha, 78, arq);

            if (result)
            {
                LeCampo(cpf_temp, 65, 75, linha);
                cliente_id = BuscaClienteCPF(cpf_temp);

                if (cliente_id != -1)
                {
                    LeCampo(clientes[cliente_id].senha, 0, 32, linha);
                    LeCampo(clientes[cliente_id].avaliacaotot, 33, 38, linha);
                    LeCampo(clientes[cliente_id].avaliacaonum, 39, 44, linha);
                    LeCampo(clientes[cliente_id].numero_celular, 45, 63, linha);
                }
            }
        }
    }
}

void CargaDeDadosClientes()
{
    FILE *arq;
    char linha[102];
    char *result;

    arq = fopen("Dataclientes.txt", "r");

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo.\n");
        return;
    }
    else
    {
        while (!feof(arq))
        {

            result = fgets(linha, 102, arq);

            if (result)
            {
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

void CadastrarCliente(){
	char temp_mail[256];
	char temp_senha[256];
	char temp_confirma_senha[256];
	bool escape;
	
	printf("Cadastre-se como cliente");
	
	do{
		printf("\nInsira um email valido: ");
		gets(temp_mail);
	}while(verificaemail(temp_mail) == false);
	
	do{
		printf("\nInsira uma senha valida: ");
		gets(temp_senha);
		if(SenhaValida(temp_senha) == true){
			printf("\nInsira a senha novamente para confirmar: ");
			gets(temp_confirma_senha);
			
			if(strcmp(temp_senha, temp_confirma_senha) == 0)
				escape = true;
		}
		else{
			system("cls");
			printf("Senha invalida, tente novamente");
			
		}
	}while(escape == false);
}

void CadastrarUsuario(){
	int escolha_usuario;
	bool escape = false;
	
	while(escape == false){
		printf("Como deseja utilizar a sua conta? \n");
		printf("1 - Cliente\n");
		printf("2 - Prestador de servico\n");
		
		scanf("%d",&escolha_usuario);
		
		switch(escolha_usuario){
			case 1:
				CadastrarCliente();
				escape = true;		
				break;
			case 2:
//				CadastrarPrestador();
				escape = true;
				break;
			default:
				system("cls");
				printf("Opcao invalida, tente novamente.\n");
				break;
		}
	}
}
//	do{

//	}while(getch() != '1' || getch() ) 
	

int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_CTYPE, "pt_BR.UTF-8");

//    printf("Compilei!!\n");
    CargaDeDadosClientes();
    CadastrarUsuario();
//    printf("nome: %s\n", clientes[1].nome);
//    printf("email: %s\n", clientes[1].email);
//    printf("cpf: %s\n", clientes[1].cpf);
//    printf("sexo: %s\n", clientes[1].sexo);
//    printf("SENHA: %s\n", clientes[1].senha);
//    printf("tot avaliacoes: %s\n", clientes[1].avaliacaotot);
//    printf("num avaliacoes: %s\n", clientes[1].avaliacaonum);
//    printf("num celular: %s\n", clientes[1].numero_celular);

        return 0;
}