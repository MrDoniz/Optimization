// AUTOR: Daniel Dóniz García
// FECHA: 23 abr 2020
// EMAIL: alu0101217277@ull.edu.es
// ASIGNATURA: Optimización
// COMPILACIÓN: clear; g++ -Wall -Wextra -Wpedantic -std=c++11 -o main pg1_.cpp grafo_.cpp
// EJECUCIÓN  : ./main
#include "grafo.h"

GRAFO::~GRAFO()
{
	n = 0;
	m = 0;
	dirigido = 0;
	LS.clear();
	LP.clear();
}

void GRAFO:: actualizar(char nombrefichero[85], int &errorapertura)
{
	LS.clear();
	LP.clear();
  bool estofunciona = false;
  do{
    cout << "Introduce el nombre completo del fichero de datos" << endl;
    cin >> nombrefichero;
    ifstream cargaGrafo;
    cargaGrafo.open(nombrefichero);
    bool introducido = false;
    ElementoLista dummy;
    ElementoLista aux;
    int nodo;

    if (!cargaGrafo.fail()){
      cargaGrafo >> n;
      cargaGrafo >> m;
      cargaGrafo >> dirigido;
      LS.resize(n);
      if (Es_dirigido() == 1){
        while (!cargaGrafo.eof()){
          if (!cargaGrafo.eof()){
            cargaGrafo >> nodo;
            cargaGrafo >> dummy.j;
            dummy.j--;
            dummy.c = 0;
            LS[nodo-1].push_back(dummy);
          }
        }
        errorapertura = 0;
        ListaPredecesores();
      }else{
        while (!cargaGrafo.eof()){
          if (!cargaGrafo.eof()){
            cargaGrafo >> nodo;
            cargaGrafo >> dummy.j;
            dummy.j--;
            dummy.c = 0;
            for (unsigned i=0; i<LS[nodo-1].size(); i++){
              if (dummy.j == LS[nodo-1][i].j){
                introducido = true;
                break;
              }
            }
            if (!introducido)
              LS[nodo-1].push_back(dummy);
            aux.j = nodo-1;
            aux.c = 0;
            introducido=false;
            for (unsigned i=0; i<LS[dummy.j].size(); i++){
              if (aux.j == LS[dummy.j][i].j){
                introducido = true;
                break;
              }
            }
            if (!introducido)
              LS[dummy.j].push_back(aux);
            introducido=false;
          }
        }
        errorapertura = 0;
      }
      estofunciona = false;
    }else{
      cout << "Error en la apertura del fichero: revisa nombre y formato" << endl;
      cargaGrafo.close();  
      estofunciona = true;
    }
  }while(estofunciona == true);
}

void GRAFO::Info_Grafo()
{
  if (dirigido == 1)
  {
    cout << "Grafo dirigido ";
  }else
  {
    cout << "Grafo no dirigido ";
  }
  cout << " | nodos " << n << " | ";
  if (dirigido == 1)
  {
    cout << " arcos ";
  }else
  {
        cout << "aristas ";
    };
    cout << m << " " << endl;
}

unsigned GRAFO::Es_dirigido()
{
	return dirigido;
}

void GRAFO :: Mostrar_Listas (int l)
{
  //Muestra lista de sucesores y adyacencia
	if (l == 0){
		for (unsigned i=0; i<n; i++){
			cout <<"Nodo: " << i+1 << " { ";
			for (unsigned k=0; k<LS[i].size(); k++){
				cout << LS[i][k].j + 1<< " ";
			}
			cout << " } " <<endl;
		}
		cout << endl;
	}
  //Muestra lista de predecesores
	else {
		for (unsigned i=0; i<n; i++){
			cout << "Nodo: " << i+1 << " { ";
			for (unsigned k=0; k<LP[i].size(); k++){
				cout << LP[i][k].j + 1<< " ";
			}
			cout << " } " << endl;
		}
		cout << endl;
	}
}

void GRAFO::dfs(unsigned i, vector<bool> &visitado)
{
	visitado[i] = true;
    cout << i+1 << ", ";
	for (unsigned j=0;j<LS[i].size();j++)
             if (visitado[LS[i][j].j] == false)
                 dfs(LS[i][j].j, visitado);
}

void GRAFO::ComponentesConexas()
{
	int contador = 0;
	vector <bool> visitado(n);
	for (unsigned i = 0; i < n; ++i)
		visitado[i] = false;
	for (unsigned i = 0; i < n; ++i)
		if (visitado[i] == false){ //doble == porque es una condicion
			cout << endl << "Componente Conexa omg" << ++contador << " ; { ";
			dfs (i, visitado); 
			cout << " } " << endl;
    }
}

void GRAFO::ListaPredecesores() 
{
	LP.resize(n);
	ElementoLista dummy;

	for (unsigned i=0; i < n; i++){
		for (unsigned k=0; k < LS[i].size(); k++){
			dummy.j = i;
			dummy.c = 0;
			LP[LS[i][k].j].push_back(dummy);
		}
	}
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	ifstream cargaGrafo;
	cargaGrafo.open(nombrefichero);
	bool introducido = false;
	ElementoLista dummy;
	ElementoLista aux;
	int nodo;
	if (!cargaGrafo.fail()){
		cargaGrafo >> n;
		cargaGrafo >> m;
		cargaGrafo >> dirigido;
		LS.resize(n); //LS vectores de tamaño variable
    if (Es_dirigido() == 1){
      while (!cargaGrafo.eof()){
					cargaGrafo >> nodo;
					cargaGrafo >> dummy.j;
					dummy.j--;
					dummy.c = 0;
					LS[nodo-1].push_back(dummy);
			}
			errorapertura = 0;
			ListaPredecesores();
		}else {
			while (!cargaGrafo.eof()){
				if (!cargaGrafo.eof()){
					cargaGrafo >> nodo;
					cargaGrafo >> dummy.j;
					dummy.j--;
					dummy.c = 0;
					for (unsigned i=0; i<LS[nodo-1].size(); i++){
						if (dummy.j == LS[nodo-1][i].j){
							introducido = true;
							break;
						}
					}
					if (!introducido)
						LS[nodo-1].push_back(dummy);
					aux.j = nodo-1;
					aux.c = 0;
					introducido=false;
					for (unsigned i=0; i<LS[dummy.j].size(); i++){
						if (aux.j == LS[dummy.j][i].j){
							introducido = true;
							break;
						}
					}
					if (!introducido)
						LS[dummy.j].push_back(aux);
					introducido=false;
				}
			}
			errorapertura = 0;
		}
	}else
		errorapertura = 1;
	cargaGrafo.close();
}




