using namespace std;

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

#include "gestor.h"

const string DOMINIO = "fdimail.com";


int menu();


/**
*	PROGRAMA PRINCIPAL
*/

int main(){

tGestor gestor;
int opcion;
	cout << "Bienvenido" << endl;

	if(!arrancar(gestor,DOMINIO)){
	cout << "se arranca con listas vacias";
		do{
			opcion = menu();
			switch(opcion){
				case 1:
				if(iniciarSesion(gestor))
					gestionarSesion(gestor);
					break;
				case 2:
				if(crearCuenta(gestor))
					gestionarSesion(gestor);
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