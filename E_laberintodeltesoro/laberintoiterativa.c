#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5000

int matriz[MAX][MAX];
int dp[MAX][MAX];

long long contador = 0;
clock_t tiempo_inicio, tiempo_fin;

int LT_iterativo(int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            contador++;

            if (i == 0 && j == 0) {
                dp[i][j] = matriz[i][j];
            }
            else if (i == 0) {
                dp[i][j] = matriz[i][j] + dp[i][j - 1];
            }
            else if (j == 0) {
                dp[i][j] = matriz[i][j] + dp[i - 1][j];
            }
            else {
                int arriba = dp[i - 1][j];
                int izquierda = dp[i][j - 1];

                dp[i][j] = matriz[i][j] + 
                           (arriba > izquierda ? arriba : izquierda);
            }
        }
    }

    return dp[n - 1][n - 1];
}

int main() {
    int n_max, paso;

    printf("Tamano maximo de la matriz: ");
    scanf("%d", &n_max);

    printf("Intervalo (paso): ");
    scanf("%d", &paso);

    if (n_max > MAX) {
        printf("Error: el maximo permitido es %d\n", MAX);
        return 1;
    }

    srand(1);

    for (int i = 0; i < n_max; i++) {
        for (int j = 0; j < n_max; j++) {
            matriz[i][j] = rand() % 20 + 1;
        }
    }

    printf("\nN,Max_Tesoro,Pasos,Tiempo\n");

    for (int n = n_max; n >= 1; n -= paso) {

        contador = 0;

        tiempo_inicio = clock();

        int resultado = LT_iterativo(n);

        tiempo_fin = clock();

        double tiempo = (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;

        printf("%d,%d,%lld,%f\n", n, resultado, contador, tiempo);
    }

    return 0;
}