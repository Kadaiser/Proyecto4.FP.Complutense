#ifndef CORREO_H
#define CORREO_H

using namespace std;
const string CENTINELACORREO= "XXX";
const string CENTINELACUERPO= "X";

typedef time_t tFecha;

typedef struct{
string emisor;
string destinantario;
string asunto;
string cuerpo;
tFecha fecha;
string identificador;
} tCorreo;

/**
* Recibe un identificador de emisor y devuelve un correo con todos sus datos rellenos
*/
void correoNuevo(tCorreo &correo, string emisor);

/**
* Recibe un identificador de emisor y el correo original que se va a contestar, y devuelve un correo con todos sus datos rellenos
*/
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor);

/**
* Devuelve un string con el contenido completo del correo para poderlo mostrar por consola
*/
string aCadena(const tCorreo &correo);

/**
* Devuelve un string que contiene la información que se mostrará en la bandeja de entrada/salida: emisor, asunto y fecha sin hora
*/
string obtenerCabecera(const tCorreo &correo);

/**
* Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a un correo y lo devuelve. Devuelve false sólo si el correo cargado no es válido.
*/
bool cargar(tCorreo &correo, ifstream& archivo);

/**
* Dado un flujo de archivo de salida (ya abierto), escribe en el flujo los datos que corresponden a un correo
*/
void guardar(const tCorreo &correo, ofstream& archivo);

/**
* Genera el cuerpo del correo a partir de un flujo de entrada (ya abierto), escribe almacenandolo en una variable tipo string
*/
void leerCuerpo(string& cuerpo, ifstream& archivo);
#endif
