#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000

int extraerMin(int key[], int visitado[], int n){
    int menor = INT_MAX;
    int indice = -1;
    for(int i = 0; i < n; i++){
        if(visitado[i] == 0 && key[i] < menor){
            menor = key[i];
            indice = i;
        }
    }
    return indice;
}

void leer_archivo(int n, int **R){
    FILE *archivo = fopen("coordenadas.csv", "r");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fscanf(archivo, "%d,", &R[i][j]);
        }
        int c;
        while((c = fgetc(archivo)) != '\n' && c != EOF);
    }
    fclose(archivo);
}

void crearMatriz(int filas, int columnas, int **R){
    for(int i = 0; i < filas; i++){
        R[i] = malloc(columnas * sizeof(int));
    }
}

int main(){
    int n = 10;
    int **R = malloc(n * sizeof(int *));

    crearMatriz(n, n, R);
    leer_archivo(n, R);

    //prim(R, n, 0);

    int key[n]; //pesos para llegar a cada vertice
    int padres[n]; //padre de cada vertice
    int visitado[n]; //para saber si el vertice ya esta en el aem

    //valores iniciales
    for(int i = 0; i < n; i++){
        key[i] = INT_MAX;
        padres[i] = -1;
        visitado[i] = 0;
    }

    //vertice inicial
    key[0] = 0;

    for(int i = 0; i < n; i++){
        int u = extraerMin(key, visitado, n);

        if(u == -1){
            printf("El grafo no esta conectado.\n");
            break;
        }

        visitado[u] = 1;

        for(int v = 0; v < n; v++){
            if(R[u][v] != 0 && visitado[v] == 0 && R[u][v] < key[v]){
                padres[v] = u;
                key[v] = R[u][v];
            }
        }
    }

    int pesoTotal = 0;

    printf("\narbol de expansion minima - Prim:\n");

    for(int i = 0; i < n; i++){
        if(i != 0){
            printf("[%d, %d, %d]\n", padres[i], i, R[padres[i]][i]);
            pesoTotal += R[padres[i]][i];
        }
    }

    printf("Peso total: %d\n", pesoTotal);    


    //
    for(int i = 0; i < n; i++){
        free(R[i]);
    }


    free(R);
    return 0;
}