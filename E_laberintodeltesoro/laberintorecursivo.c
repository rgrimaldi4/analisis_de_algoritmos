#include <stdio.h>

#define N 4
#define M 4

int valor[N][M] = {
    {3, 10, 1, 2},
    {1,  2, 2, 1},
    {1,  1, 1, 1},
    {1,  1,20, 5}
};

int LT[N][M];

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

int laberintoTesoro() {
    LT[0][0] = valor[0][0];

    for (int j = 1; j < M; j++) {
        LT[0][j] = valor[0][j] + LT[0][j - 1];
    }

    for (int i = 1; i < N; i++) {
        LT[i][0] = valor[i][0] + LT[i - 1][0];
    }

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            LT[i][j] = valor[i][j] + maximo(LT[i - 1][j], LT[i][j - 1]);
        }
    }

    return LT[N - 1][M - 1];
}

void imprimirTabla() {
    printf("\nTabla LT:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%4d", LT[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int resultado = laberintoTesoro();

    imprimirTabla();

    printf("\nMayor tesoro acumulado: %d\n", resultado);

    return 0;
}