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

int maximizar( Tobjeto *objetos,int longitud, int i, int capacidadBolsa, int **memo ){
    pasos++;
    int valorAgregado=0;

    if(capacidadBolsa==0 || i>=longitud){
        return 0;
    }

    // Si ya fue calculado, lo regreso
    if(memo[i][capacidadBolsa] != -1){
        return memo[i][capacidadBolsa];
    }    

    //printf( "%d - ", objetos[i].peso );
    if( objetos[i].peso <= capacidadBolsa ){
        valorAgregado = objetos[i].valor + maximizar(objetos,longitud, i+1, capacidadBolsa-objetos[i].peso, memo);
    }

    int valorIngnorado = maximizar( objetos, longitud,  i+1, capacidadBolsa, memo );

    if(valorAgregado > valorIngnorado){
        printf("agregado: %d \n", valorAgregado );
        memo[i][capacidadBolsa] = valorAgregado;
        //return valorAgregado;
    }else{
        printf("ingnorado: %d \n", valorIngnorado );
        memo[i][capacidadBolsa] = valorIngnorado;
        //return valorIngnorado;
    }
    return memo[i][capacidadBolsa];
}


int main(){
    srand(1);
        int k = 10;
        int capacidadBolsa = 20;

        Tobjeto *objetos = malloc( sizeof(Tobjeto)*5 );
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
        
        // Crear matriz memo[k][capacidadBolsa + 1]
        int **memo = malloc(sizeof(int*) * k);
        for(int i = 0; i < k; i++){
            memo[i] = malloc(sizeof(int) * (capacidadBolsa + 1));
            for(int j = 0; j <= capacidadBolsa; j++){
                memo[i][j] = -1;
            }
        }


        int valor =  maximizar( objetos, k, 0 , capacidadBolsa, memo);


        // Liberar matriz memo
        for(int i = 0; i < k; i++){
            free(memo[i]);
        }

        free(objetos);
        free(memo);

        //printf("%d, %d, %lld, %f\n",k, valor, pasos, tiempo);
        printf("%d, %d, %lld",k, valor, pasos);
}
