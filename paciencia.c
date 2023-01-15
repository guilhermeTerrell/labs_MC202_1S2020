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
                    1-) Valor e naipe da carta;
                    2-) Naipe da carta
                    3-) A cor da carta
                    4-) Uma flag que indica se a carta está aberta ou virada
                    5-) Um ponteiro para o próximo nó
*/

/*********************          Includes            *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************            Tipos de dados          *****************************/
#define TOTAL_CARTAS 52 /*quantidade total de cartas no baralho*/
#define CARTAS_DISTRIB 28 /*quantidade de cartas a serem distribuidas entre as pilhas*/
#define MAX_CARD_TYPE 5 /*Tamanho máximo para representar o conjunto de caracteres que formam o tipo da carta valor + naipe*/

/*definindo numericamente os valores das cartas que são representados por letras*/
#define A 1 /*Ás*/
#define J 11 /*Valete*/
#define Q 12 /*Dama*/
#define K 13 /*Rei*/

/*enum que atribui um valor inteiro a string que representa a cor da carta, sendo 0 = vermelha e 1 = preta*/
typedef enum corDaCarta{
    VERMELHA = 0,
    PRETA
} corDaCarta;

/*
    enum que atribui um valor inteiro a string que representa o estado da carta no jogo, sendo 0 = CARTA_VIRADA
    e 1 = CARTA_ABERTA
*/
typedef enum estadoDaCarta{
    CARTA_VIRADA = 0,
    CARTA_ABERTA
} estadoDaCarta;

/*
    A struct abaixo é um tipo abstrato de dado que possui as características que definem uma carta do baralho,
    (cor, naipe, valor, ...) além de também conter informações importantes para o andamento do jogo (se a carta 
    está aberta ou virada).

    A entrada de dado que será armazenado nessa struct é via string, por exemplo, "10E" (10 de espadas).
    Essa string deve ser quebrada em dois campos: seu valor numérico (10) e seu naipe (E), após isso o valor
    numérico será armazenado em carta.valor e o naipe em carta.naipe

    O campo corDaCarta deve ser preenchido automaticamente por Software seguindo a seguinte regra:
        Se naipe == "O" ou naipe == "C" -> carta.cor = VERMELHA
        Se naipe == "P" ou naipe == "E" -> carta.cor = PRETA 

    Além disso a struct possui como membro um ponteiro que deve apontar para o endereço da proóxima carta,
    possibilitando assim a criação de uma pilha através de lista ligada
*/
typedef struct carta{
    unsigned char valor; /*valor da carta é um número inteiro de 1 a 14*/
    char naipe[2]; /*vetor de carcteres criado estaticamente para armazenar o naipe da carta (O-Ouros, C-Copas, P-Paus, E-Espadas) + "\0"*/
    corDaCarta cor; /*0 é vermelha, 1 é preta*/
    estadoDaCarta abertaOuVirada; /*se for 1 a carta está aberta, se for 0 a carta está virada para baixo*/
    struct carta * ptr_prox_carta; /*ponteiro que aponta para o endereço da próxima carta de uma pilha*/
} carta;

typedef carta * pilha_cartas; /*definindo ponteiro para carta como um novo tipo de dado*/

/**************                 Variáveis globais       *****************************/
pilha_cartas top = NULL; /*ponteiro que aponta para o último elemento da pilha*/
pilha_cartas temp = NULL; /*ponteiro que será utilizado temporariamente para criar / deletar cartas da pilha*/

pilha_cartas top_J1 = NULL; /*ponteiro que aponta para o topo da pilha J1*/
pilha_cartas top_J2 = NULL; /*ponteiro que aponta para o topo da pilha J2*/
pilha_cartas top_J3 = NULL; /*ponteiro que aponta para o topo da pilha J3*/
pilha_cartas top_J4 = NULL; /*ponteiro que aponta para o topo da pilha J4*/
pilha_cartas top_J5 = NULL; /*ponteiro que aponta para o topo da pilha J5*/
pilha_cartas top_J6 = NULL; /*ponteiro que aponta para o topo da pilha J6*/
pilha_cartas top_J7 = NULL; /*ponteiro que aponta para o topo da pilha J7*/

/*
    Devemos utilizar ponteiro para ponteiro pois usaremos os ponteiros que apontam para o topo de cada uma
    das pilhas como parâmetro das funções. Se passarmos o ponteiro top diretamente no argumento da função
    não será possível alterar seu conteúdo.
*/
pilha_cartas * ptr_to_top_J1 = &top_J1; /*ponteiro para o ponteiro top_J1*/
pilha_cartas * ptr_to_top_J2 = &top_J2; /*ponteiro para o ponteiro top_J2*/
pilha_cartas * ptr_to_top_J3 = &top_J3; /*ponteiro para o ponteiro top_J3*/
pilha_cartas * ptr_to_top_J4 = &top_J4; /*ponteiro para o ponteiro top_J4*/
pilha_cartas * ptr_to_top_J5 = &top_J5; /*ponteiro para o ponteiro top_J5*/
pilha_cartas * ptr_to_top_J6 = &top_J6; /*ponteiro para o ponteiro top_J6*/
pilha_cartas * ptr_to_top_J7 = &top_J7; /*ponteiro para o ponteiro top_J7*/


/******************             Protótipos das funções  *****************************/
void push(pilha_cartas *);
void pop(pilha_cartas *);
void criaNo(void);
unsigned char pilhaVazia(pilha_cartas *);
void peek(void);


/*****************               Definição das funções     ***************************/
/*
    Função:     criaNo
    Descrição:  Função que cria uma struct no e aponta o ponteiro temp para esse nó
*/
void criaNo(){
    temp = malloc( sizeof(carta) ); /*alocar um espaço de memória para struc e apontar temp para o endereço desse bloco de memória*/
}

/*
    Função:     pilhaVazia
    Descrição:  Função que verifica se o ponteiro top = NULL. Se for, então a pilha está vazia.
                Se top == NULL: retorna 1
                Senão:          retorna 0
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
*/
unsigned char pilhaVazia(pilha_cartas * top){
    return (top == NULL) ? 1 : 0;
}

/*
    Função:     push
    Descrição:  Inserir elementos em um pilha
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
*/
void push(pilha_cartas * ptrTOptr){
    criaNo(); /*alocar espaço de memória para variável tipo carta*/
    if(*ptrTOptr == NULL){
        /*se o ponteiro apontar para NULL siginifica que a pilha está vazia*/
        /*inserir primeriro nó*/
        (*ptrTOptr) = temp; /*armazenar o espaço de memória alocado no membro carta_baralho*/
        (*ptrTOptr) -> ptr_prox_carta = NULL; /*primeiro no da pilha deve sempre apontar para NULL*/
    }
    else{
        /*se já houver ao menos uma carta na pilha*/
        temp -> ptr_prox_carta = *ptrTOptr; /*inserindo nova carta na pilha*/
        *ptrTOptr = temp; /*atualizando ponteiro que aponta para o topo da pilha*/
    }
}

/*
    Função:     pop
    Descrição:  Remover o último elemento de uma pilha (nó que é apontado pelo ponteiro top da pilha)
    Argumentos: Ponteiro para o ponteiro que aponta para a pilha em qustão
*/
void pop(pilha_cartas * ptrTOptr){
    if((*ptrTOptr) -> ptr_prox_carta == NULL){
        /*se (*ptrTOptr) -> ptr_prox_carta = NULL então esta é a última carta da pilha*/
        free(*ptrTOptr);/*liberar o espaço de memória*/
    }
    else{
        /*existe ao menos duas cartas na pilha*/
        temp = *ptrTOptr; /*temp aponta para o endereço da carta que atualemnte é o topo da pilha*/
        *ptrTOptr = (*ptrTOptr) -> ptr_prox_carta; /*atualizar o ponteiro que aponta para o topo da pilha para a próxima carta*/
        free(temp); /*liberar espaço de memória*/
    }
}

/*
    Função:     peek
    Descrição:  Consultar o dado armazenado no último nó da pilha
    Argumentos: Ponteiro que aponta para a pilha em questão
*/
void peek(void){
    
}

int main(){

    push(ptr_to_top_J1); /*inserir uma carta na pilha*/

    top_J1 -> valor = 10; /*valor da carta*/

    /*naipe da carta*/
    (top_J1 -> naipe)[0] = 'O';
    if(((top_J1 -> naipe)[0] == 'O') || ((top_J1 -> naipe)[0] == 'C')){
        printf("carta vermelha\n");
        top_J1 -> cor = VERMELHA;
    }
    if(((top_J1 -> naipe)[0] == 'P') || ((top_J1 -> naipe)[0] == 'E')){
        printf("carta preta\n");
        top_J1 -> cor = PRETA;
    }
    
    top_J1 -> abertaOuVirada = CARTA_ABERTA;

    printf("valor: %d\n", top_J1 -> valor);
    printf("naipe: %s\n", top_J1 -> naipe);
    printf("cor: %d\n", top_J1 -> cor);
    printf("estado: %d\n", top_J1 -> abertaOuVirada);
    printf("ptr_prox: %d\n", top_J1 -> ptr_prox_carta);
    
    pop(ptr_to_top_J1);
    
    return 0;

}