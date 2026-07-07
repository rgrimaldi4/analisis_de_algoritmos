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
    FILE *archivo = fopen("grafo.csv", "r");
    for(int i = 0; i < n; i++){
        R[i] = malloc(sizeof(int)*n);
        for(int j = 0; j < n; j++){
            fscanf(archivo, "%d,", &R[i][j]);
        }
        // Saltar todo lo que queda de esa linea
        int c;
        while((c = fgetc(archivo)) != '\n' && c != EOF);
    }
    fclose(archivo);
}

void imprimirGrafo(int *parent, int n, int*dist){
    for(int i=0; i<n; i++){
        printf("vertice: %d -- padr: %d -- dist:%d\n", i, parent[i], dist[i]);
    }
}

int extractMin(int *dist, int*visitados, int n){
    //si todos los nodos ya fueron visitados, retorna -1
    int menor = INT_MAX;
    int pos = -1;
    for(int i=0; i<n; i++){
        if(visitados[i]==0 && dist[i] < menor){
            menor = dist[i];
            pos = i;
        }
    }
    return pos;
}


/* G: es matriz de adyascencia
n: numero de vertices
s: vertice inicial, iniciamos con vertice 0
w: peso(o key) para el vertice inicial, 0 para llegar a vertice 0 */
void dijkstra(int **G, int n, int s, int w){
    int *dist = malloc(sizeof(int)*n);
    int *parent = malloc(sizeof(int)*n);
    int *visitados = malloc(sizeof(int)*n);

    for(int i=0; i<n; i++){
        dist[i] = INT_MAX;
        parent[i] = -1;
        visitados[i] = 0;
    }
    dist[s] = w;

    while(1){
        int u = extractMin( dist, visitados, n );

        if(u == -1){break;}
        
        visitados[u] = 1;

        //buscar adyascentes
        for(int v=0; v<n; v++){
            if( G[u][v] != 0 ){
                int disAcum = dist[u] + G[u][v];
                if( disAcum < dist[v]){
                    dist[v] = disAcum;
                    parent[v] = u;
                }
            }
        }
    }

    imprimirGrafo(parent, n, dist);

    free(dist);
    free(visitados);
    free(parent);
}

int main(){

    int n_vertices = 5;
    int **G = malloc(sizeof(int*)*n_vertices);
    leer_archivo(n_vertices, G);

    for(int i=0; i<n_vertices; i++){
        for(int j=0; j<n_vertices; j++){
            printf("%d -", G[i][j]);
        }printf("\n");
    }


    dijkstra(G, n_vertices, 0, 0);


    for(int i = 0; i < n_vertices; i++){
        free(G[i]);
    }
    free(G);
}