#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//leer archivo
void leer_archivo(int n, int *v){
    FILE *archivo;
    archivo = fopen("numeros_desordenados.csv", "r");

    for(int i=0; i<n; i++){
        fscanf(archivo, "%d", &v[i]);
    }
    fclose(archivo);
}

int main(){
    long long formula = 0;
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;

    double tiempos[30][100]; 
    int experimentos = 30;
    int row = 0;
    
    for(int r=0; r<experimentos; r++){
        row = 0;
        for(int k=1000; k<=100000; k+=1000){
            int size = k;
            int *v = malloc(size * sizeof(int));

            /*for(int i=0; i<size;i++){
                v[i] = rand() % 10001; //numeros entre 0 y 10,000
            }*/
            leer_archivo(k, v);
        
            int *s = malloc(size * sizeof(int));
            long long size_s = size;
            long long size_total = size;

            //encontrar el menor
            long long contador = 0;
            inicio_tiempo = clock();

            while(size_s >= 1){
                int mayor = v[0];
                int indice = 0;
                for(int i=1; i<size_total; i++){
                    if( v[i] > mayor ){
                        mayor = v[i];
                        indice = i;
                    }
                    contador++;
                }
                v[indice] = -1; //----------se marca la posicion con -1
                s[size_s-1] = mayor;
                size_s--;
            }

            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;

            formula = size_total * (size_total - 1) / 2;
            printf("%lld,%lld,%lld,%f\n", size_total, contador, formula, tiempo);

            tiempos[r][row] = tiempo;
            row++;

            free(v);
            free(s);

        }
        printf("\n--Fin de experiemento: %d--\n", r+1);
    }

    FILE *archivo;
    archivo = fopen("todos_experimentos_bl.csv", "w");
    for(int i=0; i<100; i++){
        fprintf(archivo, "%d,", (i + 1) * 1000);
        for(int j=0; j<experimentos; j++){
            printf("%f--", tiempos[j][i]);
            fprintf(archivo, "%f,", tiempos[j][i]);
        }
        fprintf(archivo, "\n");
        printf("--\n");
    }
    fclose(archivo);
   
    return 0;
}
