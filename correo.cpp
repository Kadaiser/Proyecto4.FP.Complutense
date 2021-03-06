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
		correoDestino(correo.destinatario);
		correoAsunto(correo.asunto);
		correoCuerpo(correo.cuerpo);
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){
		string cuerpoRespuesta; //la respuesta del usuario a un correo se concatenara en un unico string junto el anterior mensaje
		correo.fecha = time(0);
		correo.emisor = emisor;
		correo.identificador = correo.emisor + "_" + to_string(correo.fecha);
		correo.destinatario = correoOriginal.emisor;
		correo.asunto = "Re: " + correoOriginal.asunto;
		
		correoCuerpo(cuerpoRespuesta);
		correo.cuerpo = cuerpoRespuesta;
		for(int i=0; i<80;i++) correo.cuerpo += "-"; //se incorpora una linea separatoria del anterior correo y la constestacion
		correo.cuerpo += obtenerCabecera(correoOriginal);
		correo.cuerpo += correoOriginal.cuerpo;
}

string aCadena(const tCorreo &correo){
	string aCorreo, cadena;

	aCorreo = obtenerCabecera(correo);
	aCorreo += correo.cuerpo; //se concatena toda la informacion del correo en un unico string
	return aCorreo;
}

string obtenerCabecera(const tCorreo &correo){
	string cabecera;

	cabecera = "De: " + correo.emisor + "\t";
	cabecera += mostrarFecha(correo.fecha) + "\n";
	cabecera += "Para: " + correo.destinatario + "\n";
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
		getline(archivo, correo.destinatario);
		getline(archivo, correo.asunto);		
		leerCuerpo(correo.cuerpo, archivo);
	}
	return ok;
}

void guardar(const tCorreo &correo, ofstream& archivo){
	archivo << correo.identificador << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo;
	archivo << CENTINELACUERPO << endl;
}

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
			if(linea != CENTINELACORREO){
				flujo << linea << endl;
			}
		}while(linea != CENTINELACORREO); //El centinela sera reconocido UNICAMENTE en una linea que SOLO contenga el centinela
	cuerpo=flujo.str();
}


bool operator< (const tCorreo & correo1, const tCorreo & correo2){
	bool esMenor = true;
	tCorreo correo1aux = correo1;
	tCorreo correo2aux = correo2;
	
	quitarRe(correo1aux);
	quitarRe(correo2aux);//Se generan copias auxliares para poder eliminar los "Re: " de los asuntos
	
		if(correo2aux.asunto < correo1aux.asunto)
			esMenor = false;
		else if(correo2aux.asunto == correo1aux.asunto){
			if(correo2aux.fecha < correo1aux.fecha)
				esMenor = false;
			}
	return esMenor;
}

void quitarRe(tCorreo & correo){
	string asuntoAux = correo.asunto;
	bool esRespuesta =(asuntoAux.substr (0,4) == "Re: ");
	
	while(esRespuesta){ //minetras se identifique el patron "Re: " en los primeros 4 caracteres del string
	asuntoAux.erase (0,4); //Se elimina "Re: "
	esRespuesta =(asuntoAux.substr (0,4) == "Re: "); 
	}
	correo.asunto = asuntoAux; //Se sustitulle el anterior asunto por el nuevo sin "Re: "
}