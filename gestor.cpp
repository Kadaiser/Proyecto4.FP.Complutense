#include <iostream>
#include <string>

using namespace std;

#include "gestor.h"

bool arrancar(tGestor& gestor, string dominio){
	//inicializar(gestor, dominio);//igual es inecesario, se trara de inicializar las listas
	return (cargar(gestor.usuarios, dominio) && cargar(gestor.correos, dominio));
}

void apagar(const tGestor &gestor){
}


bool crearCuenta(tGestor &gestor){
	bool ok = false;
	tUsuario usuario;
		
		if(verificarIdentificador(gestor.usuarios, usuario)){	
			crearUsuario(usuario);
				if(aniadir(gestor.usuarios, usuario))
					ok = true;
				else{
					cout << "No pudo incluirse el usuario en la lista de usuarios";
				}
			}	
	return ok;
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
	cout << "correo de " <<endl ;
}