#include <stdio.h>
#include <stdlib.h>
#include "archivo.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include "Libro.h"
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <initializer_list>
#include <cctype>
using namespace std;


void separador1(){
	for(int i=0; i<100; i++){ //hace las lineas
		gotoxy(i,0); 
		cout<<"-";
	}  
	for(int i=1; i<30; i++){  //hace las lineas
		gotoxy(0,i); 
		cout<<"|";
	}
	for(int i=0; i<100; i++){ //hace las lineas
		gotoxy(i,29); 
		cout<<"-";
	}
	for(int i=28; i>=1; i--){  //hace las lineas
		gotoxy(99,i); 
		cout<<"|";
	}
}
//Funcion que gotoxy para ordenar elementos en la aplicacion mas facil
void gotoxy(int x,int y){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon,dwPos);
}

	
void insertar1(letraInfo *&lista, char letra) {
	if (lista == nullptr) {
		lista = new letraInfo;
		lista->letra = letra;
		lista->frecuencia = 1;
		lista->sig = nullptr;
	} else {
		letraInfo *temp = lista;
		while (temp->sig != nullptr && temp->letra != letra) {
			temp = temp->sig;
		}
		if (temp->letra == letra) {
			temp->frecuencia++;
		} else {
			temp->sig = new letraInfo;
			temp->sig->letra = letra;
			temp->sig->frecuencia = 1;
			temp->sig->sig = nullptr;
		}
	}
}

void mostrar(letraInfo *lista) {
	separador1();
	int y=2;
	gotoxy(30,y++);
	gotoxy(30,y++);
	letraInfo *temp = lista;
	while (temp != nullptr) {
		cout << "Letra: " << temp->letra << ", Frecuencia: " << temp->frecuencia ;
		temp = temp->sig;
		gotoxy(30,y++);
	}
}

void liberarMemoria(letraInfo *&lista) {
	while (lista != nullptr) {
		letraInfo *temp = lista;
		lista = lista->sig;
		delete temp;
	}
}

void procesarArchivo(const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	if (!archivo) {
		cerr << "No se pudo abrir el archivo." << endl;
		return;
	}
	
	letraInfo *lista = nullptr;
	char caracter;
	while (archivo.get(caracter)) {
		if (isalpha(caracter)) {
			insertar1(lista, tolower(caracter));
		}
	}
	
	archivo.close();
	ordenarPorFrecuencia(lista);
	mostrarYGuardarArchivo(lista);
	mostrar(lista);
	liberarMemoria(lista);
}
void mostrarYGuardarArchivo(letraInfo *lista) {
	ofstream archivo("frecuencias.txt");
	if (!archivo) {
		cerr << "No se pudo abrir el archivo de salida." << endl;
		return;
	}
	
	letraInfo *temp = lista;
	while (temp != nullptr) {
		archivo << "Letra: " << temp->letra << ", Frecuencia: " << temp->frecuencia << endl;
		temp = temp->sig;
	}
	gotoxy(25,2);
	cout << "Tabla guardada en el archivo frecuencias.txt" ;
	archivo.close();
}
void ordenarPorFrecuencia(letraInfo *&lista) {
	if (lista == nullptr || lista->sig == nullptr) {
		return;
	}
	
	bool intercambio;
	letraInfo *actual;
	letraInfo *siguiente = nullptr;
	
	do {
		intercambio = false;
		actual = lista;
		
		while (actual->sig != siguiente) {
			if (actual->frecuencia < actual->sig->frecuencia) {
				swap(actual->frecuencia, actual->sig->frecuencia);
				swap(actual->letra, actual->sig->letra);
				intercambio = true;
			}
			actual = actual->sig;
		}
		siguiente = actual;
	} while (intercambio);
}




void insertarPalabra(MatrizPalabras& matrizPalabras, string palabra) {
	int indiceLetra = palabra[0] - 'a'; // Índice de la letra
	int longitud = palabra.length();     // Longitud de la palabra
	
	// Crear un nuevo nodo PalabraInfo
	PalabraInfo* nuevoNodo = new PalabraInfo;
	nuevoNodo->palabra = palabra;
	nuevoNodo->frecuencia = 1;
	nuevoNodo->sig = nullptr;
	
	// Insertar el nodo en la lista enlazada correspondiente
	if (matrizPalabras.matriz[indiceLetra][longitud] == nullptr) {
		matrizPalabras.matriz[indiceLetra][longitud] = nuevoNodo;
	} else {
		PalabraInfo* actual = matrizPalabras.matriz[indiceLetra][longitud];
		while (actual->sig != nullptr && actual->palabra != palabra) {
			actual = actual->sig;
		}
		if (actual->palabra == palabra) {
			actual->frecuencia++;
			delete nuevoNodo; // La palabra ya existe, se elimina el nodo creado
		} else {
			actual->sig = nuevoNodo;
		}
	}
	
}
string limpiarPalabra(string palabra) {
	string palabraLimpia;
	for (char c : palabra) {
		// Solo mantener caracteres alfabéticos
		if (isalpha(c)) {
			// Convertir a minúsculas
			palabraLimpia += tolower(c);
		}
	}
	return palabraLimpia;
}

// Función para cargar la información del archivo en la matriz
void cargarArchivoEnMatriz(MatrizPalabras& matrizPalabras, const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	if (archivo.is_open()) {
		string palabra;
		while (archivo >> palabra) {
			// Limpiar la palabra antes de insertarla
			palabra = limpiarPalabra(palabra);
			if (!palabra.empty()) { // Ignorar palabras vacías después de limpiarlas
				insertarPalabra(matrizPalabras, palabra);
			}
		}
		archivo.close();
		gotoxy(20,2);
		cout<<"Se creo matriz.txt donde esta alamcenado los datos de dicha matriz! ";
	} else {
		cout << "No se pudo abrir el archivo." << endl;
	}
}
void escribirMatrizEnArchivo(const MatrizPalabras& matrizPalabras, const string& nombreArchivo) {
	ofstream archivo(nombreArchivo);
	if (archivo.is_open()) {
		for (int i = 0; i < 26; ++i) {
			for (int j = 0; j < 25; ++j) {
				PalabraInfo* actual = matrizPalabras.matriz[i][j];
				while (actual != nullptr) {
					archivo << actual->palabra << " " << actual->frecuencia << endl;
					actual = actual->sig;
				}
			}
		}
		archivo.close();
	} else {
		cout << "No se pudo abrir el archivo." << endl;
	}
}


// Función para calcular la longitud promedio de las palabras en el archivo
double longitudPromedio(const MatrizPalabras& matrizPalabras) {
	int totalLongitud = 0;
	int totalPalabras = 0;
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 25; ++j) {
			PalabraInfo* actual = matrizPalabras.matriz[i][j];
			while (actual != nullptr) {
				totalLongitud += j; // La longitud de la palabra es j
				totalPalabras++;
				actual = actual->sig;
			}
		}
	}
	if (totalPalabras > 0) {
		return double(totalLongitud) / totalPalabras;
	} else {
		return 0.0; // Evitar división por cero
	}
}

// Función para encontrar las 5 palabras con mayor frecuencia que comienzan con una letra dada
void palabrasConMayorFrecuencia( MatrizPalabras matrizPalabras, char letraInicial) {
	int indiceLetra = tolower(letraInicial) - 'a'; // Convertir a minúscula y calcular el índice
	PalabraInfo* listaOrdenada = nullptr; // Lista enlazada para almacenar temporalmente las palabras ordenadas
	
	// Recorrer la matriz y ordenar la lista enlazada de manera descendente por frecuencia
	for (int j = 24; j >= 0; --j) { // Empezar desde la longitud máxima hacia atrás para priorizar las palabras más largas
		PalabraInfo* actual = matrizPalabras.matriz[indiceLetra][j];
		while (actual != nullptr) {
			// Insertar el nodo actual en la lista ordenada manteniendo el orden descendente por frecuencia
			PalabraInfo* siguiente = actual->sig; // Guardar el siguiente nodo antes de cambiarlo
			if (listaOrdenada == nullptr or actual->frecuencia >= listaOrdenada->frecuencia) {
				actual->sig = listaOrdenada;
				listaOrdenada = actual;
			} else {
				PalabraInfo* temp = listaOrdenada;
				while (temp->sig != nullptr && temp->sig->frecuencia > actual->frecuencia) {
					temp = temp->sig;
				}
				actual->sig = temp->sig;
				temp->sig = actual;
			}
			actual = siguiente; // Mover al siguiente nodo
		}
	}
	int y=7;
	// Mostrar las palabras con mayor frecuencia
	gotoxy(25,y++);
	gotoxy(25,y++);	gotoxy(25,y++);
	cout << "Palabras con mayor frecuencia que comienzan con '" << letraInicial << "':" << endl;
	PalabraInfo* temp = listaOrdenada;
	int i = 0; 
	while(i < 5 && temp != nullptr){
		gotoxy(25,y++);
		cout << setw(10) << temp->palabra << " - Frecuencia: " << temp->frecuencia << endl;
		temp = temp->sig;
		i++;
	}
	
	// Liberar la memoria de la lista ordenada
	while (listaOrdenada != nullptr) {
		PalabraInfo* siguiente = listaOrdenada->sig;
		delete listaOrdenada;
		listaOrdenada = siguiente;
	}
}
// Función para calcular el porcentaje de palabras que comienzan con una vocal versus consonante
double porcentajePalabrasVocales(const string& nombreArchivo) {
	ifstream archivo(nombreArchivo);
	int totalPalabras = 0;
	int palabrasVocales = 0;
	if (archivo.is_open()) {
		string palabra;
		while (archivo >> palabra) {
			// Limpiar la palabra antes de procesarla
			palabra = limpiarPalabra(palabra);
			if (!palabra.empty()) { // Ignorar palabras vacías después de limpiarlas
				totalPalabras++;
				char primeraLetra = palabra[0];
				if (primeraLetra == 'a' || primeraLetra == 'e' || primeraLetra == 'i' || primeraLetra == 'o' || primeraLetra == 'u') {
					palabrasVocales++;
				}
			}
		}
		archivo.close();
	} else {
		cout << "No se pudo abrir el archivo." << endl;
		return 0.0; // Devolver 0 en caso de fallo en la apertura del archivo
	}
	if (totalPalabras > 0) {
		return double(palabrasVocales) / totalPalabras * 100.0;
	} else {
		return 0.0; // Evitar división por cero
	}
}
// Función para insertar un nuevo nodo en una lista enlazada ordenada
void insertarOrdenado(nodo*& lista, nodo *conteo) {
	while(conteo!=NULL){
		nodo* nuevo_nodo = new nodo();
		nuevo_nodo->dato.apariciones = conteo->dato.apariciones;
		nuevo_nodo->dato.palabra = conteo->dato.palabra;
		
		// Caso: Lista vacía o nuevo nodo tiene más apariciones o sigue alfabéticamente
		if (lista == nullptr or conteo->dato.apariciones > lista->dato.apariciones or
			(conteo->dato.apariciones == lista->dato.apariciones && conteo->dato.palabra.length() > lista->dato.palabra.length()) or
			(conteo->dato.apariciones == lista->dato.apariciones && conteo->dato.palabra.length() == lista->dato.palabra.length() && conteo->dato.palabra > lista->dato.palabra)) {
			nuevo_nodo->siguiente = lista;
			lista = nuevo_nodo;
		} else {
				// Caso: Insertar en posición correcta manteniendo el orden
				nodo* actual = lista;
				while (actual->siguiente != nullptr && (conteo->dato.apariciones < actual->siguiente->dato.apariciones or
					(conteo->dato.apariciones == actual->siguiente->dato.apariciones && conteo->dato.palabra.length() < actual->siguiente->dato.palabra.length()) or
					(conteo->dato.apariciones == actual->siguiente->dato.apariciones && conteo->dato.palabra.length() == actual->siguiente->dato.palabra.length() && conteo->dato.palabra < actual->siguiente->dato.palabra))) {
					actual = actual->siguiente;
				}
			nuevo_nodo->siguiente = actual->siguiente;
			actual->siguiente = nuevo_nodo;
		}
	conteo=conteo->siguiente;
	}		
}

// Función para contar las palabras en un archivo y almacenar el conteo

void insertar(nodo*& lista, string palabra) {
	if (lista == nullptr) {
		lista = new nodo{{palabra, 1}, nullptr};
	} else {
		nodo* temp = lista;
		while (temp->siguiente != nullptr && temp->dato.palabra != palabra) {
			temp = temp->siguiente;
		}
		
		if (temp->dato.palabra == palabra) {
			temp->dato.apariciones++;
		} else {
			temp->siguiente = new nodo{{palabra, 1}, nullptr};
		}
	}
}

void contarPalabras(nodo*& lista, ifstream& inputFile) {
	string palabra;
	while (inputFile >> palabra) {
		// Eliminar signos de puntuación y convertir a minúsculas
		palabra.erase(remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());
		transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
		
		// Incrementar el conteo de la palabra en la lista enlazada
		insertar(lista, palabra);
	}
}

// Función para liberar la memoria ocupada por una lista enlazada
void liberarLista(nodo*& lista) {
	while (lista != nullptr) {
		nodo* temp = lista;
		lista = lista->siguiente;
		delete temp;
	}
}

// Función para generar un archivo con las palabras que comienzan con una letra específica
void generarArchivoPorLetra(nodo* lista, char letra) {
	ofstream archivo;
	archivo.open("ArchivoConteoPorLetras.txt");
	nodo* actual = lista;
	
	while (actual != nullptr) {
		// Escribir en el archivo si la palabra comienza con la letra especificada
		if (actual->dato.palabra[0] == letra) {
			archivo << actual->dato.palabra << " - Apariciones: " << actual->dato.apariciones << endl;
		}
		actual = actual->siguiente;
	}
	gotoxy(28,15);
	cout<<"!Se genero Correctamente el Archivo!";
	archivo.close();
}


