#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "listaRegistros.h"


void inicializar(tListaRegistros &registros){
	registros.contador = 0;
}

void cargar(tListaRegistros &registros, ifstream& archivo){
	int elementos;
	tRegistro registro;
	
	inicializar(registros);
	archivo >> elementos;
	if(elementos>0){
		for(int i = 0; i < elementos; i++){
			cargarRegistro(registro, archivo);
			insertar(registros, registro);
		}
	}
}

void guardar(const tListaRegistros &registros, ofstream& archivo){
	for(int i= 0; i < registros.contador; i++){
		archivo << registros.registro[i].identificador << " " << registros.registro[i].leido << endl;
	}
}

bool insertar(tListaRegistros &registros, tRegistro registro){
	bool ok = false;
	if(registros.contador < MAXREGISTROS){
		registros.registro[registros.contador] = registro;
		registros.contador++;
		ok = true;
	}
	return ok;
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


void cargarRegistro(tRegistro& registro, ifstream& archivo){
		archivo >>registro.identificador;
		archivo >>registro.leido;
}