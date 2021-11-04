#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Funcoes.h"

typedef struct L_Category{

    char categoria[25];

}listCategory;
typedef struct L_Products{

    int ID;
    char nome[25];
    struct L_Category cat;

}listProducts;

void showList(){
    FILE *ficheiro;
    listProducts list;

    ficheiro = fopen("Product.dat","rb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }

    printf("\n== List of Products ==\n");
    while (fread(&list,sizeof(listProducts),1,ficheiro))
    {
        printf("Product:\n");
        printf("ID: %d", list.ID);
        printf("\nName: "); puts(list.nome);
        printf("Category: "); puts(list.cat.categoria);
        putchar('\n');
    }
    fclose(ficheiro);
    printf("*** Enter to continue...");getchar();
}

void insert(){
    FILE *ficheiro;
    listProducts list;

    ficheiro = fopen("Product.dat","ab");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }

    printf("\n== Insert New Product ==\n");
    printf("ID: %d", list.ID = idInc("IDprodutos.dat"));
    printf("\nCategory: "); getstr(list.cat.categoria, 25);
    printf("Product Name: "); getstr(list.nome, 25);
    fwrite(&list,sizeof(listProducts),1,ficheiro);

    fclose(ficheiro);

}

void searchByCat(){

    FILE *ficheiro;
    listProducts list;
    char categoria[25];

    ficheiro = fopen("Product.dat","rb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }

        printf("\nCategory Name:\t"); getstr(categoria,25);
        while (fread(&list,sizeof(listProducts),1,ficheiro))
        {
            if(encontrarstr (list.cat.categoria, categoria)){
                printf(":::Product INFO:::\n");
                printf("ID: %d", list.ID);
                printf("\nProduct Name: "); puts(list.nome);
                printf("Category: "); puts(list.cat.categoria);
                putchar('\n');
            }
        }
    fclose(ficheiro);
    printf("*** Enter to continue...");getchar();

}
void listProd(){

    FILE *ficheiro;
    listProducts list;

    ficheiro = fopen("Product.dat","rb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }
    printf("\n== Product List ==\n");
    while (fread(&list,sizeof(listProducts),1,ficheiro))
    {
        printf("ID: %d", list.ID);
        printf("\nProduct Name: "); puts(list.nome);
        putchar('\n');
    }
    fclose(ficheiro);

}
void searchByProd(){

    FILE *ficheiro;
    listProducts list;
    char nome[25];

    ficheiro = fopen("Product.dat","rb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }
    listProd();

        printf("\nProduct Name:\t"); getstr(nome,25);
        while (fread(&list,sizeof(listProducts),1,ficheiro))
        {
            if(encontrarstr (list.nome,nome)){
                printf(":::Product INFO:::\n");
                printf("ID: %d", list.ID);
                printf("\nName: ");puts(list.nome);
                printf("Category: "); puts(list.cat.categoria);
                putchar('\n');
            }
        }
    fclose(ficheiro);
    printf("*** Enter to continue...");getchar();
}

void change(){

    FILE *ficheiro;
    listProducts list; fpos_t pos;
    char nome[25], categoria[25], op[2];
    int op1, found = 0;

    ficheiro = fopen("Product.dat","rb+");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }
    printf("....Search by Category(1)....Show List(2)...Enter to continue..\t"); op1 = getint();
    if(op1 == 1){
        searchByCat();
    }else if(op1 == 2){
        showList();
    }

    printf("Product name:\t"); getstr(nome,25);
    fgetpos(ficheiro,&pos);

    while (fread(&list,sizeof(listProducts),1,ficheiro))
        {
            if(encontrarstr (list.nome,nome)){
                printf("\n*** Product Found ***\n");
                printf("ID: %d", list.ID);
                printf("\nProduct Name: "); puts(list.nome);
                printf("Product Category: ");puts(list.cat.categoria);
                putchar('\t');
                printf("Change Product(S/N):\t"); getstr(op,2);
                if(toupper(op[0])=='S'){
                    found++;
                    printf("Product Info change to..\n");
                    printf("ID: %d", list.ID);
                    printf("\nName: "); getstr(list.nome, 25);
                    printf("Category: "); getstr(list.cat.categoria, 25);
                    fsetpos(ficheiro,&pos);
                    fwrite(&list,sizeof(listProducts),1,ficheiro);
                    fflush(ficheiro);
                }else{
                    found=2;
                }
            }
            fgetpos(ficheiro,&pos);
        }
    if(found == 0){
        printf("**** Not found ****\n");
    }else if(found == 1){
        printf("Update successfully...");
    }
    fclose(ficheiro);

    printf("\nEnter to exit..."); getchar();
}
void delete(){

    FILE *ficheiro, *tempF;
    char nome[25]; int found = 0;
    listProducts list;

    ficheiro = fopen("Product.dat","rb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }
    tempF = fopen("TempName.dat","wb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }
    printf("....Search by Category(1)....Show List(2)...Enter to continue.."); printf("\nChoose: "); int op1 = getint();
    if(op1 == 1){
        searchByCat();
    }else if(op1 == 2){
        showList();
    }

    printf("Product name to delete:\t"); getstr(nome,25);

    while(fread(&list, sizeof(listProducts),1,ficheiro) != NULL){
            if(encontrarstr(nome, list.nome)){
                printf("**** Product deleteted ****\n");
                found=1;
            }else{
                fwrite(&list,sizeof(listProducts),1,tempF);
            }
    }
    if(found == 0){
        printf("**** Not found ****\n");
    }
    fclose(ficheiro); fclose(tempF);
    remove("Product.dat");
    rename("tempName.dat", "Product.dat");

    printf("\nEnter to exit..."); getchar();
}

void exportCSV(){

    FILE *ficheiro, *ficheiroCSV;
    listProducts list; int x = 0;

    ficheiro = fopen("Product.dat","rb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }
    ficheiroCSV = fopen("Produtos.csv","wb");
    if(ficheiro==NULL) {
        perror("Erro");
        return;
    }

    while(fread(&list, sizeof(listProducts),1,ficheiro) != NULL){
            fprintf(ficheiroCSV, "%d; %s; %s\n", list.ID, list.nome, list.cat.categoria);
            x++;
            }
    if(x == 1){
        printf("**** Export successfully ****\n");
    }
    fclose(ficheiro); fclose(ficheiroCSV);

    printf("\nEnter to exit..."); getchar();

}

int main(){

    int op;

    do{
        puts("\n== Welcome ==");
        puts("Option:");
        puts("*********");
        puts("1 - Insert Product");
        puts("2 - Change Product");
        puts("3 - Products INFO(search)");
        puts("4 - Delete Product");
        puts("5 - Show Product List");
        puts("6 - Export to CSV");
        puts("0 - Exit");
        printf("Choose: ");

        op=getint();

        if(op == 1){
            insert();

        }else if(op == 2){
            change();

        }else if(op == 3){
            printf("....Search by Category(1)....Search by Product Name(2)...."); printf("\nChoose: "); int op=getint();
            if(op == 1) searchByCat(); if(op == 2) searchByProd();

        }else if(op == 4){
            delete();

        }else if(op == 5){
            showList();

        }else if(op == 6){
            exportCSV();

        }

    }while(op != 0);


return 0;
}
