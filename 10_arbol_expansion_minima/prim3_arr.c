#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

#define maxDatos 1000

int final  = -1;
int experimentos=30;

clock_t tiempo_inicio, tiempo_fin;
double tiempo = 0;

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

int estaEncolado(int *cola, int dato){
    for(int i=0; i<=final; i++){
        if(cola[i] == dato){
            return 1;
        }
    }   
    return 0;
}

/*
void max_heapify(int *cola, int i, int k){
    int masGrande = 0;
    int l = (i*2)+1; //indice nodo hijo izquierdo
    int r = (i*2)+2; //indice nodo hijo derecho
    if (l <= k && cola[l] > cola[i]){
        masGrande = l;
    }else{
        masGrande = i;
    }
    
    if(r <= k && cola[r] > cola[masGrande]){
        masGrande = r;
    }
    
    if(masGrande != i){
        int aux = cola[i];
        cola[i] = cola[masGrande];
        cola[masGrande] = aux;
        max_heapify(cola, masGrande, k); 
    }
}*/


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
int extraer_nodo(int *cola, int *key){
    int nodo = cola[0];
    cola[0] = cola[final];
    final--;
    if(final>=0){
        min_heapify(cola, 0, final, key);
    }
    return nodo;
}

void prim( int **Grafo, int r, int n){
    //srand(time(NULL));

    final = -1;

    int *cola = malloc(sizeof(int)*n); //nodos pendientes (cola con prioridad)
    int *key  = malloc(sizeof(int)*n); //pesos 
    int *pi   = malloc(sizeof(int)*n); //padres

    //cola con prioridad(inicial)
    for(int i=0; i<n; i++){
        final++;
        cola[i] = i;
        key[i]  = INT_MAX;
        pi[i] = -1;
    }

    key[r] = 0; //asignamos la prioridad del nodo r(raiz)
    /*
    Q[0,1,2,3,4]
    key[0,m,m,m,m]
    pi[null,-,-,-,-]
    */
    while( final>=0 ){
        int minNodo = extraer_nodo(cola, key);
        
        //buscar adyacentes
        for(int i=0; i<n; i++){
            if( Grafo[minNodo][i] != 0 &&  estaEncolado(cola, i) ){
                if( Grafo[minNodo][i] < key[i] ){
                    key[i] = Grafo[minNodo][i];
                    pi[i] = minNodo;
                }
            }           
        }
        for(int j = final/2; j>=0; j--){
            min_heapify(cola, j, final, key);
        }
    }

    /*
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
    }*/   
}


int main(){

    int **Grafo = malloc(sizeof(int*)*maxDatos);
    crearMatriz(maxDatos,maxDatos,Grafo); //asigna memoria para la matriz 1000*1000

    //iniciara for de experimentos
    for(int k=20; k<=1000; k+=5){
        double mayor = -1;
        double menor = DBL_MAX;
        double suma = 0;        
        for(int r=0; r<experimentos; r++){
            getAdyacencia(k, Grafo);

            tiempo_inicio = clock();

            prim(Grafo, 0, k);

            tiempo_fin = clock();
            tiempo = (double)(tiempo_fin-tiempo_inicio) / CLOCKS_PER_SEC;
            
            suma+=tiempo;
            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;            
        }
        double promedio = (suma-(mayor+menor)) / (experimentos-2);
        printf("%d, %f\n", k, promedio);
    }
    

}