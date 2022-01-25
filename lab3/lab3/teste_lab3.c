#include <stdio.h>
#include <stdlib.h>

/*Definindo um tipo - a lista duplamente ligada de clientes*/
typedef struct cliente {
	int senha; /*senha do cliente*/
	struct cliente *prox; /*aponta para próximo cliente no círculo*/
	struct cliente *ant; /*aponta para cliente anterior no círculo*/
} cliente;
typedef struct cliente * clientela;

/*Criando uma lista vazia - primeiro elemento, nulo*/
clientela criar_lista(){
	return NULL;
}

/*Adicionando elemento na lista - adicionando cientes no círculo*/
clientela add_cliente(clientela lista, int senha){
	clientela novo;
	novo=malloc(sizeof(clientela));
	novo->senha=senha;
        if(lista==NULL){
		novo->prox=novo;
		novo->ant=novo;
	}else{
	    novo->prox=lista;
	    novo->ant=lista->ant;
	    (lista->ant)->prox=novo;
	    lista->ant=novo;
	}
	return novo;
}

/*Percorrendo uma lista - Atendendo os clientes*/
int atendendo(clientela clientes, int k, int ck, int b){
    clientela i;
    int m;
    i=clientes;
    do{ /*percorrendo a lista tentando encontrar o cliente de partida*/
        i=i->ant;
    }while((i->senha)!=ck);
    /*i encontrado é o ponto de partida, basta dar o passo k*/
    if(b==1){ /*Atendente1*/
    	for(m=0;m<k-1;m++){ i=i->ant; } //printf("i->senha:%d\n",i->senha);
        return (i->senha);
    }else if(b==2){ /*Atendente2*/
        for(m=0;m<k-1;m++){ i=i->prox; } //printf("i->senha:%d\n",i->senha);
        return (i->senha); }
}

/*Descobrindo ponto de partida da próxima iteração*/
clientela novo_atendente(int atendente, clientela clientes, int a){
    clientela i;
    i=clientes;
    do{
        i=i->ant;
    }while((i->senha)!=atendente);
	if(a==1){ return (i->ant);
	}else if(a==2){ return (i->prox); }
    return NULL;
}


/*Destruindo elementos da lista - tirando clientes já atendidos*/
clientela limpando(clientela clientes, int atendido1, int atendido2){
    clientela i;
    if(clientes->prox==clientes && clientes->ant==clientes){ return NULL; }
    i=clientes;
    do{
        i=i->prox;
    }while((i->senha)!=atendido1); /*achamos o endereço de atendido1, é i*/
    i=i->prox;
    i->ant=(i->ant)->ant;
    (i->ant)->prox=i;
    if(atendido1!=atendido2){
	    if(i->prox==i && i->ant==i){ return NULL; }else{
            do{
                i=i->prox;
            }while((i->senha)!=atendido2); /*achamos o endereço de atendido2, é j*/
            i=i->prox;
            i->ant=(i->ant)->ant;
            (i->ant)->prox=i;
	    }
    } /*removemos atendido da lista i e k, que equivale a clientes atendidos*/
    return i;
}


/*Imprimindo lista - para ver se está correta*/
void imprimir(clientela lista){
    clientela i;
    i=lista;
    do{
        printf("ant:%d atual:%d prox:%d\n",i->ant->senha,i->senha,i->prox->senha);
        i=i->prox;
    }while(i!=lista);
}

int main(){
	int n,c,k,l,atendente1,atendente2,i;
	clientela clientes,aux1,aux2;

/*1 - Entrada*/
scanf("%d %d %d %d",&n,&c,&k,&l);

/*2 - Criando uma lista duplamente ligada*/
    /*Primeiro termo é NULL*/
clientes=criar_lista();
    /*Adicionando termos*/
for(i=0; i<n; i++){ clientes=add_cliente(clientes,i); }

/*3 - Definindo quem serão atendidos e por quem*/
aux1=aux2=clientes;
/*Primeiro cliente do atendente1*/
do{ aux1=aux1->ant; }while((aux1->senha)!=c);
for(i=0; i<k;i++){ aux1=aux1->ant; }
printf("%d ",aux1->senha);
/*Primeiro cliente do atendente2*/
do{ aux2=aux2->ant; }while((aux2->senha)!=c);
for(i=0; i<l;i++){ aux2=aux2->prox; }
printf("%d\n",aux2->senha);
/********************************/
clientes=limpando(clientes,aux1->senha,aux2->senha);
atendente1=(aux1->ant)->senha;
atendente2=(aux2->prox)->senha;

do{
    atendente1=atendendo(clientes,k,atendente1,1);
    printf("%d ",atendente1); /*imprimindo quem foi cliente do atendente1*/
    aux1=novo_atendente(atendente1,clientes,1);

    atendente2=atendendo(clientes,l,atendente2,2);
    printf("%d\n",atendente2); /*imprimindo quem foi cliente do atendente2*/
    aux2=novo_atendente(atendente2,clientes,2);

    /*liberando os clientes atendidos*/
    clientes=limpando(clientes,atendente1,atendente2);

    atendente1=aux1->senha;
    atendente2=aux2->senha;

}while(clientes!=NULL);

return 0; }
