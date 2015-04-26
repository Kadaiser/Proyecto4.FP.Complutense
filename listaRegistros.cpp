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
	int posicion;
	int ini = 0, fin = registros.contador-1, mitad;
	
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < registros.registro[mitad].identificador){
		fin = mitad - 1;
		}
		else if(registros.registro[mitad].identificador < id){
		ini = mitad + 1;
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) posicion = mitad;
	else posicion = ini;
	
	return posicion;
}