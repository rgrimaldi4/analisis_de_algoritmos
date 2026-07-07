#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;

typedef struct{
    char objeto;
    int valor;
    int peso;
} Tobjeto;

int maximizar(Tobjeto *objetos, int longitud, int capacidadBolsa){
    int **tabla = malloc(sizeof(int*) * (longitud + 1));

    for(int i = 0; i <= longitud; i++){
        tabla[i] = malloc(sizeof(int) * (capacidadBolsa + 1));
    }

    for(int i = 0; i <= longitud; i++){
        for(int c = 0; c <= capacidadBolsa; c++){
            tabla[i][c] = 0;
        }
    }

    for(int i = 1; i <= longitud; i++){
        for(int c = 1; c <= capacidadBolsa; c++){
            pasos++;

            int pesoActual = objetos[i - 1].peso;
            int valorActual = objetos[i - 1].valor;

            if(pesoActual <= c){
                int valorAgregado = valorActual + tabla[i - 1][c - pesoActual];
                int valorIgnorado = tabla[i - 1][c];

                if(valorAgregado > valorIgnorado){
                    tabla[i][c] = valorAgregado;
                }else{
                    tabla[i][c] = valorIgnorado;
                }
            }else{
                tabla[i][c] = tabla[i - 1][c];
            }
        }
    }

    int mejorValor = tabla[longitud][capacidadBolsa];

    for(int i = 0; i <= longitud; i++){
        free(tabla[i]);
    }

    free(tabla);

    return mejorValor;
}

int main(){
    srand(1);

    for(int k = 10; k <= 100; k += 5){
        pasos = 0;

        Tobjeto *objetos = malloc(sizeof(Tobjeto) * k);

        for(int i = 0; i < k; i++){
            int valor = rand() % 20 + 1;
            int peso = rand() % 10 + 1;
            objetos[i].valor = valor;
            objetos[i].peso = peso;
        }

        int capacidadBolsa = 50;

        tiempo_inicio = clock();

        int valor = maximizar(objetos, k, capacidadBolsa);

        tiempo_fin = clock();

        double tiempo = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;

        free(objetos);

        printf("%d, %d, %lld, %f\n", k, valor, pasos, tiempo);
    }

    return 0;
}