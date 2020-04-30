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

#include "PoblacionG.h"
int main() {

	srand(time(0));
	int cantidadGeneraciones = 1000;
	int tamPoblacion = 1000;
	Poblacion* poblacion = new Poblacion(cantidadGeneraciones,tamPoblacion);
	poblacion->levantaDatos();

	Evolucion* evolucion = new Evolucion(poblacion);

	cantidadGeneraciones = 0;
	while (cantidadGeneraciones <= poblacion->cantidadGeneraciones) {
		printf("------------\nGeneracion %d\n", cantidadGeneraciones);
		vector<Solucion*> seleccionados = evolucion->seleccion();
		vector<Solucion*> nuevosHijos = evolucion->crossover(seleccionados);
		evolucion->mutacion(nuevosHijos);
		evolucion->agregaHijos(nuevosHijos);
		poblacion->evaluaSoluciones();

		evolucion->elitismo();
		cantidadGeneraciones = cantidadGeneraciones + 1;
		//evolucion->imprimeTodaPoblacion();


		printf("Puntaje90: %f\n",evolucion->poblacion->soluciones.at(99)->puntaje);
		evolucion->poblacion->imprimeMejorSolucion(1);
	}
	evolucion->poblacion->imprimeMejorSolucion(1);
	return EXIT_SUCCESS;
}