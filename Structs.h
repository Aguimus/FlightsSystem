#include "Lista.h"
#include <iostream>

using namespace std;

struct Fecha{
	int dia;
	int mes;
	int anio;
};

struct Aerolinea{
	string nombre;
	int numBanco;
	string aviones[15];
};

struct Usuario{
	string nombres;
	string apellidos;
	bool sexo;//0-Hombre 1-Mujer
	int edad;
	string nombreAerolinea;
};

struct Pasajero{
	string nombres;
	string apellidos;
	int numDocumento;
	Fecha nacimiento;
	string tipo;
};

struct VueloEspecifico{
	int numSillas=180;
	Fecha date;
	Lista<string> sillasVendidas;
	Lista<string> sillasDisponibles;
	int precio;
	int codVP;
};

struct VueloPlaneado{
	int codigo;
	string aerolinea;
	string origen, destino;
	int dia;
	string horaIni, horaFin;
	int numSillas;
};

struct Boleta{
	int codigo;
	int numDocumento;
	string silla;
	Fecha date;
};
