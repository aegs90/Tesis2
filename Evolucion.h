#pragma once
#include <vector>
#include "Solucion.h"
#include "Poblacion.h"
using namespace std;

class Evolucion {
public:
	Poblacion poblacion;
	Evolucion(Poblacion poblacion);
	vector<Solucion> seleccion();
	vector<Solucion> crossover(vector < Solucion> seleccionados);
	void mutacion(vector<Solucion> nuevosHijos);
	void agregarHijos(Poblacion poblacion, vector<Solucion> nuevosHijos);
	void elitismo();
};