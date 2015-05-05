#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

#include "correo.h"

void correoNuevo(tCorreo &correo, string emisor){

		correo.fecha = time(0);
		correo.emisor= emisor;
		correo.identificador = correo.emisor + "_" + char(correo.fecha);
		//correoDestino(correo.destinantario);
		//correoAsunto(correo.asunto);
		//correoCuerpo(correo.cuerpo);
		
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){
}

string aCadena(const tCorreo &correo){
	string cadena;
	return cadena;
}

string obtenerCabecera(const tCorreo &correo){
	string cabecera;
	return cabecera;
}

bool cargar(tCorreo &correo, ifstream& archivo){
	bool ok= true;
	string cuerpo;
	
	archivo >> correo.identificador;
	if(correo.identificador == CENTINELACORREO) ok = false;
	else{
		archivo >> correo.fecha;
		archivo >> correo.emisor;
		archivo >> correo.destinantario;
		archivo >> correo.asunto;
		leerCuerpo(correo.cuerpo, archivo);
	}
	return ok;
}

void guardar(const tCorreo &correo, ofstream& archivo){
	archivo << correo.identificador << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinantario << endl;
	archivo << correo.asunto;
	archivo << correo.cuerpo;
	archivo << 'X' << endl;
}

void leerCuerpo(string& cuerpo, ifstream& archivo){
	string centinela, linea;
	stringstream flujo;
	do{
		centinela = archivo.get();
		if(centinela != CENTINELACUERPO){
		cuerpo += centinela;
		getline(archivo, linea);
		cuerpo += linea + '\n';
		}
	}while(centinela != CENTINELACUERPO);
}

/**
string resultado;
string nombre= “Pepe”;
stringstream flujo; // Flujo
flujo << “Hola “ << nombre << endl; // Pasamos datos al flujo
resultado=flujo.str(); // Generamos un string
// Al final resultado contendrá la cadena “Hola Pepe\n”
*/