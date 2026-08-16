
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>


int main(){

    FILE *cadena1000;
    FILE *cadena100000;
    cadena1000 = fopen("letras_1000.txt", "r");
    cadena100000 = fopen("letras_100000.txt", "r");

    int contador = 10;
    char cadenaA[10001];
    char cadenaB[100001];

    fgets(cadenaB, 100001, cadena100000);

    while ( contador <= 1000 ){
        double suma = 0;
        double mayor=-1, menor=DBL_MAX;
        for(int ex=0; ex<30; ex++){//se repite 30 veces

            rewind(cadena1000);
            fgets(cadenaA, contador+1, cadena1000);
            clock_t inicio_tiempo, fin_tiempo;
            double tiempo=0;
            
            inicio_tiempo = clock();

            for(int i=0; i<=100000-contador; i++){
                bool encontrado = true;
                for(int j=0; j<contador; j++){
                    if(cadenaA[j] != cadenaB[i+j]){
                        encontrado=false;
                    }
                }
                /*if(encontrado)
                    printf("Cadena %c, encontrada en la posicion %d\n", cadenaA, i);*/
            }

            fin_tiempo = clock();
            tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;
            
            //printf("%f\n", tiempo);

            suma += tiempo;

            if(tiempo>mayor)
                mayor = tiempo;
            if(tiempo<menor)
                menor = tiempo;

        }

        double promedio = (suma-(mayor+menor)) / 28;
        printf("%f\n", promedio);
        
        contador+=10;

    }

    

    fclose(cadena100000);
    fclose(cadena1000);
    
}