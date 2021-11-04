#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Funcoes.h"

typedef struct Localidades{

    int IDLocalidade;
    char nome[51];


}listLocal;

typedef struct Praias{

    int IDPraia;
    char nome[51];
    char tipo[51];
    int IDLocal;


}listPraias;

int idIncL(char *file){
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
int idIncP(char *file){
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

void inserirLocalidade(){

    listLocal list;
    char nome[51];

    FILE *ficheiro = fopen("Localidades.dat","ab+");
    if(ficheiro==NULL) return;

    printf("ID:\t%d\n", list.IDLocalidade = idIncL("IDLocalidade.dat"));
    printf("Nova Localidade:\t"); getstr(nome, 51); strupper(nome);
    strcpy(list.nome, nome);
    fwrite(&list,sizeof(listLocal),1,ficheiro);
    fclose(ficheiro);

    printf("\n** Localidade inserida com sucesso **\n");
    printf("Enter para sair..."); getchar();
}

int procurarID(char *LocalProcurar){

    int id = 0;
    listLocal list;

    FILE *ficheiro = fopen("Localidades.dat","rb");
    if(ficheiro==NULL) return 0;

    while (fread(&list,sizeof(listLocal),1,ficheiro)){
        if(encontrarstr (list.nome,LocalProcurar)){
                id = list.IDLocalidade; break;
        }
    }
    return id;
}

void inserirPraia(){

    listPraias list;
    int op;
    char nomePraia[51], nomeLocalidade[51];

    FILE *ficheiro = fopen("Praias.dat","ab+");
    if(ficheiro==NULL) return;

    printf("ID:\t%d\n", list.IDPraia = idIncP("IDPraias.dat"));
    printf("Nova Praia:\t"); getstr(nomePraia, 51); strupper(nomePraia);
    strcpy(list.nome, nomePraia);
    printf("Tipo, Oceanica (1) ou Fluvial (2):\t"); op=getint();
    if(op == 1){
        strcpy(list.tipo, "OCEANICA");
    }
    else if(op == 2){
         strcpy(list.tipo, "FLUVIAL");
    }
    printf("Localidade: "); getstr(nomeLocalidade, 51); strupper(nomeLocalidade);
    int id = procurarID(nomeLocalidade);
    if(id == 0){
        printf("Esta Localidade não existe, crie uma nova");
        inserirLocalidade();
        id = procurarID(nomeLocalidade);
    }

    printf("ID da Localidade:\t%d", list.IDLocal = id);
    fwrite(&list,sizeof(listPraias),1,ficheiro);
    fclose(ficheiro);

    printf("\n** Praia inserida com sucesso **\n");
    printf("Enter para sair..."); getchar();
}

void listarLocal(){

    listLocal list;

    FILE *ficheiro = fopen("Localidades.dat","rb");
    if(ficheiro==NULL) return;

    printf("\nLocalidades disponiveis:\n");

    while(fread(&list,sizeof(listLocal),1,ficheiro)){
        printf("---------------------------\n");
        printf("ID: %d", list.IDLocalidade);
        printf("\tLocalidade: "); puts(list.nome);
        printf("---------------------------\n");
    }
    fclose(ficheiro);
    printf("Enter para continuar..."); getchar();
}

void listarPraias(){

    listPraias listP;

    FILE *ficheiro = fopen("Praias.dat","rb");
    if(ficheiro==NULL) return;

    printf("\nLista de Praias:\n");

    while(fread(&listP,sizeof(listPraias),1,ficheiro)){
        printf("---------------------------");
        printf("\nID: %d", listP.IDPraia);
        printf("\nNome: "); puts(listP.nome);
        printf("Tipo: "); puts(listP.tipo);
        printf("ID da Localidade:\t%d", listP.IDLocal);
        printf("\n---------------------------\n");
    }
    fclose(ficheiro);
    printf("\nEnter para continuar..."); getchar();

}

void listarpraiasPorLocal(){

    listPraias listP;
    char nomeLocalidade[51];

    FILE *ficheiro = fopen("Praias.dat","rb");
    if(ficheiro==NULL) return;

    printf("Nome da Localidade:\t"); getstr(nomeLocalidade, 51); strupper(nomeLocalidade);
    int id = procurarID(nomeLocalidade);
    if(id == 0){
        printf("Esta Localidade não existe, crie uma nova");
        inserirLocalidade();
        id = procurarID(nomeLocalidade);
    }

    while(fread(&listP,sizeof(listPraias),1,ficheiro)){
        if(listP.IDLocal == id){
            printf("---------------------------");
            printf("\nNome Praia: "); puts(listP.nome);
            printf("Tipo: "); puts(listP.tipo);
            printf("---------------------------\n");;
        }
    }
    fclose(ficheiro);
    printf("Enter para continuar..."); getchar();
}

void procurarPraia(){

    listPraias listP; listLocal listL;
    char nome[51], op[2];

    FILE *ficheiro = fopen("Praias.dat","rb");
    if(ficheiro==NULL) return;

    FILE *ficheiro1 = fopen("Localidades.dat","rb");
    if(ficheiro1==NULL) return;

    printf("Nome da Praia:\t"); getstr(nome, 51);
    while(fread(&listP,sizeof(listPraias),1,ficheiro) && fread(&listL,sizeof(listLocal),1,ficheiro1)){
        if(encontrarstr(listP.nome, nome)){
            printf("---------------------------");
            printf("\nNome: "); puts(listP.nome);
            printf("Tipo: "); puts(listP.tipo);
            if(listP.IDLocal == listL.IDLocalidade){
                printf("\tLocalidade: "); puts(listL.nome);
            }
            printf("---------------------------\n");
        }else{
            printf("Praia nao encontrada. Repetir procura? (S/N)"); getstr(op, 2);
                if(toupper(op[0])=='S'){
                    fclose(ficheiro); fclose(ficheiro1);
                    procurarPraia();
                }
        }
    }
    fclose(ficheiro); fclose(ficheiro1);
//    printf("Enter para continuar..."); getchar();
}

void alterarLocalidade(){

    listLocal listL;
    fpos_t pos;
    int id, found = 0;
    char op[2], nome[51];

    FILE *ficheiro = fopen("Localidades.dat","rb+");
    if(ficheiro==NULL) return;

    printf("ID da Localidade:\t"); scanf("%d", &id, stdin); getchar();
    fgetpos(ficheiro,&pos);

    while(fread(&listL,sizeof(listLocal),1,ficheiro))
    {
        if(id == listL.IDLocalidade){
            printf("---------------------------");
            printf("\nID: %d", listL.IDLocalidade);
            printf("\nLocalidade: "); puts(listL.nome);
            printf("---------------------------");
            printf("\nAlterar esta localidade (S/N)\t"); getstr(op, 2);
            if(toupper(op[0])=='S'){
                found++;
                printf("---------------------------");
                printf("ID: %d", listL.IDLocalidade);
                printf("\nNova Localidade:\t"); getstr(nome, 51); strupper(nome);
                strcpy(listL.nome, nome);
                printf("---------------------------\n");
                fsetpos(ficheiro,&pos);
                fwrite(&listL,sizeof(listLocal),1,ficheiro);
                fflush(ficheiro);
            }else{
                found = 2;
            }
        }
        fgetpos(ficheiro,&pos);
    }
    fclose(ficheiro);

    if(found == 0){
        printf("\n** ID não encontrado **");
        printf("\nProcure por novo ID (S/N)\t\n"); getstr(op, 2);
            if(toupper(op[0])=='S') alterarLocalidade();
    } else if(found == 1){
         printf("\n** Localidade alterada com sucesso **\n");
    }else if(found == 2){
        printf("\nProcure por novo ID (S/N)\t\n"); getstr(op, 2);
            if(toupper(op[0])=='S') alterarLocalidade();
    }
    printf("Enter para continuar..."); getchar();
}

void alterarPraia(){

    listPraias listP; listLocal listL;
    fpos_t pos;
    int id, opI, found = 0;
    char op[2], nomePraia[51], nomeLocalidade[51];

    FILE *ficheiro = fopen("Praias.dat","rb+");
    if(ficheiro==NULL) return;

    FILE *ficheiro1 = fopen("Localidades.dat","rb+");
    if(ficheiro1==NULL) return;

    printf("ID da Praia:\t"); scanf("%d", &id, stdin); getchar();
    fgetpos(ficheiro,&pos);

    while(fread(&listP,sizeof(listPraias),1,ficheiro) && fread(&listL,sizeof(listLocal),1,ficheiro1))
    {
        if(id == listP.IDPraia){
            printf("---------------------------\n");
            printf("ID: %d", listP.IDPraia);
            printf("\nNome: "); puts(listP.nome);
            printf("Tipo: "); puts(listP.tipo);
            printf("ID da Localidade:\t%d", listP.IDLocal);
                if(listP.IDLocal == listL.IDLocalidade){
                    printf("\tLocalidade: "); puts(listL.nome);
                }
            printf("---------------------------");
            printf("\nAlterar esta Praia (S/N)\t"); getstr(op, 2);
                if(toupper(op[0])=='S'){
                    found++;
                    printf("---------------------------\n");
                    printf("ID: %d", listP.IDPraia);
                    printf("\nNome Praia:\t"); getstr(nomePraia, 51); strupper(nomePraia);
                    strcpy(listP.nome, nomePraia);
                    printf("Tipo, Oceanica (1) ou Fluvial (2):\t"); opI=getint();
                        if(opI == 1){
                            strcpy(listP.tipo, "OCEANICA");
                        }
                        else if(opI == 2){
                             strcpy(listP.tipo, "FLUVIAL");
                        }
                    printf("Localidade: "); puts(listL.nome);
                    printf("---------------------------\n");
                    fsetpos(ficheiro,&pos);
                    fwrite(&listP,sizeof(listPraias),1,ficheiro);
                    fflush(ficheiro);
            }else{
                found = 2;
            }
        }
        fgetpos(ficheiro,&pos);
    }
    fclose(ficheiro); fclose(ficheiro1);

    if(found == 0){
        printf("\n** ID nao encontrado **");
        printf("\nProcure por novo ID (S/N)\t\n"); getstr(op, 2);
            if(toupper(op[0])=='S') alterarPraia();
    } else if(found == 1){
         printf("\n** Praia alterada com sucesso **\n");
    }else if(found == 2){
        printf("\nProcure por novo ID (S/N)\t\n"); getstr(op, 2);
            if(toupper(op[0])=='S') alterarPraia();
    }
    printf("Enter para continuar..."); getchar();
}

void apagarLocalidade(){

    listLocal listL;
    int found = 0;
    char nomeLocalidade[51];

    FILE *ficheiro = fopen("Localidades.dat","rb");
    if(ficheiro==NULL) return;

    FILE *tempF = fopen("TempName.dat","wb");
    if(tempF==NULL) return;

    listarLocal();
    printf("Escreva a Localidade:\t"); getstr(nomeLocalidade, 51);

    while(fread(&listL,sizeof(listLocal),1,ficheiro)){
        if(encontrarstr(nomeLocalidade, listL.nome)){
            printf("** Localidade Apagada **\n");
            found++;
        }else{
            fwrite(&listL,sizeof(listLocal),1,tempF);
        }
    }
    if(found == 0){
        printf("**** Localidade nao encontrada ****\n");
    }
    fclose(ficheiro); fclose(tempF);

    remove("Localidades.dat");
    rename("tempName.dat", "Localidades.dat");

    printf("Enter para continuar..."); getchar();

}

void apagarPraia(){

    listPraias listP;
    int found = 0;
    char nomePraia[51];

    FILE *ficheiro = fopen("Praias.dat","rb");
    if(ficheiro==NULL) return;

    FILE *tempF = fopen("TempName.dat","wb");
    if(tempF==NULL) return;

    listarPraias();
    printf("Escreva o nome da Praia:\t"); getstr(nomePraia, 51);

    while(fread(&listP,sizeof(listPraias),1,ficheiro)){
        if(encontrarstr(nomePraia, listP.nome)){
            printf("** Praia Apagada **\n");
            found++;
        }else{
            fwrite(&listP,sizeof(listPraias),1,tempF);
        }
    }
    if(found == 0){
        printf("**** Localidade nao encontrada ****\n");
    }
    fclose(ficheiro); fclose(tempF);

    remove("Praias.dat");
    rename("tempName.dat", "Praias.dat");

    printf("Enter para continuar..."); getchar();
}
void exportarCSV(){

    listLocal listL; listPraias listP;
    int res=0;

    FILE *ficheiro = fopen("Localidades.dat","rb");
    if(ficheiro==NULL) return;

    FILE *ficheiro1 = fopen("Praias.dat","rb");
    if(ficheiro1==NULL) return;

    FILE *ficheiroCSV = fopen("Produtos.csv","wb");
    if(ficheiroCSV==NULL) return;

    fseek(ficheiroCSV, 0, SEEK_END);
    int len = ftell(ficheiroCSV);
    if(len <= 0){
        char nomeLocalidade[51] = "Localidade", nomePraia[51] = "Praia", tipoPraia[51] = "Tipo";
        fprintf(ficheiroCSV,"%s; %s; %s\n", nomeLocalidade, nomePraia, tipoPraia);
    }
    while(fread(&listL,sizeof(listLocal),1,ficheiro) && fread(&listP,sizeof(listPraias),1,ficheiro1)){
        fprintf(ficheiroCSV,"%s; %s; %s\n", listL.nome, listP.nome, listP.tipo);
        res++;
    }
    fclose(ficheiro); fclose(ficheiro1); fclose(ficheiroCSV);

    if(res==1) printf("** Copiado com sucesso **\n");
    printf("Enter para continuar..."); getchar();
}

//void ficheiroLista(){}

int main(){

    int op;

    do{
        puts("Opcoes:");
        puts("*********");
        puts("1 - Inserir");
        puts("2 - Listar");
        puts("3 - Procurar Praia");
        puts("4 - Alterar Dados");
        puts("5 - Exportar para ficheiro CSV");
        puts("0 - Sair");
        printf("Escolher: ");

        op=getint();

        if(op == 1){
            printf("Inserir Localidade(1)...\nInserir Praia(2)->\nEscolha:\t"); op=getint();
            if(op==1){
                inserirLocalidade();
            }else if(op==2) {
                listarLocal();
                printf("Se local para a nova praia nao existir, escolha(1); se existe escolha(2): "); op=getint();
                if(op==1) inserirLocalidade(); if(op==2) inserirPraia();
            }
        }else if(op == 2){
            printf("Listar Localidades(1)...\nListar Praias(2)...\nListar Praias por Localidade(3)->\nEscolha:\t"); op=getint();
            if(op==1) listarLocal(); if(op==2) listarPraias(); if(op==3) listarpraiasPorLocal();

        }else if(op == 3){
            procurarPraia();

        }else if(op == 4){
            printf("Alterar Localidade(1)...\nApagar Localidade(2)\n----------------------------\nAlterar Praia(3)...Apagar Praia(4)->\nEscolha:\t"); op=getint();
            if(op==1) alterarLocalidade(); if(op==2) apagarLocalidade();
            if(op==3) alterarPraia(); if(op==4) apagarPraia();

        }else if(op == 5){
            exportarCSV();
        }
    }while(op != 0);

return 0;
}

