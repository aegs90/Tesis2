#include "Solucion.h"
#include <vector>
using namespace std;
#include <algorithm>
extern int cantidadBarrasPedido;
Solucion::Solucion() {}
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
	float desperdicio = 0;
	float actLargoMaterial = barrasMaterial.at(0)->largo;
	for (int i = 0; i < sizeBarrasPedido; i++) {
		//printf("Desperdicio: %f -- LargoMaterial: %f -- LargoBarra: %f\n",desperdicio,actLargoMaterial, barrasPedido.at(cromosoma[i]).largo);
		if (actLargoMaterial - sumaLargos >= barrasPedido.at(cromosoma[i])->largo) {
			sumaLargos = sumaLargos + barrasPedido.at(cromosoma[i])->largo;
		}
		else {
			desperdicio = desperdicio + actLargoMaterial - sumaLargos;
			cantMaterialesConsumidos = cantMaterialesConsumidos + 1;
			materialActual = materialActual + 1;
			actLargoMaterial = barrasMaterial.at(materialActual)->largo;
			sumaLargos = barrasPedido.at(cromosoma[i])->largo;
		}
	}
	puntaje = 1000 - cantMaterialesConsumidos * 1.0f;
	puntaje = 1000 - desperdicio;
	puntaje = 1000 - materialActual - (actLargoMaterial - sumaLargos) * 0.01f;
	puntaje = 1000.0f - desperdicio;
	//printf("Desperdicio: %f\n", desperdicio);
//		puntaje = 1000 -desperdicio;

}