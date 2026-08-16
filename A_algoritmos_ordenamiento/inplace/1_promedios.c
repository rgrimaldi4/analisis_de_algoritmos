#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>


void pormedios_bf(){
    FILE *archivo = fopen("todos_experimentos.csv", "r");

    char linea[5000];   // con mucho espacio
    int renglon = 1;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        double suma = 0.0;
        int contador = 0;
        int columna = 0;

        char *token = strtok(linea, ",");

        double mayor = -DBL_MAX;;
        double menor = DBL_MAX;

        while (token != NULL) {
            if(columna!=0){
                suma += atof(token);   // convierte texto a double
                contador++;

                if( atof(token) > mayor)
                    mayor = atof(token);
                if( atof(token) < menor)
                    menor = atof(token);

            }
            columna++;
            token = strtok(NULL, ",");
        }


        double promedio = 0.0;
        suma = suma - (mayor+menor);
        promedio = suma / (contador-2);

        //printf("Renglon %d -> suma = %.6f, promedio = %.6f\n", renglon, suma, promedio);
        printf( "%f\n", promedio );
        renglon++;
    }
    fclose(archivo);  

}


void pormedios_bl(){
    FILE *archivo = fopen("todos_experimentos_bl.csv", "r");

    char linea[5000];   // con mucho espacio
    int renglon = 1;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        double suma = 0.0;
        int contador = 0;
        int columna = 0;

        char *token = strtok(linea, ",");

        double mayor = -DBL_MAX;;
        double menor = DBL_MAX;

        while (token != NULL) {
            if(columna!=0){
                suma += atof(token);   // convierte texto a double
                contador++;

                if( atof(token) > mayor)
                    mayor = atof(token);
                if( atof(token) < menor)
                    menor = atof(token);

            }
            columna++;
            token = strtok(NULL, ",");
        }


        double promedio = 0.0;
        suma = suma - (mayor+menor);
        promedio = suma / (contador-2);

        //printf("Renglon %d -> suma = %.6f, promedio = %.6f\n", renglon, suma, promedio);
        printf( "%f\n", promedio );
        renglon++;
    }
    fclose(archivo);  

}

int main(){
    //pormedios_bl();
    pormedios_bf();

    return 0;
}






    /*
    //promedio
    FILE *archivo;
    archivo = fopen("todos_experimentos_bl.csv", "r");

    double suma_total = 0;
    double mayor = -1;
    double menor = 1000;
    double tiempo = 0;
    for(int i=0; i<30; i++){
        for(int j=0; j<100; j++){
            fscanf(archivo, "%f", tiempo);
            suma_total+= tiempo;
            if( tiempo > mayor){
                mayor=tiempo;
            }
            if(tiempo < menor){
                menor=tiempo;
            }            
        }
        printf("-suma total tiempo %d:  %f-\n",i, suma_total );
        suma_total = 0;
    } */   
