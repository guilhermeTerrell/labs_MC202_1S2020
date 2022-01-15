#include <stdio.h>
#include <stdlib.h>


//Operações: Adicionar -> 0 e Consultar -> 1

int vectorSize(int *vetor){
    int i=0;
    for(i=0; vetor[i]!='\0'; i++){
    }
    return i;
}

//Função que verifica se determinada idade X já existe no vetor de idade
void adiciona(int *vetorIdade, int *vetorCasos){
    int i, size, jaExiste=0;
    int idade, casos;
    size=vectorSize(vetorIdade);
    scanf("%d %d", vetorCasos, vetorIdade);
}

void imprime_ponteiro(int n, int *ptr1, int *ptr2){
    int i=0;
    for(i=0; i<n; i++){
        printf("%d %d\n", ptr1[i], ptr2[i]);
    }
}

int main(){
    int i, n, operacao=0;
    int tamanhoInicial=5;
    int *idade[tamanhoInicial];
    int *casosCovid[tamanhoInicial];
    printf("Insira a quantidade de operações\n");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("insira a operacao a ser realizada\n");
        scanf("%d", &operacao);
        if(operacao==0){
            //adiciona
            adiciona(idade, casosCovid);
        }
        if(operacao==1){
            //consulta
        }
    }
    imprime_ponteiro(tamanhoInicial, casosCovid, idade);
    return 0;
}
