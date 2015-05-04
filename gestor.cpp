#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#include "gestor.h"

bool arrancar(tGestor& gestor, string dominio){
	gestor.dominio = DOMINIO;
	return (cargar(gestor.usuarios, dominio) && cargar(gestor.correos, dominio));
}


void apagar(const tGestor &gestor){
	system("cls");
	cout << "Cerrando gestor de correo " << gestor.dominio << endl;
	//guardar(gestor.usuarios, gestor.dominio);
	guardar(gestor.correos, gestor.dominio);
	system("pause");
	
}


bool crearCuenta(tGestor &gestor){
	bool ok = false;
	tUsuario usuario;
	string identificador, contrasenia;
	int posUsuario;
		
		cout << "Elija un identificador de cuenta: ";
		cin >> identificador;
		cin.sync();
		identificador = identificador + "@"+ gestor.dominio;
			while(buscarUsuario(gestor.usuarios, identificador, posUsuario)){
				cout << "Usuario no disponible, por favor, escoja otro identificador: " << endl;
				cin >> identificador;
				cin.sync();
				identificador = identificador + "@"+ gestor.dominio;
			}
		cout << "Elija una contrasenia: ";
		cin >> contrasenia;
		cin.sync();
	
		inicializar(usuario, identificador, contrasenia);
			if(aniadir(gestor.usuarios, usuario)) ok = true;
			else cout << "No pudo incluirse el usuario en la lista de usuarios";

		cout << "Se genero su cuenta correctamente." << endl << "Va a iniciar su primera sesion en " << gestor.dominio << endl;
		gestor.usuarioActivo = gestor.usuarios.contador - 1;
		system("pause");
return ok;
}


bool iniciarSesion(tGestor &gestor){
	bool ok = false;
	int posUsuario;
	string identificador;
	string contrasenia;
	
		cout << "Bienvenido al correo de " << gestor.dominio <<endl;
		cout << "Introduzca su direccion de correo: ";
		cin >> identificador;
		cin.sync();
		if(buscarUsuario(gestor.usuarios, identificador, posUsuario)){
			cout << "Introduzca su contrasenia: ";
			cin >> contrasenia;
			cin.sync();
			if(validarContrasenia(gestor.usuarios.usuario[posUsuario], contrasenia)){
				gestor.usuarioActivo = posUsuario;
				ok = true;
				cout << "Iniciando sesion..." << endl;
			}
			else{
				cout << "Contrasenia incorrecta, regresando a menu principal" << endl;
			}
		}
		else{
			cout << "Cuenta no existe, regresando a menu principal"<< endl;
		}
	system("pause");
return ok;
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
	bool bEntrada= true;
	do{
		mostrarInterfazUsuario(gestor, bEntrada);
		cin >> opcion;
		if(opcion ==1){}
		else if(opcion == 2){}
		else if(opcion == 3){}
		else if(opcion == 4){
			if(bEntrada == true)bEntrada = false;
			else bEntrada = true;
		}
		else if(opcion == 5){}
	}while(opcion != 0);
	system("cls");
}

void mostrarInterfazUsuario(tGestor& gestor, bool bEntrada){
	system("cls");
	cout << "correo de " << gestor.usuarios.usuario[gestor.usuarioActivo].identificador << endl;
	for(int i=0; i<30;i++) cout << "-";
	cout << "Bandeja de ";
		if(bEntrada) cout << "entrada";
		else cout << "salida-";
	for(int i=0; i<32;i++) cout << "-" ;
	
	lineaIntercalada();
	cout <<"L" << setw(2) << "N" << setw(10) << "EMISOR" << setw(20) << "ASUNTO" << setw(45) << "FECHA" << endl;
	lineaIntercalada();

	mostarBandeja(gestor.usuarios.usuario[gestor.usuarioActivo], bEntrada);

	lineaIntercalada();
	mostrarMenu(bEntrada);
	
}

void mostrarMenu(bool bEntrada){
	cout << "Elija una opcion:" << endl;
	cout << setw(3) << "1- Leer correo" << endl;
	cout << setw(3) << "2- Enviar correo" << endl;
	cout << setw(3) << "3- Borrar correo" << endl;
	cout << setw(3) << "4- Ver bandeja de ";
	if(bEntrada) cout << "salida" << endl;
	else cout << "entrada" << endl;
	cout << setw(3) << "5- Lectua rapida de correos sin leer" << endl;
	cout << setw(3) << "0- Cerrar sesion" << endl;
	lineaIntercalada();
	cout << "Introduzca un opcion:";
}

void lineaIntercalada(){
	for(int i=0; i<80;i++) cout << "-";
}
