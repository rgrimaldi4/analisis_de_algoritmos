#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

int final = -1;
int frente = 0;

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

void min_heapify(int *cola, int i, int k, int *key){
    int masPequenio = 0;
    int l = (i*2)+1; //indice nodo hijo izquierdo
    int r = (i*2)+2; //indice nodo hijo derecho
    if (l <= k && key[cola[l]] < key[cola[i]]){
        masPequenio = l;
    }else{
        masPequenio = i;
    }
    
    if(r <= k && key[cola[r]] < key[cola[masPequenio]]){
        masPequenio = r;
    }
    
    if(masPequenio != i){
        int aux = cola[i];
        cola[i] = cola[masPequenio];
        cola[masPequenio] = aux;
        min_heapify(cola, masPequenio, k, key);
    }
}

//extrae siempre del frente
int extractMin(int *cola){
    int nodo = cola[0];
    cola[0] = cola[final];
    final--;
    return nodo;
}

/* G: es matriz de adyascencia
n: numero de vertices
s: vertice inicial, iniciamos con vertice 0
w: peso(o key) para el vertice inicial, 0 para llegar a vertice 0 */
void dijkstra(int **G, int n, int s, int w){
    int *dist = malloc(sizeof(int)*n);
    int *parent = malloc(sizeof(int)*n);
    int *visitados = malloc(sizeof(int)*n);
    int *cola = malloc(sizeof(int)*n);

    for(int i=0; i<n; i++){
        dist[i] = INT_MAX;
        parent[i] = -1;
        visitados[i] = 0;

        //iniciar la cola
        final++;
        cola[i] = i;
    }
    dist[s] = w;

    while( frente <= final ){
        int u = extractMin( cola );
        visitados[u] = 1;
        
        //heap
        if(final>=0){
            min_heapify(cola, 0, final, dist);
        }
        
        //buscar adyascentes
        for(int v=0; v<n; v++){
            if(G[u][v] != 0){
                int disAcum = dist[u] + G[u][v];
                if( disAcum < dist[v]){
                    dist[v] = disAcum;
                    parent[v] = u;
                    for(int j = final/2; j >= 0; j--){
                        min_heapify(cola, j, final, dist);
                    }                    
                }
            }
        }
    }

    imprimirGrafo(parent, n, dist);

    free(dist);
    free(visitados);
    free(parent);
    free(cola);
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