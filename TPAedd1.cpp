#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <iomanip>
#include "archivo.h"
#include "Libro.h"
#include <cctype>
#include <fstream>
#include <map>
#include <conio.h>
using namespace std;

const int tam=1000;

void Abecedario(int x); 
void mostrarrangovector (char v[],int rango, int tam);
void mostrarrangovectormayusculas (char v[],int rango, int tam);
int PuntajeB(int totalVocales,int b);
string palabraMasLarga(string palabras[]);
int contarVocales(string palabras[]);
char letraMasRepetida(string palabras[]);
void mostrardisplay(string display,int aum);
void Inicio(string linea[]);
void logo();
void IPA();	
void MenuJuegos(string linea[]);
void Menu(string linea[]);
void Menuabecedario(string linea[]);
void Ahorcado(string linea[]);
void Memorias(string linea[]);
void PalabraCifrada(string linea[]);
void NumeroEnIdiomas(string linea[]);
string cifrarPalabra(const string & palabra, int offset);
void temporizador(int);
void NombreEnIdioma(int n,int idioma);
string Segmentos(int n);
void CargarPalabras(string linea[]);
double PuntajeA(char letraComun,string a);
int puntajeC(string palabraLarga,string c,string palabrasAleatorias[] );
void procesadorTxt(string linea[]);
bool LeerArchivoBinario(int login,string password,bool &bandera);
void CrearArchivoBinario();
void EstadisticasPorCaracter(string linea[]);
void EstadisticaPorPalabra(string linea[]);
bool archivoBinCargado(string nombre);
void GenerararchivoTextoLista(nodo *lista);
	
int main(int argc, char *argv[]) {
	string linea[tam]={};
	separador1();
	srand(time(NULL));
	clock_t t;
	t=clock();
	system("color 09");
	system("mode con: cols=100 lines=30");
	IPA();
	CargarPalabras(linea);
	Inicio(linea);
	temporizador((clock()-t));
	
	return 0;
}

//funcion para cargar las palabras Del archivo Txt
void CargarPalabras(string linea[]){
	
	archivo Entrada;
	system("cls");
	separador1();
	Entrada=setup("Ahorcado en Español", "Palabras-2.txt");
	
	if (apertura(Entrada)==false){
		gotoxy(1,1);
		cout << "Error en apertura de archivo";
	}
	else {
		int j=0;
		// leo todas las lineas hasta final del archivo
		bool final=false;
		do {
			linea[j]= leerLinea(Entrada, final);
			j++;
		} while (not final);
	}
	cierre(Entrada);
	
	
	
}

//Funcion para saber el tiempo que se estuvo en la aplicacion
void temporizador(int t){
	system ("cls");
	separador1();
	gotoxy(38,1);
	cout<<"Hasta luego!";
	gotoxy(3,3);
	//
	t=((int)t)/CLOCKS_PER_SEC;
	gotoxy(3,5);
	cout<<"Duracion de la sesion: "<<t/60<<" minutos y "<<t%60<<" segundos";
	gotoxy(30,25);
}

//Funcion para Inciar sesion			
bool archivoBinCargado(string nombre){
	fstream archivo;
	bool bandera=false;
	archivo.open(nombre,ios::in);
	if(archivo.fail()){
		return bandera;
	}
	else{
		archivo.seekg(0,ios::end);//movemos el puntero lectura al final del archivo
		streampos tam=archivo.tellg(); //pos actual del puntero (tam archivo);ver streampos o streamsize cual es mas convenientes
		if(tam==0){
		    return bandera;
		}
		else{
			bandera=true;
			
		}
	}
	archivo.close();
	
	return bandera;
	
}	
void CrearArchivoBinario(){
	
	
	string nombre="Usuarios.bin";
	if(!archivoBinCargado(nombre)){
		
		ofstream archivoBinario(nombre,ios::binary);
		
		
		if (archivoBinario.fail()) {
			cout << "Error al abrir el archivo binario" << endl;
		} else {
			ifstream archivoTexto("Usuarios.txt");
			if (!archivoTexto) {
				cout << "Error al abrir el archivo de texto" << endl;
				archivoBinario.close();
			} else {
				
				datos persona;
				
				while (archivoTexto >> persona.nombre >> persona.apellido >> persona.sexo >> persona.legajo >>
					   persona.contrasena >> persona.rol >> persona.ultimoAccesoFecha.dia >>
					   persona.ultimoAccesoFecha.mes >> persona.ultimoAccesoFecha.anio >>
					   persona.ultimoAccesoHora.hora >> persona.ultimoAccesoHora.minutos >>
					   persona.ultimoAccesoHora.segundos) {
					
					// Escribir la estructura en el archivo binario
					archivoBinario.write((char*)(&persona), sizeof(datos));
					
				}
				
				archivoTexto.close();
			}
		}
		
		archivoBinario.close();
		
	}
	
}


bool LeerArchivoBinario(int login,string password,bool &bandera){
	
	fstream archivoBinarioLectura("Usuarios.bin", ios::binary | ios::in | ios::out);
	if (!archivoBinarioLectura) {
		cout << "Error al abrir el archivo binario para lectura" << endl;
		
	} else {
		datos usuario;
		bool encontrado=false;
		while ((!archivoBinarioLectura.eof()) and encontrado == false) {
			int posicion=archivoBinarioLectura.tellg();
			archivoBinarioLectura.read((char*)(&usuario), sizeof(datos));
			
			if(usuario.legajo==login){
				
				bandera=true;
				int i=0;
				while(usuario.rol[i]!='\0'){
					password= password + usuario.rol[i];
					i++;
				}
			}
			
			if(usuario.legajo==login and strcmp(usuario.contrasena,password.c_str())==0){
				
				encontrado=true;
				system("cls");
				
				separador1();
				int x=30,y=3;
				gotoxy(x,y);
				cout<<"Bienvenido/a "<<usuario.nombre<<" !";
				gotoxy(x,y++);
				y++;
				gotoxy(x,++y);
				cout<<"Ultimo acceso a la aplicacion: "<<usuario.ultimoAccesoFecha.dia<<'/'<<usuario.ultimoAccesoFecha.mes<<'/'<<usuario.ultimoAccesoFecha.anio;
				gotoxy(x,++y);
				gotoxy(x,++y);
				gotoxy(x,++y);
				
				//Aca Codificamos La actualizacion con la fecha reciente de inicializacion;
				time_t now=time(0);
				tm * time =localtime(&now);
				fecha actual;
				hora actual2;
				actual2.hora=time->tm_hour;
				actual2.minutos=time->tm_min;
				actual2.segundos=time->tm_sec;
				actual.anio=(time->tm_year%100)+2000;
				actual.dia=time->tm_mday;
				actual.mes=time->tm_mon + 1 ;
				
				
				
				
				datos usuario2=usuario;
				usuario2.ultimoAccesoFecha=actual;
				usuario2.ultimoAccesoHora=actual2;
				//pasarle la posicion de la linea a la cual vamos actualizar
			
				archivoBinarioLectura.seekp(posicion);
				archivoBinarioLectura.write((char *)(& usuario2),sizeof(datos)); //pasarle el tam de la info a agregar
			
				
				system("pause");
				system("cls");
				separador1();
				
			}
			
		}
		
		archivoBinarioLectura.close();
		
		return encontrado;
		
	}
	
	return false;
	
}
void Inicio(string linea[]) {
	separador1();
	int intentos = 0;
	CrearArchivoBinario();
	string usuario, contrasenia = "nada";
	bool bandera = false, bandera1 = false;
	
	while (intentos <= 3 && !bandera) {
		int legajo;
		gotoxy(30, 2);
		cout << "Inicie sesion ingresando Numero de legajo: ";
		gotoxy(30, 4);
		cout<<"-------------------------------";
		gotoxy(40, 3);
		cin >> usuario;
		
		while (!bandera1 && intentos < 3) {
			bool acceso = false;
			separador1();
			gotoxy(30, 2);
			cout << "Inicie sesion ingresando Numero de legajo: ";
			
			legajo = ((usuario[0] - '0') * 10000) + ((usuario[1] - '0') * 1000) + ((usuario[2] - '0') * 100) + ((usuario[3] - '0') * 10) + ((usuario[4] - '0'));
			
			LeerArchivoBinario(legajo, contrasenia, acceso);
			
			if (legajo < 10000 || legajo > 89999 || !acceso) {
				gotoxy(40, 5);
				cout << "                                 ";
				gotoxy(30, 3);
				cout << "El numero de legajo es Incorrecto! Vuelva a intentarlo: ";
				intentos++;
				gotoxy(30, 6);
				cout<<"-------------------------------";
				gotoxy(40, 5);
				cin >> usuario;
				
			} else {
				bandera1 = true;
			}
		}
		
		if (intentos < 3) {
			gotoxy(30, 7);
			cout << "Ingrese su contrasenia: ";
			gotoxy(40, 11);
			contrasenia = "";
			char ch;
			while ((ch = _getch()) != 13) { // 13 es el código ASCII de la tecla Enter
				if (ch == 8) { // 8 es el código ASCII de la tecla Backspace
					if (contrasenia.length() > 0) {
						cout << "\b \b";
						contrasenia.pop_back();
					}
				} else {
					cout << '*';
					contrasenia += ch;
				}
			}
		}
		
		while (!bandera && intentos < 3) {
			separador1();
			
			bool n;
			if (LeerArchivoBinario(legajo, contrasenia, n)) {
				bandera = true;
				
				system("cls");
				Menu(linea);
			} else {
				intentos++;
				gotoxy(30, 9);
				cout << "Contrasenia Incorrecta!";
				gotoxy(40, 11);
				cout << "                               ";
				gotoxy(40, 11);
				contrasenia = "";
				char ch;
				while ((ch = _getch()) != 13) {
					if (ch == 8) {
						if (contrasenia.length() > 0) {
							cout << "\b \b";
							contrasenia.pop_back();
						}
					} else {
						cout << '*';
						contrasenia += ch;
					}
				}
			}
		}
		
		if (intentos == 3) {
			system("cls");
			system("color 04");
			separador1();
			gotoxy(30, 4);
			cout << "Error de Inicio, has agotado todos tus intentos";
			gotoxy(30, 28);
			system("pause");
			intentos++;
		}
	}
}
//Funcion de Logo de TP	
void IPA(){
	int x=17,y=8;
	separador1();
	gotoxy(40,1);
	cout<<"Idiomas Para Aprender";
	for(int i=1;i<99;i++){
		gotoxy(i,2);
		cout<<"=";
	}
	for(int i=16;i<84;i++){
		gotoxy(i,8);
		cout<<"*";
	}
	for(int i=8;i<20;i++){
		gotoxy(16,i);
		cout<<"*";
	}
	for(int i=16;i<84;i++){
		gotoxy(i,19);
		cout<<"*";
	}
	for(int i=8;i<20;i++){
		gotoxy(84,i);
		cout<<"*";
	}
	gotoxy(x,++y);
	cout<<":::::::           :::::::::::::::::::               :::::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::       :::::             :::::    ::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::       :::::            ::::::    :::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::       :::::           :::::::    ::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::       :::::           :::::::    ::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::::::::::::::           :::::::::::::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::                       :::::::    ::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::                       :::::::    ::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::                       :::::::    ::::::: ";
	gotoxy(x,++y);
	cout<<":::::::           :::::::                       :::::::    ::::::: ";
	gotoxy(30,26); 
	system("pause");
	system("cls");
	logo();
}
//Funcion origina el Logo del TP
void logo() {
	int y = 0;
	int x = 37;
	separador1();
	gotoxy(x, ++y);
	cout << "*****       *****       *****\n";
	gotoxy(x, ++y);
	
	cout << " *****      *****      *****\n";
	gotoxy(x, ++y);
	
	cout << "  *****     *****     *****\n";
	gotoxy(x, ++y);
	cout << "   *****    *****    *****\n";
	gotoxy(x, ++y);
	cout << "    *********************\n";
	gotoxy(x, ++y);
	cout << "     *******************\n";
	gotoxy(x, ++y);
	cout << "      *****************\n";
	gotoxy(x, ++y);
	cout << " ***************************\n";
	gotoxy(x, ++y);
	cout << " ***************************\n";
	gotoxy(x, ++y);
	cout << " ***************************\n";
	gotoxy(x, ++y);
	cout << " ***************************\n";
	gotoxy(x, ++y);
	cout << "      *****************\n";
	gotoxy(x, ++y);
	cout << "     *******************\n";
	gotoxy(x, ++y);
	cout << "    *********************\n";
	gotoxy(x, ++y);
	cout << "   *****    *****    *****\n";
	gotoxy(x, ++y);
	cout << "  *****     *****     *****\n";
	gotoxy(x, ++y);
	cout << " *****      *****      *****\n";
	gotoxy(x, ++y);
	cout << "*****       *****       *****\n";
	gotoxy(x, ++y);
	cout << "\n";
	gotoxy(x, ++y);
	cout << " **  **    ******    **   **\n";
	gotoxy(x, ++y);
	cout << " **  **    ******    ***  **\n";
	gotoxy(x, ++y);
	cout << " **  **      **      *******\n";
	gotoxy(x, ++y);
	cout << " ******      **      **  ***\n";
	gotoxy(x, ++y);
	cout << " ******      **      **   **\n";
	gotoxy(x, ++y);
	cout << "\n";
	gotoxy(36, ++y);
	cout << "UNIVERSIDAD TECNOLOGICA NACIONAL\n";
	gotoxy(36, ++y);
	cout << "   FACULTAD REGIONAL SANTA FE\n";
	gotoxy(36, ++y);
	system("pause");
	system("cls");
	
	
}

//Funcion para llevar al Menu de Abecedario
void Menuabecedario(string &idioma,string linea[]){
	
	
	string opcion;
	int nro;
	bool aceptado= false;
	separador1();
	int y=1;
	//imprime toda las opciones para elegir
	gotoxy(36,y);
	cout<<"M E N U   A B E C E D A R I O"<<endl;
	for(int i=1;i<99;i++){
		gotoxy(i,2);
		cout<<"=";
	}
	int x=30;
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"1.- Espa"<<char(164)<<"ol    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"2.- Ingles    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"3.- Italiano    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"4.- Portugues    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"5.- Frances    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"X.- Volver al menu principal ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"Ingrese una opcion:     ";
	//valida que la opcion sea la correcta
	while(aceptado==false){
		cin>>opcion;
		
		if(opcion=="x" or opcion=="X"){
			
			system("cls");
			Menu(linea);
			aceptado=true;
		}else 
		   if(opcion=="1"){
			nro=1;
			idioma="Espanol" ;
			aceptado=true;
		}else 
			  if(opcion=="2"){
			   nro=2;
			   idioma="Ingles";
			   aceptado=true;
		   }else 
				 if(opcion=="3"){
				  nro=3;
				  idioma="Italiano";
				  aceptado=true;
			  }else
					if(opcion=="4"){
					 nro=4;
					 idioma="Portugues";
					 aceptado=true;
				 }else
					   if(opcion=="5"){
						nro=5;
						idioma="Frances";
						aceptado=true;
					}else {
						   system("cls");
						   separador1();
						   int y=1;
						   gotoxy(36,y);
						   cout<<"M E N U   A B E C E D A R I O";
						   gotoxy(36,++y);
						   for(int i=1;i<99;i++){
							   gotoxy(i,2);
							   cout<<"=";
						   }
						   int x=30;
						   gotoxy(x,++y);
						   cout<<"1.- Espa"<<char(164)<<"ol    ";
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   cout<<"2.- Ingles    ";
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   cout<<"3.- Italiano    ";
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   cout<<"4.- Portugues    ";
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   cout<<"5.- Frances    ";
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   gotoxy(x,++y);
						   cout<<"X.- Volver al menu principal ";
						   gotoxy(15,++y);
						   gotoxy(15,++y);
						   gotoxy(15,++y);
						   cout<<"Ingreso una opcion invalida, por favor vuelva a ingresar otra opcion: ";
						   gotoxy(x,++y);
					   }
					   
	}
	system("cls");
	separador1();
	gotoxy(3,4);
	Abecedario(nro);
	gotoxy(30,28);
	system("pause");
	system("cls");
	separador1();
	Menu(linea);
	
}
//Funcion que enseña el abecedario en difierentes idiomas
void Abecedario(int x){
	int y=2;
	//A partir de acá y hasta el final del primer switch, es todo el programa hecho con vectores.
	char a;
	//declaro los vectores alfabeto
	char letras[30];
	char letrasM[30];
	//declaro los vectores caracteres especiales
	char caracteres_especiales_espanol[100]={char(160), (char)130, (char)161, (char)162, (char)163, (char)129};
	char caracteres_especiales_ingles[100]={};
	char caracteres_especiales_italiano[100]={(char)133, (char)138, (char)130, (char)141, (char)161, (char)140, (char)149, (char)162, (char)151, (char)163};
	char caracteres_especiales_portugues[100]{(char)133, (char)138, (char)131, (char)135, (char)130, (char)136, (char)161 ,(char)162, (char)147, (char)163};
	char caracteres_especiales_frances[100]={(char)133, (char)131, (char)145, (char)135, (char)130, (char)138, (char)136, (char)137, (char)140, (char)139, (char)147,(char)151, (char)150, (char)129,(char)152};
	
	//cargo los alfabetos ingles, portugues y frances
	for(a='a';a<='z';a++){
		letras[a-'a']=a;
	}
	
	gotoxy(4,y++);
	//En cada renglón no puede haber más de 10 caracteres
	//(a excepción de los títulos obvio)
	switch (x){
	case 1:cout<<"Alfabeto  Espa"<<char(164)<<"ol en minusculas: ";
	//cargo el alfabeto español 
	for(a='a';a<='n';a++){
		letras[a-'a']=a;
	}
	
	letras[14]=char(164);
	for(a='o';a<='z';a++){
		letras[a-'a'+1]=a;
	}
	
	for(a='A';a<='N';a++){
		letrasM[a-'A']=a;
	}
	
	letrasM[14]=char(165);
	for(a='O';a<='Z';a++){
		letrasM[a-'A'+1]=a;
	}
	
	cout<<endl;
	gotoxy(4,y++);
	mostrarrangovector(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovector(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovector(letras, 20,27);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Alfabeto  Espa"<<char(164)<<"ol en mayusculas: ";
	gotoxy(4,y++);
	mostrarrangovector(letrasM, 0, 10);
	gotoxy(4,y++);
	mostrarrangovector(letrasM, 10,20);
	gotoxy(4,y++);
	mostrarrangovector(letrasM, 20,27);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Letras minisculas acentuadas: ";
	gotoxy(4,y++);
	mostrarrangovector(caracteres_especiales_espanol,0,7);
	
	break;
	
	case 2:cout<<"Alfabeto ingles en minusculas: ";
	//cargo los alfabetos ingles
	for(a='a';a<='z';a++){
		letras[a-'a']=a;
	}
	gotoxy(4,y++);
	mostrarrangovector(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovector(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovector(letras, 20,26);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Alfabeto ingles en mayusculas: ";
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 20,26);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Letras minusculas acentuadas: ";
	gotoxy(4,y++);
	mostrarrangovector(caracteres_especiales_ingles,0, 7);
	
	break;
	
	case 3:cout<<"Alfabeto italiano en minusculas: ";
	
	//cargo el alfabeto italiano
	for( a='a';a<='i';a++){
		letras[a-'a']=a;
	}
	for( a='l';a<='v';a++){
		letras[a-'a'-2]=a;
	}
	letras[20]='z';
	gotoxy(4,y++);
	mostrarrangovector(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovector(letras, 10,20);
	gotoxy(4,y++);
	cout<<letras[20];
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Alfabeto italiano en mayusculas: ";
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 10,20);
	gotoxy(4,y++);
	cout<<char(toupper(letras[20]));
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Letras minusculas acentuadas: ";
	gotoxy(4,y++);
	mostrarrangovector(caracteres_especiales_italiano,0, 10);
	
	break;
	
	case 4:cout<<"Alfabeto portugues en minusculas: ";
	//cargo los alfabetos portugues
	for(a='a';a<='z';a++){
		letras[a-'a']=a;
		
	}
	gotoxy(4,y++);
	mostrarrangovector(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovector(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovector(letras, 20,26);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Alfabeto portugues en mayusculas: ";
	gotoxy(4,y++);;
	mostrarrangovectormayusculas(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 20,26);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Letras minusculas acentuadas: ";
	gotoxy(4,y++);
	mostrarrangovector(caracteres_especiales_portugues,0, 10);
	break;
	
	case 5 :cout<<"Alfabeto frances en minusculas: ";
	//cargo los alfabetos frances
	for(a='a';a<='z';a++){
		letras[a-'a']=a;
	}
	gotoxy(4,y++);
	mostrarrangovector(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovector(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovector(letras, 20,26);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Alfabeto frances en mayusculas: ";
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 0, 10);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 10,20);
	gotoxy(4,y++);
	mostrarrangovectormayusculas(letras, 20,26);
	gotoxy(4,y++);
	gotoxy(4,y++);
	cout<<"Letras minusculas acentuadas: ";
	gotoxy(4,y++);
	mostrarrangovector(caracteres_especiales_frances,0, 15);
	break;
    }
}
//funcion para mostrar el vector donde se carga el Abecedario
void mostrarrangovector (char v[],int rango, int tam){
	
	for (int i=rango;i<tam;i++)
		cout<<v[i]<<" ";
}
//funcion para mostrar el vector donde se carga el Abecedario en Mayusculas	
void mostrarrangovectormayusculas (char v[], int rango, int tam){
	for (int i=rango;i<tam;i++){
		cout<<char(toupper(v[i]))<<" ";
	}
}	
//Funcion de Menu de la aplicacion
void Menu(string linea[]){
	system("color 07");
	string menu;
	string idioma;
	bool aceptado=false;
	int y=1;
	separador1();
	gotoxy(46,y);
	cout<< "M E N U ";
	int x=30;
	for(int i=1;i<99;i++){
		gotoxy(i,2);
		cout<<"=";
	}
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"1.- Abecedario ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"2.- Juegos ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"3.- Procesador de texto ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"X.- Salir de la aplicacion : ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"Seleccione una Opcion: ";
	
	while(aceptado==false){
		cin>>menu;
		//validacion
		if(menu=="X" or menu=="x"){
			
			string s;
			system("cls");
			separador1();
			gotoxy(40,10);
			gotoxy(40,11);
			cout<<"Desea salir ?";
			gotoxy(40,13);
			gotoxy(40,14);
			gotoxy(40,15);
			cout<<" si(1) o No(0)  ";
			cin>>s;
			
			while(s!="1" and s!="0"){
				system("cls");
				separador1();
				gotoxy(40,10);
				gotoxy(40,11);
				cout<<"Desea salir ?";
				gotoxy(40,13);
				gotoxy(40,14);
				gotoxy(40,15);
				cout<<" si(1) o No(0)  ";
				gotoxy(15,16);
				cout<<"Ingreso una opcion invalida, por favor vuelva a ingresar otra opcion: ";
				gotoxy(40,17);
				cin>>s;
			}
			if(s=="1"){
				system("cls");
			}
			else if(s=="0"){
				system("cls");
				Menu(linea);
			}
			aceptado=true;
		}
		else if(menu=="1"){
			system("cls");
			Menuabecedario(idioma,linea);
			aceptado=true;
		}
		else if(menu=="2"){
			system("cls");
			MenuJuegos(linea);
			aceptado=true;
		}
		else if(menu=="3"){
			system("cls");
			procesadorTxt(linea);
			aceptado=true;
		}
		else {
			system("cls");
			separador1();
			int y=1;
			gotoxy(46,y);
			cout<< "M E N U ";
			int x=30;
			for(int i=1;i<99;i++){
				gotoxy(i,2);
				cout<<"=";
			}
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"1.- Abecedario ";
			gotoxy(x,++y);
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"2.- Juegos ";
			gotoxy(x,++y);
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"3.- Procesador de texto ";
			gotoxy(x,++y);
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"X.- Salir de la aplicacion : ";
			gotoxy(15,++y);
			gotoxy(15,++y);
			gotoxy(15,++y);
			cout<<"Ingreso una opcion invalida, por favor vuelva a ingresar otra opcion: ";
		}
	}
}
//Funcion la cual me lleva al Menu de Juegos
void MenuJuegos(string linea[]){
	system("color 07");
	bool aceptado = false;
	string opcion;
	
		separador1();
		int y=1;
		gotoxy(40,y);
		cout<<"M E N U   J U E G O S"<<endl;
		int x=30;
		for(int i=1;i<99;i++){
			gotoxy(i,2);
			cout<<"=";
		}
		gotoxy(x,++y);
		gotoxy(x,++y);
		cout<<"1.- Ahorcado    ";
		gotoxy(x,++y);
		gotoxy(x,++y);
		gotoxy(x,++y);
		cout<<"2.- Palabra cifrada    ";
		gotoxy(x,++y);
		gotoxy(x,++y);
		gotoxy(x,++y);
		cout<<"3.- Numero en otro idioma    ";
		gotoxy(x,++y);
		gotoxy(x,++y);
		gotoxy(x,++y);
		cout<<"4.- Memoria    ";
		gotoxy(x,++y);
		gotoxy(x,++y);
		gotoxy(x,++y);
		cout<<"X.- Volver al menu principal ";
		gotoxy(x,++y);
		gotoxy(x,++y);
		gotoxy(x,++y);
		cout<<"Ingrese una opcion:     ";
		
		gotoxy(x,++y);
		gotoxy(x,++y);
	while(aceptado==false){
		cin>>opcion;
		
		if(opcion=="X" or opcion=="x"){
			
			system("cls");
			Menu(linea);
			aceptado=true;
		}else 
		   if(opcion=="1"){
			system("cls");
			Ahorcado(linea);
			aceptado=true;
		}else 
			  if(opcion=="2"){
			   system("cls");
			   PalabraCifrada(linea);
			   aceptado=true;
		   }else 
				 if(opcion=="3"){
				  system("cls");
				  NumeroEnIdiomas(linea);
				  aceptado=true;
			  }else
					if(opcion=="4"){
					 system("cls");
					 Memorias(linea);
					 aceptado=true;
				 }else{ 
					system("cls");
					separador1();
					int y=1;
					gotoxy(40,y);
					cout<<"M E N U   J U E G O S"<<endl;
					int x=30;
					for(int i=1;i<99;i++){
						gotoxy(i,2);
						cout<<"=";
					}
					gotoxy(x,++y);
					gotoxy(x,++y);
					cout<<"1.- Ahorcado    ";
					gotoxy(x,++y);
					gotoxy(x,++y);
					gotoxy(x,++y);
					cout<<"2.- Palabra cifrada    ";
					gotoxy(x,++y);
					gotoxy(x,++y);
					gotoxy(x,++y);
					cout<<"3.- Numero en otro idioma    ";
					gotoxy(x,++y);
					gotoxy(x,++y);
					gotoxy(x,++y);
					cout<<"4.- Memoria    ";
					gotoxy(x,++y);
					gotoxy(x,++y);
					gotoxy(x,++y);
					cout<<"X.- Volver al menu principal ";
					gotoxy(15,++y);
					gotoxy(15,++y);
					gotoxy(15,++y);
					cout<<"Ingreso una opcion invalida, por favor vuelva a ingresar otra opcion: ";
					gotoxy(x,++y);
					}
	}
	
	
}
//Funcion Juego Ahorcado
void Ahorcado(string linea[]){
	// Palabra a adivinar
	bool salir=false;
	int x=1,y=1;
	string palabraSecreta=linea[rand()%102];
	separador1();
	gotoxy(x,1);
	
	// Limpiar la pantalla
	system("cls"); // En Windows
	separador1();
	// Inicializar variables
	
	string palabraAdivinada(palabraSecreta.length(),'-' );
	int intentosRestantes = 6;
	int totaldepuntos=100;
	string letrasUsadas;
	string letras;
	while (intentosRestantes > 0 and salir==false) {
		x=1;
		y=1;
		
		if(intentosRestantes==6){
			
			gotoxy(30,++y);
			cout<<"--------";
			gotoxy(30,++y);
			cout<<"|       |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"     ___|___";
		}else if(intentosRestantes==5){
			gotoxy(30,++y);
			cout<<" -------";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<" O      |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"     ___|___";
		}else if(intentosRestantes==4){
			gotoxy(30,++y);
			cout<<" -------";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<" O      |";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"     ___|___";
		}else if(intentosRestantes==3){
			gotoxy(30,++y);
			cout<<" -------";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<" O      |";
			gotoxy(30,++y);
			cout<<"/|      |";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"     ___|___";
		}else if(intentosRestantes==2){
			gotoxy(30,++y);
			cout<<" -------";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<" O      |";
			gotoxy(30,++y);
			cout<<"/|"<<char(92)<<"     |";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<"        |";
			gotoxy(30,++y);
			cout<<"     ___|___";
		}else if(intentosRestantes==1){
			gotoxy(30,++y);
			cout<<" -------";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<" O      |";
			gotoxy(30,++y);
			cout<<"/|"<<char(92)<<"     |";
			gotoxy(30,++y);
			cout<<" |      |";
			gotoxy(30,++y);
			cout<<"/       |";
			gotoxy(30,++y);
			cout<<"     ___|___";
		}
		x=30;
		gotoxy(30,++y);
		// Mostrar la palabra adivinada
		cout << "Palabra adivinada: ";
		gotoxy(30,y++);
		for (char letra : palabraAdivinada) {
			gotoxy(x++,y);
			cout << letra << " ";
		}
		x=1;
		gotoxy(30,++y);
		// Mostrar letras usadas
		cout << "Letras usadas: ";
		for (char letra : letrasUsadas) {
			cout << letra << " ";
		}
		
		gotoxy(30,++y);
		
		// Mostrar intentos restantes
		cout << "Intentos restantes: " << intentosRestantes;
		gotoxy(30,++y);
		// Pedir al jugador que adivine una letra
		char letra;
		
		cout << "Adivina una letra: ";
		cin >> letras;
		transform(letras.begin(),letras.end(),letras.begin(),::tolower);
		
		while(letras.length()!=1){
			gotoxy(30,13);
			cout<<"Ingreso una opcion Incorrecta!, por favor ingrese de a 1 letra";
			gotoxy(30,14);
			cin>>letras;
			gotoxy(30,14);
			cout<<"                                      ";
		}
		letra=letras[0];
		
		
		
		// Verificar si la letra ya se ha usado
		if (find(letrasUsadas.begin(), letrasUsadas.end(), letra) != letrasUsadas.end()) {
			cout << "Ya has usado esa letra. Intenta otra.";
			gotoxy(30,++y);
			
		}
		
		letrasUsadas.push_back(letra);
		
		// Verificar si la letra está en la palabra secreta
		bool letraEncontrada = false;
		int tl=palabraSecreta.length();
		for (int i = 0; i < tl ; i++) {
			if (palabraSecreta[i] == letra) {
				palabraAdivinada[i] = letra;
				letraEncontrada = true;
			}
		}
		
		if (!letraEncontrada) {
			intentosRestantes--;
			cout << "Incorrecto. Pierdes un intento.";
			totaldepuntos-=10;
			gotoxy(30,++y);
		}
		
		// Verificar si el jugador ha adivinado toda la palabra
		if (palabraAdivinada == palabraSecreta) {
			
			separador1();
			system("color 02");
			gotoxy(20,1);
			cout << "Felicidades! Has adivinado la palabra secreta: " << palabraSecreta;
			x=30;
			for (char letra : palabraAdivinada) {
				gotoxy(x++,10);
				cout << letra << " ";
			}
			gotoxy(30,++y);
			cout<<"Total de puntos= "<<totaldepuntos;
			gotoxy(30,20);
			cout<<"Enter para volver al Menu ";
			gotoxy(30,28);
			system("pause");
			system("cls");
			MenuJuegos(linea);
			salir=true;
		}
		
		
		system("cls");
		separador1();
	}
	
	if (intentosRestantes == 0) {
		x=1;
		y=1;
		gotoxy(30,++y);
		system("color 04");
		cout<<" -------";
		gotoxy(30,++y);
		cout<<" |      |";
		gotoxy(30,++y);
		cout<<" O      |";
		gotoxy(30,++y);
		cout<<" x      |";
		gotoxy(30,++y);
		cout<<"/|"<<char(92)<<"     |";
		gotoxy(30,++y);
		cout<<" |      |";
		gotoxy(30,++y);
		cout<<"/ "<<char(92)<<"   __|__";
		gotoxy(10,++y);
		cout << "Lo siento, has agotado todos tus intentos. La palabra secreta era: " << palabraSecreta;
		gotoxy(30,14);
		cout<<"Total de puntos= "<<0;
		gotoxy(30,20);
		cout<<"Enter para volver al Menu ";
		gotoxy(30,28);
		system("pause");
		system("cls");
		MenuJuegos(linea);
		
	}
}		
//Funcion Juego Palabra Cidrada 
void PalabraCifrada(string linea[]){
	
	int x=30,y=1;
	gotoxy(20,++y);
	cout << "Bienvenido al juego de adivinanza de palabras." << endl;
	bool bandera=false;
	
	string palabraSecreta=linea[rand()%102];
	separador1();
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	// Limpiar la pantalla
	system("pause");
	system("cls"); 
	separador1();
	
	
	int offset = 14; 
	string palabraCifrada = cifrarPalabra(palabraSecreta, offset);
	int intentosRestantes;
	
	if(palabraSecreta.length()*3>=15){
		intentosRestantes = palabraSecreta.length() * 2;
	}else{
		intentosRestantes = palabraSecreta.length() * 3;
	}
	
	
	while (intentosRestantes > 0 and bandera==false) {
		separador1();
		gotoxy(x,1);
		cout << "La palabra cifrada es: ";
		for(size_t i=0;i<palabraCifrada.length();i++){
			cout<<palabraCifrada[i]<<" ";
			
		}
		gotoxy(x,3);
		cout << "Intentos restantes: " << intentosRestantes;
		gotoxy(x,5);
		cout << "Ingresa una letra: ";
		
		
		char letra;
		string letras;
		cin >> letras;
		transform(letras.begin(),letras.end(),letras.begin(),::tolower);
		if(letras.length()!=1){
			intentosRestantes--;
			cout<<"Letra Incorrecta!! ";
		}else letra=letras[0];
		
		if (palabraSecreta.find(letra) == string::npos) {
		
			system("cls");
			gotoxy(x,7);
			cout << "Incorrecto. Intentalo de nuevo." << endl;
			
			intentosRestantes--;
			
			
		} else {
			int i=0;
			int tl=palabraSecreta.length();
			bool encontrada=false;
			while( i< tl and encontrada==false) {
			    if (palabraSecreta[i] == letra and palabraCifrada[i]!=letra) {
					palabraCifrada[i] = letra;
					encontrada=true; // Sale del bucle después de encontrar la primera aparición
				}
				 i++;
		    }
			
			system("cls");
			gotoxy(x,7);
			cout << "Correcto! La palabra actual es: " << palabraCifrada << endl;
			
			if (palabraCifrada == palabraSecreta) {
				separador1();
				system("color 02");
				gotoxy(x,5);
				cout << "Felicidades! Has adivinado la palabra." << endl;
				bandera=true;
			}
			
		}
		
	}
	
	if (intentosRestantes == 0) {
		
		separador1();
		system("color 04");
		gotoxy(2,2);
		cout << "Agotaste tus intentos! La palabra era: " << palabraSecreta << endl;
	}
	gotoxy(x,28);
	system("pause");
	system("cls");
	MenuJuegos(linea);
	
}
	
//Funcion por la cual ciframos la Plabra
string cifrarPalabra(const string& palabra, int offset) {
	string cifrada = palabra;
	int tl=cifrada.length();
	for (int c=0;c < tl;c++) {
		if (cifrada[c]) {
			char base = (cifrada[c]) ? 'a' : 'A';
			cifrada[c] = (cifrada[c] - base + offset) % 26 + base;
		}
	}
	return cifrada;
}

//Funcion Del Juego Numeros En Idiomas
void NumeroEnIdiomas(string linea[]){
	string numero,idiomas,aumento;
	int x=30,y=0;
	separador1();
	gotoxy(x,++y);
	cout<<"Ingrese Numero del 0 al 9: ";
	gotoxy(x,++y);
	cin>>numero;
	int n=numero[0]-'0';
	while(numero.length()!=1 or (n<0 or n>9)){
		y=1;	
		system("cls");
		separador1();
		gotoxy(x,y++);
		cout<<"Ingrese Numero del 0 al 9: ";
		gotoxy(20,y++);
		cout<<"Opcion Incorrecta!, Porfavor igrese una opcion valida: ";
		gotoxy(x,y++);
		gotoxy(x,y++);
		cin>>numero;
		n=numero[0]-'0';
	}
	gotoxy(x,++y);
	cout<<"Ingrese Idioma 1 al 5: ";
	gotoxy(x,++y);
	cout<<"1- Espaniol..";
	gotoxy(x,++y);
	cout<<"2- Ingles..";
	gotoxy(x,++y);
	cout<<"3- Italiano..";
	gotoxy(x,++y);
	cout<<"4- Portugues..";
	gotoxy(x,++y);
	cout<<"5- Frances..";
	gotoxy(x,++y);
	cin>>idiomas;
	int idioma=idiomas[0]-'0';
	while(idiomas.length()!=1 or (idioma<1 or idioma>5)){
		system("cls");
		y=1;	
		system("cls");
		separador1();
		gotoxy(x,y++);
		cout<<"Ingrese Numero del 1 al 9: ";
		gotoxy(x,y++);
		cout<<n;
		y=3;
		gotoxy(x,++y);
		cout<<"Ingrese Idioma 1 al 5: ";
		gotoxy(x,++y);
		cout<<"1- Espaniol..";
		gotoxy(x,++y);
		cout<<"2- Ingles..";
		gotoxy(x,++y);
		cout<<"3- Italiano..";
		gotoxy(x,++y);
		cout<<"4- Portugues..";
		gotoxy(x,++y);
		cout<<"5- Frances..";
		gotoxy(x,++y);
		cout<<"Opcion Incorrecta!, Porfavor igrese una opcion valida: ";
		gotoxy(x,y++);
		gotoxy(x,y++);
		cin>>idiomas;
		idioma=idiomas[0]-'0';
	}
	gotoxy(x,y++);
	cout<<"Ingresar los aumentos por segmento entre [1,4]: ";
	gotoxy(x,y++);
	gotoxy(x,y++);
	cin>>aumento;
	int aum=aumento[0]-'0';
	while(aumento.length()!=1 or (aum<1 or aum>4)){
		system("cls");
		y=1;	
		separador1();
		gotoxy(x,y++);
		cout<<"Ingrese Numero del 1 al 9: ";
		gotoxy(x,y++);
		cout<<n;
		y=3;
		
		gotoxy(x,++y);
		cout<<"Ingrese Idioma 1 al  ";
		gotoxy(x,++y);
		cout<<"1- Espaniol..";
		gotoxy(x,++y);
		cout<<"2- Ingles..";
		gotoxy(x,++y);
		cout<<"3- Italiano..";
		gotoxy(x,++y);
		cout<<"4- Portugues..";
		gotoxy(x,++y);
		cout<<"5- Frances..";
		gotoxy(x,++y);
		gotoxy(x,y++);
		cout<<idioma;
		
		
		y=13;
	
		gotoxy(x,y++);
		cout<<"Ingresar los aumentos por segmento entre [1,4]: ";
		gotoxy(x,y++);
		cout<<"Opcion Incorrecta!, Porfavor igrese una opcion valida: ";
		gotoxy(x,y++);
		gotoxy(x,y++);
		cin>>aumento;
		aum=aumento[0]-'0';
	}
	
	system("cls");
	
	

	
	
	x=30;
	y=1;
	NombreEnIdioma(n,idioma);
	gotoxy(2,3);
	cout<<"Grafica:";
	gotoxy(x,++y);
	gotoxy(x,++y);
	mostrardisplay(Segmentos(n),aum);
	gotoxy(x,28);
	system("pause");
	system("cls");
	MenuJuegos(linea);
	
	
	
}


//Funcion en la cual determina los segmentos del display
string Segmentos(int n){
	
	
	string display;
	
	if(n==0){
		display="abcdef";
	}else if(n==1){
		display="bc";
	}if(n==2){
		display="abged";
	}else if(n==3){
		display="abgcd";
	}else if(n==4){
		display="bgfc";
	}else if(n==5){
		display="afgcd";
	}else if(n==6){
		display="afgcde";
	}else if(n==7){
		display="abc";
	}else if(n==8){
		display="abcdefg";
	}else if(n==9){
		display="abgfcd";
	}
	
	return display;
	
}
											
											
//Funcion que Muestra el numero deseado en el idioma seleccionado 
void NombreEnIdioma(int n,int idioma){
	separador1();
	string numero[tam]={"cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve",
		"zero","one","two","three","four","five","six","seven", "eight","nine",
		"zero","uno","due","tre","quattro","cinque","sei","sette","otto","nove",
		"Zero", "Um", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove",
		"zéro","un","deux","trois","quatre","cinq","six","sept","huit","neuf"};
	gotoxy(30,1);
	if(idioma==1){
		cout<<"En Español "<<n<<" es :";
		cout<<numero[n];
	}else if(idioma==2){
		cout<<"En Ingles "<<n<<" es :";
		cout<<numero[n+10];
	}else if(idioma==3){
		cout<<"En Italiano "<<n<<" es :";
		cout<<numero[n+20];
	}else if(idioma==4){
		cout<<"En Portugues "<<n<<" es :";
		cout<<numero[n+(30)];
	}else if(idioma==5){
		cout<<"En Frances "<<n<<" es :";
		cout<<numero[n+(40)];
	}
	
	
}
	

//Funcion que Muestra display de 7 segmentos
void mostrardisplay(string display,int aum){
	
	char matriz[tam][tam]={};
	int tl=display.length();
	//recorre el string display, dependiendo del segmento que sea se ingresa en la matriz
	for(int i=0;i<tl;i++){
		
		if(display[i]=='a'){
		
			for(int h=2;h<=aum+1;h++){
				matriz[1][h]='-';
			}
			
		}else if(display[i]=='b'){
			
			for(int h=2;h<=aum+1;h++){
				matriz[h][aum+2]='|';
			}
			
			}else if(display[i]=='c'){
			
			for(int h=aum+3;h-(aum+3)<aum;h++){
				matriz[h][aum+2]='|';
			}
			
			}else  if(display[i]=='d'){
				
				for(int h=2;h<=aum+1;h++){
					matriz[(aum*2)+3][h]='-';
				}

			}else if(display[i]=='f'){
			
			for(int h=2;h<=aum+1;h++){
				matriz[h][1]='|';
			}
		
			}else if(display[i]=='g'){
					
				for(int h=2;h<=aum+1;h++){
					matriz[aum+2][h]='-';
				}
					
			}else if(display[i]=='e'){
			
			for(int h=aum+3;h-(aum+3)<aum;h++){
					matriz[h][1]='|';
			}
			
		}
	}
	int x=1;
	for(int i=3;i<15;i++){ //resto 3 porque arranco en 3 asi se me imprimen los numeros correctamente
		for(int j=3;j<15;j++){
			gotoxy(j,i);
			cout<<matriz[i-3][j-3];
		}
		gotoxy(++x,i);
	}
	
}
	
//Funcion del Juego Memorias
void Memorias(string linea[]){
	separador1();
	int x=30,y=2;
	string palabrasAleatorias[tam]={};
	for(int i=0;i<5;i++){
		int n=rand()%101;
		int v[5]={};
		for(int j=0;j<5;j++){
			if(n!=v[j]){
			palabrasAleatorias[i]=linea[n];
			v[i]=n;
			}
		}
		
	}
	
	gotoxy(20,y++);
	cout << "A continuacion, se mostraran 5 palabras durante 2 segundos:" << endl;
	gotoxy(x,y++);
	gotoxy(x,y++);
	gotoxy(x,y++);
	system("pause");
	// Mostrar palabras durante 2 segundos
	gotoxy(x,y++);
	for(int i=0;i<5;i++){
		gotoxy(x,y++);
		cout<<palabrasAleatorias[i];
		gotoxy(x,y++);
	}
	// Esperar 2 segundos 
	Sleep(2000);
	system("cls");
	
	separador1();
	//Calcular resultados
	char letraComun = letraMasRepetida(palabrasAleatorias);
	int totalVocales = contarVocales(palabrasAleatorias);
	string palabraLarga = palabraMasLarga(palabrasAleatorias);
	
	string a;
	int b;
	string b2;
	string c;
	y=2;
	x=20;
	gotoxy(x,y++);
	cout<<"a. Identificar la letra que mas se repite en esas palabras.";
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"b. Adivinar cuantas vocales hay en total.";
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"c. Adivinar la palabra de mayor longitud.";
	x=30;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"a: ";
	cin>>a;
	transform(a.begin(),a.end(),a.begin(),::tolower);
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"b: ";
	cin>>b2;
	transform(b2.begin(),b2.end(),b2.begin(),::tolower);
	if((b2[0]>='0' and b2[0]<='9') and (b2[1]>='0' and b2[1]<='9')){
		b= int(b2[0]-'0')*10 + int(b2[1]-'0');
	}else b=99;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"c: ";
	cin>>c;
	transform(c.begin(),c.end(),c.begin(),::tolower);
	//calcula el puntaje obtenido en las pereguntas;
	float PuntosA= PuntajeA(letraComun,a);
	float PuntosB=PuntajeB(totalVocales,b);
	float PuntosC=puntajeC(palabraLarga,c,palabrasAleatorias);
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"Puntaje de Pregunta A: ";
	cout<<PuntosA;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"Puntaje de Pregunta B: ";
	cout<<PuntosB;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"Puntaje de Pregunta C: ";
	cout<<PuntosC;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout<<"Puntaje Total:  ";
	cout<<(PuntosA+PuntosB+PuntosC)/3; 
	gotoxy(x,28);
	system("pause");
	system("cls");
	y=2;
	separador1();
	gotoxy(x,y++);
	cout<<"Las respuestas son: ";
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout << "a. La letra que mas se repite es: " << letraComun;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout << "b. El total de vocales es: " << totalVocales ;
	gotoxy(x,y++);
	gotoxy(x,y++);
	cout << "c. La palabra mas larga es: " << palabraLarga ;
	gotoxy(20,28);
	system("pause");
	system("cls");
	MenuJuegos(linea);
	
}
// Función para contar la letra que más se repite en las palabras
char letraMasRepetida(string palabras[]) {
	string todasLasPalabras ="";
	for (int i=0;i<5;i++){
		todasLasPalabras += palabras[i];
	}
	int tl=todasLasPalabras.length();
	int frecuencia[26] = {0};
	for (int i=0;i<tl;i++) {
		frecuencia[int(todasLasPalabras[i])- 'a']++;
	}
	
	char letraMasComun = ' ';
	int maxFrecuencia = 0;
	for (int i = 0; i < 26; i++) {
		if (frecuencia[i] > maxFrecuencia) {
			maxFrecuencia = frecuencia[i];
			letraMasComun = 'a' + i;
		}
	}
	
	return letraMasComun;
}

// Función para contar las vocales en las palabras
int contarVocales(string palabras[]) {
	int totalVocales = 0;
	string todasLasPalabras ="";
	
	for (int i=0;i<5;i++) {
		todasLasPalabras+=palabras[i];
	}
	int tl=todasLasPalabras.length();
	for (int i=0;i<tl;i++) {
		if(todasLasPalabras[i]=='a' or todasLasPalabras[i]=='e' or
		   todasLasPalabras[i]=='i' or todasLasPalabras[i]=='o' or 
		   todasLasPalabras[i]=='u'){
			totalVocales++;
		}
	}
	
	return totalVocales;
}
	
// Función para encontrar la palabra de mayor longitud
string palabraMasLarga(string palabras[]) {
	string palabraMasLarga = "";
	
	for(int i=0;i<5;i++){
		
		if(palabras[i].length()>palabraMasLarga.length())	
			palabraMasLarga=palabras[i];
	}
	
	return palabraMasLarga;
}

//Funcion para sacar puntaje de la pregunta B de Memorias 
int PuntajeB(int totalVocales,int b){
	
	if(((b*10)/totalVocales)>10){
		return 0;
	}else return ((b*10)/totalVocales);
	
}
	
//Funcion para sacar Puntaje en la pregunta A de Memorias
double PuntajeA(char letraComun,string a){
	
	char letra;
	double porcentajePuntos = 0;
	if(a.length()==1){
		letra=a[0];
	}else return 0;
	if (letra>='a' or letra<='z'){
	int distancia = abs(letra - letraComun);
	
	// Calcular el porcentaje de puntos
	porcentajePuntos = 100.0 - (distancia * 100.0 / ('z' - 'a'));
	porcentajePuntos/=100;
	}
	return porcentajePuntos*10;
	
}
//Funcion para sacar Puntaje en la pregunta C de Memorias
int puntajeC(string palabraLarga,string c,string palabrasAleatorias[]){
	
	for(int i=0;i<5;i++){
		if(palabrasAleatorias[i]==palabraLarga){
			
			palabrasAleatorias[i]=palabrasAleatorias[i+1];
			
			
		}
		
	}
	
	string palabra2 = palabraMasLarga(palabrasAleatorias);
	for(int i=0;i<5;i++){
		if(palabrasAleatorias[i]==palabra2){
			
			palabrasAleatorias[i]=palabrasAleatorias[i+1];
			
		}
		
	}
	string palabra3 = palabraMasLarga( palabrasAleatorias);
	for(int i=0;i<5;i++){
		if(palabrasAleatorias[i]==palabra3){
			
			palabrasAleatorias[i]=palabrasAleatorias[i+1];
			
		}
		
	}
	string palabra4 = palabraMasLarga(palabrasAleatorias);
	for(int i=0;i<5;i++){
		if(palabrasAleatorias[i]==palabra4){
			
			palabrasAleatorias[i]=palabrasAleatorias[i+1];
			
		}
		
	}
	string palabra5 = palabraMasLarga(palabrasAleatorias);
	int puntaje=0;
	if(c==palabraLarga){
		puntaje=10;
	}else if(c==palabra2){
		puntaje=8;
	}else if(c==palabra3){
		puntaje=6;
	}else if(c==palabra4){
		puntaje=4;
	}else if(c==palabra5){
		puntaje=2;
	}else if(palabraLarga.length()==palabra2.length()){
		puntaje=10;
	}
	
	return puntaje;
	
}
//Menu Procesador de Texto
void procesadorTxt(string linea[]){
//Funcion Opcion Estadisticaporcaracter	
	system("color 07");
	bool aceptado = false;
	string opcion;
	
	separador1();
	int y=1;
	gotoxy(26,y);
	cout<<"M E N U   P R O C E S A D O R   D E   T E X T O"<<endl;
	int x=30;
	for(int i=1;i<99;i++){
		gotoxy(i,2);
		cout<<"=";
	}
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"1.- Estadisticas a nivel caracteres    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"2.- Estadisticas a nivel palabras    ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"X.- Volver al menu principal ";
	gotoxy(x,++y);
	gotoxy(x,++y);
	gotoxy(x,++y);
	cout<<"Ingrese una opcion:     ";
	
	gotoxy(x,++y);
	gotoxy(x,++y);
	while(aceptado==false){
		cin>>opcion;
		
		if(opcion=="X" or opcion=="x"){
			
			system("cls");
			Menu(linea);
			aceptado=true;
		}else if(opcion=="1"){
			system("cls");
			EstadisticasPorCaracter(linea);
			aceptado=true;
		}
		else if(opcion=="2"){
			system("cls");
			EstadisticaPorPalabra(linea);
			aceptado=true;
		}
		else{ 
			system("cls");
			separador1();
			int y=1;
			gotoxy(26,y);
			cout<<"M E N U   P R O C E S A D O R   D E   T E X T O"<<endl;
			int x=30;
			for(int i=1;i<99;i++){
				gotoxy(i,2);
				cout<<"=";
			}
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"1.- Estadisticas a nivel caracteres    ";
			gotoxy(x,++y);
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"2.- Estadisticas a nivel palabras    ";
			gotoxy(x,++y);
			gotoxy(x,++y);
			gotoxy(x,++y);
			cout<<"X.- Volver al menu principal ";
			gotoxy(15,++y);
			gotoxy(15,++y);
			gotoxy(15,++y);
			cout<<"Ingreso una opcion invalida, por favor vuelva a ingresar otra opcion: ";
			gotoxy(x,++y);
		}
	}
}
	
void EstadisticasPorCaracter(string linea[]){
	
	separador1();
	string nombreArchivo = "Leaventuredipinocchio.txt"; // Nombre del archivo de texto
	procesarArchivo(nombreArchivo);
	
	system("pause");
	system("cls");
	procesadorTxt(linea);
	
}
	
	
//Funcion Opcion EstadisticaPorPalabra
void EstadisticaPorPalabra(string linea[]){
	
	MatrizPalabras matrizPalabras;
	
	// Inicializar la matriz
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 25; ++j) {
			matrizPalabras.matriz[i][j] = nullptr;
		}
	}
	// Nombre del archivo a cargar
	string nombreArchivo = "Leaventuredipinocchio.txt";
	// Cargar el archivo en la matriz
	cargarArchivoEnMatriz(matrizPalabras, nombreArchivo);
	string nombreArchivoSalida = "matriz.txt";
	// Escribir la información de la matriz en un archivo
	gotoxy(20,1);
	cout<<"!Se creo La Matriz con filas=(letras) y columnas=(Longitud)! ";
	escribirMatrizEnArchivo(matrizPalabras, nombreArchivoSalida);
	int  y = 2;
	separador1();

	gotoxy(25,++y);
	gotoxy(25,++y);
	gotoxy(25,++y);
	//longitud palabra promedio
	double promedio = longitudPromedio(matrizPalabras);
	cout << "Longitud promedio de las palabras en el archivo: " << promedio;
	gotoxy(21,++y);
	gotoxy(21,++y);
	gotoxy(21,++y);
	//letra consulta
	cout << "Ingrese la letra para buscar las palabras mas frecuentes: ";
	char letraInicial;
	string letraprimera;
	cin>>letraprimera;
	letraInicial=letraprimera[0];
	bool bandera=false;
	while(!bandera){
		if(letraInicial>='a' and letraInicial<='z'){
			bandera=true;
		}
		else if(letraInicial>='A' and letraInicial<='Z'){
			bandera=true;
		}
		else{
			system("cls");
			
			separador1();
			y = 2;
			gotoxy(25,++y);
			gotoxy(25,++y);
			gotoxy(25,++y);
			cout << "Longitud promedio de las palabras en el archivo: " << promedio;
			gotoxy(16,++y);
			gotoxy(16,++y);
			gotoxy(16,++y);
			cout << "El caracter ingresado no es una letra, por favor ingrese una letra: ";
			cin>>letraprimera;
			letraInicial=letraprimera[0];
		}
	}
	palabrasConMayorFrecuencia(matrizPalabras, letraInicial);
	y=15;
	gotoxy(20,++y);
	double porcentajeVocales = porcentajePalabrasVocales("Leaventuredipinocchio.txt");
	double porcentajeConsonantes = 100.0 - porcentajeVocales;

	// Abrir archivo de entrada
	ifstream inputFile("Leaventuredipinocchio.txt");
	gotoxy(20,y++);
	gotoxy(20,y++);
	cout << "Porcentaje de palabras que comienzan con una vocal: " << porcentajeVocales << "%" ;
	gotoxy(20,y++);
	gotoxy(20,y++);
	cout << "Porcentaje de palabras que comienzan con una consonante: " << porcentajeConsonantes << "%" ;
	gotoxy(25,y++);
	gotoxy(25,y++);
	system("pause");
	system("cls");
	y=6;
	if (!inputFile) {
		cout << "Error opening file" << endl;
	} else {
		
		// Mapa para almacenar el conteo de palabras
		nodo* conteo=NULL;
		
		// Contar las palabras en el archivo
		contarPalabras(conteo, inputFile);
		
		// Lista enlazada para almacenar las palabras ordenadas por apariciones
		nodo* lista = nullptr;
		
		// Insertar palabras en la lista ordenadamente
		insertarOrdenado(lista, conteo);
		
		separador1();
		
		GenerararchivoTextoLista(lista);
		
		gotoxy(20,y);
		cout<<"Ingrese una Letra cual sea y se generara un Archivo de texto.";
		gotoxy(6,++y);
		gotoxy(6,++y);
		cout<<"El cual tendra todas las palabras que Inicien con la letra seleccionada y su frecuencia.";
		gotoxy(29,++y);
		gotoxy(29,++y);
		gotoxy(29,++y);
		// Generar archivo para palabras que comienzan con una letra específica
		char x;
		string xstrg;
		cout << "Ingrese la letra para generar el archivo: ";
		cin >> xstrg;
		bool bandera=false;
		while(!bandera){
			if(isalpha(xstrg[0])){
				bandera=true;
			}
			else{
				system("cls");
				separador1();
				y=6;
				gotoxy(20,y);
				cout<<"Ingrese una Letra cual sea y se generara un Archivo de texto.";
				gotoxy(6,++y);
				gotoxy(6,++y);
				cout<<"El cual tendra todas las palabras que Inicien con la letra seleccionada y su frecuencia.";
				gotoxy(11,++y);
				gotoxy(11,++y);
				gotoxy(11,++y);
				cout << "El caracter ingresado no es una letra, por favor vuelva a ingresar una lerta: ";
				cin >> xstrg;
			}
		}
		x=xstrg[0];
		generarArchivoPorLetra(lista, x);
		
		
		// Liberar la memoria al final del programa
		liberarLista(lista);
	}
	
	// Cerrar archivo de entrada
	inputFile.close();
	gotoxy(30,++y);
	gotoxy(30,++y);
	gotoxy(30,++y);
	gotoxy(30,++y);
	gotoxy(30,++y);
	gotoxy(30,++y);
	system("pause");
	system("cls");
	procesadorTxt(linea);
	
}
void GenerararchivoTextoLista(nodo *lista){
	

	ofstream archivo("PalabrasyFrecuencia.txt");
	if(archivo.fail()){
		cout<<"Error"<<endl;
	}else{
		nodo *aux=lista;
		while(aux!=NULL){
			archivo<<aux->dato.palabra<<" "<<aux->dato.apariciones<<endl;
			aux=aux->siguiente;
		}
		
	}
	archivo.close();
}
	
