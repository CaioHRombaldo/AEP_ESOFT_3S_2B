#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

bool verificaemail(char str1[]);

int main(){
	bool emailverify;
	char email[128];
	printf("Informe seu email:");
	gets(email);
	emailverify = verificaemail(email);
	if(emailverify == true){
		printf("Email valido.");
	}
	else{
		printf("Email invalido.");
	}
	return 0;
}

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