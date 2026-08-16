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
    archivo_salida = fopen("promedios_inplace.csv", "w");

    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    double suma = 0;

    //repetir 30 veces
    for(int k=1000; k<=100000; k+=1000){
        double mayor = -1;
        double menor = DBL_MAX;
        suma = 0;
        for(int re = 0; re<30; re++){//se repite 30 veces 

            //int size = k;
            int *v = malloc(k * sizeof(int));

            leer_archivo(k, v);
            inicio_tiempo = clock();

            int tope = k-1;
            while(tope >= 1){
                int itemMayor  = v[0];
                int itemIndice = 0;                
                for(int i=1; i<=tope; i++){
                    if( v[i] > itemMayor ){
                        itemMayor = v[i];
                        itemIndice = i;
                    }
                }
                int aux = v[tope];
                v[tope] = v[itemIndice];
                v[itemIndice] = aux;
                tope--;          
            }

            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;

            //printf("%d,%f\n", k, tiempo);

            suma+=tiempo;

            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;

            free(v);
            
        }

        double promedio = (suma-(mayor+menor))/28;
        printf("%d:  %f\n", k, promedio);
        fprintf(archivo_salida, "%f\n", promedio);
        
    }
    fclose(archivo_salida);
   
    return 0;
}
