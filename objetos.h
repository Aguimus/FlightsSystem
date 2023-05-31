#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Structs.h"
#include "Lista.h"

using namespace std;

class Aerolineas{
	private:
		Lista<Aerolinea> listaAerolineas;
		FILE *archivo;
		Aerolinea aeroaux;
		string aux;
		char charAux[30];
		
	public:
		
		void agregar(){
			cout << "Nombre" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			aeroaux.nombre = string(charAux);
			cout << "Numero de cuenta bancaria" << endl;
			cin >> aeroaux.numBanco;
			for (int i = 0; i <15; i++){
				cout << "aviones" << endl;
				cin.getline(charAux, 30, '\n');
				aeroaux.aviones[i] = string(charAux);
			}
			cout << endl;	
			listaAerolineas.insertarFinal(aeroaux);
		}
		
		void leer(){
			char aux[30];
			int contador=0;
			
			archivo = fopen ("registroAerolineas.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					//cout << aux << endl;
					contador++;
					if (contador==1){
						aeroaux.nombre= string(aux);	
						aeroaux.nombre.erase(aeroaux.nombre.find('\n'));
					} else if(contador == 2){
						aeroaux.numBanco = atoi(aux);	
					} else if (contador >2 && contador <18){
						aeroaux.aviones[contador-3]= string(aux);
						if(aeroaux.aviones[contador-3].find('\n')<aeroaux.aviones[contador-3].size()){
							aeroaux.aviones[contador-3].erase(aeroaux.aviones[contador-3].find('\n'));
						}
						if (contador==17){
							contador = 0;
							listaAerolineas.insertarFinal(aeroaux);	
						}
					} 
				}
			}
			rewind(archivo);
			fclose(archivo);
		}

		void guardar(){
			if(!listaAerolineas.listaVacia()){
				archivo = fopen ("registroAerolineas.db","w");
				char aux[30];
				if (archivo) {
				for (int i=1; i <= listaAerolineas.tamLista();i++){
						strcpy(aux,listaAerolineas.buscar(i)->nombre.c_str());
						fprintf(archivo,"%s\n%i\n",aux,listaAerolineas.buscar(i)->numBanco);
						for (int j=0; j<15;j++){
							strcpy(aux,listaAerolineas.buscar(i)->aviones[j].c_str());
							fprintf(archivo,"%s\n",aux);
						}
					}
				} else {
					cout << "no se pudo crear el archivo" << endl;
				}
				fclose(archivo);
			}
		}
		
		void imprimir(){
			for(int i = 1; i <= listaAerolineas.tamLista(); i++){
				cout << "Nombre: " << listaAerolineas.buscar(i)->nombre << endl;
				cout << "Cuenta bancaria:  " << listaAerolineas.buscar(i)->numBanco << endl;
				//Imprime los aviones de la aerolinea
				/*cout << "aviones:" << endl;
				for(int a = 0; a < sizeof listaAerolineas.buscar(i)->aviones / sizeof listaAerolineas.buscar(i)->aviones[0]; a++){
						cout << listaAerolineas.buscar(i)->aviones[a] << endl;
				}*/
				cout << endl;
			}
		}
		
		string * getNombres(){
			string *nombres = new string[listaAerolineas.tamLista()];
			for(int i = 0; i < listaAerolineas.tamLista(); i++){
				nombres[i] = listaAerolineas.buscar(i+1)->nombre;
			}
			return nombres;
		}
		
		bool buscarNombre(){
			string nom;
			cout << "escriba el nombre de la aerolinea" << endl;
			cin >> nom;
			bool encontrado = false;
			int i; 
			for (int i = 1; i <= listaAerolineas.tamLista(); i++){
				if(nom==listaAerolineas.buscar(i)->nombre){
					cout << endl;
					cout << "Nombre: " << listaAerolineas.buscar(i)->nombre << endl;
					cout << "Cuenta bancaria:  " << listaAerolineas.buscar(i)->numBanco << endl;
					cout << "aviones:" << endl;
					for(int a = 0; a < sizeof listaAerolineas.buscar(i)->aviones / sizeof listaAerolineas.buscar(i)->aviones[0]; a++){
						cout << listaAerolineas.buscar(i)->aviones[a] << endl;
					}
					cout << endl;
					return true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro la aerolinea" << endl;
				cout << endl;
				return encontrado;
			}
		}
};

class Usuarios{
	private:
		Lista<Usuario> listaUsuarios;
		FILE *archivo;
		Usuario usuaux;
		string aux;
		char charAux[30];
		
	public:
		
		void agregar(string *a){
			bool valido = false;
			do{
				cout << "Ingrese el nombre de la aerolinea a la que pertenece" << endl;
				cin.ignore();
				cin.getline(charAux, 30, '\n');
				usuaux.nombreAerolinea = string(charAux);

				for(int i = 0; i <= sizeof(a)/sizeof(a[0]); i++){

					if(usuaux.nombreAerolinea == a[i]){
						valido=true;
					}
				}
			}while(!valido);
			cout << "Nombres" << endl;
			cin.sync();
			cin.getline(charAux, 30, '\n');
			usuaux.nombres = string(charAux);
			cout << "apellidos" << endl;
			cin.sync();
			cin.getline(charAux, 30, '\n');
			usuaux.apellidos = string(charAux);
			cout << usuaux.apellidos << endl;
			do{
				cout << "sexo (0. hombre   1. mujer) " << endl;//rompible
				cin >> aux;
				if(aux == "0" ){
					usuaux.sexo = 0;
				} else if(aux == "1"){
					usuaux.sexo = 1;	
				}
			}while(aux != "0" && aux!= "1");
			cout << "edad" << endl;
			cin >> usuaux.edad;
			cout << endl;	
			listaUsuarios.insertarFinal(usuaux);
		}
		
		void leer(){
			char aux[30];
			int contador=0;
			
			archivo = fopen ("registroUsuarios.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					//cout << aux << endl;
					contador++;
					if (contador==1){
						usuaux.nombres = string(aux);
						if(usuaux.nombres.find('\n')<usuaux.nombres.size()){
							usuaux.nombres.erase(usuaux.nombres.find('\n'));
						}	
					} else if(contador == 2){
						usuaux.apellidos = string(aux);	
						if(usuaux.apellidos.find('\n')<usuaux.apellidos.size()){
							usuaux.apellidos.erase(usuaux.apellidos.find('\n'));
						}
					} else if (contador == 3){
						usuaux.sexo = atoi(aux);
					} else if (contador == 4){
						usuaux.edad = atoi(aux);	
					} else if (contador == 5){
						usuaux.nombreAerolinea = string(aux);
						if(usuaux.nombreAerolinea.find('\n')<usuaux.nombreAerolinea.size()){
							usuaux.nombreAerolinea.erase(usuaux.nombreAerolinea.find('\n'));
						}
						contador=0;
						listaUsuarios.insertarFinal(usuaux);	
					}
				}
			}
			rewind(archivo);
			fclose(archivo);
		}

		void guardar(){
			if(!listaUsuarios.listaVacia()){
				archivo = fopen ("registroUsuarios.db","w");
				char auxN[30], auxA[30], auxAE[30];
				if (archivo) {
				for (int i=1; i <= listaUsuarios.tamLista();i++){
						strcpy(auxN,listaUsuarios.buscar(i)->nombres.c_str());
						strcpy(auxA,listaUsuarios.buscar(i)->apellidos.c_str());
						strcpy(auxAE,listaUsuarios.buscar(i)->nombreAerolinea.c_str());
						fprintf(archivo,"%s\n%s\n%i\n%i\n%s\n",auxN, auxA, listaUsuarios.buscar(i)->sexo, listaUsuarios.buscar(i)->edad,auxAE);
					}
				} else {
					cout << "no se pudo leer el archivo" << endl;
				}
				fclose(archivo);
			}
		}
		
		void imprimir(){
			for(int i = 1; i <= listaUsuarios.tamLista(); i++){
				cout << "Nombre: " << listaUsuarios.buscar(i)->nombres << endl;
				cout << "Apellidos: " << listaUsuarios.buscar(i)->apellidos << endl;
				cout << "sexo: ";
				if( listaUsuarios.buscar(i)->edad == 1 ){
					cout << "Mujer" << endl;
				} else {
					cout << "Hombre" << endl;
				}
				cout << "edad: " << listaUsuarios.buscar(i)->edad << endl; 
				cout << endl;
			}
		}
		
		Usuario* ingreso(){
			char charAux[30];
			string nom;
			cout<< "inserte los nombres del usuario" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			nom = string (charAux);
			bool encontrado = false;
			for (int i = 1; i <= listaUsuarios.tamLista(); i++){
				if(nom==listaUsuarios.buscar(i)->nombres){
					return listaUsuarios.buscar(i);
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el usuario" << endl;
				cout << endl;
				return NULL;
			}
		}
		
		bool buscarNombre(){
			char charAux[30];
			string nom;
			cout<< "inserte los nombres del usuario" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			nom = string (charAux);
			bool encontrado = false;
			for (int i = 1; i <= listaUsuarios.tamLista(); i++){
				if(nom==listaUsuarios.buscar(i)->nombres){
					cout << endl;
					cout << "Nombre: " << listaUsuarios.buscar(i)->nombres << endl;
					cout << "Apellidos: " << listaUsuarios.buscar(i)->apellidos << endl;
					cout << "sexo:" ;
					if (listaUsuarios.buscar(i)->sexo){
						cout << " mujer" << endl;
					} else {
						cout << " hombre" << endl;
					}
					cout << "Edad: " << listaUsuarios.buscar(i)->edad << endl;
					cout << endl;
					return true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el usuario" << endl;
				cout << endl;
				return encontrado;
			}
		}
		
		bool buscarApellidos(){
			char charAux[30];
			string nom;
			cout<< "inserte los apellidos del usuario" << endl;
			cin.sync();
			cin.getline(charAux, 30, '\n');
			nom = string (charAux);
			bool encontrado = false;
			int i; 
			for (int i = 1; i <= listaUsuarios.tamLista(); i++){
				if(nom==listaUsuarios.buscar(i)->apellidos){
					cout << endl;
					cout << "Nombre: " << listaUsuarios.buscar(i)->nombres << endl;
					cout << "Apellidos: " << listaUsuarios.buscar(i)->apellidos << endl;
					cout << "sexo:" ;
					if (listaUsuarios.buscar(i)->sexo){
						cout << " mujer" << endl;
					} else {
						cout << " hombre" << endl;
					}
					cout << "Edad: " << listaUsuarios.buscar(i)->edad << endl;
					cout << endl;
					return true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el usuario" << endl;
				cout << endl;
				return encontrado;
			}
		}
};

class Pasajeros{
	private:
		Lista<Pasajero> listaPasajeros;
		FILE *archivo;
		Pasajero pasaux;
		int aux;
		char charAux[30];
		
	public:
		
		void agregar(){
			cout << "Nombres" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			pasaux.nombres = string(charAux);
			cout << "apellidos" << endl;
			cin.getline(charAux, 30, '\n');
			pasaux.apellidos = string(charAux);
			cout << "Número de documento" << endl;
			cin >>pasaux.numDocumento;
			// ESTA COSA ES MEGA ROMPIBLE
			cout << "fecha de nacimiento ( ingresar DD MM AAAA )" << endl;
			cin >> pasaux.nacimiento.dia;
			cin >> pasaux.nacimiento.mes;
			cin >> pasaux.nacimiento.anio;		
			do{
				cout << "tipo (1.Señor-2.Señora-3.Niño)" << endl;//rompible
				cin >> aux;
				if(aux == 1){
					pasaux.tipo = "Señor";
				} else if( aux == 2){
					pasaux.tipo = "Señora";	
				} else if(aux == 3 ){
					pasaux.tipo = "Niño";	
				}
			}while(aux != 1 && aux!= 2 && aux!= 3 );
			cout << endl;
			listaPasajeros.insertarFinal(pasaux);
		}
		
		void leer(){
			char aux[30];
			int contador=0;
			
			archivo = fopen ("registroPasajeros.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					//cout << aux << endl;
					contador++;
					if (contador==1){
						pasaux.nombres = string(aux);
						if(pasaux.nombres.find('\n')<pasaux.nombres.size()){
							pasaux.nombres.erase(pasaux.nombres.find('\n'));
						}
					} else if(contador == 2){
						pasaux.apellidos = string(aux);	
						if(pasaux.apellidos.find('\n')<pasaux.apellidos.size()){
							pasaux.apellidos.erase(pasaux.apellidos.find('\n'));
						}
					} else if (contador == 3){
						pasaux.numDocumento = atoi(aux);
					} else if (contador == 4){
						pasaux.nacimiento.dia = atoi(aux);	
					} else if (contador == 5){
						pasaux.nacimiento.mes = atoi(aux);	
					} else if ( contador == 6){
						pasaux.nacimiento.anio = atoi(aux);	
					} else if ( contador == 7){
						pasaux.tipo = string(aux);
						if(pasaux.tipo.find('\n')<pasaux.tipo.size()){
							pasaux.tipo.erase(pasaux.tipo.find('\n'));
						}
						contador=0;
						listaPasajeros.insertarFinal(pasaux);
					}				
				}
			}
			rewind(archivo);
			fclose(archivo);
		}

		void guardar(){
			if(!listaPasajeros.listaVacia()){
				archivo = fopen ("registroPasajeros.db","w");
				char auxN[30], auxA[30], auxT[30];
				if (archivo) {
				for (int i=1; i <= listaPasajeros.tamLista();i++){
						strcpy(auxN,listaPasajeros.buscar(i)->nombres.c_str());
						strcpy(auxA,listaPasajeros.buscar(i)->apellidos.c_str());
						strcpy(auxT, listaPasajeros.buscar(i)->tipo.c_str());
						fprintf(archivo,"%s\n%s\n%i\n%i\n%i\n%i\n%s\n",auxN, auxA, listaPasajeros.buscar(i)->numDocumento, listaPasajeros.buscar(i)->nacimiento.dia, listaPasajeros.buscar(i)->nacimiento.mes, listaPasajeros.buscar(i)->nacimiento.anio, auxT);
					}
				} else {
					cout << "no se pudo leer el archivo" << endl;
				}
				fclose(archivo);
			}
		} 
		
		void imprimir(){
			for(int i = 1; i <= listaPasajeros.tamLista(); i++){
				cout << "Nombre: " << listaPasajeros.buscar(i)->nombres << endl;
				cout << "Apellidos: " << listaPasajeros.buscar(i)->apellidos << endl;
				cout << "Número de documento: " << listaPasajeros.buscar(i)->numDocumento << endl;
				cout << "fecha de nacimiento: " << listaPasajeros.buscar(i)->nacimiento.dia << " " << listaPasajeros.buscar(i)->nacimiento.mes << " " << listaPasajeros.buscar(i)->nacimiento.anio << endl;
				cout << "tipo: " << listaPasajeros.buscar(i)->tipo << endl; 
				cout << endl;
			}
		}
		
		Pasajero* ingreso(){
			char charAux[30];
			int num;
			cout<< "inserte el número de documento del pasajero" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			num = atoi(charAux);
			bool encontrado = false;
			for (int i = 1; i <= listaPasajeros.tamLista(); i++){
				if(num==listaPasajeros.buscar(i)->numDocumento){
					return listaPasajeros.buscar(i);
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el pasajero" << endl;
				cout << endl;
				return NULL;
			}
		}
		
		bool buscarNombre(){
			char charAux[30];
			string nom;
			cout<< "inserte los nombres del pasajero" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			nom = string (charAux);
			bool encontrado = false;
			for (int i = 1; i <= listaPasajeros.tamLista(); i++){
				if(nom==listaPasajeros.buscar(i)->nombres){
					cout << endl;
					cout << "Nombre: " << listaPasajeros.buscar(i)->nombres << endl;
					cout << "Apellidos: " << listaPasajeros.buscar(i)->apellidos << endl;
					cout << "Numero de documento:" << listaPasajeros.buscar(i)->numDocumento << endl;
					cout << "Fecha de nacimiento: " << listaPasajeros.buscar(i)->nacimiento.dia << "/" << listaPasajeros.buscar(i)->nacimiento.mes << "/" << listaPasajeros.buscar(i)->nacimiento.anio<< endl;
					cout << endl;
					return true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el pasajero" << endl;
				cout << endl;
				return encontrado;
			}
		}
		
		bool buscarApellidos(){
			char charAux[30];
			string nom;
			cout<< "inserte los apellidos del pasajero" << endl;
			cin.sync();
			cin.getline(charAux, 30, '\n');
			nom = string (charAux);
			bool encontrado = false;
			int i; 
			for (int i = 1; i <= listaPasajeros.tamLista(); i++){
				if(nom==listaPasajeros.buscar(i)->apellidos){
					cout << endl;
					cout << "Nombre: " << listaPasajeros.buscar(i)->nombres << endl;
					cout << "Apellidos: " << listaPasajeros.buscar(i)->apellidos << endl;
					cout << "Numero de documento:" << listaPasajeros.buscar(i)->numDocumento << endl;
					cout << "Fecha de nacimiento: " << listaPasajeros.buscar(i)->nacimiento.dia << "/" << listaPasajeros.buscar(i)->nacimiento.mes << "/" << listaPasajeros.buscar(i)->nacimiento.anio<< endl;
					cout << endl;
					return true;
				}
			}
			if(!encontrado){
				cout<< "no se encontro el pasajero" << endl;
				return encontrado;
			}
		}
		bool buscarDocumento(){
			int doc;
			cout<< "inserte el documento del pasajero" << endl;
			cin >> doc ;
			bool encontrado = false;
			int i; 
			for (int i = 1; i <= listaPasajeros.tamLista(); i++){
				if(doc==listaPasajeros.buscar(i)->numDocumento){
					cout << endl;
					cout << "Nombre: " << listaPasajeros.buscar(i)->nombres << endl;
					cout << "Apellidos: " << listaPasajeros.buscar(i)->apellidos << endl;
					cout << "Numero de documento:" << listaPasajeros.buscar(i)->numDocumento << endl;
					cout << "Fecha de nacimiento: " << listaPasajeros.buscar(i)->nacimiento.dia << "/" << listaPasajeros.buscar(i)->nacimiento.mes << "/" << listaPasajeros.buscar(i)->nacimiento.anio<< endl;
					cout << endl;
					return true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el pasajero" << endl;
				cout << endl;
				return encontrado;
			}
		}
};

class VuelosP{
	private:
		FILE *archivo;
		Lista<VueloPlaneado> ListaVP;
		VueloPlaneado vpaux;
		char charAux[30];
		
	public:
		
		VueloPlaneado agregar(string aero){
			cout << "---para el vuuelo planeado---" << endl;
			vpaux.aerolinea = aero;
			cout << "Codigo (Identificador) del vuelo" << endl;
			cin >> vpaux.codigo;
			cout << "Origen" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			vpaux.origen = string(charAux);
			cout << "Destino" << endl;
			cin.getline(charAux, 30, '\n');
			vpaux.destino = string(charAux);
			do{
				cout << "Día" << endl;
				cout << "1-lunes 2-martes 3-miercoles 4-jueves 5-viernes 6-sabado 7-domingo" << endl;
				cin >> vpaux.dia;
			}while(vpaux.dia != 1 && vpaux.dia != 2 && vpaux.dia != 3 && vpaux.dia != 4 && vpaux.dia != 5 && vpaux.dia != 6 && vpaux.dia != 7);
			cout << "hora de salida" << endl;
			cin.ignore();
			cin.getline(charAux, 6, '\n');
			vpaux.horaIni = string(charAux);
			cout << "hora de llegada" << endl;
			cin.getline(charAux, 6, '\n');
			vpaux.horaFin = string(charAux);
			cout << "Número de sillas (max: 180)" << endl;
			cin.getline(charAux, 30, '\n');
			vpaux.numSillas = atoi(charAux);
			ListaVP.insertarFinal(vpaux);
			return vpaux;
		}
		
		void leer(){
			char aux[30];
			int contador=0;
			
			archivo = fopen ("registroVP.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					//cout << aux << endl;
					contador++;
					if (contador==1){
						vpaux.codigo = atoi(aux);
					} else if(contador == 2){
						vpaux.origen = string(aux);
						if(vpaux.origen.find('\n')<vpaux.origen.size()){
							vpaux.origen.erase(vpaux.origen.find('\n'));
						}	
					} else if (contador == 3){
						vpaux.destino = string(aux);
						if(vpaux.destino.find('\n')<vpaux.destino.size()){
							vpaux.destino.erase(vpaux.destino.find('\n'));
						}
					} else if (contador == 4){
						vpaux.dia = atoi(aux);
					} else if (contador == 5){
						vpaux.horaIni = string(aux);
						if(vpaux.horaIni.find('\n')<vpaux.horaIni.size()){
							vpaux.horaIni.erase(vpaux.horaIni.find('\n'));
						}	
					} else if ( contador == 6){
						vpaux.horaFin = string(aux);
						if(vpaux.horaFin.find('\n')<vpaux.horaFin.size()){
							vpaux.horaFin.erase(vpaux.horaFin.find('\n'));
						}	
							
					} else if ( contador == 7){
						vpaux.numSillas = atoi(aux);
					} else if ( contador == 8){
						vpaux.aerolinea = string(aux);	
						if(vpaux.aerolinea.find('\n')<vpaux.aerolinea.size()){
							vpaux.aerolinea.erase(vpaux.aerolinea.find('\n'));
						}
						contador=0;
						ListaVP.insertarFinal(vpaux);
					}				
				}
			}
			rewind(archivo);
			fclose(archivo);
		}

		void guardar(){
			if(!ListaVP.listaVacia()){
				archivo = fopen ("registroVP.db","w");
				char auxO[30], auxD[30], auxHI[30], auxHF[30], auxAE[30];
				if (archivo) {
				for (int i=1; i <= ListaVP.tamLista();i++){
						strcpy(auxO,ListaVP.buscar(i)->origen.c_str());
						strcpy(auxD,ListaVP.buscar(i)->destino.c_str());
						strcpy(auxHI,ListaVP.buscar(i)->horaIni.c_str());
						strcpy(auxHF,ListaVP.buscar(i)->horaFin.c_str());
						strcpy(auxAE,ListaVP.buscar(i)->aerolinea.c_str());
						fprintf(archivo,"%i\n%s\n%s\n%i\n%s\n%s\n%i\n%s\n", ListaVP.buscar(i)->codigo ,auxO, auxD, vpaux.dia, auxHI, auxHF, ListaVP.buscar(i)->numSillas, auxAE);
					}
				} else {
					cout << "no se pudo leer el archivo" << endl;
				}
				fclose(archivo);
			}
		}
		
		void imprimir(string aero){
			for(int i = 1; i <= ListaVP.tamLista(); i++){
				if(aero == ListaVP.buscar(i)->aerolinea){
				cout << "codigo: " << ListaVP.buscar(i)->codigo << endl;
				cout << "origen: " << ListaVP.buscar(i)->origen << endl;
				cout << "dedestino: " << ListaVP.buscar(i)->destino << endl;
				cout << "dia: " << ListaVP.buscar(i)->dia << endl;
				cout << "hora de inicio: " << ListaVP.buscar(i)->horaIni << endl; 
				cout << "hora de finalización: " << ListaVP.buscar(i)->horaFin << endl;
				cout << "Número de sillas: " << ListaVP.buscar(i)->numSillas << endl;
				cout << endl;
				}
			}
		}
		
		bool buscarCodigo(int cod){
			bool encontrado = false; 
			for (int i = 1; i <= ListaVP.tamLista(); i++){
				if(cod==ListaVP.buscar(i)->codigo){
					cout << endl;
					cout << "codigo: " << ListaVP.buscar(i)->codigo << endl;
					cout << "origen: " << ListaVP.buscar(i)->origen << endl;
					cout << "dedestino: " << ListaVP.buscar(i)->destino << endl;
					cout << "dia: " << ListaVP.buscar(i)->dia << endl;
					cout << "hora de inicio: " << ListaVP.buscar(i)->horaIni << endl; 
					cout << "hora de finalización: " << ListaVP.buscar(i)->horaFin << endl;
					cout << "Número de sillas: " << ListaVP.buscar(i)->numSillas << endl;
					return true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el vuelo" << endl;
				cout << endl;
				return encontrado;
			}
		}
		bool buscarOD(){
			char charAux[30];
			string origen, destino;
			cout<< "inserte la ciudad de origen" << endl;
			cin.ignore();
			cin.getline(charAux, 30, '\n');
			origen = string (charAux);
			cout<< "inserte la ciudad destino" << endl;
			cin.sync();
			cin.getline(charAux, 30, '\n');
			destino = string (charAux);
			bool encontrado = false;
			for (int i = 1; i <= ListaVP.tamLista(); i++){
				if(origen==ListaVP.buscar(i)->origen){
					if (destino==ListaVP.buscar(i)->destino){
						cout << endl;
						cout << "codigo: " << ListaVP.buscar(i)->codigo << endl;
						cout << "origen: " << ListaVP.buscar(i)->origen << endl;
						cout << "dedestino: " << ListaVP.buscar(i)->destino << endl;
						cout << "dia: " << ListaVP.buscar(i)->dia << endl;
						cout << "hora de inicio: " << ListaVP.buscar(i)->horaIni << endl; 
						cout << "hora de finalizacion: " << ListaVP.buscar(i)->horaFin << endl;
						cout << "Número de sillas: " << ListaVP.buscar(i)->numSillas << endl;
					}
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el vuelo" << endl;
				cout << endl;
				return encontrado;
			}
		}
};

class VuelosE{
	private:
		Lista<VueloEspecifico> listaVE;
		FILE *archivo;
		int precioaux, diaaux;
		Lista<string> listaSillasAux;
		string aux;
		VuelosP vp;
		

		
		
		void mergeListsO(VueloEspecifico *a, int start1, int end1, int start2, int end2){
				int finalStart= start1;
				int finalEnd= end2;
				int indexC=1;
				VueloEspecifico *result= new VueloEspecifico[end2];
				cout << start1 << " " << end1 << " " << start2 << " "<< end2 << endl;
				while (start1<= end1 && start2<=end2){
					if (a[start1].precio < a[start2].precio){
						result[indexC]=a[start1];
						start1=start1+1;
					}else{
						result[indexC]=a[start2];
						start2=start2+1;
					}
					indexC=indexC+1;
				}
				
				if (start1<=end1){
					for (int i=start1; i<=end1; i++){
						
						result[indexC]=a[i];
						indexC=indexC+1;
						cout << indexC << endl;
					 }
				}else{
					for (int i=start2; i<=end2; i++){
						result[indexC]=a[i];
						indexC=indexC+1;
						cout << indexC << endl;
					 }
				}
				indexC=1;
				for(int i=finalStart; i<=finalEnd;i++){
					a[i]=result[indexC];
					indexC=indexC+1;
					cout << indexC << endl;
				}
				cout << "--------"<< endl;
		}
			
		void mergeSortO(VueloEspecifico *a, int first, int last){
			int middle;
			if(first<last){
				middle=(first+last)/2;
				mergeSortO(a,first,middle);
				mergeSortO(a,middle+1,last);
				mergeListsO(a,first,middle,middle+1,last);
			}
		}
		
	public:
		
		void leerSillas(){
			char aux[30];
			string saux;
			archivo = fopen ("sillas.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					saux = string(aux);
					saux.erase(saux.find('\n'));
					listaSillasAux.insertarFinal(saux);
				}
			}
			rewind(archivo);
			fclose(archivo);
		}
		
		
		void agregar(VueloPlaneado vAux){
			cout<<"---Ahora para los vuelos especificos en base a el vieje planeado---"<<endl;
			cout<<"precio"<<endl;
			cin >> precioaux;
			calcularVE(vAux.codigo, vAux.dia, vAux.numSillas, precioaux);
		}
		
		VueloEspecifico* llenarArreglo(){
			VueloEspecifico *a;
			a = new VueloEspecifico [listaVE.tamLista()];
			for (int i=0 ; i<listaVE.tamLista(); i++){
				a[i] = *listaVE.buscar(i+1);
			}
			return a;
		}
		
		void itinerarios(){
			string ordenar;
			VueloEspecifico *a=llenarArreglo();
			do{
				cout << "Organizar por: (precio, horario, duracion)" << endl;
				cin >> ordenar;
			}while(ordenar != "precio" && ordenar != "horario" && ordenar != "duracion");
			if(ordenar == "precio"){
				cout << "ordenado por precio" << endl;
				cout << listaVE.tamLista() << endl;
				mergeSortO(a ,0 , listaVE.tamLista()-1);
			} else if (ordenar == "horario"){
		
			}else if (ordenar == "duracion"){
				
			}
			for(int i = 1; i <= listaVE.tamLista(); i++){
				cout << "Codigo vuelo planeado: " << a[i].codVP << endl;
				cout << "numSillas: " << a[i].numSillas << endl;
				cout << "fecha: " << a[i].date.dia << "/" << a[i].date.mes << "/" << a[i].date.anio << endl;
				cout << "Numero sillas vendidas: " << a[i].sillasVendidas.tamLista() << endl;
				cout << "Numero sillas disponibles: " << a[i].sillasDisponibles.tamLista() << endl;
				cout << endl;
			}
		}
		
		void imprimir(){
			for(int i = 1; i <= listaVE.tamLista(); i++){
				cout << "Codigo vuelo planeado: " << listaVE.buscar(i)->codVP << endl;
				cout << "numSillas: " << listaVE.buscar(i)->numSillas << endl;
				cout << "fecha: " << listaVE.buscar(i)->date.dia << "/" << listaVE.buscar(i)->date.mes << "/" << listaVE.buscar(i)->date.anio << endl;
				/*cout << "Numero sillas vendidas: " << listaVE.buscar(i)->sillasVendidas.tamLista() << endl;
				cout << "Numero sillas disponibles: " << listaVE.buscar(i)->sillasDisponibles.tamLista() << endl;*/
				cout << "sillas vendidas:" << endl;
				for(int s = 1; s <= listaVE.buscar(i)->sillasVendidas.tamLista(); s++){
					cout << " - " <<*listaVE.buscar(i)->sillasVendidas.buscar(s) << endl;
				}
				cout << "sillas disponibles:" << endl;
				for(int s = 1; s <= listaVE.buscar(i)->sillasDisponibles.tamLista(); s++){
					cout << " - " <<*listaVE.buscar(i)->sillasDisponibles.buscar(s) << endl;
				}
				cout << "precio: " << listaVE.buscar(i)->precio<< endl;
				cout << "-----------" << endl;
			}
		}
		
		void guardar(){
			archivo = fopen ("registroVE.db","w");
			char charAux[30];
			if (archivo) {
				for (int i=1; i <= listaVE.tamLista();i++){
					fprintf(archivo,"%i\n%i\n%i\n%i\n%i\n", listaVE.buscar(i)->numSillas, listaVE.buscar(i)->date.dia, listaVE.buscar(i)->date.mes,listaVE.buscar(i)->date.anio, listaVE.buscar(i)->sillasVendidas.tamLista());
					if(!listaVE.buscar(i)->sillasVendidas.listaVacia()){
						for(int s = 1; s <= listaVE.buscar(i)->sillasVendidas.tamLista(); s++){
							aux = *listaVE.buscar(i)->sillasVendidas.buscar(s);
							fprintf(archivo,"%s\n", aux.c_str()); 
						}
					}
				
					fprintf(archivo,"%i\n", listaVE.buscar(i)->sillasDisponibles.tamLista());
					if(!listaVE.buscar(i)->sillasDisponibles.listaVacia()){
						for(int s = 1; s <= listaVE.buscar(i)->sillasDisponibles.tamLista(); s++){
							aux =*listaVE.buscar(i)->sillasDisponibles.buscar(s);
							fprintf(archivo,"%s\n", aux.c_str()); 
						}
					}
					fprintf(archivo,"%i\n%i\n", listaVE.buscar(i)->precio, listaVE.buscar(i)->codVP);
					}
					
			} else {
				cout << "no se pudo leer el archivo" << endl;
			}
			fclose(archivo);
		}
		
		void calcularVE(int codigo, int dia, int numSillas, int precio){
			VueloEspecifico veaux;
			int mes= 8;
			int anio= 2022;
			//lunes 1, martes 2, miercoles 3, jueves  4, viernes  5, sabado  6, domingo  7;
			veaux.codVP = codigo;
			veaux.numSillas= numSillas;
			veaux.precio = precio;
			for(int s = 1; s <= numSillas; s++){
				aux = *listaSillasAux.buscar(s);
				//cout << aux << endl;
				veaux.sillasDisponibles.insertarFinal(aux);
			}
			int dias[7] = {1,2,3,4,5,6,7};
			for (int i = 0; i < 52 ; i++){
				dias[dia-1] += 7;
				if(dias[dia-1]>31 && (mes==1 || mes ==3 || mes ==5 || mes == 7 || mes ==8 || mes == 10 )){
					mes+=1;
					dias[dia-1] = (dias[dia-1] - 31);	
				} else if(dias[dia-1]>30 && (mes==4 || mes ==6 || mes ==9 || mes == 11)){
					mes+=1;
					dias[dia-1] = (dias[dia-1] - 30);	
				} else if(dias[dia-1]>31 && mes==12){
					mes = 1;
					anio += 1;
					dias[dia-1] = (dias[dia-1] - 31);	
				}else if(dias[dia-1]>28 && mes==2){
					mes +=1;
					dias[dia-1] = (dias[dia-1] - 28);	
				}
				veaux.date.dia=dias[dia-1];
				veaux.date.mes=mes;
				veaux.date.anio=anio;
				//cout << dias[dia-1] << "/" <<  mes << "/" << anio << endl;
				listaVE.insertarFinal(veaux);
			}
		} 
		
		
		void leer(){
			char aux[30];
			VueloEspecifico *veaux = new VueloEspecifico;;
			int contador=0;
			int dauxMax, vauxMax, vauxMin;
			string aux1;
			
			archivo = fopen ("registroVE.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					contador++;
					if (contador==1){
						veaux->numSillas = atoi(aux);
					}else if(contador == 2){
						veaux->date.dia = atoi(aux);		
					}else if (contador == 3){
						veaux->date.mes = atoi(aux);
					}else if (contador == 4){
						veaux->date.anio = atoi(aux);
					}else if (contador == 5){
						dauxMax = atoi(aux);
						for(int i = 1; i <= dauxMax; i++){
							fgets(aux,30,archivo);
							aux1 = string(aux);
							if(aux1.find('\n')<aux1.size()){
							aux1.erase(aux1.find('\n'));
							}
							veaux->sillasVendidas.insertarFinal(aux1);
						}
					}else if(contador == 6){
						dauxMax = atoi(aux);
						for(int i = 1; i <= dauxMax ; i++){
							fgets(aux,30,archivo);
							aux1 = string(aux);
							if(aux1.find('\n')<aux1.size()){
							aux1.erase(aux1.find('\n'));
							}
							veaux->sillasDisponibles.insertarFinal(aux1);
						}
					} else if(contador == 7){
						veaux->precio= atoi(aux);
					}else if (contador == 8){
						veaux->codVP= atoi(aux);
						contador = 0;
						listaVE.insertarFinal(*veaux);
						veaux = new VueloEspecifico;
					}
				}
			} else {
				cout << "no se pudo abrir el archivo" << endl;
			}
			rewind(archivo);
			fclose(archivo);
		}
		
		bool buscarCodigo(){
			int doc;
			cout<< "inserte el codigo del vuelo especifico" << endl;
			cin >> doc ;
			bool encontrado = false;
			int i; 
			cout<< "Información de los vuelos: " << endl;
			vp.buscarCodigo(doc);
			cout << "Fechas, sillas disponibles y vendidas de cada vuelo" << endl;
			for (int i = 1; i <= listaVE.tamLista(); i++){
				if(doc==listaVE.buscar(i)->codVP){
					cout << endl;
					cout << "Fecha del vuelo: " << listaVE.buscar(i)->date.dia << "/" << listaVE.buscar(i)->date.mes << "/" << listaVE.buscar(i)->date.anio<< endl;
					cout << "Costo del vuelo: " << listaVE.buscar(i)->precio << endl;
					cout << "sillas vendidas:" << listaVE.buscar(i)->sillasVendidas.tamLista() << endl;
					for(int s = 1; s <= listaVE.buscar(i)->sillasVendidas.tamLista(); s++){
					cout << " - " <<listaVE.buscar(i)->sillasVendidas.buscar(s) << endl;
					}
					cout << "sillas disponibles:" << listaVE.buscar(i)->sillasDisponibles.tamLista() << endl;
					for(int s = 1; s <= listaVE.buscar(i)->sillasDisponibles.tamLista(); s++){
					cout << " - " <<*listaVE.buscar(i)->sillasDisponibles.buscar(s) << endl;
					}
					cout << "----------------------" << endl;
					cout << endl;
					encontrado = true;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el pasajero" << endl;
				cout << endl;
				return encontrado;
			}
		}
		
		int buscarFecha(){
			int dia, mes, anio;
			cout << "inserte la fecha (formato DD MM AAAA)" << endl;
			cin  >> dia;
			cin  >> mes;
			cin  >> anio;
			bool encontrado = false;
			for (int i = 1; i <= listaVE.tamLista(); i++){
				if(dia == listaVE.buscar(i)->date.dia && mes == listaVE.buscar(i)->date.mes && anio == listaVE.buscar(i)->date.anio){
					cout << endl;
					vp.buscarCodigo(listaVE.buscar(i)->codVP);
					cout << "Fecha del vuelo: " << listaVE.buscar(i)->date.dia << "/" << listaVE.buscar(i)->date.mes << "/" << listaVE.buscar(i)->date.anio<< endl;
					cout << "Costo del vuelo: " << listaVE.buscar(i)->precio << endl;
					cout << "sillas vendidas:" << listaVE.buscar(i)->sillasVendidas.tamLista() << endl;
					for(int s = 1; s <= listaVE.buscar(i)->sillasVendidas.tamLista(); s++){
					cout << " - " <<*listaVE.buscar(i)->sillasVendidas.buscar(s) << endl;
					}
					cout << "sillas disponibles:" << listaVE.buscar(i)->sillasDisponibles.tamLista() << endl;
					for(int s = 1; s <= listaVE.buscar(i)->sillasDisponibles.tamLista(); s++){
					cout << " - " <<*listaVE.buscar(i)->sillasDisponibles.buscar(s) << endl;
					}
					cout << "----------------------" << endl;
					cout << endl;
					return i;
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el pasajero" << endl;
				cout << endl;
				return 0;
			}
		}
		
		int buscarVuelo(int doc, int dia, int mes, int anio){
			bool encontrado = false;
			cout << doc << " " << dia << " " << mes << " " << anio << endl;
			cout << listaVE.tamLista() << endl;
			for (int i = 1; i <= listaVE.tamLista(); i++){
				if(doc==listaVE.buscar(i)->codVP){
					if (dia == listaVE.buscar(i)->date.dia){
						if (mes == listaVE.buscar(i)->date.mes && anio){
						 if(anio == listaVE.buscar(i)->date.anio){
						 	cout << endl; 
							vp.buscarCodigo(doc);
							cout << "Fecha del vuelo: " << listaVE.buscar(i)->date.dia << "/" << listaVE.buscar(i)->date.mes << "/" << listaVE.buscar(i)->date.anio<< endl;
							cout << "Costo del vuelo: " << listaVE.buscar(i)->precio << endl;
							cout << "sillas vendidas:"  << listaVE.buscar(i)->sillasVendidas.tamLista() << endl;
							for(int s = 1; s <= listaVE.buscar(i)->sillasVendidas.tamLista(); s++){
							cout << " - " <<*listaVE.buscar(i)->sillasVendidas.buscar(s) << endl;
							}
							cout << "sillas disponibles:" << listaVE.buscar(i)->sillasDisponibles.tamLista() << endl;
							for(int s = 1; s <= listaVE.buscar(i)->sillasDisponibles.tamLista(); s++){
							cout << " - " <<*listaVE.buscar(i)->sillasDisponibles.buscar(s) << endl;
							}
							cout << "----------------------" << endl;
							cout << endl;
							return i;
					
				}}}
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el vuelo" << endl;
				cout << endl;
				return 0;
			}
		}
		
		bool compra(int pos, string silla){
			bool encontrado= false;
			for(int s = 1; s <= listaVE.buscar(pos)->sillasDisponibles.tamLista(); s++){
					if (silla == *listaVE.buscar(pos)->sillasDisponibles.buscar(s)){
						listaVE.buscar(pos)->sillasDisponibles.eliminar(s);
						listaVE.buscar(pos)->sillasVendidas.insertarFinal(silla);
						return true;
					}
				}
			if (!encontrado){
				cout << "no se encontro la silla" << endl;
				return false;
			}
		}
		
		
};

class Compra{
	private:
		FILE *archivo;
		Lista<Boleta> ListaB;
		Boleta auxB;
		char charAux[30];
		VuelosE ve;
	public:
		
		void agregar(VuelosE auxVE,int doc){
			ve = auxVE;
			bool opcion;
			int pos, cantidad;
			auxB.numDocumento = doc;
			cout << "---Compra de boleta---" << endl;
			cout << "Codigo (Identificador) del vuelo" << endl;
			cin >> auxB.codigo;
			cout << "Fecha (insertada como DD MM AAAA)" << endl;
			cin >> auxB.date.dia;
			cin >> auxB.date.mes;
			cin >> auxB.date.anio;
			cout << "Este es el vuelo que desea tomar? (escriba 0 para no y 1 para si)" << endl;
			pos = ve.buscarVuelo(auxB.codigo,auxB.date.dia,auxB.date.mes,auxB.date.anio);
			cin >> opcion;
			if (opcion){
				cout << "Cuantas sillas desesa reservar" << endl;
				cin >> cantidad;
				for (int i=0; i < cantidad;i++){
					cout << "inserte el codigo de una de las sillas disponibles" << endl;
					cin >> auxB.silla;
					if(ve.compra(pos, auxB.silla)){
						cout << "Compra exitosa" << endl;
					} else {
						do{
							cout << "inserte el codigo de una de las sillas disponibles" << endl;
							cin >> auxB.silla;
						}while(!ve.compra(pos, auxB.silla));
					}
					ListaB.insertarFinal(auxB);
				}
			}
		}
		
		void leer(){
			char aux[30];
			int contador=0;
			
			archivo = fopen ("registroB.db", "r") ;
			if (archivo) {
				while (!feof(archivo)){
					fgets(aux,30,archivo);
					//cout << aux << endl;
					contador++;
					if (contador==1){
						auxB.codigo = atoi(aux);
					} else if(contador == 2){
						auxB.numDocumento = atoi(aux);	
					} else if (contador == 3){
						auxB.silla = string(aux);
						if(auxB.silla.find('\n')<auxB.silla.size()){
							auxB.silla.erase(auxB.silla.find('\n'));
							}	
					} else if (contador == 4){
						auxB.date.dia = atoi(aux);
					} else if (contador == 5){
						auxB.date.mes = atoi(aux);
					} else if (contador == 6){
						auxB.date.anio = atoi(aux);
						contador=0;
						ListaB.insertarFinal(auxB);
					} 			
				}
			}
			rewind(archivo);
			fclose(archivo);
		}
	
		void guardar(){
			if(!ListaB.listaVacia()){
				archivo = fopen ("registroB.db","w");
				char auxS[30];
				if (archivo) {
				for (int i=1; i <= ListaB.tamLista();i++){
						strcpy(auxS,ListaB.buscar(i)->silla.c_str());
						fprintf(archivo,"%i\n%i\n%s\n%i\n%i\n%i\n", ListaB.buscar(i)->codigo ,ListaB.buscar(i)->numDocumento, auxS, ListaB.buscar(i)->date.dia,ListaB.buscar(i)->date.mes,ListaB.buscar(i)->date.anio );
					}
				} else {
					cout << "no se pudo leer el archivo" << endl;
				}
				fclose(archivo);
			}
		}
		/*
		void imprimir(){
			for(int i = 1; i <= ListaVP.tamLista(); i++){
				cout << "codigo: " << ListaVP.buscar(i)->codigo << endl;
				cout << "origen: " << ListaVP.buscar(i)->origen << endl;
				cout << "dedestino: " << ListaVP.buscar(i)->destino << endl;
				cout << "dia: " << ListaVP.buscar(i)->dia << endl;
				cout << "hora de inicio: " << ListaVP.buscar(i)->horaIni << endl; 
				cout << "hora de finalización: " << ListaVP.buscar(i)->horaFin << endl;
				cout << "Número de sillas: " << ListaVP.buscar(i)->numSillas << endl;
				cout << endl;
			}
		}
		
		VueloPlaneado* buscarCodigo(int cod){
			bool encontrado = false;
			int i; 
			for (int i = 1; i <= ListaVP.tamLista(); i++){
				if(cod==ListaVP.buscar(i)->codigo){
					return ListaVP.buscar(i);
				}
			}
			if(!encontrado){
				cout << endl;
				cout<< "no se encontro el pasajero" << endl;
				cout << endl;
				return NULL;
			}
		}*/
};
