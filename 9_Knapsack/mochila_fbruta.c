#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
 
long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;

typedef struct{
    char objeto;
    int valor;
    int peso;
}Tobjeto;

int maximizar(Tobjeto *objetos, int longitud, int i, int capacidadBolsa){
    pasos++;
    int mejorValor = 0;
    int totalCombinaciones = 2;

    for(int i=1; i<longitud; i++){
        totalCombinaciones = totalCombinaciones * 2;
    }

    for(int combinacion=0; combinacion<totalCombinaciones; combinacion++){
        pasos++;

        int pesoTotal = 0;
        int valorTotal = 0;

        for(int j=0; j<longitud; j++){
            pasos++;
            int mascara = 1;

            for(int z=0; z<j; z++){
                mascara = mascara * 2;
            }
            if( (combinacion & mascara) != 0 ){
                pesoTotal = pesoTotal + objetos[j].peso;
                valorTotal = valorTotal + objetos[j].valor;
            }
        }

        if(pesoTotal <= capacidadBolsa){
            if(valorTotal > mejorValor){
                mejorValor = valorTotal;
            }
        }
    }

    return mejorValor;
}

int main(){
    srand(1);

    for(int k=10; k<=100; k+=5){
        pasos=0;
        Tobjeto *objetos = malloc(sizeof(Tobjeto)*k);

        for(int i=0; i<k; i++){
            int valor = rand()%20+1;
            int peso = rand()%10+1;
            objetos[i].valor = valor;
            objetos[i].peso = peso;
        }

        int capacidadBolsa = 50;

        tiempo_inicio = clock();

        int valor = maximizar(objetos, k, 0, capacidadBolsa);

        tiempo_fin = clock();
        double tiempo = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;

        free(objetos);

        printf("%d, %d, %lld, %f\n", k, valor, pasos, tiempo);
    }
}