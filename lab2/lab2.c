#include <stdio.h>

void adiciona(int *ptrVetorIdade, int *ptrVetorCasos, int tamanhoNecessario, int *counter){
    //Inicio da funcao
    int idade, casos, i=0;
    scanf("%d %d", &casos, &idade);
    //Verificar se já existe essa idade no vetor de idade
    for(i=0; i<tamanhoNecessario; i++){
        if(ptrVetorIdade[i]==idade){
            //Idade já existe
            printf("idade já existe\n");
            ptrVetorCasos[i]=ptrVetorCasos[i]+casos;
            printf("%d %d\n", ptrVetorCasos[i], ptrVetorIdade[i]);
            break;
        }
        else if(i==tamanhoNecessario-1){
            //Idade nova
            //Armazenar idade e casos na próxima posição
            printf("idade nova %d\n", i);
            ptrVetorIdade[*counter]=idade;
            ptrVetorCasos[*counter]=casos;
            printf("%d %d\n", ptrVetorCasos[*counter], ptrVetorIdade[*counter]);
            (*counter)++;
        }
    }
}

void consulta(int *ptrVetorIdade, int *ptrVetorCasos, int *counter, int *totalDeCasos){
    int idadeMin, idadeMax, total, i=0;
    printf("Digite o intervalo de idade a ser consultado\n");
    scanf("%d %d", &idadeMin, &idadeMax);
    for(i=0; i<(*counter); i++){
        if((ptrVetorIdade[i]>=idadeMin) && (ptrVetorIdade[i]<=idadeMax)){
            printf("counter: %d\n", (*counter));
            printf("casos: %d\n", ptrVetorCasos[i]);
            (*totalDeCasos)=(*totalDeCasos)+ptrVetorCasos[i];
        }
    }
}


int main(){
    int i, n, operacao, counter=0;
    int totalDeCasos=0;
    int tamanhoInicial=5;
    //Inicialização dos vetores
    int tamanhoNecessario=tamanhoInicial;
    int vetorIdade=malloc(tamanhoNecessario*sizeof(int));
    int vetorCasos=malloc(tamanhoNecessario*sizeof(int));
    //Inicialização dos ponteiros
    int *ptrVetorIdade=vetorIdade;
    int *ptrVetorCasos=vetorCasos;
    printf("Digite a quantidade de operacoes\n");
    scanf("%d", &n);
    for(i=0; i<n; i++){
        printf("Digite a operacao\n");
        scanf("%d", &operacao);
        if(operacao==0){
            //adiciona
            adiciona(ptrVetorIdade, ptrVetorCasos, tamanhoNecessario, &counter);
            if(counter==tamanhoNecessario){
                //vetor cheio
                printf("Alocando mais memoria\n");
                tamanhoNecessario=2*(tamanhoNecessario);
                realloc(ptrVetorIdade, tamanhoNecessario);
                realloc(ptrVetorCasos, tamanhoNecessario);
            }
        }
        if(operacao==1){
            //consulta
            consulta(ptrVetorIdade, ptrVetorCasos, &counter, &totalDeCasos);
            printf("Total de casos: %d\n", totalDeCasos);
        }
        totalDeCasos=0;
    }
    free(vetorCasos);
    free(vetorIdade);
    return 0;
}

