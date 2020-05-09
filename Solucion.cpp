#include "Solucion.h"
#include <vector>
using namespace std;
#include <algorithm>
extern int cantidadBarrasPedido;
Solucion::Solucion() {
	this->cantidadCromosomas = 0;
	this->cromosoma = NULL;
	this->puntaje = -1;
}
Solucion::Solucion(int cantidadCromosomas) {
	this->cantidadCromosomas = cantidadCromosomas;
	cromosoma = new int[cantidadCromosomas];
	for (int i = 0; i < cantidadCromosomas; i++) {
		cromosoma[i] = i;
	}
	std::random_shuffle(cromosoma, cromosoma + cantidadCromosomas);
	for (int i = 0; i < cantidadCromosomas; i++) {
		//	printf("%d",cromosoma[i]);
	}
	this->puntaje = -1;

}
Solucion::Solucion(Solucion* s1, Solucion* s2, int index) {
	this->cantidadCromosomas = s1->cantidadCromosomas;
	cromosoma = new int[s1->cantidadCromosomas];
	for (int i = 0; i < index; i++) {
		cromosoma[i] = s1->cromosoma[i];
	}
	for (int i = index; i < cantidadCromosomas; i++) {
		cromosoma[i] = s2->cromosoma[i];
	}
	fixCromosoma();
}
#include <utility>
#include <tuple>

bool comparaDesperdicios(tuple<int*, int, float, float> a, tuple<int*, int, float, float> b) {
	return get<3>(a) > get<3>(b);
}
bool comparaTamanios(tuple<int*, int, float, float> a, tuple<int*, int, float, float> b) {
	return get<2>(a) > get<2>(b);
}


void llena(int* nuevoCromosoma, int* a, int ax, int* b, int bx, int &largoNuevo) {
	for (int i = 0; i < ax; i++) {
		if (a[i] >= 0) {
			nuevoCromosoma[largoNuevo] = a[i];
			largoNuevo = largoNuevo + 1;
		}
	}
	printf("largoNuevo = %d\n", largoNuevo);
}

void Solucion::getBloques(vector<tuple<int*, int, float, float>> &bloques) {


}

void Solucion::localSearch(vector<Material*> barrasMaterial, vector<Barra*> barrasPedido) {
	printf("LocalSearch\n");
	printf("\n\nCantidad Cromosomas: %d\n\n", cantidadCromosomas);
	vector<tuple<int*, int, float, float>> bloques;

	float sumaLargos = 0;
	int materialActual = 0;
	float actLargoMaterial = barrasMaterial.at(materialActual)->largo;
	float desperdicioTotal = 0;
	int cantidadGenes = 1;
	int menosI = 1; /////////////////////////
	int totalGenes = 0;
	int* cicm = NULL;
	int* anterior = cromosoma;

	for (int i = 0; i < this->cantidadCromosomas; i++) {
		if ((actLargoMaterial - sumaLargos) >= barrasPedido.at(cromosoma[i])->largo) {
			sumaLargos = sumaLargos + barrasPedido.at(cromosoma[i])->largo;
			cantidadGenes = cantidadGenes + 1;
		}
		else {
			tuple<int*, int, float, float> bloqueTuple(anterior, cantidadGenes, sumaLargos, actLargoMaterial - sumaLargos);
			bloques.push_back(bloqueTuple);

			anterior = anterior + cantidadGenes;
			totalGenes = totalGenes + cantidadGenes;
			cantidadGenes = 1;

			desperdicioTotal = desperdicioTotal + actLargoMaterial - sumaLargos;
			materialActual = materialActual + 1;
			actLargoMaterial = barrasMaterial.at(materialActual)->largo;
			sumaLargos = barrasPedido.at(cromosoma[i])->largo;

		}
	}
	if (cantidadCromosomas - totalGenes > 0) {
		tuple<int*, int, float, float> bloqueTuple(anterior, cantidadCromosomas - totalGenes, sumaLargos, actLargoMaterial - sumaLargos);
		bloques.push_back(bloqueTuple);
	}
	printf("\nTotalGenes: %d\n", totalGenes);


	// Hasta aqui, tengo los bloques, tengo los tamanios y largos de los bloques y los desperdicios.
	// [PunteroLugar][LargoEnGenes][LargoBloque][Desperdicio]
	// Lo que hay q hacer es llenar los Desperdicios con LargoBloque

	vector<tuple<int*, int, float, float>> set3(bloques);
	sort(set3.begin(), set3.end(), comparaTamanios); // Mas a menos

	int* nuevoCromosoma = new int[cantidadCromosomas];

	int largoActual = 0;
	int cantidadTotal = 0;
	for (int i = 0;i < set3.size();i++) {
		if (get<3>(set3.at(i)) >= 0) {
			llena(nuevoCromosoma, get<0>(set3.at(i)), get<1>(set3.at(i)), NULL, 0, largoActual);
			printf("\nIfLargo: %d\n", largoActual);
			int punteroJ = -1;
			int punteroK = -1;
			float maxLargoK = 0;
			for (int j = i + 1;j < set3.size();j++) {
				if (get<3>(set3.at(j)) >= 0) {
					for (int k = 0; k < get<1>(set3.at(j)); k++) {

						if ((get<0>(set3.at(j))[k]) >= 0 &&
							get<3>(set3.at(i)) >= barrasPedido[(get<0>(set3.at(j))[k])]->largo) {

							float largoK = barrasPedido[(get<0>(set3.at(j))[k])]->largo;
							if (largoK > maxLargoK) {
								maxLargoK = largoK;
								punteroJ = j;
								punteroK = k;
							}
						}
					}
				}
			}
			if (punteroJ > -1) {

			llena(nuevoCromosoma, get<0>(set3.at(punteroJ)) + punteroK, 1, NULL, 0, largoActual);
			(get<0>(set3.at(punteroJ))[punteroK]) = -1;
			cantidadTotal = cantidadTotal + 1;
			}

			//		get<3>(set3.at(i)) = -1;
		}
	}

	printf("CantidadTotal %d\n\n", cantidadTotal);
	if (cantidadTotal == 0) {
		delete[] nuevoCromosoma;
		return;
	}
	delete[] cromosoma;
	cromosoma = nuevoCromosoma;
	printf("Antes");
}
/*void Solucion::localSearch(vector<Material*> barrasMaterial, vector<Barra*> barrasPedido) {
	printf("LocalSearch\n");
	printf("\n\nCantidad Cromosomas: %d\n\n", cantidadCromosomas);
	vector<tuple<int*, int, float, float>> bloques;

	float sumaLargos = 0;
	int materialActual = 0;
	float actLargoMaterial = barrasMaterial.at(materialActual)->largo;
	float desperdicioTotal = 0;
	int cantidadGenes = 1;
	int menosI = 1; /////////////////////////
	int totalGenes = 0;
	int* cicm = NULL;
	int* anterior = cromosoma;

	for (int i = 0; i < this->cantidadCromosomas; i++) {
		if ((actLargoMaterial - sumaLargos) >= barrasPedido.at(cromosoma[i])->largo) {
			sumaLargos = sumaLargos + barrasPedido.at(cromosoma[i])->largo;
			cantidadGenes = cantidadGenes + 1;
		}
		else {
			tuple<int*, int, float, float> bloqueTuple(anterior, cantidadGenes, sumaLargos, actLargoMaterial - sumaLargos);
			bloques.push_back(bloqueTuple);

			anterior = anterior + cantidadGenes;
			totalGenes = totalGenes + cantidadGenes;
			cantidadGenes = 1;

			desperdicioTotal = desperdicioTotal + actLargoMaterial - sumaLargos;
			materialActual = materialActual + 1;
			actLargoMaterial = barrasMaterial.at(materialActual)->largo;
			sumaLargos = barrasPedido.at(cromosoma[i])->largo;

		}
	}
	if (cantidadCromosomas - totalGenes > 0) {
		tuple<int*, int, float, float> bloqueTuple(anterior, cantidadCromosomas - totalGenes, sumaLargos, actLargoMaterial - sumaLargos);
		bloques.push_back(bloqueTuple);
	}
	printf("\nTotalGenes: %d\n", totalGenes);

	
	// Hasta aqui, tengo los bloques, tengo los tamanios y largos de los bloques y los desperdicios.
	// [PunteroLugar][LargoEnGenes][LargoBloque][Desperdicio]
	// Lo que hay q hacer es llenar los Desperdicios con LargoBloque

	vector<tuple<int*, int, float, float>> set3(bloques);
	sort(set3.begin(), set3.end(), comparaTamanios); // Mas a menos

    int* nuevoCromosoma = new int[cantidadCromosomas];

	int largoActual = 0;
	int cantidadTotal = 0;
	for (int i = 0;i < set3.size();i++) {
		if (get<3>(set3.at(i)) >= 0) {
			llena(nuevoCromosoma, get<0>(set3.at(i)), get<1>(set3.at(i)), NULL, 0, largoActual);
			printf("\nIfLargo: %d\n", largoActual);
			for (int j = i+1;j < set3.size();j++) {
				if (get<3>(set3.at(j)) >= 0) {
					for (int k = 0; k < get<1>(set3.at(j)); k++) {

						if ((get<0>(set3.at(j))[k]) >= 0 &&
							get<3>(set3.at(i)) >= barrasPedido[(get<0>(set3.at(j))[k])]->largo) {

							
							llena(nuevoCromosoma,get<0>(set3.at(j))+k, 1, NULL, 0, largoActual);
							(get<0>(set3.at(j))[k]) = -1;
							cantidadTotal = cantidadTotal + 1;
						}
					}
				}
			}
	//		get<3>(set3.at(i)) = -1;
		}
	}

	printf("CantidadTotal %d\n\n",cantidadTotal);
	if (cantidadTotal == 0) {
		delete[] nuevoCromosoma;
		return;
	}
	delete[] cromosoma;
	cromosoma = nuevoCromosoma;
	printf("Antes");
}
*/
void Solucion::fixCromosoma() {

	int* indices = new int[cantidadCromosomas];
	int cantidadIndices = 0;
	for (int i = 0;i < cantidadCromosomas;i++) {
		indices[i] = -1;
	}

	for (int i = 0;i < cantidadCromosomas;i++) {
		//printf("--%d--", i);
		//printf("--%d--", cromosoma[0]);
		if (indices[cromosoma[i]] == -1) {
			indices[cromosoma[i]] = i;////////////////////////////////////////////////////////////////////////
			cantidadIndices = cantidadIndices + 1;
		}
		else {
			int r = rand() % 2;
			if (r == 0) {
				cromosoma[i] = -1;
			}
			else {
				cromosoma[indices[cromosoma[i]]] = -1;
				indices[cromosoma[i]] = i;
			}
		}
	}
	int cantFaltantes = cantidadCromosomas - cantidadIndices;
	int* faltantes1 = new int[cantFaltantes];
	int indiceFaltantes = 0;
	vector<int> faltantes;
	for (int i = 0; i < cantidadCromosomas; i++) {
		if (indices[i] == -1) {
			faltantes.push_back(i);
			indiceFaltantes = indiceFaltantes + 1;
		}
	}
	std::random_shuffle(faltantes.begin(), faltantes.end());
	int curFaltantes = 0;
	for (int i = 0; i < cantidadCromosomas; i++) {
		if (cromosoma[i] == -1) {
			cromosoma[i] = faltantes.at(curFaltantes);
			curFaltantes = curFaltantes + 1;
		}
	}
}

void Solucion::evalua(vector<Barra*> barrasPedido, vector<Material*> barrasMaterial) {


	int sizeBarrasPedido = barrasPedido.size();
	int cantMaterialesConsumidos = 1;
	float sumaLargos = 0;
	int materialActual = 0;
	float materialUsado = 0;
	float desperdicio = 0;

	float actLargoMaterial = barrasMaterial.at(0)->largo;
	materialUsado = actLargoMaterial;
	float sumaTodosLargos = 0;

	for (int i = 0; i < sizeBarrasPedido; i++) {
		//printf("Desperdicio: %f -- LargoMaterial: %f -- LargoBarra: %f\n",desperdicio,actLargoMaterial, barrasPedido.at(cromosoma[i]).largo);
		if (actLargoMaterial - sumaLargos >= barrasPedido.at(cromosoma[i])->largo) {
			sumaLargos = sumaLargos + barrasPedido.at(cromosoma[i])->largo;
		}
		else {
			desperdicio = desperdicio + actLargoMaterial - sumaLargos;
			cantMaterialesConsumidos = cantMaterialesConsumidos + 1;
			materialActual = materialActual + 1;
			if (materialActual < barrasMaterial.size()) {
				actLargoMaterial = barrasMaterial.at(materialActual)->largo;
				materialUsado = materialUsado + actLargoMaterial;
			}
			sumaTodosLargos = sumaTodosLargos + sumaLargos;
			sumaLargos = barrasPedido.at(cromosoma[i])->largo;
		}
	}
	//	puntaje = 1000 - cantMaterialesConsumidos * 1.0f;
//	puntaje = 1000 - desperdicio;
//	puntaje = 1000 - materialActual - (actLargoMaterial - sumaLargos) * 0.01f;
//	puntaje = 1000.0f - desperdicio;
	puntaje = 1000000.0f - materialUsado * 0.1 -desperdicio * 0.1;
	puntaje = 1000000.0f - materialUsado * 0.1;
	puntaje = (100.0f - desperdicio) / sumaTodosLargos;



}