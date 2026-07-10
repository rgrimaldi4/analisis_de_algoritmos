#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define maxDatos 1000

int frente = 0;
int final  = -1;

void crearMatriz(int filas, int columnas, int **M){
    for(int i = 0; i < filas; i++){
        M[i] = malloc(columnas * sizeof(int));
    }
}

void getAdyacencia(int n, int **Grafo){
    FILE *archivo = fopen("coordenadas.csv", "r");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            fscanf(archivo, "%d,", &Grafo[i][j]);
        }
        //saltar todo lo que queda de esa linea
        int c;
        while((c = fgetc(archivo)) != '\n' && c != EOF);
    }
    fclose(archivo);
}

//-----------------------------------

int extraer_min(int *cola){
    int nodo = cola[frente];
    frente++;
    return  nodo;
}

int estaEncolado(int *cola, int dato){
    for(int i=frente; i<=final; i++){
        if(cola[i] == dato){
            return 1;
        }
    }   
    return 0;
}

void subirNodo(int *cola, int *key, int posicion){
    //buscamos el index del nodo
    int indiceDeQ = -1;
    for(int i=frente; i<=final; i++){
        if(cola[i] == posicion){
            indiceDeQ = i;
            break;
        }   
    }

    int padre = (indiceDeQ-1)/2;
    while(key[cola[indiceDeQ]] < key[cola[padre]] && indiceDeQ > frente){
        int padre = (indiceDeQ-1)/2;
        int temp = cola[padre];
        cola[padre] = cola[indiceDeQ];
        cola[indiceDeQ] = temp;
        indiceDeQ = padre;
    }

}

void prim( int **Grafo, int r, int n){
    
    int *cola = malloc(sizeof(int)*n);
    int *key  = malloc(sizeof(int)*n);
    int *pi   = malloc(sizeof(int)*n);

    //cola con prioridad(inicial)
    for(int i=0; i<n; i++){
        final++;
        cola[i] = i;
        key[i]  = INT_MAX;
    }

    key[r] = 0; //asignamos la prioridad del nodo r
    pi[r]  = -1; //indicamos que el nodo r, es el nodo raiz
    
    /*
    Q[0,1,2,3,4]
    key[0,m,m,m,m]
    pi[null,-,-,-,-]
    */
    while( frente <= final ){
        int minNodo = extraer_min(cola);

        //buscar adyacentes
        for(int i=0; i<n; i++){
            if( Grafo[minNodo][i] != 0 &&  estaEncolado(cola, i) ){
                if( Grafo[minNodo][i] < key[i] ){
                    key[i] = Grafo[minNodo][i];
                    pi[i] = minNodo;
                    subirNodo(cola, key, i); //i que representa al nodo en key
                }
            }
        }
    }

    printf("\n\nArbol Exp Min:\n");
    for(int i = 0; i < n; i++){
        if(pi[i] != -1){
            printf("%d -- %d  peso %d\n",
                pi[i],
                i,
                Grafo[pi[i]][i]);
        }
    }

    printf("\n\nPesos: ");
    for(int i=0; i<n; i++){
        printf( "%d  ", key[i] );
    }    
}


int main(){

    int **Grafo = malloc(sizeof(int*)*maxDatos);
    crearMatriz(maxDatos,maxDatos,Grafo); //asigna memoria para la matriz 1000*1000

    //iniciara for de experimentos
    int k=5;
    getAdyacencia(k, Grafo);
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            printf("%d  ", Grafo[i][j]);
        }
        printf("\n");
    }
    
    prim(Grafo, 0, k);

}