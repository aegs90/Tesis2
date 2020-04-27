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
	vector<Solucion> soluciones;
	vector<Barra> barrasPedido;
	vector<Material> barrasMaterial;
	Solucion mejorSolucion;
	int maximoGeneraciones;
	int actualGeneracion;
	float sumDesperdicios;
	Poblacion();
	void inicializaPoblacion();
	void evaluaSoluciones();
	void imprimeTodaPoblacion();
	void levantaDatos();
	void generaInicial();
	void imprimeMejorSolucion();
};