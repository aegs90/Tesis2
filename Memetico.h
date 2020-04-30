#pragma once
#include "Poblacion.h"
class Memetico {
public:
	int cantidadBarrasPedido;
	float largoBarra;
	Memetico(int,float);
	void printFragmentos(vector<int*>&, vector<float>&);
	void busquedaLocal(Poblacion &);
};