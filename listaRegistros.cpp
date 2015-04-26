#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "listaRegistros.h"


void inicializar(tListaRegistros &registros){
	registros.contador = 0;
}

void cargar(tListaRegistros &registros, ifstream& archivo){
	inicializar(registros);
	archivo >> registros.contador;
	for(int i = 0; i < registros.contador; i++){
		//cargarRegistro();
		//añadirRegistro();
	}
}

void guardar(const tListaRegistros &registros, ofstream& archivo){
}

bool insertar(tListaRegistros &registros, tRegistro registro){
return true;
}

bool borrar(tListaRegistros &registros, string id){
return true;
}

bool correoLeido(tListaRegistros &registros, string id){
return true;
}

int buscar(const tListaRegistros &registros, string id){
	int pos = 0;
	return pos;
}