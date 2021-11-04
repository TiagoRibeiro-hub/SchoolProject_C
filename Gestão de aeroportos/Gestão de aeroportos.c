#include "myfuncs.h"
#include <stdlib.h>
#define DIM 3 // quantidade de aeroportos

typedef struct{
    char nome[51];
    char municipio[51];
    char ICAO[5];
    char IATA[4];

}dados;

dados aeroporto[DIM], aero;
int cont=0;

void inserir(){

    system("cls");
    if(cont == DIM){
        puts("---------------------------------");
        puts("||Lista de aeroportos completa!||");
        puts("---------------------------------");
        getchar();
        return;
    }
           char op[2];

    do{
        puts("**Dados aeroporto**");
        puts("-------------------");
        printf("Nome: "); getstr(aero.nome,51);
        printf("Municipio: "); getstr(aero.municipio,51);
        printf("ICAO: "); getstr(aero.ICAO,5);
        printf("IATA: "); getstr(aero.IATA,4);
        aeroporto[cont]=aero;
        puts("\n[--Aeroporto inserido com sucesso!--]\n");
        puts("Inserir outro (S/N): "); getstr(op,2);
        cont++;

    }while(toupper(op[0])=='S' && cont != DIM);

     if(cont == DIM){
        puts("---------------------------------");
        puts("||Lista de aeroportos completa!||");
        puts("---------------------------------");
        puts("\nEnter para sair...");
        getchar();
        return;
    }

}

void listar(){

    system("cls");
    printf("___Aeroportos___\n");

    char op[2];
    if(cont == 0){
        puts("\nLista encontra-se vazia\n");
    }

    for(int lista=0; lista <cont; lista++){
        aero = aeroporto[lista];
        printf("\nAeroporto %d \n",lista+1);
        puts(aero.nome);
        puts(aero.municipio);
        puts(aero.ICAO);
        puts(aero.IATA);
    }

    puts("Deseja inserir um aeroporto (S/N)? "); getstr(op,2);
    if(toupper(op[0])=='S' && cont != DIM)
        return inserir();
    else if (cont == DIM){
        puts("---------------------------------");
        puts("||Lista de aeroportos completa!||");
        puts("---------------------------------");
        puts("\nDeseja alterar um aeroporto (S/N)? "); getstr(op,2);
        if(toupper(op[0])=='S')
            return alterar();
    }
    else
        puts("\nDeseja alterar um aeroporto(S/N)? "); getstr(op,2);
        if(toupper(op[0])=='S')
            return alterar();

    printf("\nEnter para sair...");
    getchar();
}

void procurar(){

    system("cls");
    char nome[51];
    printf("Nome do aeroporto: "); getstr(nome, 51);
    printf("\n");

    for(int lista=0; lista<cont;lista++){
        aero = aeroporto[lista];
        if(strstrcase(aero.nome, nome)){
            puts("**Dados aeroporto**");
            puts("-------------------");
            puts(aero.nome);
            puts(aero.municipio);
            puts(aero.ICAO);
            puts(aero.IATA);
        }
    }
    printf("\nEnter para sair...");
    getchar();
}

void alterar(){

    system("cls");
    char nome[51];
    char op[2];
    printf("Qual o nome do aeroporto a alterar?  "); getstr(nome, 51);

    for(int lista=0; lista<cont; lista++){
        aero = aeroporto[lista];
        if(strstrcase(aero.nome, nome)){
            printf("Aeroporto %d \n",lista+1);
            puts(aero.nome);
            puts(aero.municipio);
            puts(aero.ICAO);
            puts(aero.IATA);

            printf("Pretende alterar (S/N)?  "); getstr(op,2);
            if(toupper(op[0])=='S'){
                printf("Nome: "); getstr(aero.nome, 51);
                printf("Municipio: "); getstr(aero.municipio, 51);
                printf("ICAO: "); getstr(aero.ICAO, 5);
                printf("IATA: "); getstr(aero.IATA, 4);

                aeroporto[lista] = aero;
                puts("\nAeroporto alterado com Sucesso!!");
                getchar();
                return;
            }
        }
    }
    printf("Este aeroporto nao foi encontrado\n");
    printf("Enter para sair...");
    getchar();
}

/// Tabela de opçao:
int main(){
    int op;

    do{
        system("cls");
        puts(" Opcoes:");
        puts("*********");
        puts("1 - Inserir");
        puts("2 - Listar");
        puts("3 - Procurar");
        puts("4 - Alterar");
        puts("5 - Sair");
        printf("Escolha: ");

        op=getint();

            switch(op){
                case 1:inserir(); break;
                case 2:listar(); break;
                case 3: procurar(); break;
                case 4: alterar();
            }
    }while(op!=5);
return 0;
}
