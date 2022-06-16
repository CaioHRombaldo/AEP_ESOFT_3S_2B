#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

void esquecisenha(char* str1);
void menucodigosenha();

int main(){
	char senha[32]; //senha a ser importada do txt.
	srand(time(NULL));
	gets(senha); //simula��o da senha que ser� importada.
	esquecisenha(senha); //chamar a fun��o da "tela" de esqueci minha senha.
	//printf("%s", senha); printar senha alterada.
	system("pause");
 } 

void esquecisenha(char* str1){
	int i = 0;
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
	printf("\nSenha atualizada com sucesso.\n");
}

void menucodigosenha(){
	int a = 0,b,i;
	char inputemail[128],email[128] = "teste";
	char codigo[7] = " ", inputcodigo[7];
	
	for(i=0;i<6;i++){
		codigo[i] = (rand() % 10) + 48; //Gera��o de c�digo aleat�rio.
	}
	codigo[6] = '\0';
	printf("Informe o email da sua conta: ");
	gets(inputemail); //Pegar input de email do usu�rio.
	fflush(stdin);
	b = strcmp(inputemail,email); //Comparar com um email existente no txt
	while(b != 0){
		system("cls");
		printf("email inexistente, por favor digite um email v�lido:");
		gets(inputemail);
		fflush(stdin);
		b = strcmp(inputemail,email);
	}
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