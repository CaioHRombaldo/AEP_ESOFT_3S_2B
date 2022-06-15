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
    char nome[35];
    char email[51];
    char senha[33];
    char cpf[12];
    char avaliacaotot[8];
    char avaliacaonum[8];
    char numero_celular[21];
    char sexo[6];

    struct endereco endereco_cliente[32];
};

struct usuario_prestador
{
    char nome[35];
    char email[51];
    char senha[33];
    char numero_celular[21];
    char profissao[256];
    char cpf[12];
    char sexo[6];
    char avaliacaotot[8];
    char avaliacaonum[8];

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

bool verificacpf(char *cpf){
	int cpfnum[11];
	int i, confirma,valido = 0, igualdade = 0;
	
	for(i = 0; i<strlen(cpf); i++){
		cpfnum[i] = ((int)(cpf[i])) - 48;
	}
	system("pause");
	confirma = calccpf(9,cpfnum);
	if (confirma == cpfnum[9]){ //confirma se o 10 digito do cpf � valido.
		valido++;
	}
	confirma = calccpf(10,cpfnum);
	if(confirma == cpfnum[10]){ //confirma se o 11 digito do cpf � valido.
		valido++;
	}
	for(i=0; i<11; i++){ //confirma se o cpf n�o � uma sequencia de numeros iguais.
		if(cpfnum[0] == cpfnum[i]){
			igualdade++;
		}
	}
	if(igualdade == 11){
		return false;
	}
	if(valido == 2){
		return true;
	}
	else{
		return false;
	}
	
}

int calccpf(int parar, int cpftemp[]){ //calcula o digito correto do cpf(10 e 11).
	int i, cont = 0;
    for(i=0; i < parar;i++){
        cont = cont + (cpftemp[i] * ((parar+1)-i));      
    }
    cont = 11 - (cont % 11);   
    if(cont>9){
        cont = 0;   
    }
    return cont;
}

bool verificaemail(char str1[]){
	int tam = strlen(str1);
	int arbpos,arbverify = 0,dotverify;
    int i;

    for(i=0;i<tam;i++){ // procura pela existencia de um @ na string do email.
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
	int verify = 0;
	int tam = strlen(str1);
    int i;
	//Verifica se o tamanho da senha é superior ou igual a 8 caracteres, caso contrário retorna falso.
	if (tam >= 8 && tam <=32){
		//Verifica se existe algum caracter especial na senha.
		for(i=0;i<tam;i++){
			if((str1[i] > 32 && str1[i] < 48) || str1[i] > 57 && str1[i] < 65){
				verify++;
				i = tam;
			}
		}
		//Verifica se existe alguma letra minúscula na senha.
		for(i=0;i<tam;i++){
			if(str1[i]>96 && str1[i]<123){
				verify++;
				i = tam;
			}
		}
		//Verifica se existe alguma letra maiúscula na senha.
        for(i=0;i<tam;i++){
			if(str1[i]>64 && str1[i] < 91){
				verify++;
				i = tam;
			}
		}
		//Verifica se existe algum número na senha.
        for(i=0;i<tam;i++){
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
                    LeCampo(clientes[cliente_id].avaliacaotot, 34, 38, linha);
                    LeCampo(clientes[cliente_id].avaliacaonum, 40, 44, linha);
                    LeCampo(clientes[cliente_id].numero_celular, 46, 63, linha);
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

    char temp_cidade[128];
    char temp_endereco[128];
    char temp_complemento;
    char temp_numero_celular[128];
    char temp_cpf[128];
    char temp_sexo;

    int escolha_usuario; 
	bool escape;
	
    system("cls");

	printf("Cadastre-se como cliente");
	
	do{
		printf("\nInsira um email valido: ");
        fflush(stdin);
		gets(temp_mail);
	}while(verificaemail(temp_mail) == false);
	
    escape = false;
	do{
		printf("\nInsira uma senha valida: ");
        fflush(stdin);
		gets(temp_senha);
		if(verificasenha(temp_senha) == true){
			printf("\nInsira a senha novamente para confirmar: ");
            fflush(stdin);
			gets(temp_confirma_senha);
			
			if(strcmp(temp_senha, temp_confirma_senha) == 0)
				escape = true;
		}
		else{
			system("cls");
			printf("\nSenha invalida, tente novamente");
			
		}
	}while(escape == false);

    system("cls");

    printf("\nInsira a sua cidade: ");
    fflush(stdin);
    gets(temp_cidade);

    printf("\nInsira o seu endereço residencial: ");
    fflush(stdin);
    gets(temp_endereco);

    escape == false;
    while(escape == false){
        printf("\nEscolha o complemento: ");
        printf("\n1 - Casa\n2 - Apartamento\n3 - Condomínio");

        switch (escolha_usuario){
        case 1:
            temp_complemento = 'h';
            escape = true; 
            break;
        case 2:
            temp_complemento = 'a';
            escape = true;
            break;
        case 3:
            temp_complemento = 'c';
            escape = true;
            break;
        default:
            system("cls");
            printf("Insira uma opcao valida");
            break;
        }

    }

    printf("\nInsira seu numero de celular: ");
    fflush(stdin);
    gets(temp_numero_celular);

    do{
        printf("\nInsira seu CPF: ");
        fflush(stdin);
        gets(temp_cpf);
    }while(verificacpf(temp_cpf) == false);


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
	
int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_CTYPE, "pt_BR.UTF-8");

    CargaDeDadosClientes();
    //CadastrarUsuario();

    printf("nome: %s\n", clientes[1].nome);
    printf("email: %s\n", clientes[1].email);
    printf("cpf: %s\n", clientes[1].cpf);
    printf("sexo: %s\n", clientes[1].sexo);
    printf("SENHA: %s\n", clientes[1].senha);
    printf("Total Avaliacoes: %s\n", clientes[1].avaliacaotot);
    printf("Numero Avaliacoes: %s\n", clientes[1].avaliacaonum);
    printf("Numero Celular: %s\n", clientes[1].numero_celular);

        return 0;
}