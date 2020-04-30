#include "Poblacion.h"
Poblacion::Poblacion() {}
Poblacion::Poblacion(int cantidadGeneraciones, int tamPoblacionInicial) {
	this->cantidadGeneraciones = cantidadGeneraciones;
	this->tamPoblacionInicial = tamPoblacionInicial;
}
void Poblacion::evaluaSoluciones() {
	int cantSoluciones = soluciones.size();
	for (int i = 0; i < cantSoluciones; i++) {
		soluciones.at(i)->evalua(barrasPedido, barrasMaterial);
	}
}
void Poblacion::imprimeTodaPoblacion() {
	int cantidadSoluciones = soluciones.size();
	float total = 0;
	for (int i = 0; i < cantidadSoluciones; i++) {
		printf("%d)", i);
		printf("%f)", soluciones.at(i)->puntaje);
		total = total + soluciones.at(i)->puntaje;
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
	printf("\nTotal: %f\n", total);
	printf("Promedio: %f\n", total / cantidadSoluciones);
}
void Poblacion::levantaDatos() {

	int cantidadCromosomas = 0;

	int cantidadMateriales = 3;
	float* materialesID = new float[cantidadMateriales];
	float* materialesLargo = new float[cantidadMateriales];
	float* materialesCantidad = new float[cantidadMateriales];
	materialesID[0] = 1;
	materialesID[1] = 2;
	materialesID[2] = 3;
	materialesLargo[0] = 10;
	materialesLargo[1] = 22;
	materialesLargo[2] = 33;
	materialesCantidad[0] = 1;
	materialesCantidad[1] = 2;
	materialesCantidad[2] = 5;

	int cantidadProductos = 5;
	float* productosID = new float[cantidadProductos];
	float* productosLargo = new float[cantidadProductos];
	productosID[0] = 1;
	productosID[1] = 2;
	productosID[2] = 3;
	productosID[3] = 4;
	productosID[4] = 5; 
	productosLargo[0] = 1;
	productosLargo[1] = 2;
	productosLargo[2] = 3;
	productosLargo[3] = 4;
	productosLargo[4] = 5;


	int cantidadPedido = 3;
	int* pedidoID = new int[cantidadPedido];
	float* pedidoCantidad = new float[cantidadPedido];
	pedidoID[0] = 1;
	pedidoID[1] = 2;
	pedidoID[2] = 4;
	pedidoCantidad[0] = 15;
	pedidoCantidad[1] = 20;
	pedidoCantidad[2] = 20;

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
		for (int j = 0; j < materialesCantidad[i];j++) {
			Material* actMaterial = new Material(materialesLargo[i]);
			barrasMaterial.push_back(actMaterial);
		}
	}
	for (int i = 0;i < cantidadPedido;i++) {
		for (int j = 0;j < pedidoCantidad[i];j++) {
			Barra* actBarra = new Barra(productosLargo[pedidoID[i]]);
			barrasPedido.push_back(actBarra);
			cantidadCromosomas = cantidadCromosomas + 1;
		}
	}
	for (int i = 0; i < tamPoblacionInicial; i++) {
		Solucion* actSolucion = new Solucion(cantidadCromosomas);
		soluciones.push_back(actSolucion);
	}
	this->cantidadCromosomas = cantidadCromosomas;
	evaluaSoluciones();
}
void Poblacion::imprimeMejorSolucion(int cantidad) {
	for (int i = 0;i < cantidad;i++) {
		printf("Puntaje Solucion: %f\n", this->soluciones.at(cantidad-i)->puntaje);
	}
}
