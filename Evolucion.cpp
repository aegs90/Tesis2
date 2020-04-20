#include "Evolucion.h"
#include "Poblacion.h"
#include <algorithm>
#include <time.h>
extern int cantidadBarrasPedido;
Evolucion::Evolucion(Poblacion poblacion) {
	this->poblacion = poblacion;
}
vector<Solucion> Evolucion::seleccion() {
	srand(time(0));
	vector<Solucion> seleccionados;
	int sizeSoluciones = poblacion.soluciones.size();
	float* probabilidades = new float[sizeSoluciones];
		float fAcumulada = 0;
	for (int i = 0; i < sizeSoluciones; i++) {
		fAcumulada = fAcumulada + poblacion.soluciones.at(i).puntaje;
		probabilidades[i] = fAcumulada;
	}
	int cantSeleccionados = 20;
	float rx = fAcumulada / cantSeleccionados;
	for (int i = 0;i < cantSeleccionados;i++) {
	float randomR = rx * i + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / rx));
	bool found = false;
		for (int j = 0; j < sizeSoluciones && found == false;j++) {
			if (randomR < probabilidades[j]) {
				seleccionados.push_back(poblacion.soluciones.at(j));
				found = true;
			}
		}
	}
	//printf("Size: %d\n", seleccionados.size());
	return seleccionados;
}

vector<Solucion> Evolucion::crossover(vector < Solucion> seleccionados) {
	vector<Solucion> nuevosHijos;
	int cantidadCrossover = seleccionados.size();
	int randIndex = rand() % cantidadBarrasPedido;
	for (int i = 0; i < cantidadCrossover; i++) {
		Solucion solucion1(seleccionados.at(i), seleccionados.at(i + 1), randIndex);
		Solucion solucion2(seleccionados.at(i + 1), seleccionados.at(i), randIndex);
		nuevosHijos.push_back(solucion1);
		nuevosHijos.push_back(solucion2);

		i = i + 1;
	}
	//printf("Nuevos hijos: %d", nuevosHijos.size());
	return nuevosHijos;
}
void Evolucion::mutacion(vector<Solucion> nuevosHijos) {
	int sizeNuevosHijos = nuevosHijos.size();
	for (int k = 0; k < sizeNuevosHijos; k++) {
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			int r = rand() % 20;
			if (r == 1) {
				int r2 = rand() % cantidadBarrasPedido;
				int cromosomaR2 = nuevosHijos.at(k).cromosoma[r2];
				nuevosHijos.at(k).cromosoma[r2] = nuevosHijos.at(k).cromosoma[i];
				nuevosHijos.at(k).cromosoma[i] = cromosomaR2;
			}
		}
	}
}
void Evolucion::agregarHijos(Poblacion poblacion, vector<Solucion> nuevosHijos) {
	int cantNuevosHijos = nuevosHijos.size();
	for (int i = 0; i < cantNuevosHijos; i++) {
		poblacion.soluciones.push_back(nuevosHijos.at(i));
	}
}
bool funcCompara(Solucion a, Solucion b) {
	printf("%f > %f: %d\n", a.puntaje, b.puntaje, a.puntaje > b.puntaje);
	return (a.puntaje > b.puntaje);
}
void Evolucion::elitismo() {
	sort(poblacion.soluciones.begin(), poblacion.soluciones.end(), funcCompara);
	
}