using namespace std;

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>


const int MAXREGISTROS = 100;

typedef struct{
string identificador;
bool leido;
}tRegistro;

typedef struct{
tRegistro registro[MAXREGISTROS];
int contador;
}tListaRegistros;

/**
* Inicializa la lista
*/
void inicializar(tListaRegistros &listaReg);


/**
* Dado un flujo de archivo de entrada (ya abierto), 
* lee los datos que corresponden a una lista de registros y la devuelve.
*/
void cargar(tListaRegistros &listaReg, ifstream& archivo);

/**
* Dado un flujo de archivo de salida (ya abierto), guarda los datos de la lista de registro.
*/
void guardar(const tListaRegistros &listaReg, ofstream& archivo);

/**
* Dado un registro lo inserta al final de la lista. Si la lista est� llena devuelve false, 
* en otro caso devuelve true. Este subprograma se ejecutar� cuando un usuario env�e un correo 
* ya que se insertar� el registro correspondiente en la lista de registros que representa su bandeja de salida,
* y tambi�n en las listas de registros que representan las bandejas de entrada de cada uno de los destinatarios del correo
*/
bool insertar(tListaRegistros &listaReg, tRegistro registro);

/**
* Dado un identificador de correo, busca el registro correspondiente y si lo encuentra lo elimina de la lista (�sin dejar huecos!). 
* Si no lo encuentra, devuelve false, en otro caso devuelve true. Este subprograma representa la acci�n de un usuario del borrado de un determinado correo de una de sus bandejas.
* OJO: esta operaci�n s�lo supone que el registro es borrado de la lista de registros, pero el correo seguir� existiendo en la lista de correos.
*/
bool borrar(tListaRegistros &listaReg, string id);

/**
* Dado un identificador de correo, busca el correspondiente registro y pone el indicador de le�do a true. La operaci�n devuelve un booleano indicando si se encontr� o no el registro.
*/
bool correoLeido(tListaRegistros &listaReg, string id);

/**
* Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posici�n, y si no existe devuelve -1.
*/
int buscar(const tListaRegistros &listaReg, string id);

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
* Recibe un identificador de usuario y una contrase�a y los asigna al usuario.
*/
void inicializar(tUsuario& usuario, string id, string contrasenia);

/**
*Recibe una contrase�a y un usuario y devuelve si la contrase�a es correcta o no.
*/
bool validarContrasenia(const tUsuario &usuario, string contrasenia);



const string ARCHIVO = "fdimail.com_Usuarios.txt";
const int MAXUSUARIOS = 100;

typedef struct{
tUsuario usuario[MAXUSUARIOS];
int contador;
}tListaUsuarios;

/**
* Inicializa la lista
*/
void inicializar(tListaUsuarios &usuarios);

/**
* Implementa la carga de la lista de usuarios desde el fichero de usuarios 
* de nombre <NombreDominio>_usuarios.txt .
*/
bool cargar(tListaUsuarios& usuarios, string dominio);

/**
* Implementa el guardado de la lista de usuarios en el fichero de usuarios 
* de nombre <NombreDominio>_usuarios.txt .
*/
void guardar(const tListaUsuarios& usuarios, string dominio);

/**
* A�ade un usuario en la posici�n de la lista que le corresponde, si hay sitio para ello.
* Adem�s devuelve un booleano indicando si la operaci�n tuvo �xito o no.
*/
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario);

/**
* Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posici�n y el valor true, 
* y si no existe en la lista, la posici�n que le corresponder�a y el valor false. (IMPLEMENTADA)
*/
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion);

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
* Devuelve un string que contiene la informaci�n que se mostrar� en la bandeja de entrada/salida: emisor, asunto y fecha sin hora
*/
string obtenerCabecera(const tCorreo &correo);

/**
* Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a un correo y lo devuelve. Devuelve false s�lo si el correo cargado no es v�lido.
*/
bool cargar(tCorreo &correo, ifstream& archivo);

/**
* Dado un flujo de archivo de salida (ya abierto), escribe en el flujo los datos que corresponden a un correo
*/
void guardar(const tCorreo &correo, ofstream& archivo);


const int MAXCORREOS = 100;

typedef struct{
	tCorreo listaCorreos[MAXCORREOS];
	int contador;
} tListaCorreos;



/**
*  Inicializa la lista
*/
void inicializar(tListaCorreos &correos);

/**
* Implementa la carga de la lista de correos desde el fichero de correos de nombre <NombreDominio>_correos.txt.
*/
bool cargar(tListaCorreos &correos, string dominio);

/**
* Implementa el guardado de la lista de correos en el fichero de correos de nombre <NombreDominio>_ correos.txt 
* Guarda en fichero la lista de correos. El nombre del fichero ser� como en el subprograma anterior
*/
void guardar(const tListaCorreos &correos, string dominio); 

/**
* Dado un correo, si hay espacio en la lista, lo coloca en la posici�n de la lista que le corresponda 
* de acuerdo con su identificador y devuelve true. Si no lo ha podido colocar devuelve false
*/
bool insertar(tListaCorreos &correos, const tCorreo &correo);

/**
* Dado un identificador de correo y la lista, devuelve, si dicho identificador existe en la lista, su posici�n y el valor true, 
* y si no existe en la lista, la posici�n que le corresponder�a y el valor false.
*/
bool buscar(const tListaCorreos &correos, string id, int &pos);

/**
* Dada una lista de correos la devuelve ordenada por asunto y fecha. 
* Como es una clave de ordenaci�n doble, habr� que redefinir el operador de comparaci�n en el m�dulo que corresponda.
*/
void ordenar_AF(tListaCorreos &correos);

const string DOMINIO = "fdimail.com";


int menu();
typedef struct{
	string dominio;
	int usuarioActivo;
	tListaCorreos correos;
	tListaRegistros registros;
	tListaUsuarios usuarios;
}tGestor;


/**
* Inicializa el gestor e intenta arrancarlo cargando la informaci�n del dominio que se le pasa como par�metro.
* Para ello inicializar� y cargar� la lista de usuarios y de correos de dicho dominio.
* Si tiene �xito en todas las operaciones devuelve true y si alguna falla devuelve false.
*/
bool arrancar(tGestor& gestor, string dominio);

/**
* Esta operaci�n apaga el gestor y guarda para ello las listas de usuarios y de correos del dominio que se encontrase activo en ese momento.
*/
void apagar(const tGestor &gestor);

/**
*Lee los datos de usuario necesarios para crear una cuenta (id y contrase�a) y si el id de usuario no existe y hay espacio en la lista de usuarios
* crea la cuenta del usuario y registra al nuevo usuario como usuario activo en el gestor. Devuelve un booleano indicando si la operaci�n tuvo �xito.
*/
bool crearCuenta(tGestor &gestor);

/**
* Lee los datos de usuario necesarios para validar la cuenta (id y contrase�a) y si el usuario existe y la contrase�a coincide, 
* registra al usuario como usuario activo. Devuelve un booleano indicando si la operaci�n tuvo �xito.
*/
bool iniciarSesion(tGestor &gestor);

/**
* Solicita el correo que el usuario quiere leer (ser� el n�mero con el que el correo es mostrado por pantalla en la bandeja correspondiente),
* valida que existe y si es as�, lo marca como correo le�do. A continuaci�n, busca el correo en la lista de correos y si lo encuentra 
* lo muestra en la pantalla de lectura del correo.
*/
void leerCorreo(tGestor& gestor, tListaRegistros& listaReg);


/**
* Este subprograma implementa el env�o del correo en nuestra aplicaci�n. Para ello el correo recibido como par�metro es insertado en la lista de correo.
* Si ha habido �xito, entonces se inserta el registro correspondiente en la lista de registros enviados del emisor y se intenta insertar igualmente un registro
* de dicho correo en la lista de registros recibidos del destinatario del correo. Si el destinatario no existe o si su bandeja de entrada est� llena, 
* entonces se mostrar� un mensaje de error.
*/
void enviarCorreo(tGestor& gestor, const tCorreo &correo);

/**
* Este subprograma implementa el borrado del correo de una bandeja de un determinado usuario (OJO: el correo no se borra de la lista de correos).
* Para ello, solicita el correo que el usuario quiere borrar (ser� el n�mero con el que el correo es mostrado por pantalla en la bandeja correspondiente),
* valida que existe y si es as�, procede a borrarlo.
*/
void borrarCorreo(tGestor& gestor, tListaRegistros& listaReg);

/**
* Este subprograma implementa la lectura r�pida de correos sin leer. El resultado es que muestra en una pantalla todos los correos sin leer ordenados
* por asunto (ignorando todos los �Re: �) y por fecha. Al finalizar su ejecuci�n los correos sin leer quedar�n marcados como le�dos.
*/
void lecturaRapida(tGestor& gestor, tListaRegistros& listaReg);

/**
*	Esta funcion muestra la interfaz de usuario y toma una opcion a partir del menu de opciones de la sesion de usuario ya arrancada
*/
void gestionarSesion(tGestor& gestor);

/**
*	Este subprograma muestra la interfaz basica del gestor 
*/
void mostrarInterfazUsuario(tGestor& gestor);

/**
*	PROGRAMA PRINCIPAL
*/

int main(){

tGestor gestor;
int opcion;

	if(!arrancar(gestor,DOMINIO)){
	cout << "se arranca con listas vacias";
		do{
			opcion = menu();
			switch(opcion){
				case 1:
				//if(iniciarSesion(gestor))
					//gestionarSesion(gestor);
					break;
				case 2:
				//if(crearCuenta(gestor))
					//gestionarSesion(gestor);
				break;
			}
			
		}while(opcion != 0);
	}

system("pause");
}




int menu(){
	int opcion;
		cin >> opcion;
		cin.sync();
		
		while(opcion <0 || opcion >2){
			cout << "Opcion no valida, por favor intruduzca una opcion" << endl;			
			cin >> opcion;
			cin.sync();
		}
	return opcion;
}

bool arrancar(tGestor& gestor, string dominio){
return true;
}

void apagar(const tGestor &gestor){
}

bool crearCuenta(tGestor &gestor){
return true;
}

bool iniciarSesion(tGestor &gestor){
return true;
}

void leerCorreo(tGestor& gestor, tListaRegistros& listaReg){
}

void enviarCorreo(tGestor& gestor, const tCorreo &correo){
}

void borrarCorreo(tGestor& gestor, tListaRegistros& listaReg){
}

void lecturaRapida(tGestor& gestor, tListaRegistros& listaReg){
}

void gestionarSesion(tGestor& gestor){
	int opcion;
	do{
		mostrarInterfazUsuario(gestor);
		cin >> opcion;
		if(opcion ==1){}
		else if(opcion == 2){}
		else if(opcion == 3){}
		else if(opcion == 5){}
	}while(opcion != 0);
}

void mostrarInterfazUsuario(tGestor& gestor){
}

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

		if(id < correos.listaCorreos[mitad].identificador){
		fin = mitad - 1;
		}
		else if(correos.listaCorreos[mitad].identificador < id){
		ini = mitad + 1;
		}
		else{
		encontrado = true;
		}
	}
	if(encontrado) pos = mitad;
	else pos = ini;
	
	return encontrado;
}

void ordenar_AF(tListaCorreos &correos){
}

void correoNuevo(tCorreo &correo, string emisor){
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){
}

string aCadena(const tCorreo &correo){
	string cadena;
	return cadena;
}

string obtenerCabecera(const tCorreo &correo){
	string cabecera;
	return cabecera;
}

bool cargar(tCorreo &correo, ifstream& archivo){
return true;
}

void guardar(const tCorreo &correo, ofstream& archivo){
}

void inicializar(tListaUsuarios &usuarios){
}

bool cargar(tListaUsuarios& usuarios, string dominio){
return true;
}

void guardar(const tListaUsuarios& usuarios, string dominio){
}

bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario){
return true;
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

void inicializar(tListaRegistros &listaReg){
}

void cargar(tListaRegistros &listaReg, ifstream& archivo){
}

void guardar(const tListaRegistros &listaReg, ofstream& archivo){
}

bool insertar(tListaRegistros &listaReg, tRegistro registro){
return true;
}

bool borrar(tListaRegistros &listaReg, string id){
return true;
}

bool correoLeido(tListaRegistros &listaReg, string id){
return true;
}

int buscar(const tListaRegistros &listaReg, string id){
	int pos;
	return pos;
}
