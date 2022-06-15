#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

void menu_principal();
void menu_login();
void menu_usuario();
bool login_status = false;

char email[128] = "teste";
char senha[128] = "teste";

int main(){
	int a = 1;
	while(a == 1){
		menu_principal();	
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