/*Ejercicio Matriz */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Estructura para pasar parametros a los hilos
struct parametros {
  int id; // Id del hilo
  float escalar; // Escalar por el que se multiplicara la matriz 
  float matriz[3][3]; // Matriz
};

// Funcion para inicializar la matriz
void init(float m[3][3]) {
  int i; // Contador filas
  int j; // Contador conlumnas
  for (i = 0; i < 3; i++) { // Recorremos todos los elementos de la matriz
    for (j = 0; j < 3; j++) {
      m[i][j] = random() * 100; // Asignamos un valor aleatorio a cada elelemnto
    }
  }
}

// Funcion que multiplica la matriz por un escalar
void *matrizporescalar(void *arg) {
  struct parametros *p; // Estructura con los parametros de la matriz
  int i; // Contador filas
  int j; // COntador columnas

  p = (struct parametros *)arg; // Cast de los parametros
  for (i = 0; i < 3; i++) { // Recorremos todas los elementos
    printf(" Hilo %d multiplicando fila %d\n", p->id, i);
    for (j = 0; j < 3; j++) {
      p->matriz[i][j] = p->matriz[i][j] * p->escalar; // Multiplicamos cada elemento por el escalar
      // sleep(2);
    }
  }
}

// Funcion de ejecuion
int main(int argc, char *argv[]) {
  pthread_t h1;
  struct parametros p1;
  p1.id = 1;
  p1.escalar = 0.5;

  init(p1.matriz);
  pthread_create(&h1, NULL, matrizporescalar, (void *)&p1);

  // Wait for the thread to finish
  pthread_join(h1, NULL);

  return 0;
}













