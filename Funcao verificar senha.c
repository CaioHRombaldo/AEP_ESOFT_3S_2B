#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool verificasenha(char str1[]);
bool verifica;
char senha[256];
int verify = 0;

int main(){
	verifica = verificasenha(senha);
	if (verifica == true){
		printf("A senha e valida.");
	}
	else{
		printf("A senha n e valida.");
	}
}

bool verificasenha(char str1[]){
	//int verify = 0;
	int tam = strlen(str1);
	//Verifica se o tamanho da senha � superior ou igual a 8 caracteres, caso contr�rio retorna falso.
	if (tam >= 8){
		//Verifica se existe algum caracter especial na senha.
		for(int i=0;i<tam;i++){
			if((str1[i] > 32 && str1[i] < 48) || str1[i] > 57 && str1[i] < 65){
				verify++;
				i = tam;
				printf("1");
			}
		}
		//Verifica se existe alguma letra min�scula na senha.
		for(int i=0;i<tam;i++){
			if(str1[i]>96 && str1[i]<123){
				verify++;
				i = tam;
				printf("2");
			}
		}
		//Verifica se existe alguma letra mai�scula na senha.
		for(int i=0;i<tam;i++){
			if(str1[i]>64 && str1[i] < 91){
				verify++;
				i = tam;
				printf("3");
			}
		}
		//Verifica se existe algum n�mero na senha.
		for(int i=0;i<tam;i++){
			if(str1[i]>47 && str1[i] < 58){
				verify++;
				i = tam;
				printf("4");
			}
		}
		/*Caso todas as verifica��es sejam positivas, verify ser� igual a 4 e retornar�
		true, caso contr�rio retornar� false.*/
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