#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

#include "correo.h"

void correoNuevo(tCorreo &correo, string emisor){
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
		getline(archivo, correo.asunto);
		archivo >> cuerpo;
		while(cuerpo != CENTINELACUERPO){
			getline(archivo, correo.asunto);
			archivo >> cuerpo;
		}
	}
	return ok;
}

void guardar(const tCorreo &correo, ofstream& archivo){
}
