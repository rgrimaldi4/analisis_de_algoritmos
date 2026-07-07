#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int matriz[MAX][MAX];
long long contador = 0;
double tiempo_inicio=0, tiempo_fin=0;

// funcion recursiva
int LT_rec(int i, int j) {
    contador++;

    if (i == 0 && j == 0)
        return matriz[0][0];

    if (i == 0)
        return matriz[i][j] + LT_rec(i, j - 1);

    if (j == 0)
        return matriz[i][j] + LT_rec(i - 1, j);

    int arriba = LT_rec(i - 1, j);
    int izquierda = LT_rec(i, j - 1);

    return matriz[i][j] + (arriba > izquierda ? arriba : izquierda);
}

int main() {

    int n_max, paso;

    printf("Tamano maximo de la matriz: ");
    scanf("%d", &n_max);

    printf("Intervalo (paso): ");
    scanf("%d", &paso);

    // semilla fija (puedes cambiar 1,2,3,4)
    srand(1);

    // generar matriz base grande
    for (int i = 0; i < n_max; i++)
        for (int j = 0; j < n_max; j++)
            matriz[i][j] = rand() % 20 + 1;

    printf("\nN,Max_Tesoro,Llamadas\n");

    for (int n = n_max; n >= 1; n -= paso) {

        //  evitar explosion de tiempo
        if (n > 25) {
            printf("...\n");
            break;
        }

        contador = 0;

        tiempo_inicio = clock();

        int resultado = LT_rec(n - 1, n - 1);

        tiempo_fin = clock();

        double tiempo = (double)(tiempo_fin-tiempo_inicio) / CLOCKS_PER_SEC;

        printf("%d,%d,%lld, %f\n", n, resultado, contador, tiempo);

        tiempo = 0;

    }

    return 0;
}
