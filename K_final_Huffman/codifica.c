/*
55 caracteres: a-z | A-Z | punto, coma, espacio en blanco (no Ñ, no acentos)

encabezado del archivo comprimido: 5100adcde.......
numero_d_simbolos|tamaño_dl_mensaje|caracteres_usados|inicio_del_mensaje

Nota: para que su programa funcione correctamente, deberán manipular información a
nivel de bits y almacenarla en bytes sin desperdicio. El archivo resultante no es un
archivo ASCII, sino un archivo binario.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxCodigos 128

//para crear cada nodo del arbol
typedef struct nodo{
    int caracter;
    int frecuencia;
    struct nodo *izq;
    struct nodo *der;
}Tnodo;

//para crear el vector de apuntadores: cada posicion apunta a un caracter
//esta sera la cola de prioridad
typedef struct{
    Tnodo **caracteres;
    int tamanio;
}TnodoCola;


//leer archivo
int contar_frecuencias(char *arNombre, char* alfabeto, int *frecuencias, int longAlfabeto){
    //iniciar todas las frecuencias con -1 caracteres no validos
    for(int i=0; i<maxCodigos; i++){
        frecuencias[i] = -1;
    }
    //iniciar los caracteres validos con 0
    for(int i=0; i<longAlfabeto-1;i++){
        frecuencias[alfabeto[i]] = 0;
    }

    FILE *archivo = fopen(arNombre, "r");
    int caracter;
    int totalCaracteres = 0;
    while( (caracter = fgetc(archivo)) != EOF ){
        if(frecuencias[caracter] != -1){
            totalCaracteres++;
            frecuencias[caracter]++;
        }
    }
    fclose(archivo);
    return totalCaracteres;
}

void ordenarCola(TnodoCola *Q){
    Tnodo *temp = NULL;
    for(int i=0; i<Q->tamanio-1; i++){
        for(int j=i+1; j<Q->tamanio; j++){
            if( Q->caracteres[i]->frecuencia > Q->caracteres[j]->frecuencia){
                temp = Q->caracteres[i];
                Q->caracteres[i] = Q->caracteres[j];
                Q->caracteres[j] = temp;
            }
        }
    }
}

Tnodo *extract_min(TnodoCola *Q){
    Tnodo *nodo = Q->caracteres[0];
    Q->caracteres[0] = Q->caracteres[ Q->tamanio-1 ];
    Q->tamanio--;
    ordenarCola(Q);
    
    return nodo;
}

void insertar(TnodoCola *Q, Tnodo *z){
    Q->tamanio++;
    Q->caracteres[ Q->tamanio-1 ] = z;
    ordenarCola(Q);
}

Tnodo *huffman(TnodoCola *Q){
    while(Q->tamanio > 1){
        Tnodo *z = malloc(sizeof(Tnodo));
        z->caracter = -1;
        z->izq =  extract_min(Q);
        z->der =  extract_min(Q);
        z->frecuencia = z->izq->frecuencia + z->der->frecuencia;
        insertar(Q, z);
    }
    return extract_min(Q);
}

void generarCodigos(Tnodo *nodo, int nivel, char *codigo, char **codigos){
    if(nodo->der == NULL && nodo->izq == NULL ){
        codigo[nivel] = '\0';
        strcpy(codigos[nodo->caracter], codigo);
        //printf("%s ", codigo);
        //printf(" | %c - %d - %d\n", nodo->caracter, nodo->frecuencia, nivel);
        return;
    }
    
    codigo[nivel] = '0';
    generarCodigos(nodo->izq, nivel+1, codigo, codigos);

    codigo[nivel] = '1';
    generarCodigos(nodo->der, nivel+1, codigo, codigos);
}

void imprimir(Tnodo *nodo, int nivel){
    if(nodo->der == NULL && nodo->izq == NULL ){
        printf("%c(%d) - %d - nivel:%d\n", nodo->caracter,nodo->caracter, nodo->frecuencia, nivel);
        return;
    }
    printf("%c(%d) - %d - nivel:%d\n", nodo->caracter,nodo->caracter, nodo->frecuencia, nivel);
    imprimir(nodo->izq, nivel+1);
    imprimir(nodo->der, nivel+1);
}

int main(int argc, char *argv[]){

    char *arText_Nombre = argv[1];
    char *arText_NombreComprimido = argv[2];

    /*CUENTO LAS FRECUENCIAS DE CADA CARACTER*/
    char alfabeto[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz., ";
    int longAlfabeto = sizeof(alfabeto);
    int *frecuencias = malloc(sizeof(int)*maxCodigos);
    
    //cuenta frecuencias y retorna el total de caracteres en el documento
    int totalCaracteres = contar_frecuencias(arText_Nombre, alfabeto, frecuencias, longAlfabeto);
    /*----------------*/


    /*--GENERO EL ARBOL DE HUFFMAN--*/

    //contar solo caracteres usados(agrupados)
    int numCaracteresUsados=0;
    int k=0;
    char *car_usados = malloc(sizeof(char)*longAlfabeto);
    for(int i=0; i<maxCodigos; i++){
        if(frecuencias[i]>0){
            numCaracteresUsados++;
            car_usados[k] = i;
            k++;
        }
    }

    //esta es la cola de prioridad
    TnodoCola *Q = malloc(sizeof(TnodoCola)); 
    Q->caracteres = malloc(sizeof(Tnodo*)*numCaracteresUsados);
    Q->tamanio = numCaracteresUsados;

    //crear los nodos de cada caracter y ligarlos a la cola de prioridad
    int posit=0;
    for(int i=0; i<maxCodigos; i++){
        if(frecuencias[i]>0){
            Tnodo *nuevo = malloc(sizeof(Tnodo));
            nuevo->caracter = i;
            nuevo->frecuencia = frecuencias[i];
            nuevo->der = NULL;
            nuevo->izq = NULL;
            
            Q->caracteres[posit] = nuevo;
            posit++;
        }
    }

    //se ordena la cola
    ordenarCola(Q);

    //se genera el arbol de huffman
    Tnodo *raiz = huffman(Q);
    //imprimir(raiz, 0);
    /*------------*/

    /*GENERO LOS CODIGOS BINARIOS DE LOS CARACTERES*/
    //matriz para guardar los codigos binarios de cada letra utilizada
    //longitud de 128x56(longitud del alfabeto)
    char **codigos = malloc(sizeof(char*)*maxCodigos);
    for(int i=0; i<maxCodigos; i++){
        codigos[i] = malloc( sizeof(char)*longAlfabeto );
        codigos[i][0] = '\0';
    }

    char *codigo = malloc(sizeof(char)*maxCodigos);
    generarCodigos(raiz, 0, codigo, codigos);

    /*printf("\ncodigos binarios:\n");
    for(int i=0; i<maxCodigos; i++){
        if(codigos[i][0] != '\0'){
            if(i == 32)
                printf("espacio : %s\n", codigos[i]);
            else
                printf("%c : %s\n", i, codigos[i]);
        }
    }*/
    /*---------------------*/


    /*GENERO EL ARCHIVO COMPRIMIDO*/
    //archivo codificado
    FILE *archivoComp = fopen(arText_NombreComprimido, "wb");
    
    //archivo real
    FILE *archivo = fopen(arText_Nombre, "r");
    

    //encabezado
    /*encabezado del archivo comprimido: 5100adcde.......
    numero_d_simbolos|tamaño_dl_mensaje|carac|frec|carac|frec...|inicio_del_mensaje*/
    //aqui me quede
    int n_simbolos = numCaracteresUsados;
    int tamanioMsj  = totalCaracteres;
    fwrite(&n_simbolos, sizeof(int), 1, archivoComp);
    fwrite(&tamanioMsj, sizeof(int), 1, archivoComp);
    
    for(int i=0; i<numCaracteresUsados; i++){
        fwrite(&car_usados[i], 1, 1, archivoComp);
        fwrite(&frecuencias[car_usados[i]], sizeof(int), 1, archivoComp);
    }

    int caracter;
    int bits = 0;
    unsigned char bait = 0;
    while( (caracter = fgetc(archivo)) != EOF ){
        //printf("%d - %c - %s\n", caracter, caracter, codigos[caracter]);
        char *codigo = codigos[caracter];
        int i=0;
        while( codigo[i] != '\0' ){
            bait = bait << 1; //desplazar un bit a la izquierda
            //si digito es 1, hacer or(00000001), pone ultimo bit en 1
            if (codigo[i] == '1'){
                bait = bait | 1;
            }
            bits++;
            if(bits == 8){
                fwrite(&bait, 1, 1, archivoComp);
                bits=0;
                bait=0;
            }
            i++;
        }
    }

    //si el ultimo byte quedo incompleto, se rellena con ceros
    if(bits>0){
        int r = 8-bits;
        bait = bait << r;
        fwrite(&bait, 1, 1, archivoComp);
    }

    fclose(archivo);
    fclose(archivoComp);
    /*--------------------*/

    printf("\nCompresion completa: %s", arText_NombreComprimido);

    for(int i = 0; i < maxCodigos; i++){
        free(codigos[i]);
    }
    free(codigos);
    free(car_usados);
    free(frecuencias);
    return 0;
}