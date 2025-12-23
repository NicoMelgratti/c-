
using namespace std;

struct tex {
	string palabra;
	int apariciones=0;
	int longitud;
};

// Estructura para un nodo en una lista enlazada
struct nodo {
	tex dato;
	nodo* siguiente;
};

struct letraInfo {
	int frecuencia;
	char letra;
	letraInfo *sig;
};
struct PalabraInfo {
	string palabra;
	int frecuencia;
	PalabraInfo* sig;
};

struct MatrizPalabras {
	PalabraInfo* matriz[26][25]; // 26 letras del alfabeto, 25 longitudes de palabra
};


void separador1();
void gotoxy(int x,int y);	
void insertarOrdenado(nodo*& lista, nodo* conteo);
void insertar(nodo*& lista, string palabra);
void contarPalabras(nodo*& lista, ifstream& inputFile); 
void mostrarLista(nodo* lista);
void liberarLista(nodo*& lista);
void generarArchivoPorLetra(nodo* lista, char letra);
void mostrarYGuardarArchivo(letraInfo *lista);
void insertar1(letraInfo *&lista, char letra);
void liberarMemoria(letraInfo *&lista);
void procesarArchivo(const string& nombreArchivo);
void ordenarPorFrecuencia(letraInfo *&lista);
void insertarPalabra(MatrizPalabras& matrizPalabras, string palabra);
void cargarArchivoEnMatriz(MatrizPalabras& matrizPalabras, const string& nombreArchivo);
void escribirMatrizEnArchivo(const MatrizPalabras& matrizPalabras, const string& nombreArchivo);
string limpiarPalabra(string palabra);
double longitudPromedio(const MatrizPalabras& matrizPalabras);
void palabrasConMayorFrecuencia(const MatrizPalabras matrizPalabras, char letraInicial);
double porcentajePalabrasVocales(const string& nombreArchivo);
