#include <stdio.h>
#include <time.h>
#include <string.h>

long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;
double tiempo = 0;

int LCSS(char *A, char *B){
    pasos++; //contar pasos
    
    if(A[0] == 0 || B[0]==0) //si alguna esta vacia, losgitud es 0
        return 0;

    if(A[0] == B[0])
        return 1 + LCSS(&A[1], &B[1]); //si coincide la primera, avanza en las dos cadenas

    int caso1 = LCSS(&A[1], &B[0]);
    int caso2 = LCSS(&A[0], &B[1]);

    return (caso1 > caso2) ? caso1 : caso2;
}

int main(){

    char *cadena1 = "abcmdefghijklmabcmdefghijklmabcmdefghijklmabcmde";
    char *cadena2 = "mlkjihgfedcbamlkjihgfedcbamlkjihgfedcbamlkjihgfe";

    int longitud_total = strlen(cadena1);

    for(int k=10; k<=longitud_total; k+=2){
        pasos=0;
        char A[100];
        char B[100];

        //copiar los primeros k caracteres
        strncpy(A, cadena1, k);
        strncpy(B, cadena2, k);
        A[k] = '\0';
        B[k] = '\0';        
        
        tiempo_inicio = clock();
        
        int longitud = 0;
        longitud = LCSS(A, B);
        
        tiempo_fin = clock();
        tiempo = (double)(tiempo_fin-tiempo_inicio) / CLOCKS_PER_SEC;

        printf("%d, %d, %lld, %f\n",k, longitud, pasos, tiempo);

    }

}