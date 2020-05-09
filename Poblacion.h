#pragma once
#include <vector>
#include "Solucion.h"

extern float largoMaterial;
extern int barrasPedido;
extern int cantidadBarras[];
extern int cantidadMateriales;
extern float largoBarras[];
extern int sizePoblacion;
extern int tiposBarras;
class Poblacion {
public:
	int cantidadGeneraciones;
	int tamPoblacionInicial;
	int cantidadCromosomas;
	vector<Solucion*> soluciones;
	vector<Barra*> barrasPedido;
	vector<Material*> barrasMaterial;
	Solucion mejorSolucion;
	int maximoGeneraciones;
	int actualGeneracion;
	float sumDesperdicios;
	Poblacion();
	Poblacion(int,int);
	void evaluaSoluciones();
	void imprimeTodaPoblacion();
	void levantaDatos(int);
	void imprimeMejorSolucion(int);
};