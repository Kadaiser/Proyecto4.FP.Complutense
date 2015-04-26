using namespace std;
#include <iostream>
#include <fstream>
#include <string>

#include "listaCorreos.h"

void inicializar(tListaCorreos &correos){
	correos.contador = 0;
}

bool cargar(tListaCorreos &correos, string dominio){
return true;
}

void guardar(const tListaCorreos &correos, string dominio){
}

bool insertar(tListaCorreos &correos, const tCorreo &correo){
return true;
}

bool buscar(const tListaCorreos &correos, string id, int &pos){

	int ini = 0, fin = correos.contador-1, mitad;
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < correos.listaCorreos[mitad].identificador){			//acoto mi rango de busqueda por la derecha
		fin = mitad - 1;
		}
		else if(correos.listaCorreos[mitad].identificador < id){	//acoto mi rango de busqueda por la izquierda
		ini = mitad + 1;
		}
		else{							//Si el elemtno comparado no es mayor ni menor, entonces es el que busco.
		encontrado = true;
		}
	}
	if(encontrado) pos = mitad;			//almacena la posicion que le correpsonde en el indice de la lista
	else pos = ini;						//en caso de no encontrarlo, nos indica la posicion del indice donde deberia estar.
	
	return encontrado;
}

void ordenar_AF(tListaCorreos &correos){
}