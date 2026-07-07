#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 100000;
    char cadena[100001]; // +1 para '\0'

    srand(time(NULL));

    for(int i = 0; i < n; i++) {
        cadena[i] = 'a' + rand() % 26;
    }

    cadena[n] = '\0';

    // Crear archivo CSV
    FILE *archivo = fopen("cadena.csv", "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo\n");
        return 1;
    }

    // Puedes guardarlo como una sola celda:
    fprintf(archivo, "%s\n", cadena);

    fclose(archivo);

    printf("Cadena guardada en cadena.csv\n");

    return 0;
}