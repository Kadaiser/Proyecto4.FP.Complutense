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
		correo.identificador = correo.emisor + "_" + to_string(correo.fecha);
		correoDestino(correo.destinantario);
		correoAsunto(correo.asunto);
		correoCuerpo(correo.cuerpo);
		cout << "El correo se ha enviado a tu bandeja de salida" << endl;
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
	do{
		centinela = archivo.get();
		if(centinela != CENTINELACUERPO){
		cuerpo += centinela;
		getline(archivo, linea);
		cuerpo += linea + '\n';
		}
	}while(centinela != CENTINELACUERPO);
}

void correoDestino(string& destinatario){
	string destinatarioExtra;
	do{
		if(destinatario !=CENTINELACORREO){
			cout << "Destinatario (Al menos uno, XXX para terminar): ";
			cin >> destinatario;
		}
	}while(destinatario == CENTINELACORREO);
	do{

		cout << endl << "Destinatario (XXX para terminar): ";
		cin >> destinatarioExtra;
		
		destinatario += " "; 
		destinatario+= destinatarioExtra;
	}while(destinatarioExtra != CENTINELACORREO);
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
