/*
    Descrição geral:    Pilha é uma estrutura de dados baseda no conceito LIFO (Last In First Out)
                        Só é possível acessar (inserir / remover) o elemento que está no topo da pilha.
    Objetivos:  Implementar uma estrutura dados tipo pilha utilizando lista ligada
*/

/****************        Includes             ****************/
#include <stdio.h>

/***************         Tipos de dados      ***************/
typedef struct no{
    unsigned short int dado;
    struct no * ptr_prox;
} no;

/***************        Variáveis globais     *********************/
no * top = NULL; /*ponteiro que aponta para o topo da pilha*/
no * temp = NULL; /*ponteiro que será utilizado temporariamente na craição de novos nos e liberação de espaço de memória*/

/*************            Protótipos das funções  ******************/
void push(void);
void pop(void);
void criaNo(void);

/**************************       Funções         ******************************/
/*
	Função:		criaNo
	Descrição:	Função que cria um no por alocação dinâmica e faz o ponteiro temporario "temp" apontar para o endereço desse no
*/
void criaNo(){
	temp = malloc(sizeof(no)); /*alocação dinâmica de espaço de mamória para variável do tipo struct no*/
}

/*
    Função:     push
    Descrição:  Função que insere um novo nó na pilha. O pornteiro top deve sempre apontar para o novo nó que foi inserido.
*/
void push(){
    if(top == NULL){
        /*Pilha está vazia, esse será o primeiro nó*/
        top = temp; /*ponteiro top aponta para o nó*/
        top -> ptr_prox = NULL; /*ptr_prox do nó aponta para NULL. ptr_prox do primeiro nó da pilha sempre aponta para NULL*/
    }
    else{
        /*Já existe ao menos um nó na pilha*/
        temp -> ptr_prox = top; /*ptr_prox do novo nó aponta para último nó do topo pilha*/
        top = temp; /*top aponta para o novo nó, que agora é o topo da pilha*/
    }
}

/*
    Função:     pop
    Descrição:  Função que remove um nó da pilha.
*/
void pop(){
    if(top -> ptr_prox == NULL){
        /*Se top -> ptr_prox = NULL significa que só existe um nó na pilha*/
        free(top); /*Liberar o espaço de memória*/
        else{
            temp = top; /*temp aponta para o nó que está no topo da lista*/
            top = top -> prox; /*top aponta para o nó imediatamente abaixo do nó que está no topo da pilha*/
            free(temp); /*Liberar espaço de memória apontado por temp*/
        }
    }
}


int main(void){
    
    /*criar uma pilha com 11 elementos*/
	for(i = 0; i <= 10; i++){
		criaNo();
		temp -> dado = i;
		push();
	}

	imprimeLista();

	printf("---------------------------------\n");

	//deletaLista();

	for(i = 0; i <= 10; i++){
		printf("%d-)\n", i);
		deletaNoComeco();
		imprimeLista();
		printf("---------------------------------\n");
	}

    return 0;
}