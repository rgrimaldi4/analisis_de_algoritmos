#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

#define MAX 1000

void make_set(int V[], int tamanio){
    for(int i=0; i<tamanio; i++){
        V[i] = i;
        //printf("%d - ", V[i]);
    }
}

int contarAristas(int **R, int max){
    int contador=0;
    for(int i=0; i<max; i++){
        for(int j=0; j<i; j++){
            if(R[i][j] != 0){
                contador++;
            }
        }
    }    
    return contador;
}

void setAristas(int A[][3], int **R, int max){
    int k = 0;
    for(int i = 0; i < max; i++){
        for(int j = 0; j < i; j++){
            if(R[i][j] != 0){
                A[k][0] = i;       // origen
                A[k][1] = j;       // destino
                A[k][2] = R[i][j]; // peso
                k++;
            }
        }
    }
}

void union_set(int V[], int a, int b, int max){
    int valorA = V[a];
    int valorB = V[b];
    for(int i = 0; i < max; i++){
        if(V[i] == valorB){
            V[i] = valorA;
        }
    }
}

//-------------------------

//leer archivo
void leer_archivo(int n, int **R){ //matriz cuadrada
    FILE *archivo = fopen("coordenadas.csv", "r");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fscanf(archivo, "%d,", &R[i][j]);
        }
        // Saltar todo lo que queda de esa linea
        int c;
        while((c = fgetc(archivo)) != '\n' && c != EOF);
    }
    fclose(archivo);
}

void crearMatriz(int filas, int columnas, int **R){
    //int **R = malloc(filas * sizeof(int *));
    for(int i = 0; i < filas; i++) {
        R[i] = malloc(columnas * sizeof(int));
    }
}

//caso base
int comparar(const void *a, const void *b){
    const int *aristaA = (const int *)a;
    const int *aristaB = (const int *)b;
    return aristaA[2] - aristaB[2];
}

int main(){
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    int experimentos = 30;

    int **R = malloc(sizeof(int*)*MAX);
    crearMatriz(MAX, MAX, R);

    for(int ex=0;ex<experimentos; ex++){

        double mayor = -1;
        double menor = DBL_MAX;
        double suma = 0;

        //toma del archivo de 10 en 10
        for(int k=10; k<1000; k+=20){

            leer_archivo(k, R);

            int nu_aristas = contarAristas(R, k);

            int *V = malloc(sizeof(int)*k);
            int (*A)[3] = malloc(nu_aristas * sizeof(int[3]));
            int (*T)[3] = malloc((k - 1) * sizeof(int[3]));

            make_set(V, k);
            setAristas(A, R, k);
            qsort(A, nu_aristas, sizeof(A[0]), comparar);

            int aristasTomadas = 0;
            int pesoTotal = 0;

            //principal
            inicio_tiempo = clock();
            for(int i = 0; i < nu_aristas && aristasTomadas < k - 1; i++){
            //for(int i = 0; i < (nu_aristas-1); i++){
                int origen = A[i][0];
                int destino = A[i][1];
                int peso = A[i][2];

                if(V[origen] != V[destino]){
                    T[aristasTomadas][0] = origen;
                    T[aristasTomadas][1] = destino;
                    T[aristasTomadas][2] = peso;

                    pesoTotal += peso;
                    union_set(V, origen, destino, k);
                    aristasTomadas++;
                }
            }
            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;

            suma+=tiempo;
            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;
            
            printf("peso:%d | tiempo:%f \n", pesoTotal, tiempo);

            /*for(int i = 0; i < k; i++){
                free(R[i]);
            }*/
        }
        double promedio = (suma-(mayor+menor)) / (experimentos-2);
        printf("\n %d: %lld , %f\n", 1, promedio);
        
    }

    
    free(R);
    return 0; 
    
}
