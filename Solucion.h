#pragma once
#include <vector>
#include "Material.h"
#include "Barra.h"
using namespace std;

class Solucion {
public:
	int* cromosoma;
	float puntaje;
	Solucion();
	Solucion(Solucion s1, Solucion s2, int index);
	void fixCromosoma();
	void evalua(vector<Barra> barrasPedido, vector<Material> barrasMaterial);
};