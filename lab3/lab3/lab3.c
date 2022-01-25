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

p_no headLista(p_no lista, int c){
    int i=0;
    for(i=0; i<c; i++){
        lista=lista->prox;
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

p_no posicao_inicial(p_no atend, int c){
    int i=0;
    for(i=0; i<c; i++){
        atend = atend->prox;
    }
    return atend;
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
    p_no lista, proximo, atend1, atend2, backupAtend1, backupAtend2;
    //Inicialização da lista
    lista = cria_lista_vazia();
    printf("Insira os dados: N, C, k e l\n");
    scanf("%d %d %d %d", &n, &c, &k, &l);
    lista = cria_lista_circular(lista, n);
    atend1 = lista;
    atend2 = lista;
    //Inicialização dos ponteiros atend1 e atend2
    atend1 = posicao_inicial(atend1, c);
    atend2 = posicao_inicial(atend2, c);
    //Deslocamento dos ponteiros atend1 e atend2
    atend1 = movimenta_atend1(atend1, k);
    atend2 = movimenta_atend2(atend2, l);
    for(proximo = lista->prox; proximo != lista; proximo = proximo->prox){
        if((atend1 == lista) || (atend2 == lista)){
            lista = lista->prox;
            liberado = 0;
        }
        else{
            liberado = 0;
        }
        if(liberado == 0){
            if(atend1 != atend2){
                //salvar posições dos ponteiros
                backupAtend1 = atend1->ant;
                backupAtend2 = atend2->prox;
                if(backupAtend1 == atend2){
                    backupAtend1 = backupAtend1->ant;
                }
                if(backupAtend2 == atend1){
                    backupAtend2 = backupAtend2->prox;
                }
                printf("%d %d\n", atend1->senha, atend2->senha);
                //remover nós
                lista = remover_no(lista, atend1);
                lista = remover_no(lista, atend2);
                //retomar posições dos ponteiros
                atend1 = backupAtend1;
                atend2 = backupAtend2;
                //movimentar ponteiros
                atend1 = movimenta_atend1(atend1, k);
                atend2 = movimenta_atend2(atend2, l);
                liberado = 1;
            }
            else{
                //salvar posições dos ponteiros
                backupAtend1 = atend1->ant;
                backupAtend2 = atend2->prox;
                printf("%d %d\n", atend1->senha, atend2->senha);
                //remover nós
                lista = remover_no(lista, atend1);
                //retomar posições dos ponteiros
                atend1 = backupAtend1;
                atend2 = backupAtend2;
                //movimentar ponteiros
                atend1 = movimenta_atend1(atend1, k);
                atend2 = movimenta_atend2(atend2, l);
                liberado = 1;
            }
        }
    }
    if(proximo == lista){
        printf("%d %d\n", atend1->senha, atend2->senha);
        free(lista);
    }
    return 0;
}
