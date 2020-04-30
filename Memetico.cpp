#include "Memetico.h"
Memetico::Memetico(int cantidadBarrasPedido, float largoBarra) {
	this->cantidadBarrasPedido = cantidadBarrasPedido;
	this->largoBarra = largoBarra;
}
void Memetico::printFragmentos(vector<int*> &fragmentos, vector<float> &vacios) {
	
}
void Memetico::busquedaLocal(Poblacion &p) {
/*
	int tamPoblacion = p.soluciones.size();
	for (int i = 0;i < tamPoblacion;i++) {
		vector<int*> fragmentos;
		vector<float> vacios;
		float sumaLargos = 0;
		float desperdicio = 0;
		int sumLargos = 0;
		float actLargoMaterial = largoMaterial;
		for (int j = 0;j < cantidadBarrasPedido;j++) {
			if (actLargoMaterial - sumLargos >= ((p.soluciones.at(i).cromosoma[j]).largo)) {
				sumLargos = sumLargos + p.soluciones.at(i).cromosoma[j].largo;
			}
			else {
				int* fragmento = p.soluciones.at(i).cromosoma + j;
				fragmentos.push_back(fragmento);
				vacios.push_back(actLargoMaterial - sumaLargos);
				actLargoMaterial = largoBarra;
				sumaLargos = p.soluciones.at(i).cromosoma[j].largo;
			}
		}
		printFragmentos(fragmentos,vacios);
	}
*/
}