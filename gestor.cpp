#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#include "gestor.h"

bool arrancar(tGestor& gestor, string dominio){
	gestor.dominio = DOMINIO;
	//inicializar(gestor, dominio);//igual es inecesario, se trara de inicializar las listas
	return (cargar(gestor.usuarios, dominio) && cargar(gestor.correos, dominio));
}



void apagar(const tGestor &gestor){
}



bool crearCuenta(tGestor &gestor){
	bool ok = false;
	tUsuario usuario;
	int pos;
		
		if(verificarIdentificador(gestor.usuarios, usuario)){	
			crearUsuario(usuario);
				if(aniadir(gestor.usuarios, usuario))
					ok = true;
				else{
					cout << "No pudo incluirse el usuario en la lista de usuarios";
				}
			}
		cout << "Se genero su usuario correctamente. Va a iniciar su primera sesion en " << gestor.dominio << endl;
	system("pause");
	return ok;
}




bool iniciarSesion(tGestor &gestor){
		string identificador;
		cout << "Bienvenido al correo de " << gestor.dominio <<endl;
		cout << "Introduzca su identificador de correo: ";
		cin >> identificador;
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
	bool bandejaEntrada= true;
	do{
		mostrarInterfazUsuario(gestor, bandejaEntrada);
		cin >> opcion;
		if(opcion ==1){}
		else if(opcion == 2){}
		else if(opcion == 3){}
		else if(opcion == 4){
			if(bandejaEntrada == true)bandejaEntrada = false;
			else bandejaEntrada = true;
		}
		else if(opcion == 5){}
	}while(opcion != 0);
	system("cls");
}

void mostrarInterfazUsuario(tGestor& gestor,bool bandejaEntrada){
	system("cls");
	cout << "correo de " << gestor.usuarios.usuario[gestor.usuarioActivo].identificador + "@" + gestor.dominio << endl ;
	for(int i=0; i<30;i++) cout << "-";
	cout << "Bandeja de ";
		if(bandejaEntrada) cout << "entrada";
		else cout << "salida-";
	for(int i=0; i<32;i++) cout << "-" ;
	lineaIntercalada();
	cout <<"L" << setw(2) << "N" << setw(10) << "EMISOR" << setw(20) << "ASUNTO" << setw(45) << "FECHA" << endl;
	
	lineaIntercalada();
/**
	if(bandejaEntrada)mostarBandejaEntrada(gestor.usuarios.usuario[gestor.usuarioActivo]);
	else mostarBandejaSalida(gestor.usuarios.usuario[gestor.usuarioActivo]);
*/
	lineaIntercalada();
	mostrarMenu(bandejaEntrada);
	
}

void mostrarMenu(bool bandejaEntrada){
	cout << "Elija una opcion:" << endl;
	cout << setw(3) << "1- Leer correo" << endl;
	cout << setw(3) << "2- Enviar correo" << endl;
	cout << setw(3) << "3- Borrar correo" << endl;
	cout << setw(3) << "4- Ver bandeja de ";
	if(bandejaEntrada) cout << "salida" << endl;
	else cout << "entrada" << endl;
	cout << setw(3) << "5- Lectua rapida de correos sin leer" << endl;
	cout << setw(3) << "0 - Cerrar sesion" << endl;
	lineaIntercalada();
	cout << "Introduzca un opcion:";
}

void lineaIntercalada(){
	for(int i=0; i<80;i++) cout << "-";
}