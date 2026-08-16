#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//leer archivo
void leer_archivo(int n, int *v){
    FILE *archivo;
    archivo = fopen("numeros_desordenados.csv", "r");

    for(int i=0; i<n; i++){
        fscanf(archivo, "%d", &v[i]);
    }
    fclose(archivo);
}

//eliminar elemento por indice
void remover_elemento(int **vector, int *size, int indice){
    for(int i=indice; i<*size-1; i++){
        (*vector)[i] = (*vector)[i+1];
    }
    (*size)--;
    *vector = realloc(*vector, (*size)*sizeof(int) );
}

int main(){
    long long formula = 0;
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;

    double tiempos[30][100];
    
    //repetir 30 veces
    const int experimentos = 30;
    int row = 0;
    for(int r=0; r<experimentos; r++){
        row = 0;
        for(int k=1000; k<=100000; k+=1000){
            int size = k;
            int *v = malloc(size * sizeof(int));

            leer_archivo(k, v);
        
            int *s = malloc(size * sizeof(int));
            long long size_s = size;

            //encontrar el menor
            long long contador = 0;
            inicio_tiempo = clock();
            while(size >= 2){
                int mayor = v[0];
                int indice = 0;
                for(int i=1; i<size; i++){
                    if( v[i] > mayor ){
                        mayor = v[i];
                        indice = i;
                    }
                    contador++;
                }
                remover_elemento(&v, &size, indice);
                s[size] = mayor;

                if(size == 1){
                    size--;
                    s[size] = v[0];
                }
            }
            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;


            formula = size_s * (size_s - 1) / 2;
            printf("%lld,%lld,%lld,%f\n", size_s, contador, formula, tiempo);


            //agrego los tiempo a la matriz
            tiempos[r][row] = tiempo;
            row++;

            free(v);
            free(s);
        }
    }

    FILE *archivo;
    archivo = fopen("todos_experimentos.csv", "w");
    for(int i=0; i<100; i++){
        fprintf(archivo, "%d,", (i + 1) * 1000);
        for(int j=0; j<experimentos; j++){
            fprintf(archivo, "%f,", tiempos[j][i]);
        }fprintf(archivo, "\n");
    }
    fclose(archivo);

    return 0;
}

//./mi_ordenamiento 1000 > primeros_mil.txt
// head -1000 datos.csv | sort > validacion_primeros_mil.txt
// diff primeros_mil.txt validacion_primeros_mil.txt
