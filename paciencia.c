/*
    MC202
    Lab 1:      Paciência
    Objetivo:   Implementar em linguagem C o jogo de cartas chamado de "paciência"
    Link:       https://www.ic.unicamp.br/~francesquini/mc202/files/lab01.pdf
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
                    1-) Valor da carta;
                    2-) Naipe da carta
                    3-) A cor da carta
                    4-) Uma flag que indica se a carta está aberta ou virada
                    5-) Um ponteiro para a próxima carta
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

    Além disso a struct possui como membro um ponteiro que deve apontar para o endereço da próxima carta,
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

pilha_cartas top_J1 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J1*/
pilha_cartas top_J2 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J2*/
pilha_cartas top_J3 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J3*/
pilha_cartas top_J4 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J4*/
pilha_cartas top_J5 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J5*/
pilha_cartas top_J6 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J6*/
pilha_cartas top_J7 = NULL; /*ponteiro que aponta para o topo da pilha de jogo J7*/

pilha_cartas pilha_estoque = NULL; /*ponteiro que aponta para o topo da pilha de estoque*/

pilha_cartas pilha_descarte = NULL; /*ponteiro que aponta para o topo da pilha de descarte*/

pilha_cartas saida_ouros = NULL; /*ponteiro que aponta para o topo da pilha de saída do naipe ouros*/
pilha_cartas saida_paus = NULL; /*ponteiro que aponta para o topo da pilha de saída do naipe paus*/
pilha_cartas saida_copas = NULL; /*ponteiro que aponta para o topo da pilha de saída do naipe copas*/
pilha_cartas saida_espadas = NULL; /*ponteiro que aponta para o topo da pilha de saída do naipe espadas*/

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
void peek(pilha_cartas *);
void inicializaPilha(pilha_cartas *);
void imprimePilha(pilha_cartas *);
void destroiPilha(pilha_cartas *);
estadoDaCarta verificaCartaAberta(pilha_cartas *);
void verificaPilhaDescarte(void);
void moveCarta(pilha_cartas *, pilha_cartas *);
void abreCartasDaPilha(pilha_cartas *);
void abreCartasDeJogo();

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
        *ptrTOptr = temp; /*armazenar o espaço de memória alocado no membro carta_baralho*/
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
    Descrição:  Consultar o dado armazenado em uma carta da pilha
    Argumentos: Ponteiro para o ponteiro que aponta para a carta de interesse (geralmente o top)
*/
void peek(pilha_cartas * ptrTOptr){
    printf("valor: %d\n", (*ptrTOptr) -> valor);
    printf("naipe: %s\n", (*ptrTOptr) -> naipe);
    if((*ptrTOptr) -> cor == VERMELHA){
        printf("cor: vermelha\n");
    }
    if((*ptrTOptr) -> cor == PRETA){
        printf("cor: preta\n");
    }
    if((*ptrTOptr) -> abertaOuVirada){
        printf("estado: carta aberta\n");
    }
    else{
        printf("estado: carta virada\n");
    }
    printf("ptr_prox: %d\n", (*ptrTOptr) -> ptr_prox_carta);
}

/*
    Função:     inicializaPilha
    Descrição:  Atribui valores a pilha recém criada
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
*/
void inicializaPilha(pilha_cartas * ptrTOptr){

    unsigned int i = 1;

    for(i = 1; i <= 12; i++){

        push(ptrTOptr); /*inserir uma carta na pilha*/

        (*ptrTOptr) -> valor = i; /*valor da carta*/

        /*naipe da carta*/
        ((*ptrTOptr) -> naipe)[0] = 'O';

        /*a cor da carta é preenchida por software*/
        if((((*ptrTOptr) -> naipe)[0] == 'O') || (((*ptrTOptr) -> naipe)[0] == 'C')){
            (*ptrTOptr) -> cor = VERMELHA;
        }
        if((((*ptrTOptr) -> naipe)[0] == 'P') || (((*ptrTOptr) -> naipe)[0] == 'E')){
            (*ptrTOptr) -> cor = PRETA;
        }
        
        (*ptrTOptr) -> abertaOuVirada = CARTA_VIRADA;
    }
}

/*
    Função:     imprimePilha
    Descrição:  Percorrer todas as cartas de uma pilha de cartas imprimindo as informções de
                valor da carta, naipe, se está aberta ou virada, etc
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
*/
void imprimePilha(pilha_cartas * ptrTOptr){
    /*loop será executado enquanto houver mais de uma carta*/
    while((*ptrTOptr) -> ptr_prox_carta != NULL){
        peek(ptrTOptr);
        printf("-----------------------------\n");
        (*ptrTOptr) = (*ptrTOptr) -> ptr_prox_carta; /*apontar carta_atual para a próxima carta da pilha*/
    }
    /*quando (*ptrTOptr) -> ptr_prox_carta = NULL significa que só restou a primeira carta da pilha*/
    /*imprimir a primeira carta da pilha*/
    peek(ptrTOptr);
}

/*
    Função:     destroiPilha
    Descrição:  Libera todo o espaço de memória que foi alocado para a pilha
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
*/
void destroiPilha(pilha_cartas * ptrTOptr){
    /*(*ptrTOptr) -> ptr_prox_carta != NULL há mais de uma carta na pilha*/
    while((*ptrTOptr) -> ptr_prox_carta != NULL){
        pop(ptrTOptr); /*libera o espaço de memória da carta atual*/
        (*ptrTOptr) = (*ptrTOptr) -> ptr_prox_carta; /*apontar carta_atual para a próxima carta da pilha*/
    }
    /*quando (*ptr_to_top_J1) -> ptr_prox_carta == NULL significa que só há uma carta na pilha*/
    pop(ptrTOptr);
}


/*
    Função:     verificaCartaAberta
    Descrição:  Verificar se a carta apontada pelo ponteiro está aberta. Somente cartas abertas podem ser movidas
                entre as pilhas de jogo (VER REGRA 1!)
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
    Saída:      Retorna CARTA_ABERTA (1) se a carta estiver aberta ou CARTA_FECHADA(0) se a carta estiver virada.
*/
estadoDaCarta verificaCartaAberta(pilha_cartas * ptrTOptr){
    return (*ptrTOptr) -> abertaOuVirada;
}

/*
    Função:     verificaPilhaDescarte
    Descrição:  Verificar se a pilha de descarte está vazia. Se sim é preciso mover a primeira carta da pilha
                de estoque para a pilha de descarte (VER REGRA 2!)
*/
void verificaPilhaDescarte(){
    if(pilha_descarte == NULL){
        /*pilha de descarte está vazia*/
        pilha_descarte = pilha_estoque; /*apontar o ponteiro de pilha descarte para a primeira carta da pilha de estoque*/
        pilha_estoque = pilha_estoque -> ptr_prox_carta; /*atualizar o ponteiro da pilha de estoque para a próxima carta*/
        pilha_descarte -> ptr_prox_carta = NULL; /*apontar ptr_prox_carta pois essa é a unica carta na pilha de estoque*/
    }
}

/*
    Função: moveCarta
    Descrição:  Função que move cartas de uma pilha para outra, respeitando as regras estabelecidas
    Argumentos: pilha de origem, pilha de destino
    Saída:      printar na tela a pilha de origem, pilha de destino e carta sendo movimentada
*/
void moveCarta(pilha_cartas * ptrTOptr_origem, pilha_cartas * ptrTOptr_destino){
    if((*ptrTOptr_origem) -> ptr_prox_carta == NULL){
        /*só existe essa carta na pilha*/
        (*ptrTOptr_origem) -> ptr_prox_carta = *ptrTOptr_destino; /*apontar o ptr_prox para o topo da outra pilha*/
        *ptrTOptr_destino = *ptrTOptr_origem; /*atualizar o ponteiro do topo da pilha de destino para o endereço da nova carta*/
        *ptrTOptr_origem = NULL; /*pilha de origem que só tinha uma carta fica vazia após move-la para outr pilha*/
    }
}

/*
    Função:     abreCartasDaPilha
    Descrição:  Função que abre as cartas de jogo de uma pilha em específico, i.e. cartas que estão no topo da pilha de jogo.
                caso o membro "abertaOuVirada" da struct carta seja igual a CARTA_VIRADA significa que a primeira carta da pilha
                ainda está virada, e portanto deve ter seu valor alterado para CARTA_ABERTA (VER REGRA 3!)
    Argumentos: Ponteiro para o ponteiro que aponta para o top da pilha em questão
*/
void abreCartasDaPilha(pilha_cartas * ptrTOptr){
    /*deve haver ao menos uma carta na pilha*/
    if(((*ptrTOptr) != NULL) && ((*ptrTOptr) -> abertaOuVirada == CARTA_VIRADA)) (*ptrTOptr) -> abertaOuVirada = CARTA_ABERTA;
}

/*
    Função: abreCartasDeJogo
    Descrição:  Função que abre sequencialmente todas as cartas de jogo, i.e. cartas que estão no topo das pilhas de jogo (VER REGRA 3!). 
*/
void abreCartasDeJogo(){
    abreCartasDaPilha(ptr_to_top_J1);
    abreCartasDaPilha(ptr_to_top_J2);
    abreCartasDaPilha(ptr_to_top_J3);
    abreCartasDaPilha(ptr_to_top_J4);
    abreCartasDaPilha(ptr_to_top_J5);
    abreCartasDaPilha(ptr_to_top_J6);
    abreCartasDaPilha(ptr_to_top_J7);
}


/***********************         Main           ***********************************/
int main(){

    inicializaPilha(ptr_to_top_J3);

    abreCartasDeJogo(ptr_to_top_J3);

    imprimePilha(ptr_to_top_J3);
    
    destroiPilha(ptr_to_top_J3);
    
    return 0;
}