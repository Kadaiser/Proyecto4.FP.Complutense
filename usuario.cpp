#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

#include "usuario.h"


bool cargar(tUsuario& usuario, ifstream& archivo){
	bool ok= true;
	archivo >> usuario.identificador;
	if(usuario.identificador == CENTINELA) ok = false;
	else{
		archivo >> usuario.contrasenia;
		cargar(usuario.bandejaEntrada, archivo);
		cargar(usuario.bandejaSalida, archivo);
	}
	return ok;
}

void guardar(const tUsuario& usuario, ofstream& archivo){
	archivo << usuario.identificador << endl;
	archivo << usuario.contrasenia<< endl;
	archivo << usuario.bandejaEntrada.contador<< endl;
	if(usuario.bandejaEntrada.contador != 0) guardar(usuario.bandejaEntrada, archivo);
	archivo << usuario.bandejaSalida.contador<< endl;
	if(usuario.bandejaSalida.contador != 0)	guardar(usuario.bandejaSalida, archivo);
}

void inicializar(tUsuario& usuario, string id, string contrasenia){
	usuario.identificador = id;
	usuario.contrasenia = contrasenia;
	inicializar(usuario.bandejaEntrada);
	inicializar(usuario.bandejaSalida);
}

bool validarContrasenia(const tUsuario &usuario, string contrasenia){
	bool ok = false;
	if(contrasenia == usuario.contrasenia) ok = true;
return ok;
}

void mostarBandeja(const tUsuario & usuario, bool bEntrada){
	if(bEntrada){
		for(int i =  0; i< usuario.bandejaEntrada.contador; i++){
			if(!usuario.bandejaEntrada.registro[i].leido) cout << " ";
			else cout << "*";
			cout << setw(2) << "-" << setw(10) << usuario.bandejaEntrada.registro[i].identificador << setw(20) << "asunto" << setw(45) << "fecha" << endl;
		}
	}
	else{
		for(int i =0; i < usuario.bandejaSalida.contador; i++){
			cout << " "<< setw(2) << "-" << setw(10) << usuario.bandejaSalida.registro[i].identificador << setw(20) << "asunto" << setw(45) << "fecha" << endl;
			}
		}
}
