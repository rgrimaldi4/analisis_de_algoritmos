//en
//experiemento donde M o el patron es variable
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define EXPERIMENTOS 30 
#define longCadena 10000
int PASOS = 0;

void escribir(){
    FILE *archivo = fopen("cadena.csv", "w");
    char c = 'A';
    for(int i=0; i<1000; i++){
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
    double tiempo = 0;
    clock_t inicio_tiempo, fin_tiempo;    

    char *Texto = malloc(sizeof(char)*longCadena);
    leerArchivo(longCadena, Texto);
    
    //
    for(int k=100; k<=longCadena; k+=100){
        PASOS=0;

        char *patron = malloc(sizeof(char)*k);
        for(int i=0; i<k; i++){
            patron[i] = 'A';
        }

        //inicio tiempo
        inicio_tiempo = clock();//inicio tiempo

        NaiveSearch(Texto, longCadena, patron, k);
        
        fin_tiempo = clock(); //fin tiempo
        tiempo = (double)(fin_tiempo-inicio_tiempo)/CLOCKS_PER_SEC;
        //fin de tiempo

        //total peor caso = (n-m)+1
        printf("Texto:%d, Patron:%d, pasos: %d, tiempo:%f\n",longCadena, k, PASOS, tiempo);

        free(patron);
    }

    //AABAACAADAABAABA

}

