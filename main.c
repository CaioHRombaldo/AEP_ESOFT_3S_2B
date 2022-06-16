#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

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
    char profissao[128];
    char sexo[6];

};

// Declaração de Variaveis Globais:
struct usuario_cliente clientes[256];
int totClientes = 0;

struct usuario_prestador prestadores[256];
int totPrestadores = 0;

char cpf_temp[12];

char cpf_logado[12];
int tipo_de_conta;

bool login_status = false;

bool parada_system = false;

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

    if (arq == NULL || arq_edit == NULL)
    {
        printf("Problema ao abrir o arquivo.\n");
    }
    else
    {
        fputs(str_cliente, arq);
        fputs(str_cliente_edit, arq_edit);
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

void EditarCampoBancoCliente(char *cpf, int pos, int tam, char *novo_dado){
    FILE *arq;
    char linha[78];
    char *result;

    char tmp_novo_dado[128];
    strcpy(tmp_novo_dado, novo_dado);
    completastring(tmp_novo_dado, tam);

    arq = fopen("Dataclienteedit.txt", "r+");

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo Editando dados editaveis Cliente.\n");
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
                    fseek(arq, -pos, SEEK_CUR);
                    fputs(tmp_novo_dado, arq);
                    break;
                }
            }
        }
    }
}

void EditarCampoBancoPrestador(char *cpf, int pos, int tam, char *novo_dado){
    FILE *arq;
    char linha[112];
    char *result;

    char tmp_novo_dado[128];
    strcpy(tmp_novo_dado, novo_dado);
    completastring(tmp_novo_dado, tam);

    arq = fopen("Datapsedit.txt", "r+");

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo Editando dados editaveis Prestador.\n");
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
                    fseek(arq, -pos, SEEK_CUR);
                    fputs(tmp_novo_dado, arq);
                    break;
                }
            }
        }
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

int BuscaClienteEmail(char *email)
{
    int count = 0;
    for (count = 0; count < totClientes; count++)
    {
        if (strcmp(clientes[count].email, email) == 0)
        {
            return count;
        }
    }

    return -1;
}

int BuscaPrestadorCPF(char *cpf)
{
    int count = 0;
    for (count = 0; count < totPrestadores; count++)
    {
        if (strcmp(prestadores[count].cpf, cpf) == 0)
        {
            return count;
        }
    }

    return -1;
}

int BuscaPrestadorEmail(char *email)
{
    int count = 0;
    for (count = 0; count < totPrestadores; count++)
    {
        if (strcmp(prestadores[count].email, email) == 0)
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

void CargaDeDadosEditaveisPS()
{
    FILE *arq;
    char linha[112];
    char *result;
    int count = 0;
    int prestador_id;

    arq = fopen("Datapsedit.txt", "r");

    if (arq == NULL)
    {
        printf("Problema ao abrir o arquivo editavel.\n");
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
                prestador_id = BuscaPrestadorCPF(cpf_temp);

                if (prestador_id != -1)
                {
                    LeCampo(prestadores[prestador_id].senha, 0, 32, linha);
                    LeCampo(prestadores[prestador_id].avaliacaotot, 34, 38, linha);
                    LeCampo(prestadores[prestador_id].avaliacaonum, 40, 44, linha);
                    LeCampo(prestadores[prestador_id].numero_celular, 46, 63, linha);
                    LeCampo(prestadores[prestador_id].profissao, 65, 97, linha);
                }
            }
        }
    }
}

void CargaDeDadosPS()
{
    FILE *arq;
    char linha[102];
    char *result;

    arq = fopen("Dataps.txt", "r");

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
                LeCampo(prestadores[totPrestadores].nome, 0, 32, linha);
                LeCampo(prestadores[totPrestadores].email, 34, 83, linha);
                LeCampo(prestadores[totPrestadores].sexo, 84, 88, linha);
                LeCampo(prestadores[totPrestadores].cpf, 89, 99, linha);
            }
            totPrestadores++;
        }
        CargaDeDadosEditaveisPS();
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

    system("cls");
	
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
	char escolha_temp;
    int input_idade;
    system("cls");

	if(login_status == true){
		menu_usuario();
	}
	else{
		while(verifyEscolha == false){
            printf("= = = =iServe = = = = =\n");
            printf("1 - Logar como cliente\n");
            printf("2 - Logar como prestador\n");
            printf("3 - Cadastro\n");
            printf("4 - Esqueci minha senha\n");
            printf("0 - Sair\n");
            printf("= = = = = = = = = = = =\n");
			scanf("%c",&escolha_temp);
			fflush(stdin);
			switch (escolha_temp){
				case '1':
					verifyEscolha = true;
					menu_login_cliente();
					break;
				case '2':
					verifyEscolha = true;
					menu_login_prestadores();
					break;
				case '3':
					printf("Informe a sua idade:");
                    scanf("%d",&input_idade);
                    if(input_idade >= 18){
					    verifyEscolha = true;
					    CadastrarUsuarioEscolha();
                    }else{
                        system("cls");
                        printf("Voce precisa ter mais de 18 anos para se cadastrar.\n");
                        system("pause");
                    }
                    break;
				case '4':
					verifyEscolha = true;
					esquecisenha();
				case '0':
					exit(0);
					break;
				default:
                    system("cls");
					printf("Escolha uma opcao valida.\n");
					break;
			}
		}
	}	
}

void esquecisenha(){
	int i = 0;
    char str1[128]; 
	menucodigosenha(); //Gera��o de c�digo aleat�rio e confirma��o do mesmo.
	printf("Digite sua nova senha: ");
	fflush(stdin);
	while(str1[i] != 13){ //Condi��o de parada = usu�rio apertar enter.
		str1[i] = getch();
		if(str1[i] != 8 && str1[i] != 13 && i<32){ //Limitar os caracteres da nova senha at� 32
			putchar('*'); //mascarar o que foi escrito com "*"
			i++;
		}
		if(str1[i] == 8 && i>0){ //remover as "*" por " "
			str1[i] = '\0';
			i--;
			printf("\b \b");
		}
	}
	str1[i] = '\0'; //Colocar um final na string de senha para n�o causar erro de mem�ria.
    EditarCampoBancoCliente(cpf_logado, 78, 34, str1);

	printf("\nSenha atualizada com sucesso.\n");
}

void menucodigosenha(){
	int a = 0,b,i, count;
	char inputemail[128];
	char codigo[7] = " ", inputcodigo[7];
    bool escape = false;
	
	for(i=0;i<6;i++){
		codigo[i] = (rand() % 10) + 48; //Gera��o de c�digo aleat�rio.
	}
	codigo[6] = '\0';
	
    
    do{
        printf("Informe o email da sua conta: ");
	    gets(inputemail); //Pegar input de email do usu�rio.
	    fflush(stdin);

        for(count = 0; count < totClientes; count++){
            if(strcmp(inputemail, clientes[count].email) == 0){
                strcmp(cpf_logado, clientes[count].cpf);
                escape = true;
                break;
            }
        }

    }while(escape == false);

	system("cls");
	fflush(stdin);
	printf("Codigo gerado e enviado ao email do usuario:%s\n",codigo);
	printf("Codigo enviado com sucesso ao seu email!\n");
	printf("Digite o codigo enviado: ");
	while(a == 0){ //Pegar input do c�digo digitado pelo usu�rio e comparar com o c�digo real.
		gets(inputcodigo);
		if(strcmp(inputcodigo,codigo) == 0){
			a = 1;
		}
		else{
			system("cls");
			printf("Codigo errado, por favor digite o codigo enviado ao seu email:");
		}
	}
	
}

void menu_login_cliente(){
	int count = -1;
	char input_email[128],input_senha[128];
	int verifySenha;
	system("cls");
	printf("Insira seu email: ");
	gets(input_email);
	while(strcmp(input_email,clientes[count].email) != 0){
		count++;
		if(strcmp(input_email,clientes[count].email) == 0){
			printf("Insira sua senha: ");
			while(verifySenha != 0){
				gets(input_senha);
				verifySenha = strcmp(input_senha, clientes[count].senha);
				if(verifySenha == 0){
					login_status = true;
                    strcpy(cpf_logado, clientes[count].cpf);
                    tipo_de_conta = 1;
					menu_usuario();
				}
				else{
					system("cls");
					printf("Informe uma senha valida: ");
				}
			}	
		}
		if(count > totClientes){
			system("cls");
			printf("Informe um email valido: ");
			gets(input_email);
			count = -1;
		}
	}
}

void menu_login_prestadores(){
	int cont = -1;
	char input_email[128],input_senha[128];
	int verifySenha;
	system("cls");
	printf("Insira seu email: ");
	fflush(stdin);
    gets(input_email);
	while(strcmp(input_email,prestadores[cont].email) != 0){
		cont++;
		if(strcmp(input_email,prestadores[cont].email) == 0){
			printf("Insira sua senha: ");
			while(verifySenha != 0){
				gets(input_senha);
				verifySenha = strcmp(input_senha, prestadores[cont].senha);
				if(verifySenha == 0){
					login_status = true;
                    strcpy(cpf_logado, prestadores[cont].cpf);
                    tipo_de_conta = 2;
					menu_usuario();
				}
				else{
					system("cls");
					printf("Informe uma senha valida: ");
				}
			}	
		}
		if(cont > totPrestadores){
			system("cls");
			printf("Informe um email valido: ");
			gets(input_email);
			cont = -1;
		}
	}
}

void menu_usuario(){
	char input_usuario;
    char esc_user[128];
    int id;

	system("cls");
	printf("= = = =iServe = = = = =\n");
	printf("1 - Ver informacoes\n");
	printf("2 - Editar Senha\n");
    printf("3 - Editar Numero Celular\n");
	printf("4 - Deletar conta\n");
	printf("0 - Sair\n");
	printf("= = = = = = = = = = = =\n");
	scanf("%c",&input_usuario);
	fflush(stdin);
	switch(input_usuario){
		case '1':
			if(tipo_de_conta == 1){
                id = BuscaClienteCPF(cpf_logado);
                system("cls");
                printf("= = = Informacoes = = =\n");
                printf("Nome: %s\n", clientes[id].nome);

                float aval_tot = atof(clientes[id].avaliacaotot);
                float aval_num = atof(clientes[id].avaliacaonum);
                printf("Avaliacao: %.2f\n",aval_tot / aval_num);

                printf("Numero Celular: %s\n", clientes[id].numero_celular);
                printf("Sexo: %s\n", clientes[id].sexo);
                printf("E-mail: %s\n", clientes[id].email);
                printf("CPF: %s\n", clientes[id].cpf);
                printf("= = = = = = = = = = = =\n");

                system("pause");

            }else{
                id = BuscaPrestadorCPF(cpf_logado);
                system("cls");
                printf("= = = Informacoes = = =\n");
                printf("Nome: %s\n", prestadores[id].nome);
                
                float aval_tot = atof(prestadores[id].avaliacaotot);
                float aval_num = atof(prestadores[id].avaliacaonum);
                printf("Avaliacao: %.2f\n",aval_tot / aval_num);

                printf("Numero Celular: %s\n", prestadores[id].numero_celular);
                printf("Sexo: %s\n", prestadores[id].sexo);
                printf("E-mail: %s\n", prestadores[id].email);
                printf("CPF: %s\n", prestadores[id].cpf);
                printf("= = = = = = = = = = = =\n");

                system("pause");
            }

			break;
		case '2':
            printf("Digite a sua nova senha: ");
            gets(esc_user);

			if(tipo_de_conta == 1){
                EditarCampoBancoCliente(cpf_logado, 78, 34, esc_user);
            }else{
                EditarCampoBancoPrestador(cpf_logado, 112, 34, esc_user);
            }
			break;
        case '3':
            printf("Digite o seu novo numero: ");
            gets(esc_user);

            if(tipo_de_conta == 1){
                EditarCampoBancoCliente(cpf_logado, 32, 19, esc_user);
            }else{
                EditarCampoBancoPrestador(cpf_logado, 66, 19, esc_user);
            }
            break;
		case '4':
            printf("Insira o seu CPF para confirmar a exclusao da conta: ");
            gets(esc_user);
            if(strcmp(esc_user, cpf_logado) == 0){
                if (tipo_de_conta == 1)
                {
                    DeletarUsuarioBancoCliente(esc_user);
                    system("cls");
                    printf("Conta deletada com sucesso.");
                    login_status = false;
                    system("pause");
                    
                }else{
                    DeletarUsuarioBancoPS(esc_user);
                    system("cls");
                    printf("Conta deletada com sucesso.");
                    login_status = false;
                    system("pause");

                }
            }
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

    CargaDeDadosClientes();
    CargaDeDadosPS();

    menu_principal();
    
    return 0;
}