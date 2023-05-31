#include <iostream>	
#include "objetos.h"

using namespace std;

//creacion de objetos
Aerolineas aero;
Usuarios usua;
Pasajeros pasa;
VuelosP vp;
VuelosE ve;
Compra com;

int menuUsuario(){
	int opcion;
	int cod;
	Usuario *auxU=usua.ingreso();
	if (auxU!= NULL){
		do{
		cout << "1. registrar vuelos" << endl;
		cout << "2. ver vuelos" << endl;
		cout << "3. buscar vuelo planeado (por codigo)" << endl;
		cout << "4. buscar vuelo especifico (por codigo)" << endl;
		cout << "5. buscar vuelos especificos (por fecha)" << endl;
		cout << "6. buscar vuelo planeado (por fecha)" << endl;
		cout << "0. volver al menú principal" << endl;
		cin >> opcion;
		switch(opcion){
			case 1://agregar vuelo
				ve.agregar(vp.agregar(auxU->nombreAerolinea));
				break;
			case 2://muestra en consola los vuelos
				vp.imprimir(auxU->nombreAerolinea);
				break;
			case 3://muestra en consola los vuelos especificos según su codigo
				cout << "inserte el codigo del vuelo" << endl;
				cin >> cod;
				vp.buscarCodigo(cod);
				break;
			case 4://muestra en consola los vuelos planeados según su codigo
				ve.buscarCodigo();
				break;
			case 5://agrega usuario
				ve.buscarFecha();
				break;
			case 0://Vuelve al menú principal
				//ingresar una funcion que reincie la lista de boletas
				return 0;
		}
	}	while(opcion != 0);
		return 0;	
	}else {
		return 0;
	}
}

int menuPasajero(){
	Pasajero *pasaux = pasa.ingreso();
	
	
	int opcion;
	int cod;
	if (pasaux!= NULL){
		do{
		cout << "1. ver vuelos por origen y destino" << endl;
		cout << "2. buscar vuelo planeado (por codigo)" << endl;
		cout << "3. buscar vuelo especifico (por codigo)" << endl;
		cout << "4. buscar vuelos especificos (por fecha)" << endl;
		cout << "5. buscar vuelo planeado (por fecha)" << endl;
		cout << "6. comprar boletas" << endl;
		cout << "0. volver al menú principal" << endl;
		cin >> opcion;
		switch(opcion){
			case 1://muestra en consola los vuelos
				vp.buscarOD();
				break;
			case 2://muestra en consola los vuelos especificos según su codigo
				cout << "inserte el codigo del vuelo" << endl;
				cin >> cod;
				vp.buscarCodigo(cod);
				break;
			case 3://muestra en consola los vuelos planeados según su codigo
				ve.buscarCodigo();
				break;
			case 4://agrega usuario
				ve.buscarFecha();
				break;
			case 6://agrega usuario
				com.agregar(ve,pasaux->numDocumento);
				break;
			case 0://Vuelve al menú principal
				//ingresar una funcion que reincie la lista de boletas
				return 0;
		}
	}	while(opcion != 0);
		return 0;	
	}else {
		return 0;
	}
}

int opciones(){
	int opcion;
	do{
		cout << "menú de opciones:" << endl;
		cout << "1. registrar aerolinea" << endl;
		cout << "2. ver aerolineas" << endl;
		cout << "3. registrar usuarios" << endl;
		cout << "4. registrar pasajeros" << endl;
		cout << "5. ingresar como usuario " << endl;
		cout << "6. ingresar como pasajero" << endl;
		cout << "0. cerrar el programa" << endl;
		cin >> opcion;
		switch(opcion){
			case 1://agregar aerolinea
				aero.agregar();
				break;
			case 2://muestra en consola las Aerolineas
				aero.imprimir();
				break;
			case 3://agrega usuario
				usua.agregar(aero.getNombres());
				break;
			case 4://agrega pasajaeros
				pasa.agregar();
				break;
			case 5:	//muestra en consola los pasajeros
				menuUsuario();
				break;
			case 6://agrega vuelos //ve.agregar(vp.agregar());				
				menuPasajero();
				break;
			case 0:
				aero.guardar();
				usua.guardar();
				pasa.guardar();
				vp.guardar();
				ve.guardar();
				com.guardar();
				return 0;		
		}
	}while(opcion != 0);
}

int main(int argc, char** argv) {
	
	string buscador;
	
	//Inicia las listas con los datos de la base de datos
	ve.leerSillas();
	aero.leer();
	usua.leer();
	pasa.leer();
	vp.leer();
	ve.leer();
	com.leer();
	//aero.imprimir();
	//ve.itinerarios();
	opciones();

	return 0;
}


