#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

#define blanco 0
#define gris   1
#define negro  2

//leer archivo
void leer_archivo(int n, int **R){ //matriz cuadrada
    FILE *archivo = fopen("coordenadas.csv", "r");
    for(int i = 0; i < n; i++){
        R[i] = malloc(sizeof(int)*n);
        for(int j = 0; j < n; j++){
            fscanf(archivo, "%d,", &R[i][j]);
            if(R[i][j]!=0){
                R[i][j] = 1;
            }
        }
        // Saltar todo lo que queda de esa linea
        int c;
        while((c = fgetc(archivo)) != '\n' && c != EOF);
    }
    fclose(archivo);
}

void BFS(int **G, int n, int s){
    int *color = malloc(sizeof(int) * n);
    int *d     = malloc(sizeof(int) * n);
    int *pi    = malloc(sizeof(int) * n);
    int *Q     = malloc(sizeof(int) * n);

    int frente = 0;
    int final = 0;

    //inicializa valores
    for(int u = 0; u < n; u++){
        color[u] = blanco; //todos inician blanco, no han sido visitados
        d[u] = INT_MAX;
        pi[u] = -1; //todos tienen padre nulo
    }

    //vertice inicial s
    color[s] = gris; //fue descubierto
    d[s] = 0; 
    pi[s] = -1; //raiz, sin padre, null

    Q[final] = s; 
    final++;

    while(frente < final){
        int u = Q[frente];
        frente++;

        //printf("%d ", u);

        //buscar adyascentes de u sin revisar
        for(int v = 0; v < n; v++){
            if(G[u][v] == 1 && color[v] == blanco){
                color[v] = gris;
                d[v] = d[u] + 1;
                pi[v] = u;

                Q[final] = v;
                final++;
            }
        }

        color[u] = negro; //marco como revisado
    }

    printf("\n");
    for(int i=0; i<n; i++){
        printf("vert:%d -  padr:%d - dist:%d \n",i, pi[i], d[i]);
    }

    free(color);
    free(d);
    free(pi);
    free(Q);
}


//usando arreglos
int main(){
    srand(time(NULL));
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    int experimentos = 1;

    //tomar k vertices
    for(int k=10; k<=10; k+=50){
        int **matrizAdj = malloc(sizeof(int*)*k);
        leer_archivo(k, matrizAdj);

        printf("\nGrafo(mat adj): \n");
        for(int i=0; i<k; i++){
            for (int j = 0; j < k; j++){
                printf("%d ", matrizAdj[i][j]);
            }printf("\n");
        }

        double mayor = -1;
        double menor = DBL_MAX;
        double suma = 0;
        for(int exp=0; exp < experimentos; exp++){
            inicio_tiempo = clock();//inicio tiempo
            
            //printf("\nbusqueda en amplitud:\n");
            BFS(matrizAdj, k, 0);
            
            fin_tiempo = clock(); //fin tiempo
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;
            suma+=tiempo;
            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;
        }

        double promedio = (suma-(mayor+menor)) / (experimentos-2);
        printf("%d, %f \n", k, promedio);

        //liberar memoria
        for(int i=0; i<k; i++){
            free(matrizAdj[i]);
        }
        free(matrizAdj);
    }
}
