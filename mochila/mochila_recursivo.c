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

int maximizar( Tobjeto *objetos,int longitud, int i, int capacidadBolsa ){
    pasos++;
    int valorAgregado=0;

    if(capacidadBolsa==0 || i>=longitud){
        return 0;
    }

    //printf( "%d - ", objetos[i].peso );
    if( objetos[i].peso <= capacidadBolsa ){
        valorAgregado = objetos[i].valor + maximizar(objetos,longitud, i+1, capacidadBolsa-objetos[i].peso);
    }

    int valorIngnorado = maximizar( objetos, longitud,  i+1, capacidadBolsa );

    if(valorAgregado > valorIngnorado){
        return valorAgregado;
    }else{
        return valorIngnorado;
    }
}


int main(){
    srand(1);

    for(int k=10; k<=100; k+=5){
        pasos=0;

        Tobjeto *objetos = malloc( sizeof(Tobjeto)*k );

        for(int i=0; i<k; i++){
            int valor = rand()%20+1;
            int peso = rand()%10+1;
            objetos[i].valor = valor;
            objetos[i].peso = peso;
        }

        /*for(int i=0; i<k; i++){
            printf("objeto: %d | valor: %d - peso: %d\n", i+1, objetos[i].valor, objetos[i].peso);
        }*/

        int capacidadBolsa = 50;

        tiempo_inicio = clock();

        int valor =  maximizar( objetos, k, 0 , capacidadBolsa);

        tiempo_fin = clock();
        double tiempo = (double)((tiempo_fin - tiempo_inicio)) / CLOCKS_PER_SEC;

        free(objetos);

        printf("%d, %d, %lld, %f\n",k, valor, pasos, tiempo);

    }
}
