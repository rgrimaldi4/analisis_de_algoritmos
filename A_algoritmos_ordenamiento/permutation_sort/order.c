#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>

//leer archivo
void leer_archivo(int n, int *v){
    FILE *archivo;
    archivo = fopen("numeros_desordenados.csv", "r");

    for(int i=0; i<n; i++){
        fscanf(archivo, "%d", &v[i]);
    }
    fclose(archivo);
}

void permutar(int n, int *v){
    for(int i=0; i<n; i++){
        int j = rand() % n;

        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

bool validarOrden(int n, int *v){
    bool ordenado = true;
    for(int i=0; i<n-1; i++){
        if( v[i] > v[i+1] ){
            ordenado = false;
            break;
        }
    }
    return ordenado;
}

void guardarVectorOrdenado(int n, int *v){
    FILE *archivo_ordenados;
    archivo_ordenados = fopen("numeros_ordenados.csv", "w");
    for(int i=0; i<n; i++){
        fprintf(archivo_ordenados, "%d\n", v[i]);
    } 
    fclose(archivo_ordenados);  
}

int main(){
    srand(time(NULL));
    FILE *archivo_salida;
    archivo_salida = fopen("promedios.csv", "w");
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;
    int experimentos = 1;

    //repetir 30 veces
    for(int k=2; k<=20; k+=1){
        double mayor = -1;
        double menor = DBL_MAX;
        double suma = 0;
        long long pasos = 0;

        for(int z = 0; z<experimentos; z++){//se repite 30 veces 
            pasos=0;

            //int size = k;
            int *v = malloc(k * sizeof(int));
            

            leer_archivo(k, v);
            inicio_tiempo = clock();
            
            // ordenamiento
            bool ordenado = false;
            while( ordenado == false ){
                permutar(k, v);
                pasos++;
                ordenado = validarOrden(k, v);
            }
            //

            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;

            suma+=tiempo;

            if(tiempo > mayor )
                mayor = tiempo;
            if(tiempo < menor )
                menor = tiempo;
                
            if(k == 100000)
                guardarVectorOrdenado(k, v);

            free(v);
        }

        //double promedio = (suma-(mayor+menor)) / (experimentos-2);
        printf("%d: %lld , %f\n", k, pasos, tiempo);
        fprintf(archivo_salida, "%f\n", tiempo);
        
    }
    fclose(archivo_salida);
   
    return 0;
}
