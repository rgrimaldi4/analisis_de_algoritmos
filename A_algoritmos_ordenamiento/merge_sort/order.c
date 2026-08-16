#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>

//leer archivo
void leer_archivo(int n, int *v){
    FILE *archivo;
    archivo = fopen("numeros_desordenados.csv", "r");

    for(int i=0; i<n; i++){
        fscanf(archivo, "%d", &v[i]);
    }
    fclose(archivo);
}

void guardarVectorOrdenado(int n, int *v){
    FILE *archivo_ordenados;
    archivo_ordenados = fopen("numeros_ordenados.csv", "w");
    for(int i=0; i<n; i++){
        fprintf(archivo_ordenados, "%d\n", v[i]);
    } 
    fclose(archivo_ordenados);  
}

void merge(int inicio, int medio, int fin, int *v, long long *pasos){
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int *izq = malloc(n1 * sizeof(int));
    int *der = malloc(n2 * sizeof(int));

    for(int i = 0; i < n1; i++){
        izq[i] = v[inicio + i];
    }
    for(int j = 0; j < n2; j++){
        der[j] = v[medio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while(i < n1 && j < n2){
        (*pasos)++;
        if(izq[i] <= der[j]){
            v[k] = izq[i];
            i++;
        }else{
            v[k] = der[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        v[k] = izq[i];
        i++;
        k++;
    }

    while(j < n2){
        v[k] = der[j];
        j++;
        k++;
    }

    free(izq);
    free(der);
}


void mergeSort(int inicio, int fin, int *v, long long *pasos){
    if( inicio < fin ){
        int medio = (inicio+fin)/2;
        mergeSort(inicio, medio, v, pasos); //izquierda
        mergeSort(medio+1, fin, v, pasos);  //derecha
                                                                                                                                                                                                              
        merge(inicio, medio, fin, v, pasos);
    }
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

        for(int z = 0; z<experimentos; z++){//se repite n veces 
            pasos=0;

            //int size = k;
            int *v = malloc(k * sizeof(int));
            

            leer_archivo(k, v);
            inicio_tiempo = clock();
            
            //ordenamiento
            mergeSort(0, k-1, v, &pasos);
            //

            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;

            suma+=tiempo;

            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;

            if(k == 100000)
                guardarVectorOrdenado(k, v);

            free(v);
        }
        
        double promedio = (suma-(mayor+menor)) / (experimentos-2);
        printf("%d: %lld , %f\n", k, pasos, promedio);
        fprintf(archivo_salida, "%f\n", promedio);
        
    }
    fclose(archivo_salida);
   
    return 0;
}
