#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX 1024

// colocar string em maiusculas
void strupper (char *str){

    for(int i=0; str[i]; i++)
            str[i]= toupper(str[i]);
}
// colocar string em minusculas

void strlower (char *str){

    for(int i=0; str[i]; i++)
        str[i] = tolower(str[i]);
}
// copiar string para uma auxiliar por em maiusculas e compará-las(strcmp)

bool compararstr (char *str1, char *str2){

    char aux1[strlen(str1)+1]; char aux2[strlen(str2)+1];

    strcpy(aux1,str1); strcpy(aux2,str2);

    strupper(aux1); strupper(aux2);

    if(strcmp(aux1, aux2)==0)
        return true;
    else
        return false;
}
// copiar string para uma auxiliar por em maiusculas e encontrá-las(strstr)

bool encontrarstr (char *str1, char *str2){

    char aux1[strlen(str1)+1]; char aux2[strlen(str2)+1];

    strcpy(aux1,str1); strcpy(aux2,str2);

    strupper(aux1); strupper(aux2);

    if(strstr(aux1,aux2)!=NULL)
        return true;
    else
        return false;
}

void getstr (char *str,size_t len){

    char buffer[MAX];
    fgets(buffer,MAX,stdin);

    buffer[strcspn(buffer,"\n")]=0;     //quando encontra o ultimo caracter \n transforma em \0

    if(strlen(buffer)<len)
        strcpy(str, buffer);
    else
        strncpy(str, buffer, len-1);    // copiar até encontar len-1
        strcat(str, "\0");              // acrescenta \0 no final da string
}
// string de numeros em numeros inteiros
long getint(){

    char str_int[MAX];
    fgets(str_int,MAX,stdin);

    return strtol(str_int, NULL, 0);
}

int idInc(char *file){
    int cont=1;

    FILE *f=fopen(file,"ab+");
    if(f==NULL) return 0;

    while(fread(&cont,sizeof(int),1,f)){
        cont++;
    }
    rewind(f);
    fwrite(&cont,sizeof(int),1,f);
    fclose(f);
    return cont;
}
