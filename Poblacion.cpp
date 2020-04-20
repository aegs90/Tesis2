#include "Poblacion.h"
Poblacion::Poblacion() {}
void Poblacion::inicializaPoblacion() {

	for (int i = 0; i < sizePoblacion; i++) {
		Solucion actSolucion = Solucion();
		soluciones.push_back(actSolucion);
	}

		for (int i = 0; i < cantidadMateriales; i++) {
			Material actMaterial = Material(largoMaterial);
			barrasMaterial.push_back(actMaterial);
		}
		for (int i = 0;i < tiposBarras;i++) {
			for (int j = 0;j < cantidadBarras[i];j++) {
				Barra actBarra = Barra(largoBarras[i]);
				barrasPedido.push_back(actBarra);
			}
		}
		evaluaSoluciones();
	}
	void Poblacion::evaluaSoluciones() {
		sumDesperdicios = 0;
		int cantSoluciones = soluciones.size();
		for (int i = 0; i < cantSoluciones; i++) {
			soluciones.at(i).evalua(barrasPedido, barrasMaterial);
			sumDesperdicios = sumDesperdicios + soluciones.at(i).puntaje;
		}
	}
	void Poblacion::imprimeTodaPoblacion() {
		for (int i = 0; i < sizePoblacion; i++) {
			printf("%d)", i);
			printf("%f)", soluciones.at(i).puntaje);
			/*			for (int j = 0;j < cantidadBarrasPedido;j++) {
							printf("%d-", soluciones.at(i).cromosoma[j]);
							printf("(%f)-", barrasPedido.at(soluciones.at(i).cromosoma[j]).largo);
						}
			*/			printf("\n");
		}
		/*for (int i = 0; i < cantidadBarrasPedido; i++) {
			printf("%d-", i);
			printf("%f-", barrasPedido.at(i).largo);

			printf("\n");
		}*/
	}
	void Poblacion::generaInicial() {

		// Podria generarse con un algoritmo voraz
		// Se genera aleatoriamente
		inicializaPoblacion();
		imprimeTodaPoblacion();

	}
	void Poblacion::imprimeMejorSolucion() {

	}
