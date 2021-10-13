/* avl.h
 * Definição do TAD para representar uma árvore AVL e protótipo
 * de suas operações.
 *
 * AUTORES
* Lara Iasmine P Fabiano
* Gustavo Lino Barbosa
* Victor Filippi
* Vitor Tuler
* 13/10/2021
 */

#ifndef _AVL_H
#define _AVL_H

#include <stdbool.h>
#include <stdio.h>

// Definição da estrutura de dados
typedef struct {
    char chave[31];
    char sinonimo[31];
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

/*
 * Imprime a árvore AVL t através de um percurso em ordem.
 */
void print_tree(avl_tree t);

/*
 * Armazena os dados da árvore AVL t através de um percurso em ordem.
 */
void save_tree(avl_tree t, FILE * arq);

/*
 * Verifica se a palavra x já ocorreu na árvore AVL t; 
 * caso afirmativo, seu sinonimo é atualizado pelo novo valor;
 * caso contrário, x e seu sinonimo são inseridos
 * em t e h sinaliza que houve um aumento da
 * altura de t.
 */
void avl_search(avl_tree * t, char * x, char * s, bool * h);

/* 
 * Substitui o sinonimo de uma palavra por outro
 */
void avl_sub(avl_tree * t, char * x, char * s, bool * h);

/* Procura o sinonimo da palavra x na arvore AVL t;
 *caso true, devolve o sinonimo da palavra
 *caso false, devolve negativo.
 */
void avl_sin(avl_tree * t, char * x, bool * h);



/* 
 * Faz uma rotação para a direita na árvore AVL t. 
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void rotacao_esq(avl_tree *);

/*
 * Se a palavra x está contida na árvore AVL t, x é
 * removida de t, h sinaliza uma diminuição da altura
 * de t e a função devolve verdadeiro; caso contrário,
 * nada é feito e a função devolve falso.
 */
bool delete(avl_tree * t, char * x, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore esquerda e sinaliza se houve uma 
 * dimuição da altura dessa subárvore através de h.
 */
void balance_esq(avl_tree * t, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore direita e sinaliza se houve uma 
 * dimuição da altura dessa subárvore através de h.
 */
void balance_dir(avl_tree *, bool *);

/*
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se 
 * houve uma diminuição da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);

/* Devolve a profundidade da árvore AVL apontada por t. */
int avl_profundidade(avl_tree t);

#endif
