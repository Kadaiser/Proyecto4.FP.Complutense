#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "listaCorreos.h"

void inicializar(tListaCorreos &correos){
	correos.contador = 0;
}

bool cargar(tListaCorreos &correos, string dominio){
	bool ok;
	ifstream archivo;
	inicializar(correos);
	string nombreFichero = dominio + "_" + ficheroCorreos;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	ok = false;
	}
	else{
		tCorreo correo;
		while (cargar(correo, archivo)){
		
		insertar(correos, correo);
		}
		archivo.close();
		ok = true;
	}
	return ok;
}

void guardar(const tListaCorreos &correos, string dominio){
	ofstream archivo;
	string nombreFichero = dominio + "_" + ficheroCorreos;
	
	archivo.open(nombreFichero);
	if(!archivo.is_open()){
	cout << "Error al guardar la lista de correos en el fichero" << endl;
	}
	else{
		for (int i= 0; i < correos.contador; i++){
		
		guardar(correos.correo[i], archivo);
		}
		archivo << "XXX" << endl;
		archivo.close();
	}
}

bool insertar(tListaCorreos &correos, const tCorreo &correo){
	bool ok = false;
	if(correos.contador < MAXCORREOS){	//Si hay espacio en la lista de registros, se incluye
		correos.correo[correos.contador] = correo;
		correos.contador++;
		ok = true;
	}
	return ok;
}

bool borrar(tListaCorreos &correos, string id){
	bool borrado = false;
	int posicion;
	buscar(correos, id , posicion);
	if(posicion != -1){	//Si existe se proce a borrar el registro de la lista
				for (posicion; posicion < correos.contador; posicion++){
			correos.correo[posicion] = correos.correo[posicion+1]; //Se desplazan los registros desde esa posicion a la derecha
		}
		correos.contador--;
		borrado = true;
	}
return borrado;
}
/*	No implementado por ciertos comportamientos con asuntos que comparten el mismo asunto en diferentes emisores

bool buscar(const tListaCorreos &correos, string id, int &pos){
	int posicion;
	int ini = 0, fin = correos.contador-1, mitad;
	
	bool encontrado = false;			//Por defecto no se ha econtrado el elemento que se busca
	
	while(ini<=fin && !encontrado){		//Mientras que mi rango de busqueda exista y no haya encontrado el elemento
		mitad = (ini+fin) / 2;

		if(id < correos.correo[mitad].identificador){
		fin = mitad - 1;
		}
		else if(correos.correo[mitad].identificador < id){
		ini = mitad + 1;
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) posicion = mitad;
	else posicion = -1;
	
	return posicion;
}
*/

bool buscar(const tListaCorreos &correos, string id, int &pos){
	bool encontrado = false;

	pos = 0;
	while (pos < correos.contador && !encontrado){
		if (id == correos.correo[pos].identificador){
			encontrado = true;		//una vez encontrado se devuelve la posicion del contador junto el boleano
		}
		else{
			pos++;
		}		
	}
	return encontrado;
}

void ordenar_AF(tListaCorreos &correos){
	bool intercambio = true;
	int i = 0;
	
	while((i<correos.contador) && intercambio){
		intercambio = false;
		for (int j = correos.contador-1; j > i; j--){
			if(correos.correo[j] < correos.correo[j-1]){ //operator< para definir si es cierto que el primer parametro tCorreo es menor que el segundo parametro tCorreo
				tCorreo tmp;
				tmp = correos.correo[j];
				correos.correo[j] = correos.correo[j-1];
				correos.correo[j-1] = tmp;
				intercambio = true;
			}
		}
		if (intercambio) i++;
	}
}
