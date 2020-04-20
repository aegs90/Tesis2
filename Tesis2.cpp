// Tesis2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
/*
class TipoBarra {
	int id;
	float largoBarra;
};

class Material {
	Barra *tiposdeBarrasDisponibles;
	int *cantidadPorTipoDeBarra;
};

class Producto {
	int id;
	float largo;
};

class LineaPedido {
	int idLinea;
	Producto productoPedido;
	int cantidad;
};

class Pedido {
	int idPedido;
	Material materialDisponible;
	LineaPedido* lineasDePedido;
};

class Cromosoma {
	int idCromosoma;
	int idPedido;
	int* idProductoProducido;
};

class Poblacion {
	int idMejorSolucion;
	int cantidadGeneraciones;
	Cromosoma* cromosomas;
};
*/

#include "Material.h"
#include "Barra.h"
#include "Solucion.h"
#include "Evolucion.h"
#include "Poblacion.h"
// Tenemos como condiciones que:
// LargoBarra <= LargoMaterial
// Suma(LargoBarra * CantidadBarras) <= LargoMaterial * CantidadMaterial
int cantidadBarrasPedido = 20;
int tiposBarras = 3;
float largoBarras[] = { 2,5,6 };
int cantidadBarras[] = { 5,4,11 };
// Sumaria = 24+148+60+318+115 = 172+378+115 = 680;
// 680 / 15 = 45.34;
int cantidadMateriales = 60;
float largoMaterial = 11;
int sizePoblacion = 100;

void levantaDatos() {
	// Genera las clases a partir de arreglos de datos
}


int main()
{

	std::cout << "Hello World!\n";
	srand(time(NULL));
	Poblacion poblacion = Poblacion();
	poblacion.generaInicial();

	Evolucion evolucion = Evolucion(poblacion);

	int cantidadGeneraciones = 0;
	while (cantidadGeneraciones <= poblacion.maximoGeneraciones) {
		vector<Solucion> seleccionados = evolucion.seleccion();
		vector<Solucion> nuevosHijos = evolucion.crossover(seleccionados);
		evolucion.mutacion(nuevosHijos);
		evolucion.agregarHijos(poblacion, nuevosHijos);
		evolucion.elitismo();
		cantidadGeneraciones = cantidadGeneraciones + 1;
	}
	poblacion.imprimeMejorSolucion();
}
