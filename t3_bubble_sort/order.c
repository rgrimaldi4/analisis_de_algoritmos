#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>

//leer archivo
void leer_archivo(int n, int *v){
    FILE *archivo;
    archivo = fopen("numeros_desordenados.csv", "r");

    for(int i=0; i<n; i++){
        fscanf(archivo, "%d", &v[i]);
    }
    fclose(archivo);
}

int main(){
    FILE *archivo_salida;
    archivo_salida = fopen("promedios.csv", "w");
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    int experimentos = 30;

    //repetir 30 veces
    for(int k=1000; k<=100000; k+=1000){
        double mayor = -1;
        double menor = DBL_MAX;
        double suma = 0;
        long long pasos = 0;

        for(int z = 0; z<experimentos; z++){//se repite 30 veces 
            pasos=0;

            //int size = k;
            int *v = malloc(k * sizeof(int));
            

            leer_archivo(k, v);
            inicio_tiempo = clock();
            
            // 3,5,1,6,9
            for(int i=0; i<k-1; i++){
                for(int j=0; j<k-1-i; j++){
                    if( v[j] > v[j+1] ){
                        int aux  = v[j+1];
                        v[j+1] = v[j];
                        v[j] = aux;
                    }
                    pasos++;
                }
            }

            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;

            suma+=tiempo;

            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;

            free(v);
            
        }

        double promedio = (suma-(mayor+menor)) / (experimentos-2);
        printf("%d: %lld , %f\n", k, pasos, promedio);
        fprintf(archivo_salida, "%f\n", promedio);
        
    }
    fclose(archivo_salida);
   
    return 0;
}
