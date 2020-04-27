// Tesis2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

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
	srand(time(0));
	Poblacion poblacion = Poblacion();
	poblacion.levantaDatos();
	poblacion.generaInicial();
	
	Evolucion evolucion = Evolucion(poblacion);

	int cantidadGeneraciones = 0;
	while (cantidadGeneraciones <= poblacion.maximoGeneraciones) {
		printf("------------\nGeneracion %d\n", cantidadGeneraciones);
		vector<Solucion> seleccionados = evolucion.seleccion();
		vector<Solucion> nuevosHijos = evolucion.crossover(seleccionados);
		evolucion.mutacion(nuevosHijos);
		evolucion.agregarHijos(poblacion, nuevosHijos);
		evolucion.elitismo(poblacion);
		cantidadGeneraciones = cantidadGeneraciones + 1;
		evolucion.poblacion.imprimeTodaPoblacion();
		evolucion.poblacion.imprimeMejorSolucion();
	}
	evolucion.poblacion.imprimeMejorSolucion();
}
