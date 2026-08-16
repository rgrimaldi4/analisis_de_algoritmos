#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
 
long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;

typedef struct{
    char objeto;
    int valor;
    int peso;
}Tobjeto;

int maximizar( Tobjeto *objetos,int longitud, int i, int capacidadBolsa, int **memo ){
    pasos++;
    int valorAgregado=0;

    if(capacidadBolsa==0 || i>=longitud){
        return 0;
    }

    //si es diferente de -1 ya fue calculado
    if(memo[i][capacidadBolsa] != -1){
        return memo[i][capacidadBolsa];
    }

    //printf( "%d - ", objetos[i].peso );
    if( objetos[i].peso <= capacidadBolsa ){
        valorAgregado = objetos[i].valor + maximizar(objetos,longitud, i+1, capacidadBolsa-objetos[i].peso, memo);
    }

    int valorIngnorado = maximizar( objetos, longitud,  i+1, capacidadBolsa, memo );

    if(valorAgregado > valorIngnorado){
        memo[i][capacidadBolsa] = valorAgregado;
        //return valorAgregado;
    }else{
        memo[i][capacidadBolsa] = valorIngnorado;
        //return valorIngnorado;
    }

    return memo[i][capacidadBolsa];
}


int main(){
    srand(1);

    for(int k=10; k<=MAX; k+=5){
        int capacidadBolsa = 50;
        pasos=0;

        Tobjeto *objetos = malloc( sizeof(Tobjeto)*k );

        for(int i=0; i<k; i++){
            int valor = rand()%20+1;
            int peso = rand()%10+1;
            objetos[i].valor = valor;
            objetos[i].peso = peso;
        }

        //creo matriz para memoizacion con -1 inicialmente en toda la matriz
        int **memoizacion = malloc( sizeof(int*)*k );
        for(int i=0; i<k; i++){
            memoizacion[i] = malloc(sizeof(int) * (capacidadBolsa+1) );
            for(int j=0; j<=capacidadBolsa; j++){
                memoizacion[i][j] = -1;
            }
        }

        tiempo_inicio = clock();

        int valor =  maximizar( objetos, k, 0 , capacidadBolsa, memoizacion);

        tiempo_fin = clock();
        double tiempo = (double)((tiempo_fin - tiempo_inicio)) / CLOCKS_PER_SEC;

        free(objetos);

        printf("%d, %d, %lld, %f\n",k, valor, pasos, tiempo);

    }
}
