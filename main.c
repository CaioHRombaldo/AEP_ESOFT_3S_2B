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
    char cpf[12];
    char avaliacaotot[8];
    char avaliacaonum[8];
    char numero_celular[21];
    char profissao[256];
    char sexo[6];

    struct endereco endereco_prestador[32];
};

// Declaração de Variaveis Globais:
struct usuario_cliente clientes[256];
int totClientes = 0;

struct usuario_prestador prestadores[256];
int totPrestadores = 0;

char cpf_temp[12];

bool login_status = false;

// Fim Declaração de Variaveis Globais

void completastring(char *str, int parada){
	int i,tam = strlen(str);
	for(i=tam ;i<parada;i++){
		str[i] = '=';
	}
	str[i] = '\0';
}

void CriaClienteBanco(char *str_cliente, char *str_cliente_edit, char tipo){    
    FILE *arq, *arq_edit, *arq_endereco;

    if (tipo == "u"){
        arq = fopen("Dataclientes.txt", "a+");
        arq_edit = fopen("Dataclienteedit.txt", "a+");
    }else {
        arq = fopen("Dataps.txt", "a+");
        arq_edit = fopen("Datapsedit.txt", "a+");
    }
    
    //arq_endereco = fopen("Dataclienteendereco.txt", "a+");

    if (arq == NULL || arq_edit == NULL)
    {
        printf("Problema ao abrir o arquivo.\n");
    }
    else
    {
        fputs(str_cliente, arq);
        fputs(str_cliente_edit, arq_edit);
        //fputs(str_cliente_endereco, arq_endereco);
    }

    CargaDeDadosClientes();
}

void DeletaDadosEditaveisCliente(char *cpf){
    FILE *arq;
    char linha[78];
    char *result;

    arq = fopen("Dataclienteedit.txt", "r+");
    

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo Deletando dados editaveis Cliente.\n");
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

                if(strcmp(cpf_temp, cpf) == 0){
                    fseek(arq, -78, SEEK_CUR);
                    fputs("                                                                            ", arq);
                    break;
                }
            }
        }
    }
}

void DeletaDadosEditaveisPS(char *cpf){
    FILE *arq;
    char linha[112];
    char *result;

    arq = fopen("Datapsedit.txt", "r+");

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo.\n");
        return;
    }
    else
    {
        while (!feof(arq))
        {

            result = fgets(linha, 112, arq);
            
            if (result)
            {
                LeCampo(cpf_temp, 99, 109, linha);

                if(strcmp(cpf_temp, cpf) == 0){
                    fseek(arq, -112, SEEK_CUR);
                    fputs("                                                                                                              ", arq);
                    break;
                }
            }
        }
    }
}

void DeletarUsuarioBancoCliente(char *cpf){
    FILE *arq;
    char linha[102];
    char *result;

    arq = fopen("Dataclientes.txt", "r+");

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
                LeCampo(cpf_temp, 89, 99, linha);

                if(strcmp(cpf_temp, cpf) == 0){
                    fseek(arq, -102, SEEK_CUR);
                    fputs("                                                                                                    ", arq);
                    break;
                }
            }
        }
        DeletaDadosEditaveisCliente(cpf);
    }
}

void DeletarUsuarioBancoPS(char *cpf){
    FILE *arq;
    char linha[102];
    char *result;

    arq = fopen("Dataps.txt", "r+");

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
                LeCampo(cpf_temp, 89, 99, linha);

                if(strcmp(cpf_temp, cpf) == 0){
                    fseek(arq, -102, SEEK_CUR);
                    fputs("                                                                                                      ", arq);
                    break;
                }
            }
        }
        DeletaDadosEditaveisPS(cpf);
    }
}

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

void CadastrarUsuario(int tipo){
    char temp_nome[256];
	char temp_mail[256];
	char temp_senha[256];
	char temp_confirma_senha[256];

    char temp_cidade[128];
    char temp_endereco[128];
    char temp_complemento;
    char temp_numero_celular[128];
    char temp_cpf[128];
    char temp_sexo[128];

    char temp_profissao[128];

    char atot[7] = "0";
    char anum[7] = "0";

    char str_temp[128] = "\n";
    char str_temp_edit[128] = "\n";
    char str_temp_endereco[128] = "\n";

    int escolha_usuario; 
	bool escape;
	
    system("cls");

	printf("Cadastre-se");

    printf("\n Insira seu nome: ");
    fflush(stdin);
    gets(temp_nome);
    completastring(temp_nome, 34);
    strcat(str_temp, temp_nome);

	do{
		printf("\nInsira um email valido: ");
        fflush(stdin);
		gets(temp_mail);
	}while(verificaemail(temp_mail) == false);
    completastring(temp_mail, 50);
    strcat(str_temp, temp_mail);

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
    completastring(temp_senha, 34);
    strcat(str_temp_edit, temp_senha);

    completastring(atot, 6);
    strcat(str_temp_edit, atot);

    completastring(anum, 6);
    strcat(str_temp_edit, anum);

    system("cls");

    printf("\nInsira a sua cidade: ");
    fflush(stdin);
    gets(temp_cidade);

    printf("\nInsira o seu endereco residencial: ");
    fflush(stdin);
    gets(temp_endereco);

    escape == false;
    escolha_usuario = 0;
    while(escape == false){
        printf("\nEscolha o complemento: ");
        printf("\n1 - Casa\n2 - Apartamento\n3 - Condomínio");
        fflush(stdin);
        scanf("%d",&escolha_usuario);

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

    completastring(temp_numero_celular, 19);
    strcat(str_temp_edit, temp_numero_celular);

    do{
        printf("\nInsira seu CPF: ");
        fflush(stdin);
        gets(temp_cpf);
    }while(verificacpf(temp_cpf) == false);
    printf("%s", str_temp);

    escape = false;
    escolha_usuario = 0;
    while (escape == false)
    {
        printf("\nEscolha o seu sexo: ");
        printf("\n1 - Feminino\n2 - Masculino\n3 - Prefiro nao informar");
        fflush(stdin);
        scanf("%d",&escolha_usuario);

        switch (escolha_usuario)
        {
        case 1:
            temp_sexo[0] = 'F';
            escape = true;
            break;
        case 2:
            temp_sexo[0] = 'M';
            escape = true;
            break;
        case 3:
            temp_sexo[0] = '0';
            escape = true;
            break;
        default:
            system("cls");
            printf("\nEscolha uma opcao valida.");
            break;
        }
    }

    if (tipo == 2){
        printf("\nInsira a sua area de atuacao: ");
        fflush(stdin);
        gets(temp_profissao);

        completastring(temp_profissao, 34);
        strcat(str_temp_edit, temp_profissao);
    }

     

    completastring(temp_sexo, 5);
    strcat(str_temp, temp_sexo);
    printf("%s", str_temp);
    

    strcat(str_temp, temp_cpf);
    strcat(str_temp_edit, temp_cpf);

    printf("%s", str_temp);

    CriaClienteBanco(str_temp, str_temp_edit, tipo);
    

}

void CadastrarUsuarioEscolha(){
	int escolha_usuario;
	bool escape = false;
	
	while(escape == false){
		printf("Como deseja utilizar a sua conta? \n");
		printf("1 - Cliente\n");
		printf("2 - Prestador de servico\n");
		
		scanf("%d",&escolha_usuario);
		
		switch(escolha_usuario){
			case 1:
				CadastrarUsuario(1);
				escape = true;		
				break;
			case 2:
                CadastrarUsuario(2);
				escape = true;
				break;
			default:
				system("cls");
				printf("Opcao invalida, tente novamente.\n");
				break;
		}
	}
}

void menu_principal(){
	bool verifyEscolha = false;
	char escolha_temp,input_idade[4];
	if(login_status == true){
		menu_usuario();
	}
	else{
		printf("= = = =iServe = = = = =\n");
		printf("1 - Login\n");
		printf("2 - Cadastro\n");
		printf("3 - Esqueci minha senha\n");
		printf("0 - Sair\n");
		printf("= = = = = = = = = = = =\n");
		while(verifyEscolha == false){
			scanf("%c",&escolha_temp);
			fflush(stdin);
			switch (escolha_temp){
				case '1':
					verifyEscolha = true;
					menu_login();
					break;
				case '2':
					printf("Informe a sua idade:");
					verifyEscolha = true;
					//funcCadastro
					break;
				case '3':
					verifyEscolha = true;
					//funcEsqueciMinhaSenha
				case '0':
					exit(0);
					break;
				default:
					printf("Escolha uma opcao valida.\n");
					break;
			}
		}
	}	
}

void menu_login(){
	char input_email[128],input_senha[128];
	bool verifyEmail = false, verifySenha = false;
	system("cls");
	printf("Insira seu email: ");
	while(verifyEmail == false){
		fflush(stdin);
		gets(input_email);
		if(strcmp(input_email,email) == 0){
			verifyEmail = true;
			printf("Insira sua senha:");
			while(verifySenha == false){
				fflush(stdin);
				gets(input_senha);
				if(strcmp(input_senha,senha) == 0){
					verifySenha = true;
					login_status = true;
					menu_usuario();
				}
				else{
					system("cls");
					printf("Insira uma senha valida: ");
				}
			}
		}
		else{
			system("cls");
			printf("Insira um email valido:");
		}
	}
}

void menu_usuario(){
	char input_usuario;
	system("cls");
	printf("= = = =iServe = = = = =\n");
	printf("1 - Ver informacoes\n");
	printf("2 - Editar informacoes\n");
	printf("3 - Deletar conta\n");
	printf("0 - Sair\n");
	printf("= = = = = = = = = = = =\n");
	scanf("%c",input_usuario);
	fflush(stdin);
	switch(input_usuario){
		case '1':
			//funcRead();
			break;
		case '2':
			//funcEdit();
			break;
		case '3':
			//funcDelete();
			break;
		case '0':
			login_status = false;
			break;
	}
}
	
int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_CTYPE, "pt_BR.UTF-8");

    //CargaDeDadosClientes();
    //CadastrarUsuarioEscolha();    
    DeletarUsuarioBancoPS("07526069135");

    return 0;
}