#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <float.h>

#define blanco 0
#define gris   1
#define negro  2

int time_step = 0;

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

void print_path(int g, int s, int v, int*pi){
    if(v==s){
        printf("%d, padre:%d\n", s, pi[s]);
    }else if( pi[v] == -1 ){
        printf("no puede llegar de %d a %d\n", s,v);
    }else{
        print_path(g, s, pi[v], pi);
        printf("%d, padre:%d\n", v, pi[v]);
    }
}

void DFS_visit(int g, int u, int*color, int*d, int*pi, int*f, int **matAdj){
    time_step++;
    d[u] = time_step;
    color[u] = gris;

    for(int v=0; v<g; v++){
        if(matAdj[u][v] == 1){
            if( color[v] == blanco ){
                pi[v] = u;
                DFS_visit(g,v, color, d, pi, f, matAdj);
            }
        }
    }
    
    color[u] = negro;
    time_step++;
    f[u] = time_step;

    printf("%d [%d](%d/%d)- " , u, pi[u], d[u], f[u]);
}

void DFS(int g, int **matAdj ){
    int *color = malloc(sizeof(int)*g);
    int *d     = malloc(sizeof(int)*g);
    int *pi    = malloc(sizeof(int)*g);
    int *f     = malloc(sizeof(int)*g);

    for(int i=0; i<g; i++){
        color[i] = blanco;
        pi[i] = -1;
        d[i] = 0;
        f[i] = 0;
    }
  
    time_step=0;

    for(int i=0; i<g; i++){
        if(color[i] == blanco){
            DFS_visit(g, i, color,d,pi,f, matAdj);
        }
    }

    printf("\n");
    print_path(g,0,g-1,pi);

    free(color);
    free(d);
    free(pi);
    free(f);
}

//falta arreglar promedios
//usando arreglos
int main(){
    srand(time(NULL));
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    int experimentos = 1;

    //tomar k vertices
    for(int k=10; k<=50; k+=50){

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
            
            
            DFS(k, matrizAdj);
            
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
