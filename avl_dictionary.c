/**
* avl_dictionary.c
*
* Descrição: este programa cria um arquivo de dicionário de 
* palavras com seus sinonimos utilizando uma árvore AVL
* para armazenar estas palavras
*
*
*        AUTORES
* Lara Iasmine P Fabiano
* Gustavo Lino Barbosa
* Victor Filippi
* Vitor Tuler
* 13/10/2021
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

#define MAX_LEN 300
#define DELIM " ,.;:!?()\"\n"
#define FILENAME "dicionario.txt"
#define LIM 31

enum menu_opcoes {
    INSERIR = 1,
    PROCURAR_SIN = 2,
    SUBSTITUIR_SIN = 3,
    EXCLUIR_PALAVRA = 4,
    PRINT = 5,
    SAIR = 0
};

int menu(char * [], int); 

int main() {
    char * opcoes[] = {
        "Inserir palavra",
        "Procurar por sinonimo",
        "Substituir sinonimo",
        "Excluir palavra",
        "Imprimir arvore",
        "Sair do programa"
    };

    int op;

    FILE * arq; // Arquivo lógico
    avl_tree t = NULL; // Ponteiro para a raiz da árvore
    char linha[MAX_LEN], * palavra, * sinonimo; 
    char palavra_n[LIM], sinonimo_n[LIM];
    bool h;
    
    if ((arq = fopen(FILENAME, "r")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", FILENAME);
        return 1;
    }
    // leitura do arquivo 
    while (fgets(linha, MAX_LEN, arq) != NULL) { 
        int contador = 0;
        palavra = strtok(linha, DELIM);
        sinonimo = strtok(NULL, DELIM);
        avl_search(&t, palavra, sinonimo, &h);
    }
    fclose(arq);
    print_tree(t);
    do {
        op = menu(opcoes, sizeof(opcoes) / sizeof(char *));

        switch (op) {
            case INSERIR :
                printf("Digite a palavra a ser inserida: ");
                scanf(" %30[^\n]", palavra_n);
                printf("Digite seu sinonimo: ");
                scanf(" %30[^\n]", sinonimo_n);
                avl_search(&t, palavra_n, sinonimo_n, &h);
                break;

            case PROCURAR_SIN:
                printf("Digite a palavra que gostaria de saber o sinonimo: ");
                scanf(" %30[^\n]", palavra_n);
                avl_sin(&t, palavra_n, &h);
                break;

            case SUBSTITUIR_SIN:
                printf("Digite a palavra para inserir um novo sinonimo: ");
                scanf(" %30[^\n]", palavra_n);
                printf("Digite o novo sinonimo: ");
                scanf(" %30[^\n]", sinonimo_n);
                avl_sub(&t, palavra_n, sinonimo_n, &h);
                break;
            case EXCLUIR_PALAVRA:
                printf("Digite a palavra a ser excluida: ");
                scanf(" %30[^\n]", palavra_n);
                if (delete(&t, palavra_n, &h)) {
                    printf("Remocao realizada com sucesso!\n");
                    print_tree(t);
                }
                else {
                    printf("%s nao esta' na arvore\n", palavra_n);
                }
                break;
            case PRINT: 
                print_tree(t);
                
            case SAIR: 
                break;
            default: 
                    printf("\n\tOpcao invalida\n");
        }
    } while (op != 0);

    //CRIAR UM ARQUIVO DICIONARIO COM AS PALAVRAS DA ARVORE
    if ((arq = fopen(FILENAME, "w")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", FILENAME);
        return 1;
    }

    // //escreve no arquivo
    save_tree(t, arq);
    fclose(arq);
    return 0;
}

int menu(char * opcoes[], int num) 
{   
    int i, op;
    printf("\n\n\t\tDicionario de Sinonimos\n\n");
        for (i = 0; i < num-1; i++) {
            printf("\t%2d - %s\n", i + 1, opcoes[i]);
        }
    printf("\t%2d - %s\n", SAIR, opcoes[i]);
    printf("\tOpcao: ");
    scanf("%d", &op);
    return op;
}