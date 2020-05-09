#pragma once
#include <vector>
#include "Solucion.h"
#include "Poblacion.h"
using namespace std;

class Evolucion {
public:
	Poblacion* poblacion;
	Evolucion(Poblacion* poblacion);
	vector<Solucion*> seleccion();
	vector<Solucion*> crossover(vector < Solucion*>&);
	void mutacion(vector<Solucion*>&);
	void agregaHijos(vector<Solucion*>&);
	void elitismo();
	void busquedaLocal(vector<Solucion*>&);
	void imprimeTodaPoblacion();
};