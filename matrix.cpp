#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Parametros de la matriz
struct parametros {
    int id; // ID del proceso
    float escalar; // Numero por el que se multiplica la maytriz
    float matriz[3][3]; // Matriz a multiplicar
};

void init(float m[3][3]) { // Inicializa la matriz
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m[i][j] = (float)rand() / RAND_MAX * 100; // Aque se genera un numero aleatorio entre 0 y 100 para la mtriz
        }
    }
}

// Multiplicar la matriz por el escalar
void *matrizporescalar(void *arg) {
    struct parametros *p = (struct parametros *)arg;
    for (int i = 0; i < 3; i++) { // Recorrer filas
        printf("Hilo %d multiplicando fila %d\n", p->id, i);
        for (int j = 0; j < 3; j++) { // Loop columnas
            p->matriz[i][j] *= p->escalar; // Multiplicar cada elemento por escalar
        }
    }
    return NULL;
}

// Imprimir matriz, doble for loop
void print_matrix(float m[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // Se inicializa la seed para los numeros aleatorios
    pthread_t h1; // Se crea el hilo
    struct parametros p1 = {1, 0.5}; // Se crea la estructura de parametros de matriz

    init(p1.matriz); // Inicializa la matriz con valores
    
    printf("Matriz original:\n");
    print_matrix(p1.matriz);

    pthread_create(&h1, NULL, matrizporescalar, &p1); // Se realiza la multiplicacaion
    pthread_join(h1, NULL);

    printf("\n Matriz resultante:\n"); // Imprimir matriz ersultante
    print_matrix(p1.matriz);

    return 0;
}