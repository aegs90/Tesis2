#include "Evolucion.h"
#include "Poblacion.h"
#include <algorithm>
#include <time.h>
extern int cantidadPedido;
Evolucion::Evolucion(Poblacion* poblacion) {
	this->poblacion = poblacion;
}
void imprime(vector<Solucion*> seleccionados) {
	for (int i = 0; i < seleccionados.size(); i++) {
		for (int j = 0; j < seleccionados.at(i)->cantidadCromosomas;j++) {
			printf("[%d]", seleccionados.at(i)->cromosoma[j]);
		}
		printf("\n");
	}
}
vector<Solucion*> Evolucion::seleccion() {

	vector<Solucion*> seleccionados;
	int sizeSoluciones = poblacion->soluciones.size();
	float* probabilidades = new float[sizeSoluciones];
	float fAcumulada = 0;
	for (int i = 0; i < sizeSoluciones; i++) {
		fAcumulada = fAcumulada + poblacion->soluciones.at(i)->puntaje;
		probabilidades[i] = fAcumulada;
	}
	int cantSeleccionados = 20;
	float rx = fAcumulada / cantSeleccionados;
	for (int i = 0;i < cantSeleccionados;i++) {
		float randomR = rx * i + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / rx));
		bool found = false;
		for (int j = 0; j < sizeSoluciones && found == false;j++) {
			if (randomR < probabilidades[j]) {
				seleccionados.push_back(poblacion->soluciones.at(j));
				found = true;
			}
		}
	}
	printf("Seleccion) Cantidad de seleccionados: %d\n", seleccionados.size());
	printf("Seleccion) Cantidad de soluciones en la poblacion: %d\n", poblacion->soluciones.size());
	//imprime(seleccionados);
	return seleccionados;
}

vector<Solucion*> Evolucion::crossover(vector < Solucion*> seleccionados) {
	vector<Solucion*> nuevosHijos;
	int cantidadCrossover = seleccionados.size();

	
	for (int i = 0; i < cantidadCrossover; i++) {
		int randCromosoma = rand() % this->poblacion->cantidadCromosomas;
		int randCrossover = rand() % cantidadCrossover;
		Solucion* solucion1 = new Solucion(seleccionados.at(i), seleccionados.at(randCrossover), randCromosoma);
		Solucion* solucion2 = new Solucion(seleccionados.at(randCrossover), seleccionados.at(i), randCromosoma);
		nuevosHijos.push_back(solucion1);
		nuevosHijos.push_back(solucion2);
	}

	printf("Crossover) Nuevos hijos: %d\n", nuevosHijos.size());
	return nuevosHijos;
}
void Evolucion::mutacion(vector<Solucion*> nuevosHijos) {

	int sizeNuevosHijos = nuevosHijos.size();
	int cantMutaciones = 0;
	for (int k = 0; k < sizeNuevosHijos; k++) {
		for (int i = 0; i < this->poblacion->cantidadCromosomas; i++) {
			int r = rand() % 20;
			
			if (r == 1) {
				cantMutaciones = cantMutaciones + 1;
				int r2 = rand() % this->poblacion->cantidadCromosomas;
				int cromosomaR2 = nuevosHijos.at(k)->cromosoma[r2];
				nuevosHijos.at(k)->cromosoma[r2] = nuevosHijos.at(k)->cromosoma[i];
				nuevosHijos.at(k)->cromosoma[i] = cromosomaR2;
			}
		}
	}
	printf("Mutacion) Cantidad de Genes Mutados: %d\n", cantMutaciones);
}
void Evolucion::agregaHijos(vector<Solucion*> nuevosHijos) {
	printf("AgregaHijos) CantSoluciones: %d\nAgregaHijos) CantNuevosHijos: %d\n", poblacion->soluciones.size(), nuevosHijos.size());
	int cantNuevosHijos = nuevosHijos.size();
	for (int i = 0; i < cantNuevosHijos; i++) {
		poblacion->soluciones.push_back(nuevosHijos.at(i));
	}

	printf("AgregaHijos) CantSoluciones: %d\n", poblacion->soluciones.size());
}
bool funcCompara(Solucion* a, Solucion* b) {
	//printf("%f > %f: %d\n", a.puntaje, b.puntaje, a.puntaje > b.puntaje);
	return (a->puntaje - b->puntaje > 0.0001f);
}
void Evolucion::elitismo() {
	sort(poblacion->soluciones.begin(), poblacion->soluciones.end(), funcCompara);
	poblacion->soluciones.erase(poblacion->soluciones.end() - 40, poblacion->soluciones.end());
}
void Evolucion::imprimeTodaPoblacion() {
	poblacion->imprimeTodaPoblacion();
}