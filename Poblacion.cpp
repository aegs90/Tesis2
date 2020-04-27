#include "Poblacion.h"

Poblacion::Poblacion() {}
void Poblacion::inicializaPoblacion() {
	this->maximoGeneraciones = 100;
	for (int i = 0; i < sizePoblacion; i++) {
		Solucion actSolucion = Solucion();
		soluciones.push_back(actSolucion);
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
/*					for (int j = 0;j < cantidadBarrasPedido;j++) {
						printf("%d-", soluciones.at(i).cromosoma[j]);
						printf("(%f)-", barrasPedido.at(soluciones.at(i).cromosoma[j]).largo);
					}
					printf("\n");*/
	}
	/*for (int i = 0; i < cantidadBarrasPedido; i++) {
		printf("%d-", i);
		printf("%f-", barrasPedido.at(i).largo);

		printf("\n");
	}*/
}
void Poblacion::levantaDatos() {
	
/*
	FILE* punteroInput;
	int openInput = fopen_s(&punteroInput,"material.txt", "r");
	char cabecera[50];
	if (openInput > 0) {
		scanf_s("%s", &cabecera,50);
		char c;
		int idMat;
		while (openInput > 0) {
			scanf_s("%c", &c,1);
			scanf_s("%d", &idMat);

			openInput = 0;
		}
	} */

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
}
void Poblacion::generaInicial() {

	// Podria generarse con un algoritmo voraz
	// Se genera aleatoriamente
	inicializaPoblacion();
	imprimeTodaPoblacion();

}
void Poblacion::imprimeMejorSolucion() {
	printf("Puntaje Solucion: %f\n", this->soluciones.at(0).puntaje);
}
