#include <stdio.h>
#include <time.h>

long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;
double tiempo = 0;

long long fibo(int n){
    pasos++; //contar las veces que entra a la funcion
    if(n == 0){ 
        return 0;
    }
    if(n == 1){ 
        return 1;
    }

    return fibo(n-1) + fibo(n-2);
}

int main(){

    for(int k=10; k<=100; k+=2){
        pasos = 0;
        //printf("Para %d numeros: \n", k);

        tiempo_inicio = clock();
        for(int i=0; i<=k; i++){
            fibo(i);
            //printf("%lld  ", fibo(i) );
        }
        tiempo_fin = clock();
        tiempo = (double)(tiempo_fin-tiempo_inicio) / CLOCKS_PER_SEC;

        //printf("\n");
        printf("%d, %lld, %f\n", k, pasos, tiempo);
    }

    return 0;
    //nota solo correlo en la noche y guardar los datos en la mañana
}