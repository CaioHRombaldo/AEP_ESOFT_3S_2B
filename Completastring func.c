#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

void completastring(char *str, int parada);

int main(){
	char string[128];
	printf("Digite algo");
	gets(string);
	completastring(string,25);
	printf("%s",string);
}

void completastring(char *str, int parada){
	int i,tam = strlen(str);
	for(i=tam ;i<parada;i++){
		str[i] = '=';
	}
	str[i] = '\0';
}