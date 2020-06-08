// AUTOR: Daniel Dóniz García
// FECHA: 23 abr 2020
// EMAIL: alu0101217277@ull.edu.es
// ASIGNATURA: Optimización

#include "grafo.h"

GRAFO::~GRAFO()
{
	n = 0;
	m = 0;
	dirigido = 0;
	LS.clear();
	LP.clear();
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
  bool failArchivo = false;
  do
  {
    cout << "Introduce el nombre completo del fichero de datos" << endl;
    cin >> nombrefichero;
    ifstream inputFile;
    inputFile.open(nombrefichero); //otro grafo distinto sin necesidad de cerrar el programa.
    ElementoLista dummy1;
    ElementoLista dummy2;
    errorapertura = 0;
    if (!inputFile.fail())
    {
      unsigned i, j;
      // leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
      inputFile >> n >> m >> dirigido;
      // los nodos internamente se numeran desde 0 a n-1
      // creamos las n listas de sucesores
      LS.clear();
      LS.resize(n);
      // leemos los m arcos y creamos las listas de sucesores LS
      if (dirigido == 1)
      {
        for (j = 0; j < m; ++j)
        {
          inputFile >> i >> dummy1.j >> dummy1.c;
          dummy1.j--;
          LS[i - 1].push_back(dummy1);
        }
        inputFile.close();
        ListaPredecesores();
      }
      else
      {
        for (j = 0; j < m; j++)
        {
          inputFile >> i >> dummy1.j >> dummy1.c;
          dummy1.j--;
          LS[i - 1].push_back(dummy1);
          if (dummy1.j != i - 1)
          {
            dummy2.j = i - 1;
            dummy2.c = dummy1.c;
            LS[dummy1.j].push_back(dummy2);
          }
        }
        inputFile.close();
      }
      errorapertura = 0;
      failArchivo = false;
    }else
    {
      cout << "Error en la apertura del fichero: revisa nombre y formato" << endl;
      inputFile.close();  
      failArchivo = true;
    }
  }while(failArchivo == true);
}

unsigned GRAFO::Es_dirigido()
{
return dirigido;
}

void GRAFO::Info_Grafo()
{
	cout << endl;
	if (dirigido == 1)
		cout << "Grafo dirigido ";
	else
		cout << "Grafo no dirigido ";
	cout << "| nodos " << n << " | ";
	if (dirigido == 1)
		cout << " arcos ";
	else
		cout << "aristas ";
	cout << m << " " << endl << endl;
}



void GRAFO::MostrarCamino(unsigned k, unsigned i, vector<unsigned> pred)
{
  if (i != k)
  {
    MostrarCamino(k,pred[i],pred);
    cout << pred[i]+1 << " -> ";
  }
}


void GRAFO :: Mostrar_Listas (int l)
{
  //Muestra lista de sucesores y adyacencia
	if (l == 0)
  {
		for (unsigned i=0; i < n; i++)
    {
			cout <<"Nodo: " << i+1 << " { ";
			for (unsigned k=0; k < LS[i].size(); k++)
				cout << LS[i][k].j + 1<< " ";
			cout << " } " <<endl;
		}
		cout << endl;
	}
  //Muestra lista de predecesores
	else
  {
		for (unsigned i=0; i < n; i++)
    {
			cout << "Nodo: " << i+1 << " { ";
			for (unsigned k=0; k < LP[i].size(); k++)
				cout << LP[i][k].j + 1<< " ";
			cout << " } " << endl;
		}
		cout << endl;
	}
}

void GRAFO::dfs(unsigned i, vector<bool> &visitado)
{
	visitado[i] = true;
	cout << i + 1;
	for (unsigned j = 0; j < LS[i].size(); j++)
		if (visitado[LS[i][j].j] == false)
		{
			cout << ", ";
			dfs(LS[i][j].j, visitado);
		}
}

void GRAFO::ComponentesConexas()
{
	int contador = 0;
	vector<bool> visitado(n);
	cout << endl;
	for (unsigned i = 0; i < n; ++i)
		visitado[i] = false;
	for (unsigned i = 0; i < n; ++i)
		if (visitado[i] == false)
		{
			cout << "Componente Conexa " << ++contador << ": { ";
			dfs(i, visitado);
			cout << " }" << endl;
		}
	cout << endl;
}

void GRAFO::Kruskal()
{
    vector <AristaPesada> Aristas;
    /*Usaremos la busqueda del menor en cada momento, pues es el mejor para Kruskal que no exige tener todas las aristas ordenadas*/
    /*Cargamos todas las aristas de la lista de adyacencia*/
    Aristas.resize(m);
    unsigned k = 0;
    for (unsigned i = 0; i<n; i++)
        for (unsigned j=0; j<LS[i].size();j++)
            if (i < LS[i][j].j)
            {
                Aristas[k].extremo1 = i;
                Aristas[k].extremo2 = LS[i][j].j;
                Aristas[k++].peso = LS[i][j].c;
                }
    /*Inicializamos el indice a la cabeza del vector*/
    unsigned head = 0;
    AristaPesada AristaDummy; //Para los intercambios en la ordenacion parcial

    /*Inicializamos el contador de aristas en la solución*/
    unsigned a = 0;

    /*Inicializamos el peso de la solucion*/
    unsigned pesoMST = 0;

    /*Inicializamos el registro de componentes conexas: cada nodo está en su compomente conexa*/
    vector <unsigned> Raiz;
    Raiz.resize(n);
    for (unsigned q = 0;q < n; q++)
        Raiz[q]=q;
    /*Comenzamos Kruskal*/
    do
    {
        /* Implementamos el algoritmo de Kruskal */
        AristaDummy = Aristas[head];
        unsigned indice = head;
        
        for(unsigned i = head; i < Aristas.size(); ++i)
          if(AristaDummy.peso > Aristas[i].peso)
            indice = i;
        
        if (indice != head)
        {
          AristaDummy = Aristas[head];
          Aristas[head] = Aristas[indice];
          Aristas[indice] = AristaDummy;
        }
        
        if(Raiz[Aristas[head].extremo1] != Raiz[Aristas[head].extremo2])
        {
          pesoMST = pesoMST + Aristas[head].peso;
          Raiz[Aristas[head].extremo1] = Raiz[Aristas[head].extremo2];
          a = a + 1;
          cout << "Arista numero" << a << " incorporada (" << Aristas[head].extremo1 + 1 << ", " << Aristas[head].extremo2 + 1 << "), con peso " << Aristas[head].peso << endl;
        }
        head = head + 1;
        } while ((a < (n-1)) && (head < m));

        if (a == (n - 1))
            cout << "El peso del arbol generador de minimo coste es " << pesoMST << endl;
        else
        {
            cout << "El grafo no es conexo, y el bosque generador de minimo coste tiene peso " << pesoMST << endl;
        };
}

void GRAFO::ListaPredecesores()
{
	ElementoLista dummy1;
	LP.clear();
	LP.resize(n);
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j < LS[i].size(); ++j)
		{
			dummy1.j = i;
			LP[LS[i][j].j].push_back(dummy1);
		}
	}
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	ifstream inputFile;
	inputFile.open(nombrefichero); //otro grafo distinto sin necesidad de cerrar el programa.
	ElementoLista dummy1;
	ElementoLista dummy2;
  if (!inputFile.fail())
	{
		unsigned i, j;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		inputFile >> n >> m >> dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.clear();
		LS.resize(n);
		// leemos los m arcos y creamos las listas de sucesores LS
		if (dirigido == 1)
		{
			for (j = 0; j < m; ++j)
			{
				inputFile >> i >> dummy1.j >> dummy1.c;
				dummy1.j--;
				LS[i - 1].push_back(dummy1);
			}
			inputFile.close();
			ListaPredecesores();
		}
		else
		{
			for (j = 0; j < m; j++)
			{
				inputFile >> i >> dummy1.j >> dummy1.c;
				dummy1.j--;
				LS[i - 1].push_back(dummy1);
				if (dummy1.j != i - 1)
				{
					dummy2.j = i - 1;
					dummy2.c = dummy1.c;
					LS[dummy1.j].push_back(dummy2);
				}
			}
			inputFile.close();
		}
		errorapertura = 0;
	}
  else
    errorapertura = 1;
  inputFile.close();
}

void GRAFO::Dijkstra()
{
  vector<bool> nodoEtiquetado;
  vector<int> d;
  vector<unsigned> pred;
  unsigned s, nodoElegido;
  unsigned predNull = maxint;
  int min; //Declaro min como entero para la comparacion con maxint
  //Inicialmente no hay ningun nodo etiquetado
  nodoEtiquetado.resize(n, false);
  //Inicialmente todas las etiquetas distancias son infinito
  d.resize(n, maxint);
  //Inicialmente el pred es null
  pred.resize(n, predNull);
  //Solicitamos al usuario nodo origen
  cout << "\nIntroduzca el nodo de partida. De 1 a "<< n << ": ";
  cin >> s;
  //El nodo irigen tiene el pred propio y origen 0.
  d[--s] = 0;
  pred[s] = s;
  do
  {
    min = maxint;
    //Buscamos un nodo a ser etiquetado. 
    for (unsigned i=0; i < n; ++i)
      if ((nodoEtiquetado[i] == false) && (d[i] < min))
      {
        nodoElegido = i;
        min = d[i];
      }
    if (nodoElegido!=predNull)
    {
      //Si existe ese NodoElegido, lo etiqueto y usamos los arcos de la lista para buscar atajos
      nodoEtiquetado[nodoElegido] = true;
      for (unsigned k = 0; k < LS[nodoElegido].size(); ++k)
        if (nodoEtiquetado[LS[nodoElegido][k].j]==false)
          if ((d[LS[nodoElegido][k].j]) > (d[nodoElegido] + LS[nodoElegido][k].c))
          {
            d[LS[nodoElegido][k].j] = (d[nodoElegido] + LS[nodoElegido][k].c);
            pred[LS[nodoElegido][k].j] = nodoElegido;
          }
    }
  }while (min < maxint);
    cout << endl;
    for (unsigned i = 0; i < n; ++i)
      if (i != s)
      {
        if (nodoEtiquetado[i] == true)
        {
          cout << "El camino desde " << s + 1 << " al nodo " << i +1 << " es: ";
          MostrarCamino(s,i,pred);
          cout << i + 1 << " de longitud " << d[i] << endl;
        }
        else 
          cout << "ERROR. No hay camino desde: " << s + 1 <<" al nodo " << i + 1 <<endl;
      }
 }