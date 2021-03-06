#ifndef USUARIO_H
#define USUARIO_H

using namespace std;

const string CENTINELA= "XXX";

#include "listaRegistros.h"

typedef struct{
string identificador;
string contrasenia;
tListaRegistros bandejaEntrada;
tListaRegistros bandejaSalida;
}tUsuario;

/**
* Dado un flujo de archivo (ya abierto), se carga un usuario de fichero
*/
bool cargar(tUsuario& usuario, ifstream& archivo);

/**
* Dado un flujo de archivo (ya abierto), se guarda un usuario en fichero
*/
void guardar(const tUsuario& usuario, ofstream& archivo);

/**
* Recibe un identificador de usuario y una contraseņa y los asigna al usuario.
*/
void inicializar(tUsuario& usuario, string id, string contrasenia);

/**
* Recibe una contraseņa y un usuario y devuelve si la contraseņa es correcta o no.
*/
bool validarContrasenia(const tUsuario &usuario, string contrasenia);


#endif