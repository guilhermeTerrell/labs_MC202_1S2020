/*
    MC202
    Lab 1:      Paciência
    Objetivo:   Implementar em linguagem C o jogo de cartas chamado de "paciência"
    Método:     As pilhas de jogo serão implementadas utilizando lista ligada,

                |                 | 
                |    elemento_n  <-  top
                |                 |
                |       ...       |
                |    elemento_1   |
                |    elemento_0 ->  NULL
                |_________________|
                onde top é um ponteiro que aponta sempre para o último elemento da pilha
                
                Os elementos da pilha serão structs que conterão:
                    1-) O naipe da carta;
                    2-) Um ponteiro para o próximo nó

*/

/*********************          Includes            *********************************/
#include <stdio.h>
#include <stdlib.h>

/*******************            Tipos de dados          *****************************/
#define MAX_CARD_TYPE 5 /*Tamanho máximo para representar o conjunto de caracteres que formam um naipe*/

typedef struct no{
    char naipe[MAX_CARD_TYPE]; /*o naipe da carta é um vetor de caracteres alocado estaticamente*/
    unsigned char cartaAberta; /*se for 1 a carta está aberta, se for 0 a carta está virada*/
    struct no * ptr_prox; /*ponteiro que aponta para o próximo nó da pilha*/
} no;


/**************                 Variáveis globais       *****************************/
no * top = NULL; /*ponteiro que aponta para o último elemento da pilha*/
no * temp = NULL; /*ponteiro que será utilizado temporariamente para criar / deletar nós da pilha*/


/******************             Protótipos das funções  *****************************/
void push(void);
void pop(void);
void criaNo(void);
unsigned char pilhaVazia(void);


/*****************               Definição das funções     ***************************/
/*
    Função:     criaNo
    Descrição:  Função que cria uma struct no e aponta o ponteiro temp para esse nó
*/
void criaNo(){
    temp = (no * )malloc(sizeof(no)); /*alocar um espaço de memória para struc e apontar temp para o endereço desse bloco de memória*/
}

/*
    Função:     pilhaVazia
    Descrição:  Função que verifica se top = NULL. Se for, então a pilha está vazia.
                Se top == NULL: retorna 1
                Senão:          retorna 0
*/
unsigned char pilhaVazia(){
    return(top == NULL) ? 1 : 0;
}

/*
    Função:     push
    Descrição:  Inserir elementos em um pilha
*/
void push(){
    if(pilhaVazia()){
        /*inserir primeiro nó na pilha*/
        printf("estava vazia mesmo\n");
        top = temp; /*ao receeber o endereço de temp, top passa a apontar para o novo nó*/
        top -> ptr_prox = NULL; /*o primeiro nó da pilha sempre deve ter ptr_prox apontado para NULL*/
    }

    else{
        /*Já existe ao menos um nó na pilha*/
            printf("não estava vazia");
            temp -> ptr_prox = top; /*ptr_prox do novo nó aponta para o último nó da pilha*/
            top = temp; /*top é atualizado para o novo nó que será o novo topo da pilha*/
    }
}


int main(){

    criaNo();
    push();
    
    return 0;
}