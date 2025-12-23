#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct archivo{
	string nombre;
	string nombrefisico;
	int cantidad;
}; 

struct fecha {
	int dia;
	int mes;
	int anio;
};

struct hora {
	int segundos;
	int minutos;
	int hora;
};

struct datos {
	char nombre[50];
	char apellido[50];
	char sexo;
	int legajo;
	char contrasena[5];
	char rol[10];
	fecha ultimoAccesoFecha;
	hora ultimoAccesoHora;
};


archivo setup(string nombre, string nombreF);
bool apertura(archivo X);
string leerLinea(archivo & X, bool & final);
int leidas(archivo X);
bool cierre(archivo X);
