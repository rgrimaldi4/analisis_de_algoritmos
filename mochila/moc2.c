#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
 
long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;

typedef struct{
    char objeto;
    int valor;
    int peso;
}Tobjeto;

int maximizar( Tobjeto *objetos,int longitud, int i, int capacidadBolsa ){
    pasos++;
    int valorAgregado=0;

    if(capacidadBolsa==0 || i>=longitud){
        return 0;
    }

    //printf( "%d - ", objetos[i].peso );
    if( objetos[i].peso <= capacidadBolsa ){
        valorAgregado = objetos[i].valor + maximizar(objetos,longitud, i+1, capacidadBolsa-objetos[i].peso);
    }

    int valorIngnorado = maximizar( objetos, longitud,  i+1, capacidadBolsa );

    if(valorAgregado > valorIngnorado){
        printf("agregado: %d\n", valorAgregado );
        return valorAgregado;
    }else{
        printf("ignorado: %d\n", valorIngnorado );
        return valorIngnorado;
    }
}


int main(){
    srand(1);
        int k = 10;
        Tobjeto *objetos = malloc( sizeof(Tobjeto)*k );
        objetos[0].valor = 1;  objetos[0].peso = 2;
        objetos[1].valor = 2;  objetos[1].peso = 1;
        objetos[2].valor = 3;  objetos[2].peso = 10;
        objetos[3].valor = 5;  objetos[3].peso = 8;
        objetos[4].valor = 7;  objetos[4].peso = 7;
        objetos[5].valor = 6;  objetos[5].peso = 12;
        objetos[6].valor = 8;  objetos[6].peso = 15;
        objetos[7].valor = 10; objetos[7].peso = 16;
        objetos[8].valor = 9;  objetos[8].peso = 9;
        objetos[9].valor = 4;  objetos[9].peso = 3;


        /*for(int i=0; i<k; i++){
            printf("objeto: %d | valor: %d - peso: %d\n", i+1, objetos[i].valor, objetos[i].peso);
        }*/

        int capacidadBolsa = 20;


        int valor =  maximizar( objetos, k, 0 , capacidadBolsa);


        free(objetos);

        //printf("%d, %d, %lld, %f\n",k, valor, pasos, tiempo);
        printf("%d, %d, %lld \n",k, valor, pasos);
}
