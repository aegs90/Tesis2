#include "Solucion.h"
#include <vector>
using namespace std;
#include <algorithm>
extern int cantidadBarrasPedido;
Solucion::Solucion() {
		cromosoma = new int[cantidadBarrasPedido];
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			cromosoma[i] = i;
		}

		std::random_shuffle(cromosoma, cromosoma + cantidadBarrasPedido);
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			//	printf("%d",cromosoma[i]);
		}
	}
Solucion::Solucion(Solucion s1, Solucion s2, int index) {
		cromosoma = new int[cantidadBarrasPedido];
		for (int i = 0; i < index; i++) {
			cromosoma[i] = s1.cromosoma[i];
		}
		for (int i = index; i < cantidadBarrasPedido; i++) {
			cromosoma[i] = s2.cromosoma[i];
		}
		fixCromosoma();
	}
	void Solucion::fixCromosoma() {

		for (int i = 0;i < cantidadBarrasPedido;i++) {
			//	printf("%d\n", cromosoma[i]);
		}


		//printf("asdasdas");
		int* indices = new int[cantidadBarrasPedido];
		int cantidadIndices = 0;
		for (int i = 0;i < cantidadBarrasPedido;i++) {
			indices[i] = -1;
		}

		//printf("asdasdas");
		for (int i = 0;i < cantidadBarrasPedido;i++) {
			//printf("--%d--", i);
			//printf("--%d--", cromosoma[0]);
			if (indices[cromosoma[i]] == -1) {
				//printf("--a--");
				indices[cromosoma[i]] = i;////////////////////////////////////////////////////////////////////////
				cantidadIndices = cantidadIndices + 1;
			}
			else {
				//printf("--b--");
				int r = rand() % 2;
				if (r == 0) {
					//	printf("--c--");
					cromosoma[i] = -1;
				}
				else {
					//	printf("--d--");
					cromosoma[indices[cromosoma[i]]] = -1;
					indices[cromosoma[i]] = i;
				}
			}
		}
		//printf("asdasdas");
		int cantFaltantes = cantidadBarrasPedido - cantidadIndices;
		int* faltantes1 = new int[cantFaltantes];
		int indiceFaltantes = 0;

		//printf("asdasdas");
		vector<int> faltantes;
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			if (indices[i] == -1) {
				faltantes.push_back(i);
				indiceFaltantes = indiceFaltantes + 1;
			}
		}
		std::random_shuffle(faltantes.begin(), faltantes.end());

		//printf("asdasdas");
		int curFaltantes = 0;
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			if (cromosoma[i] == -1) {
				cromosoma[i] = faltantes.at(curFaltantes);
				curFaltantes = curFaltantes + 1;
			}
		}
	}

	void Solucion::evalua(vector<Barra> barrasPedido, vector<Material> barrasMaterial) {
		int sizeBarrasPedido = barrasPedido.size();
		int cantMaterialesConsumidos = 1;
		float sumaLargos = 0;
		int materialActual = 0;
		float desperdicio = 0;
		float actLargoMaterial = barrasMaterial.at(0).largo;
		for (int i = 0; i < sizeBarrasPedido; i++) {
			//printf("Desperdicio: %f -- LargoMaterial: %f -- LargoBarra: %f\n",desperdicio,actLargoMaterial, barrasPedido.at(cromosoma[i]).largo);
			if (actLargoMaterial - sumaLargos >= barrasPedido.at(cromosoma[i]).largo) {
				sumaLargos = sumaLargos + barrasPedido.at(cromosoma[i]).largo;
			}
			else {
				desperdicio = desperdicio + actLargoMaterial - sumaLargos;
				cantMaterialesConsumidos = cantMaterialesConsumidos + 1;
				materialActual = materialActual + 1;
				actLargoMaterial = barrasMaterial.at(materialActual).largo;
				sumaLargos = barrasPedido.at(cromosoma[i]).largo;
			}
		}
		puntaje = cantMaterialesConsumidos * 1.0f;
		//printf("Desperdicio: %f\n", desperdicio);
		puntaje = desperdicio;
	}