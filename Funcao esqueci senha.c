#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void esquecisenha(char str1[]);
void menucodigosenha();

int main(){
	srand(time(NULL));
	printf("Hello world");
	menucodigosenha();
}

void esquecisenha(char str1[]){
	menucodigosenha();
	
}

void menucodigosenha(){
	int a = 10,b = 0,i;
	char email[128];
	char codigo[6], inputcodigo[6];
	for(int i=0;i<6;i+	+){
		codigo[i] = (rand() % 10) + 48;
	}
	codigo[6] = '\0';
	printf("%s", codigo);
	printf("Informe o email da sua conta: ");
	gets(email);
	do{
		b++;
		system("cls");
		printf("Codigo gerado e enviado ao email do usuario:%s",codigo);
		if(b > 1){
			printf("Codigo invalido.");	
		}
		printf("Codigo enviado ao seu email");
		printf("\n Digite o codigo enviado: ");
		gets(inputcodigo);
		a = strcmp(inputcodigo, codigo);
	}
	while(a != 0);
	
}