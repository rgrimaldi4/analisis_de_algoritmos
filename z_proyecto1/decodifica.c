#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxCodigos 128

typedef struct nodo{
    int caracter;
    int frecuencia;
    struct nodo *izq;
    struct nodo *der;
}Tnodo;

typedef struct{
    Tnodo **caracteres;
    int tamanio;
}TnodoCola;

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

void imprimir(Tnodo *nodo, int nivel){
    if(nodo->der == NULL && nodo->izq == NULL ){
        printf("%c(%d) - %d - nivel:%d\n", nodo->caracter,nodo->caracter, nodo->frecuencia, nivel);
        return;
    }
    printf("%c(%d) - %d - nivel:%d\n", nodo->caracter,nodo->caracter, nodo->frecuencia, nivel);
    imprimir(nodo->izq, nivel+1);
    imprimir(nodo->der, nivel+1);
}

void decodificar(){

}

int main(int argc, char *argv[]){
 
    char *ar_Nombre = argv[1];
    FILE *archivo = fopen(ar_Nombre, "rb");
    
    //variables de encabezado
    int  n_simbolos;
    int  tamanioMsj;
    char caracter;
    int  frecuencia;
         
    fread(&n_simbolos, sizeof(int), 1,  archivo);
    fread(&tamanioMsj, sizeof(int), 1,  archivo);

    //printf("%d\n", n_simbolos);
    //printf("%d\n", tamanioMsj);

    //cola
    TnodoCola *Q  = malloc(sizeof(TnodoCola));
    Q->caracteres = malloc(sizeof(Tnodo*)*n_simbolos);
    Q->tamanio = n_simbolos;

    for(int i = 0; i < n_simbolos; i++){
        fread(&caracter,  1, 1,  archivo);
        fread(&frecuencia, sizeof(int),  1,  archivo);
        //printf("%c,", caracter);
        //printf("%d | ", frecuencia);

        Tnodo *nuevo = malloc(sizeof(Tnodo));
        nuevo->caracter = caracter;
        nuevo->frecuencia = frecuencia;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        Q->caracteres[i] = nuevo;
    }

    //se ordena la cola
    ordenarCola(Q);

    //se genera el arbol de huffman
    Tnodo *raiz = huffman(Q);
    //imprimir(raiz, 0);

    //decodificar el mensaje
    Tnodo *actual = raiz;
    unsigned char bait = 0;
    int contador=0;
    while(contador < tamanioMsj){
        fread(&bait, 1,1,archivo); ///leer 1 byte en cada iteracion
        
        for(int i=7; i>=0 && contador<tamanioMsj; i--){
            int bit = (bait>>i) & 1;

            if(bit == 0){
                actual = actual->izq;
            }else{
                actual = actual->der;
            }
            
            if(actual->izq==NULL && actual->der==NULL){
                printf("%c", actual->caracter);
                contador++;
                actual = raiz; //reinicia en la raiz
            }
        }
    }

    fclose(archivo);    
}