//los simbolos se convirten a numeros
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define longCadena 20
#define longAlfabeto 52
#define MOD 1001

void escribir(){
    srand(time(NULL));
    FILE *archivo = fopen("cadena_2.csv", "w");
    //char c = 'A';
    for(int i=1; i<longCadena; i++){
        char c = 'A' + rand() % 5;
        fwrite(&c, 1,1, archivo);
    }
    fclose(archivo);
}

void leerArchivo( char *Text, int n ){
    FILE *archivo = fopen("cadena_2.csv", "r");
    fread(Text, sizeof(char), n, archivo);
    fclose(archivo);
}

//A-Z(1-26) a-z(27-52)
int getNum_caracter(char caracter){
    if(caracter>='A' && caracter<='Z'){
        return caracter-'A'+1;
    }else if(caracter>='a' && caracter<='z'){
        return caracter-'a'+27;
    }

    return -1;
}

int validarCadena(char *Text, char *Patron, int m, int incidencia){
    int p=0;
    for(int i=incidencia; i<m+incidencia; i++){
        if(Patron[p] != Text[i]){
            return 0;
        }
        p++;
    }
    return 1;
}

//metodo convertir los n sub textos a numeros
void search(char *Text, int n, char *Patron, int m){
    //hash del patron
    // ABCD = 1234 = 1*52^3 + 2*52^2 + 3*52^1 + 4*52^0 = R
    // factorizando de horner: (((1*52+2)*52+3)*52+4)
    int hashPatron = 0;
    for(int i=0; i<m; i++){                         
        int numCar = getNum_caracter( Patron[i] );
        hashPatron = (hashPatron * longAlfabeto + numCar) % MOD;
    }
    printf("hash patron: %d\n", hashPatron);

    //hash del primer substring
    int hash = 0;
    for(int i=0; i<m; i++){
        int numCar = getNum_caracter( Text[i] );
        hash = (hash * longAlfabeto + numCar) % MOD;
    }

    if(hash == hashPatron){
        int inicio = 0;
        int ret = validarCadena(Text, Patron, m, inicio);
        if(ret==1){
            printf("igual:%d\n", inicio);
        }
    }

    int indCarSale = 0;
    int carSale  = getNum_caracter( Text[indCarSale] );
    int hashAnterior = hash;
    int hashNuevo = 0;

    printf("%d\n", hash);

    //hash del resto de los substring
    for(int i=m; i<n; i++){
        //calcular valor posicional del caracter que sale (modulo)
        int valPosiCaracterSale = (carSale * (int)pow(longAlfabeto, m-1))%MOD;
        //al hash anteriror restamos el modulo del valor posicional del caracter que sale
        hashNuevo = (hashAnterior-valPosiCaracterSale+MOD)%MOD;
        //acumular el nuevo caracter
        hashNuevo = (hashNuevo * longAlfabeto + getNum_caracter(Text[i]) ) % MOD;
        
        printf("%d\n", hashNuevo);

        if(hashNuevo == hashPatron){
            int inicio = i-m+1;
            int ret = validarCadena(Text, Patron, m, inicio);
            if(ret==1){
                printf("igual:%d\n", inicio);
            }
        }

        indCarSale++;
        carSale = getNum_caracter(Text[indCarSale]);
        hashAnterior = hashNuevo;
    }
}

int main(int argc, char *argv[]){
    //escribir();

    char patron[] = "ABCD";             //patron
    int  longPatron  = strlen(patron);  //longitud del patron
        
    char *Texto = malloc(sizeof(char)*longCadena); //reservo memoria para el texto
    leerArchivo(Texto, longCadena);                //leer el texto del archivo

    search(Texto, longCadena, patron, longPatron );


    free(Texto);
}

