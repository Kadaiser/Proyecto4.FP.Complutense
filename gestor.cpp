#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#include "fecha.h"
#include "gestor.h"

bool arrancar(tGestor& gestor, string dominio){
	gestor.dominio = DOMINIO;
	return (cargar(gestor.usuarios, dominio) && cargar(gestor.correos, dominio));
}


void apagar(const tGestor &gestor){
	system("cls");
	cout << "Cerrando gestor de correo " << gestor.dominio << endl;
	guardar(gestor.usuarios, gestor.dominio);
	guardar(gestor.correos, gestor.dominio);
	
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
		buscarUsuario(gestor.usuarios, identificador, gestor.usuarioActivo); //Otra forma de reutilzar la funcion de busqueda de uusuarios es para cargar el usuario activo en base al identificador recien creado
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
	int numCorreo, pos, opcion;
	string cabecera, cadena;

	cout << "Introduzca el numero correo a leer: ";
	cin >> numCorreo;

	if (numCorreo > 0 && numCorreo <= listaReg.contador){
		listaReg.registro[numCorreo-1].leido = true; //Al acceder a un correo ()siempre en la posicion n-1 respecto de lo que el usuario ve en la lista, se marca como leido
		buscar(gestor.correos, listaReg.registro[numCorreo-1].identificador, pos);	//Buscar correo en la lista de correos
		
		verCorreo(gestor.correos.correo[pos]); //Se muestra el contenido del correo
		do{
			mostrarMenuVerCorreo();	//Se muestra el menu de opciones d ela lectura de correos
			cin >> opcion;
			if (opcion == 1){
				//correoContestacion ()		//Se puede enviar una respuesta (Re:) al emisor; 
			}
		}while(opcion != 0);
	}
}



void enviarCorreo(tGestor& gestor, const tCorreo &correo){	
	tRegistro registro;
	int pos;

	if (insertar(gestor.correos, correo)){
		registro.leido = false;
		registro.identificador = correo.identificador;
		if (insertar(gestor.usuarios.usuario[gestor.usuarioActivo].bandejaSalida, registro)){
			if (buscarUsuario(gestor.usuarios, correo.destinatario, pos)){				
				if (insertar(gestor.usuarios.usuario[pos].bandejaEntrada, registro)){
					cout << "Correo enviado correctamente." << endl;
				}
				else{
					cout << "Bandeja de correo de destinatario llena!!!" << endl;
				}

			}
			else{
				cout << "Destinatario no encontrado" << endl;
			}
		}

	}
}



void borrarCorreo(tGestor& gestor, tListaRegistros& listaReg){
	int numCorreo;

	cout << "Introduzca el numero correo a borrar: ";
	cin >> numCorreo;

	if (numCorreo > 0 && numCorreo <= listaReg.contador){			
		for (int i=numCorreo-1; i<listaReg.contador; i++){
			listaReg.registro[i].identificador = listaReg.registro[i+1].identificador;
			listaReg.registro[i].leido = listaReg.registro[i+1].leido;
		}
		listaReg.contador--;
	}
}



void lecturaRapida(tGestor& gestor, tListaRegistros& listaReg){
	int pos;

	system("cls");

	ordenar_AF(gestor.correos);

	for (int i = 0; i<listaReg.contador; i++){

		if (!listaReg.registro[i].leido){
			buscar(gestor.correos, listaReg.registro[i].identificador, pos);
		
			verCorreo(gestor.correos.correo[pos]);
			listaReg.registro[i].leido = true;
		}
		
		
	}

	system("pause");
}



void gestionarSesion(tGestor& gestor){
	int opcion;
	bool bEntrada= true;
	tCorreo nuevoCorreo;

	do{
		mostrarInterfazUsuario(gestor, bEntrada);
		cin >> opcion;
		if(opcion ==1){
			if (bEntrada){
				leerCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada);		
			}
			else{
				leerCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaSalida);		
			}
		}
		else if(opcion == 2){
			system("cls");
			correoNuevo(nuevoCorreo, gestor.usuarios.usuario[gestor.usuarioActivo].identificador);
			enviarCorreo(gestor, nuevoCorreo);
			system("pause");
		}
		else if(opcion == 3){
			if (bEntrada){
				borrarCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada);		
			}
			else{
				borrarCorreo(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaSalida);		
			}
		}
		else if(opcion == 4){
			bEntrada = !bEntrada;
		}
		else if(opcion == 5){
			lecturaRapida(gestor, gestor.usuarios.usuario[gestor.usuarioActivo].bandejaEntrada);
		}
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

	mostarBandeja(gestor, bEntrada);

	lineaIntercalada();
	mostrarMenu(bEntrada);
	
}

void mostarBandeja(const tGestor & gestor, bool bEntrada){
	int pos;
	tUsuario usuario = gestor.usuarios.usuario[gestor.usuarioActivo];

	if(bEntrada){
		for(int i =  0; i< usuario.bandejaEntrada.contador; i++){
			if(!usuario.bandejaEntrada.registro[i].leido) cout << " ";
			else cout << "*";
			if (buscar(gestor.correos, usuario.bandejaEntrada.registro[i].identificador, pos)){
				cout << setw(2) << i+1 << " " << gestor.correos.correo[pos].emisor << setw(20) << gestor.correos.correo[pos].asunto << setw(35) << mostrarSoloDia(gestor.correos.correo[pos].fecha) << endl;
			}
		}
	}
	else{
		for(int i =0; i < usuario.bandejaSalida.contador; i++){
			if (buscar(gestor.correos, usuario.bandejaSalida.registro[i].identificador, pos)){
				cout << " " << setw(2) << i+1 << " " << gestor.correos.correo[pos].destinatario << setw(20) << gestor.correos.correo[pos].asunto << setw(35) << mostrarSoloDia(gestor.correos.correo[pos].fecha) << endl;
			}
		}
	}
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

void mostrarMenuVerCorreo(){
	lineaIntercalada();
	cout << "Elija una opcion:" << endl;
	cout << setw(3) << "1- Contestar correo" << endl;
	cout << setw(3) << "0- Volver a la bandeja" << endl;
	lineaIntercalada();
	cout << "Introduzca un opcion:";	
}

void lineaIntercalada(){
	for(int i=0; i<80;i++) cout << "-";
}
