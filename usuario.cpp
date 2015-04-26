#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "usuario.h"


bool cargar(tUsuario& usuario, ifstream& archivo){
	bool ok= true;
	archivo >> usuario.identificador;
	if(usuario.identificador == CENTINELA) ok = false;
	else{
		archivo >> usuario.contrasenia;
		//cargarBandejaEntrada(archivo, usuario.recibidos);
		//cargarBandejaEntrada(archivo, usuario.enviados);
	}
	return ok;
}

void guardar(const tUsuario& usuario, ofstream& archivo){
}

void inicializar(tUsuario& usuario, string id, string contrasenia){
}

bool validarContrasenia(const tUsuario &usuario, string contrasenia){
return true;
}