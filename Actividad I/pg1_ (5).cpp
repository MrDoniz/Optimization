// AUTOR: Daniel Dóniz García
// FECHA: 23 abr 2020
// EMAIL: alu0101217277@ull.edu.es
// ASIGNATURA: Optimización
// COMPILACIÓN: clear; g++ -Wall -Wextra -Wpedantic -std=c++11 -o main pg1_.cpp grafo_.cpp
// EJECUCIÓN  : ./main
#include <string.h>
#include "grafo.h"

void clrscr(){
	system("cls");
}

//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
void menu (unsigned dirigido, char &opcion){
  if (dirigido == 0){
    cout << endl << endl 
    << "c. [c]argar grafo desde fichero.\n" 
    << "i. Mostrar [i]nformacion basica del grafo.\n" 
    << "a. Mostrar la lista de [a]dyacencia del grafo.\n" 
    << "o. Mostrar c[o]mponentes conexas del grafo.\n" 
    << "q. Finalizar el programa.\n" 
    << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
    while (opcion != 'c' && opcion != 'i' && opcion != 'a' && opcion != 'o' && opcion != 'q'){
      cout << endl << "Ha introducido una opción no correcta. Por favor introduzca una opción correcta: " << endl;
      cin >> opcion;
    }
  }
  if (dirigido == 1){
    cout << endl << endl 
    << "c. [c]argar grafo desde fichero.\n" 
    << "i. Mostrar [i]nformacion basica del grafo.\n"
    << "s. Mostrar la lista de [s]ucesores del grafo.\n" 
    << "p. Mostrar la lista de [p]redecesores del grafo.\n" 
    << "q. Finalizar el programa.\n" 
    << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
    while (opcion != 'c' && opcion != 'i' && opcion != 's' && opcion != 'p' && opcion != 'q'){
      cout << endl << "Ha introducido una opción no correcta. Por favor introduzca otra nuevamente: " << endl;
      cin >> opcion;
    }
  }
}

int main(int argc, char *argv[]){
  int error_apertura;
  char nombrefichero[85], opcion;
	clrscr();
	if (argc > 1){
		cout << "Cargando datos desde el fichero dado como argumento" << endl;
    strcpy(nombrefichero, argv[1]);
  }else{
    cout << "Introduce el nombre completo del fichero de datos" << endl;
    cin >> nombrefichero;
		clrscr();
  }
  GRAFO G(nombrefichero, error_apertura);
  if (error_apertura == 1){
    cout << "Error en la apertura del fichero: revisa nombre y formato" << endl;
  }else{
    do{
      menu(G.Es_dirigido(), opcion);
      switch (opcion){
        case 'c':
          G.actualizar(nombrefichero, error_apertura);
        break;
        case 'i':
          G.Info_Grafo();
        break;
        case 'q':
          cout << "\nGracias por utilizar este programa.\n" << endl;
        break;
        
        if(G.Es_dirigido() == 0){
          case 'a':
            G.Mostrar_Listas(0);
          break;
          case 'o':
            G.ComponentesConexas();
          break;
        }
        if(G.Es_dirigido() == 1){
          case 's':
            G.Mostrar_Listas(0);
          break;
          case 'p':
            G.Mostrar_Listas(1);
          break;
        }
      }
    }while (opcion != 'q');
  }
  cout << "Fin del programa";
	return(0);
}
