#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX 10000

long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;
double tiempo = 0;

int dp[10001][10001]; //

int LCSS(char *A, char *B, int i, int j){
    pasos++; //contar pasos

    if (A[i] == '\0' || B[j] == '\0')
        return 0;

    //si ya esta calculado, lo regresamos
    if (dp[i][j] != -1)
        return dp[i][j];

    if (A[i] == B[j]) {
        dp[i][j] = 1 + LCSS(A, B, i + 1, j + 1);
    } else {
        int caso1 = LCSS(A, B, i + 1, j);
        int caso2 = LCSS(A, B, i, j + 1);

        dp[i][j] = (caso1 > caso2) ? caso1 : caso2;
    }

    return dp[i][j]; 
}

int main(){
    FILE *archivoA = fopen("cadenaA.csv", "r");
    FILE *archivoB = fopen("cadenaB.csv", "r");

    char cadena1[10001];
    char cadena2[10001];

    fgets(cadena1, MAX+1, archivoA);
    fgets(cadena2, MAX+1, archivoB);
    
    fclose(archivoA);
    fclose(archivoB);

    cadena1[strcspn(cadena1, "\n")] = '\0';
    cadena2[strcspn(cadena2, "\n")] = '\0';

    int longitud_total = strlen(cadena1);

    for(int k=1000; k<=longitud_total; k+=1000){
        pasos=0;
        char A[10001];
        char B[10001];

        //copiar los primeros k caracteres
        strncpy(A, cadena1, k);
        strncpy(B, cadena2, k);
        A[k] = '\0';
        B[k] = '\0';

        //memo
        // inicializar dp en -1
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                dp[i][j] = -1;
            }
        }        
        //meno
        
        tiempo_inicio = clock();
        
        int longitud = 0;
        longitud = LCSS(A, B, 0, 0);
        
        tiempo_fin = clock();
        tiempo = (double)(tiempo_fin-tiempo_inicio) / CLOCKS_PER_SEC;

        printf("%d, %d, %lld, %f\n",k, longitud, pasos, tiempo);

    }

}