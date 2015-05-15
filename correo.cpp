#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

#include "fecha.h"
#include "correo.h"

void correoNuevo(tCorreo &correo, string emisor){

		correo.fecha = time(0);
		correo.emisor= emisor;
		correo.identificador = correo.emisor + "_" + to_string(correo.fecha);
		correoDestino(correo.destinantario);
		correoAsunto(correo.asunto);
		correoCuerpo(correo.cuerpo);
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){
}

string aCadena(const tCorreo &correo){
	return correo.cuerpo;
}

string obtenerCabecera(const tCorreo &correo){
	string cabecera;

	cabecera = "De: " + correo.emisor + "\t";
	cabecera += mostrarFecha(correo.fecha) + "\n";
	cabecera += "Para: " + correo.destinantario + "\n";
	cabecera += "Asunto: " + correo.asunto + "\n\n";

	return cabecera;
}

bool cargar(tCorreo &correo, ifstream& archivo){
	bool ok= true;
	string cuerpo, fecha;
	
	archivo >> correo.identificador;
	if(correo.identificador == CENTINELACORREO) ok = false;
	else{
		archivo >> correo.fecha;
		getline(archivo, fecha);
		getline(archivo, correo.emisor);
		getline(archivo, correo.destinantario);
		getline(archivo, correo.asunto);		
		leerCuerpo(correo.cuerpo, archivo);
	}
	return ok;
}

void guardar(const tCorreo &correo, ofstream& archivo){
	archivo << correo.identificador << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinantario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo;
	archivo << 'X' << endl;
}

/*void leerCuerpo(string& cuerpo, ifstream& archivo){
	string centinela, linea;
	do{
		centinela = archivo.get();
		if(centinela != CENTINELACUERPO){
		cuerpo += centinela;
		getline(archivo, linea);
		cuerpo += linea + '\n';
		}
	}while(centinela != CENTINELACUERPO);
}*/

void leerCuerpo(string& cuerpo, ifstream& archivo){
	string linea = "";

	cuerpo = "";
	getline(archivo, linea);
	while(linea != CENTINELACUERPO){
		cuerpo += linea + '\n';
		getline(archivo, linea);
	}
}

void correoDestino(string& destinatario){
	cout << "Introduce la direccion del destinatario: ";
	cin >> destinatario;
	cin.sync();
}

void correoAsunto(string& asunto){
	cout << "Introduce el asunto (una linea): ";
	getline(cin, asunto);
	cin.sync();
}

void correoCuerpo(string& cuerpo){
	string linea;
	stringstream flujo;
	cout << "Escribe tu mensaje (XXX para terminar): " << endl;
		do{
			getline(cin, linea);
			if(linea != CENTINELACORREO)flujo << linea << endl;
		}while(linea != CENTINELACORREO);
	cuerpo=flujo.str();
}

void verCorreo(tCorreo correo){
	string cabecera, cadena;

	cabecera = obtenerCabecera(correo);
	cadena = aCadena(correo);

	cout << cabecera << cadena << endl;
}