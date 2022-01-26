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

void imprime_lista_circ_ligada(p_no lista){
    p_no atual;
    for(atual = lista->prox; atual!=lista; atual = atual->prox){
        if(atual == lista->prox){
            printf("Senha: %d\n", atual->ant->senha);
        }
        printf("Senha: %d\n", atual->senha);
    }
}

p_no movimenta_atend1(p_no atend1, int passo1){
    int i=0;
    for(i=0; i<passo1; i++){
        atend1 = atend1->prox;
    }
    return atend1;
}

p_no movimenta_atend2(p_no atend2, int passo2){
    int i=0;
    for(i=0; i<passo2; i++){
        atend2 = atend2->ant;
    }
    return atend2;
}

p_no posicao_inicial(p_no lista, p_no head, int c){
    head = lista;
    int i=0;
    for(i=0; i<c; i++){
        head = head->prox;
    }
    return head;
}

p_no remover_no(p_no lista, p_no atend){
    p_no remover = atend;
    atend->ant->prox = atend->prox;
    atend->prox->ant = atend->ant;
    free(remover);
    return lista;
}

int main(){
    int n, c, k, l, i=0;
    int liberado = 1;
    p_no head, no, atend1, atend2, temp1, temp2;
    //Inicialização da lista
    atend1 = cria_lista_vazia();
    printf("Insira os dados: N, C, k e l\n");
    scanf("%d %d %d %d", &n, &c, &k, &l);
    atend1 = cria_lista_circular(atend1, n);
    head = posicao_inicial(atend1, head, c);
    //Inicialização dos ponteiros atend1 e atend2
    atend1 = head;
    atend2 = head;
    atend1 = movimenta_atend1(atend1, k);
    atend2 = movimenta_atend2(atend2, l);
    do{
        printf("%d %d\n", atend1->senha, atend2->senha);
        temp1 = atend1;
        temp2 = atend2;
        atend1 = atend1->ant;
        atend2 = atend2->prox;
        if(temp1 != temp2){
            //apaga os dois nós
            if(temp1 == atend2){
                atend2=atend2->prox;
            }
            atend1 = remover_no(atend1, temp1);
            if(temp2 == atend1){
                atend1 = atend1->ant;
            }
            atend2 = remover_no(atend2, temp2);
        }
        else{
            //apaga só um
            atend1 = remover_no(atend1, temp1);
        }
        atend1 = movimenta_atend1(atend1, k);
        atend2 = movimenta_atend2(atend2, l);
    }while(atend1->prox != atend1);
    if(atend1 == atend2){
        printf("%d %d\n", atend1->senha, atend1->senha);
        free(atend1);
    }
    return 0;
}
