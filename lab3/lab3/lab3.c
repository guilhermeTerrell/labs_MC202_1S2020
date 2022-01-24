#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int senha;
    struct no *ant;
    struct no *prox;
}no;

typedef struct no *p_no;

p_no cria_lista_vazia(){
    return NULL;
}

p_no add_no_dupla_Circ(p_no lista){
    p_no novo;
    if(lista == NULL){ //lista vazia
        //inserir primeir nó
        novo = malloc(sizeof(struct no));
        novo->prox = novo;
        novo->ant = novo;
    }
    return novo;
}

//Função que cria uma lista circular duplamente ligada com n nós
p_no cria_lista_circular(p_no lista, int n){
    p_no novo, ultimo;
    int i=0;
    for(i=0; i<n; i++){
        novo = malloc(sizeof(no));
        if(i==0){
            lista = novo;
            lista->prox = lista;
            lista->ant = lista;
            lista->senha = i;
            ultimo = lista;
        }
        else{
            novo->ant = ultimo;
            novo->prox = lista;
            lista->ant = novo;
            novo->senha = i;
            ultimo->prox = novo;
            ultimo = ultimo->prox;
        }
    }
    return lista;
}

int main(){
    int n, c, k, l, i=0;
    p_no lista, atual;
    //Inicialização
    lista = cria_lista_vazia();
    printf("Insira os dados: N, C, k e l\n");
    scanf("%d %d %d %d", &n, &c, &k, &l);
    lista = cria_lista_circular(lista, n);
    printf("%d\n", lista->senha);
    printf("%d\n", lista->ant->senha);
    for(atual = lista->prox; atual!=lista; atual = atual->prox){
        if(atual == lista->prox){
            printf("Senha: %d\n", atual->ant->senha);
        }
        printf("Senha: %d\n", atual->senha);
    }
    return 0;
}
