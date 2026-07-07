#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10000

long long pasos = 0;
clock_t tiempo_inicio, tiempo_fin;
double tiempo = 0;

int dp[MAX + 1][MAX + 1];

int LCSS_iterativo(char *A, char *B) {
    int n = strlen(A);
    int m = strlen(B);

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pasos++;

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                int caso1 = dp[i - 1][j];
                int caso2 = dp[i][j - 1];

                dp[i][j] = (caso1 > caso2) ? caso1 : caso2;
            }
        }
    }

    return dp[n][m];
}

int main() {
    FILE *archivoA = fopen("cadenaA.csv", "r");
    FILE *archivoB = fopen("cadenaB.csv", "r");

    if (archivoA == NULL || archivoB == NULL) {
        printf("Error al abrir archivos\n");
        return 1;
    }

    char *cadena1 = malloc(MAX + 1);
    char *cadena2 = malloc(MAX + 1);

    if (cadena1 == NULL || cadena2 == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    fgets(cadena1, MAX + 1, archivoA);
    fgets(cadena2, MAX + 1, archivoB);

    fclose(archivoA);
    fclose(archivoB);

    cadena1[strcspn(cadena1, "\n")] = '\0';
    cadena2[strcspn(cadena2, "\n")] = '\0';

    int longitud_total = strlen(cadena1);

    for (int k = 1000; k <= longitud_total; k += 1000) {
        pasos = 0;

        char *A = malloc(k + 1);
        char *B = malloc(k + 1);

        if (A == NULL || B == NULL) {
            printf("Error al asignar memoria\n");
            return 1;
        }

        strncpy(A, cadena1, k);
        strncpy(B, cadena2, k);

        A[k] = '\0';
        B[k] = '\0';

        tiempo_inicio = clock();

        int longitud = LCSS_iterativo(A, B);

        tiempo_fin = clock();

        tiempo = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;

        printf("%d, %d, %lld, %f\n", k, longitud, pasos, tiempo);

        free(A);
        free(B);
    }

    free(cadena1);
    free(cadena2);

    return 0;
}