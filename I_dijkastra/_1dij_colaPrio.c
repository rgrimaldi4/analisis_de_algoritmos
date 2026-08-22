#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

int final = -1;
int frente = 0;

//leer archivo
/*void leer_archivo(int n, int **R){ //matriz cuadrada
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
}*/

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

void imprimirGrafo(int *parent, int n, int*dist){
    for(int i=0; i<n; i++){
        printf("vertice: %d -- padr: %d -- dist:%d\n", i, parent[i], dist[i]);
    }
}


void intercambiar(int *cola, int *pos, int i, int j) {
    int temp = cola[i];
    cola[i] = cola[j];
    cola[j] = temp;

    pos[cola[i]] = i;
    pos[cola[j]] = j;
}

void decreaseKey(int *cola, int *pos, int v, int *dist) {
    int i = pos[v]; // Acceso directo sin bucle for

    if (i == -1) return; // Ya no está en la cola

    while (i > 0) {
        int padre = (i - 1) / 2;
        if (dist[cola[i]] < dist[cola[padre]]) {
            intercambiar(cola, pos, i, padre);
            i = padre;
        } else {
            break;
        }
    }
}

void min_heapify(int *cola, int *pos, int i, int k, int *key) {
    int masPequenio = i;
    int l = (i * 2) + 1;
    int r = (i * 2) + 2;

    if (l <= k && key[cola[l]] < key[cola[masPequenio]]) {
        masPequenio = l;
    }

    if (r <= k && key[cola[r]] < key[cola[masPequenio]]) {
        masPequenio = r;
    }

    if (masPequenio != i) {
        intercambiar(cola, pos, i, masPequenio);
        min_heapify(cola, pos, masPequenio, k, key);
    }
}

int extractMin(int *cola, int *pos, int *dist) {
    int nodo = cola[0];
    
    pos[nodo] = -1; // Marcamos que el nodo extraído ya no está en la cola
    cola[0] = cola[final];
    
    if (final > 0) {
        pos[cola[0]] = 0;
    }
    
    final--;

    if (final >= 0) {
        min_heapify(cola, pos, 0, final, dist);
    }

    return nodo;
}

/* G: es matriz de adyascencia
n: numero de vertices
s: vertice inicial, iniciamos con vertice 0
w: peso(o key) para el vertice inicial, 0 para llegar a vertice 0 */
void dijkstra(int **G, int n, int s, int w) {
    int *dist = malloc(sizeof(int) * n);
    int *parent = malloc(sizeof(int) * n);
    int *visitados = malloc(sizeof(int) * n);
    int *cola = malloc(sizeof(int) * n);
    int *pos = malloc(sizeof(int) * n); // Rastrea la posición de cada vértice en la cola

    final = -1;

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visitados[i] = 0;

        final++;
        cola[i] = i;
        pos[i] = i; // Inicialmente el vértice 'i' está en la posición 'i'
    }

    dist[s] = w;
    decreaseKey(cola, pos, s, dist); // Coloca el nodo inicial al frente del Heap

    while (frente <= final) {
        int u = extractMin(cola, pos, dist);
        visitados[u] = 1;

        if (dist[u] == INT_MAX) break;

        for (int v = 0; v < n; v++) {
            // Se verifica la existencia de arista y que el nodo v siga en la cola
            if (G[u][v] != 0 && pos[v] != -1) {
                
                // Corrección del overflow de INT_MAX
                if (dist[u] != INT_MAX && dist[u] + G[u][v] < dist[v]) {
                    dist[v] = dist[u] + G[u][v];
                    parent[v] = u;

                    decreaseKey(cola, pos, v, dist); // O(log V)
                }
            }
        }
    }

    //imprimirGrafo(parent, n, dist);

    free(dist);
    free(visitados);
    free(parent);
    free(cola);
    free(pos);
}

int main(){
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    int experimentos = 30;

    //toma del archivo de 10 en 10
    for(int k=20; k<=1000; k+=20){

        int n_vertices = k;
        int **G = malloc(sizeof(int*)*n_vertices);
        for(int i = 0; i < n_vertices; i++) {
            G[i] = malloc(n_vertices * sizeof(int));
        }   

        leer_archivo(n_vertices, G);

        /*for(int i=0; i<n_vertices; i++){
            for(int j=0; j<n_vertices; j++){
                printf("%d -", G[i][j]);
            }printf("\n");
        }
        printf("\n\n");*/


        double suma = 0;
        double tiempoMenor = DBL_MAX;
        double tiempoMayor = 0;

        for( int i=0; i<experimentos; i++ ){
            inicio_tiempo = clock();

            dijkstra(G, n_vertices, 0, 0);

            fin_tiempo = clock();
            tiempo = ((double)(fin_tiempo - inicio_tiempo)*1000) / CLOCKS_PER_SEC;
            suma+=tiempo;

            if(tiempo>tiempoMayor){
                tiempoMayor = tiempo;
            }
            if(tiempo<tiempoMenor){
                tiempoMenor=tiempo;
            }
        }   

        double promedio = (suma-(tiempoMayor+tiempoMenor)) / (experimentos-2);
        printf("%d, %f\n",k, promedio);

        for(int i = 0; i < n_vertices; i++){
            free(G[i]);
        }
        free(G);
    }    


}