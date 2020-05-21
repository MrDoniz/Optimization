// AUTOR: Daniel Dóniz García
// FECHA: 23 abr 2020
// EMAIL: alu0101217277@ull.edu.es
// ASIGNATURA: Optimización
// COMPILACIÓN: clear; g++ -Wall -Wextra -Wpedantic -std=c++11 -o main pg1_.cpp grafo_.cpp
// EJECUCIÓN  : ./main
#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;
const unsigned UERROR = 65000;
const int maxint = 1000000;

// definicion de un elemento de la lista de adyacencia

typedef struct
{
	unsigned j; // nodo
	int      c; // atributo para expresar el peso, la longitud, el coste, la inversion, etc..., esto es, lo que me implica que ese arco o arista forme parte de la solucion
} ElementoLista;

// definicion del tipo de una lista de adyacencia de un nodo

typedef vector<ElementoLista> LA_nodo;


class GRAFO
 {
	unsigned            n;         /* numero de NODOS */
	unsigned            m;         /* numero de ARCOS */
	unsigned   			dirigido;  /* 0 si el grafo es no dirigido y 1 si es dirigido */
	vector<LA_nodo>     LS;        /* Lista de adyacencia de los sucesores: es una matriz dode cada fila posiblemente es posiblemente de distinto tamaño*/
	vector<LA_nodo>     LP;        /* Lista de adyacencia de los predecesores: es una matriz dode cada fila posiblemente es posiblemente de distinto tamaño*/
 public:
     GRAFO(char nombrefichero[], int &errorapertura);
     void actualizar (char nombrefichero[], int &errorapertura);
     unsigned Es_dirigido();   /*devuelve 0 si el grafo es no dirigido y 1 si es dirigido*/
     void Info_Grafo();
     void Mostrar_Listas(int l);
     void ListaPredecesores();
     void ComponentesConexas();
     void dfs(unsigned i, vector<bool> &visitado);
     ~GRAFO();
};


#endif
