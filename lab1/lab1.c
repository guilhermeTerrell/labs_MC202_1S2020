#include <stdio.h>

//Lab. 1

//Fun��o que recebe um n�mero inteiro do usu�rio
int get_integer(void){
    int integer=0;
    scanf("%d", &integer);
    return integer;
}

//Fun��o que recebe um n�mero inteiro e uma matriz nxn vazia n e gera uma matriz nxn preenchida com dados do usu�rio
void gera_matriz(int n, int matriz[][n]){
    int i, j=0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            scanf("%d", &matriz[i][j]);
        }
        j=0;
    }
}

//Fun��o que calcula a soma da diagonal principal de uma matriz nxn
int somaDiagPrincipal(int n, int matriz[][n], int resultado){
    int i, j=0;
    resultado=0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(i==j){
                resultado=matriz[i][j]+resultado;
            }
        }
        j=0;
    }
    return resultado;
}

//Fun��o que calcula a soma da diagonal secund�ria de uma matriz nxn
int somaDiagSecundaria(int n, int matriz[][n], int resultado){
    int i, j=0;
    resultado=0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if((i+j)==(n-1)){
                resultado=matriz[i][j]+resultado;
            }
        }
        j=0;
    }
    return resultado;
}

//Fun��o que indica a quantidade de colunas de uma matriz nxn cuja soma resulta em um n�mero par
int somaColunasPares(int n, int matriz[][n], int pares){
    int i, j=0, soma=0;
    pares=0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            soma=matriz[j][i]+soma;
        }
        if(soma%2==0){
            pares++;
        }
        j=0;
        soma=0;
    }
    return pares;
}

//Fun��o que indica a quantidade de colunas de uma matriz nxn cuja soma resulta em um n�mero impar
int somaColunasImpares(int n, int matriz[][n], int impares){
    int i, j=0, soma=0;
    impares=0;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            soma=matriz[j][i]+soma;
        }
        if(soma%2!=0){
            impares++;
        }
        j=0;
        soma=0;
    }
    return impares;
}


int main(){
    int n, resultDiagPrincipal, resultDiagSecundaria, colunasPares, colunasImpares=0;
    n=get_integer();
    int matriz[n][n];
    gera_matriz(n, matriz);
    resultDiagPrincipal=somaDiagPrincipal(n, matriz, resultDiagPrincipal);
    resultDiagSecundaria=somaDiagSecundaria(n, matriz, resultDiagSecundaria);
    colunasPares=somaColunasPares(n, matriz, colunasPares);
    colunasImpares=somaColunasImpares(n, matriz, colunasImpares);
    printf("%d %d %d %d", resultDiagPrincipal, resultDiagSecundaria, colunasPares, colunasImpares);
    return 0;
}
