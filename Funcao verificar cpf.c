#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

void charnumcpf();
bool verificacpf();
int calccpf();

char cpf[11];

int main(){
	printf("Digite seu cpf: ");
	gets(cpf);
	bool cpfreturn;
	cpfreturn = verificacpf();
	if(cpfreturn == true){
		printf("cpf valido.");
	}
	else{
		printf("cpf invalido.");
	}
	return 0;
}

bool verificacpf(){
	int cpfnum[11];
	int confirma,valido = 0, igualdade = 0;
	
	for(int i = 0; i<strlen(cpf); i++){
		cpfnum[i] = ((int)(cpf[i])) - 48;
	}
	system("pause");
	confirma = calccpf(9,cpfnum);
	if (confirma == cpfnum[9]){
		valido++;
	}
	confirma = calccpf(10,cpfnum);
	if(confirma == cpfnum[10]){
		valido++;
	}
	for(int i=0; i<11; i++){
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

int calccpf(int parar, int cpftemp[]){
	int cont = 0;
    for(int i=0; i < parar;i++){
        cont = cont + (cpftemp[i] * ((parar+1)-i));      
    }
    cont = 11 - (cont % 11);   
    if(cont>9){
        cont = 0;   
    }
    return cont;
}