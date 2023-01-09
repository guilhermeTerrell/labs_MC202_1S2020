/*************************             Includes                **********************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************        Tipos de dados           ***********************************************/
typedef struct no {
	int dado;
	struct no * ptr_prox;
} no;


/*********************              Variáveis globais             *******************************************/
no * head = NULL; /*ponteiro que aponta sempre para o primeiro nó da lista. Como a lista começa vazia, é inicilizado com NULL*/
no * tail = NULL; /*ponteiro que aponta sempre para o último nó da lista. Como a lista começa vazia, é inicilizado com NULL*/
no * temp = NULL; /*ponteiro que irá armazenar temporariamente o endereço de novos nos que forem criados. Inicialmente aponta para NULL*/
unsigned char listaVazia = 1; /*se for 1, siginifica que a lista está vazia*/

/********************               Protótipos das funções           *****************************************/
void criaNo(void);
void adicionaNoComeco(void);
void adicionaNoFinal(void);
void imprimeLista(void);
unsigned char checkListaVazia(void);
void deletaNoComeco(void);
void deletaLista(void);

/*********************              Definição das funções           *****************************************/
/*
	Função:		criaNo
	Descrição:	Função que cria um no por alocação dinâmica e faz o ponteiro temporario "temp" apontar para o endereço desse no
*/
void criaNo(){
	temp = malloc(sizeof(no)); /*alocação dinâmica de espaço de mamória para variável do tipo struct no*/
}

/*
	Função:		checkListaVazia
	Descrição:	Verificar se uma lista ligada está vazia. Se estiver, função retorna 1. Se não, a função retorna 0
*/
unsigned char checkListaVazia(){
	if(head == NULL){
		/*lista está vazia*/
		return 1;
	}
	
	else{
		/*lista não está vazia*/
		return 0;
	}
}

/*
	Função:		adicionaNoComeco
	Descrição:	Função que insere um nó no começo de uma lista ligada. Se a lista ligada estiver vazia (head = NULL), 
				head e tail devem receber o endereço de temp, se não apenas head deve ser atualizado.
*/
void adicionaNoComeco(){
	if(head == NULL){
		/*Lista vazia -> temp será o primeiro nó*/
		head = temp; /*head aponta para o endereço de temp*/
		tail = temp; /*tail aponta para o endereço de temp*/
		head -> ptr_prox = NULL; /*ptr_prox do no criado aponta para NULL*/
	}
	else{
		/*Já existe ao menos 1 nó*/
		temp -> ptr_prox = head; /*ptr_prox do novo no aponta para o primeiro nó da lista ligada*/
		head = temp; /*atualizar head para apontar para o novo nó que será o primeiro da lista ligada*/
	}
}

/*
	Função:		adicionaNoFinal
	Descrição:	Função que insere um nó no final de uma lista ligada. Se a lista ligada estiver vazia (head = NULL), 
				head e tail devem receber o endereço de temp, se não apenas tail deve ser atualizado.
*/
void adicionaNoFinal(){
	if(head == NULL){
		/*Lista vazia -> temp será o primeiro nó*/
		head = temp; /*head aponta para o endereço de temp*/
		tail = temp; /*tail aponta para o endereço de temp*/
		head -> ptr_prox = NULL; /*ptr_prox do no criado aponta para NULL*/
	}
	else{
		/*Já existe ao menos 1 nó*/
		tail -> ptr_prox = temp; /*ptr_prox do último no da lista aponta para o novo no*/
		tail = temp; /*atualizar o último no apontado por tail*/
		tail -> ptr_prox = NULL; /*último nó deve apontar para NULL*/
	}
}

/*
	Função:		imprimeLista
	Descrição:	Função que imprime o membro "dado" da struct no de uma lista ligada enquanto o proximo endereço não for NULL.
				Quando o próximo endereço for NULL siginifica que toda a lista foi percorrida
*/
void imprimeLista(){
	no * p_no = head; /*p_no aponta para o primeiro nó da lista*/
	while(p_no != NULL){
		printf("%d\n", p_no -> dado);
		p_no = p_no -> ptr_prox; /*atualiza para apontar para o endereço do próximo nó*/
	}
}

/*
	Função: 	deletaNoComeco
	Descrição:	Deleta o primeiro nó da lista ligada (aquele que é apontado por head)
*/
void deletaNoComeco(){
	/*se head -> ptr_prox = NULL siginifica que só existe um nó na lista*/
	if(head -> ptr_prox == NULL){
		free(head);
	}
	else{
		temp = head; /*ponteiro temp aponta para o mesmo endereço de head*/
		head = head -> ptr_prox; /*head é atualizado para apontar para o próximo nó*/
		free(temp); /*espeço de memória do primeiro nó da lista é liberado*/
	}
}


/*
	Função:		deletaLista
	Descrição:	Deletar todos os nos que compõem a lista ligada
*/
void deletaLista(){
	/*Enquanto head -> ptr_prox != NULL significa que existe mais de um nó*/
	while(head -> ptr_prox != NULL){
		temp = head; /*apontar temp para o mesmo no que head*/
		head = head -> ptr_prox; /*atualizar o endereço de head para o próximo nó*/
		free(temp); /*liberar o espaço de memória apontado por temp*/
	}
	/*Quando head -> ptr_prox = NULL, siginifica que só restou um nó, tanto head quanto tail apontam para ele*/
	free(head);
}

int main(void){
	int i = 0;
	/*
	            _______________      _______________             __________
	   head -> |dado1|ptr_prox1| -> |dado1|ptr_prox1| -> ... -> |dadon|NULL| <- tail

	*/
	
	/*criar a lista ligada com */
	for(i = 0; i <= 10; i++){
		criaNo();
		temp -> dado = i;
		adicionaNoFinal();
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
	free(tail);
	return 0;
}
