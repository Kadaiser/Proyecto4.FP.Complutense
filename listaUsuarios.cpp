#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "listaUsuarios.h"


void inicializar(tListaUsuarios &usuarios){
	usuarios.contador=0;
}


bool cargar(tListaUsuarios& usuarios, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(usuarios);
	string nombreFichero = dominio + "_" + ficheroUsuarios;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	ok = false;
	}
	else{
		tUsuario usuario;
		while (cargar(usuario,archivo)){
		aniadir(usuarios, usuario);
		}
		archivo.close();
		ok = true;
	}
	return ok;
}

void guardar(const tListaUsuarios& usuarios, string dominio){
}

bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario){
	bool ok = false;
	int pos;
	
	if(usuarios.contador >= MAXUSUARIOS);
	else{
		usuarios.usuario[usuarios.contador]= usuario;
		usuarios.contador++;
		ok =true;
	}
return ok;
}

bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion){

	int ini = 0, fin = usuarios.contador-1, mitad;
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < usuarios.usuario[mitad].identificador){
		fin = mitad - 1;
		}
		else if(usuarios.usuario[mitad].identificador < id){
		ini = mitad + 1;
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) posicion = mitad;
	else posicion = ini;
	
	return encontrado;
}
