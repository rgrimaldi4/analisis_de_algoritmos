//los simbolos se gestionan como caracteres
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>

#define EXPERIMENTOS 30 
#define longCadena 100000
int PASOS = 0;

void escribir(){
    FILE *archivo = fopen("cadena.csv", "w");
    char c = 'A';
    for(int i=0; i<100000; i++){
        fwrite(&c, 1,1, archivo);
    }   
    fclose(archivo);
}

void leerArchivo( int n , char *Text){
    FILE *archivo = fopen("cadena.csv", "r");
    fread(Text, sizeof(char), n, archivo);
    fclose(archivo);
}

void NaiveSearch(char *Text, int n, char *Patron, int m ){
    for(int i=0; i<=(n-m); i++){
        int cont=0;
        int j=0;
        for(j=0; j<m; j++){
            PASOS++;
            if(Patron[j] != Text[i+j]){
               break;
            }
        }
        if(j==m){
            //printf("ocurrencia: %d\n", i);
        }
    }
}

int main(int argc, char *argv[]){
    char patron[] = "AAAAA";
    int n_patron  = strlen(patron);

    for(int k=100; k<=longCadena; k+=100){
        //tiempo = 0;
        double tiempoms = 0;
        double sumaTiempo = 0;
        double mayorTiempo = 0;
        double menorTiempo = DBL_MAX;
        
        char *Texto = malloc(sizeof(char)*k);
        leerArchivo(k, Texto);

        
        //30 experimentos
        for(int ex=0; ex<EXPERIMENTOS; ex++){
            PASOS=0;

            //inicio tiempo
            clock_t inicio_tiempo = clock();//inicio tiempo

            NaiveSearch(Texto, k, patron, n_patron);
            
            clock_t fin_tiempo = clock();
            //fin de tiempo

            //tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;
            tiempoms = ((double)(fin_tiempo-inicio_tiempo)*1000)/CLOCKS_PER_SEC;
            sumaTiempo+=tiempoms;

            if(tiempoms>mayorTiempo){
                mayorTiempo = tiempoms;
            }
            if(tiempoms<menorTiempo){
                menorTiempo = tiempoms;
            }
        }

        double promedioTiempo = (sumaTiempo-(mayorTiempo+menorTiempo))/(EXPERIMENTOS-2);

        //total peor caso = (n-m)+1
        //printf("Texto:%d, pasos: %d, tiempo:%f, tiempo ms:%f\n",k, PASOS, tiempo, tiempoms);
        printf("%d, %d, %f\n",k, PASOS, promedioTiempo);

        free(Texto);
    }

    

}

