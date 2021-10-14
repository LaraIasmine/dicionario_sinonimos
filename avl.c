/* avl.c
 * Implementação das operações realizadas sobre o TAD que  
 * representa uma árvore AVL.
 *
 * Lara Iasmine P Fabiano - 7986907
 * Gustavo Lino Barbosa - 9656506
 * Victor Filippi - 5148846
 * Vitor Tuler - 4736500  
 */

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tree(avl_tree t) {
    if (t != NULL) {
        print_tree(t->esq);
        printf("%30s %30s\n", t->dado.chave, t->dado.sinonimo); 
        print_tree(t->dir);
    } 
}

void save_tree(avl_tree t, FILE * arq) {
    char linha[31]= "";//char para armazenar os valores a serem inseridos no arquivo
    if (t != NULL) {
        save_tree(t->esq, arq);
        strcat(linha, t->dado.chave);
        strcat(linha, " ");
        strcat(linha, t->dado.sinonimo);
        strcat(linha, "\n");
        fwrite(linha, strlen(linha), 1, arq);//escreve no arquivo as informações do char linha
        save_tree(t->dir, arq);
    }
}

void avl_search(avl_tree * t, char * x, char * s, bool * h) {
    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        *h = true;
        strcpy((*t)->dado.chave,x);
        strcpy((*t)->dado.sinonimo,s);
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (strcasecmp(x,(*t)->dado.chave) < 0 ) { // Inserir a esquerda
        avl_search(&(*t)->esq, x, s, h);
        if (*h) { // O ramo esquerdo cresceu
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        *h = false;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotação simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotação dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    } // fim do if
    else if (strcasecmp(x,(*t)->dado.chave) > 0) { // Inserir a direita
        avl_search(&(*t)->dir, x, s, h);
        if (*h) { // O ramo direito cresceu
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                         *h = false;
                         break;
                case 0 : (*t)->bal = 1;
                         break;
                case 1: // Rebalanceamento
                    if ((*t)->dir->bal == 1) { // Rotação simples p/ esquerda
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    }
                    else { // Rotação dupla para esquerda
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                    } // fim do else
                    *h = false;
                    (*t)->bal = 0;
                    break;
            } // fim do switch
        }
    } // fim do if
    else // a chave já está na árvore, atualiza o sinonimo
        strcpy((*t)->dado.sinonimo,s);
} // fim de avl_search

void avl_sin(avl_tree * t, char * x, bool * h) {
    if (*t == NULL) {
        printf("A palavra nao se encontra no dicionario");
    }
    else if (strcasecmp(x,(*t)->dado.chave) < 0) { //Procura a esquerda
        avl_sin(&(*t)->esq, x, h);
    } // fim do if
    else if (strcasecmp(x,(*t)->dado.chave) > 0) { //Procura a direita
        avl_sin(&(*t)->dir, x, h);
    } // fim do if
    else 
        printf("O sinonimo da palavra e': %s", (*t)->dado.sinonimo);
}//fim avl_sin

void avl_sub(avl_tree * t, char * x, char * s, bool * h){
  if (*t == NULL) {
        printf("A palavra nao se encontra no dicionario");
    }
    else if (strcasecmp(x,(*t)->dado.chave) < 0) { //Procura a esquerda
        avl_sub(&(*t)->esq, x, s, h);
    } // fim do if
    else if (strcasecmp(x,(*t)->dado.chave) > 0) { // Procura a direita
        avl_sub(&(*t)->dir, x, s, h);
    } // fim do if
    else //atualiza o valor do sinonimo 
        strcpy((*t)->dado.sinonimo,s); 
        printf("\n\n\t\tSinonimo atualizado com sucesso!\n");
}//fim avl_sub

void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}

bool delete(avl_tree * t, char * x, bool * h) {
    avl_tree p;
    bool result;
    if (*t == NULL) // A chave não se encontra na árvore
        return false;
    else if (strcasecmp(x,(*t)->dado.chave) == 0) { // a chave está neste nó
        p = *t;
        if ((*t)->esq == NULL) { // nó folha ou somente com subárvore direita
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL) { // nó com uma única subárvore esquerda
            *t = p->esq;
            *h = true;
        }
        else { // nó com duas subávores
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.chave) < 0) {
        result = delete(&(*t)->esq, x, h);
        if (*h) balance_esq(t, h);
        return result;
    }
    else {
        result = delete(&(*t)->dir, x, h);
        if (*h) balance_dir(t, h);
        return result;
    }
} // fim do delete

void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
                break;
        case 0: (*t)->bal = -1;
                *h = false;
                break;
        case -1: // rebalanceamento
                p1 = (*t)->esq;
                b1 = p1->bal;
                if (b1 <= 0) { // rotação simples
                    (*t)->esq = p1->dir;
                    p1->dir = *t;
                    if (b1 == 0) {
                        (*t)->bal = -1;
                        p1->bal = 1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotaçãoo dupla
                    p2 = p1->dir;
                    b2 = p2->bal;
                    p1->dir = p2->esq;
                    p2->esq = p1;
                    p1->esq = p2->dir;
                    p2->dir = *t;
                    if(b2 == -1) (*t)->bal = 1;
                    else (*t)->bal = 0;
                    if(b2 == 1) p1->bal = -1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}

void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotação simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}

avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}

int avl_profundidade(avl_tree t)
{
    if (t == NULL) {
        return 0;
    }
    int e = avl_profundidade(t->esq);
    int d = avl_profundidade(t->dir);
    return 1 + (e > d ? e : d);
}