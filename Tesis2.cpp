// Tesis2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

#include "Material.h"
#include "Barra.h"
#include "Solucion.h"
#include "Evolucion.h"
#include "Poblacion.h"
// Tenemos como condiciones que:
// LargoBarra <= LargoMaterial
// Suma(LargoBarra * CantidadBarras) <= LargoMaterial * CantidadMaterial
int cantidadBarrasPedido = 20;
int tiposBarras = 3;
float largoBarras[] = { 2,5,6 };
int cantidadBarras[] = { 5,4,11 };
// Sumaria = 24+148+60+318+115 = 172+378+115 = 680;
// 680 / 15 = 45.34;
int cantidadMateriales = 60;
float largoMaterial = 11;
int sizePoblacion = 100;

#include <fstream>
#include <string>
#include <string>
#include <iomanip>      // std::setprecision
void generateDatos() {

	int largoMax = 30;
	int largoMin = 1;

	int largoMMax = 60;
	int largoMMin = 2;

	int cantMax = 300;
	int cantMaxUnit = 20;
	int cantMaxM = 20;

	for (int i = 0; i < 40;i++) {
		vector<float> largos;
		vector<int> cantidades;
		vector<float> largosMateriales;
		vector<int> cantidadesMateriales;

		int cant = 0;
		float largoTotal = 0;
		while (cant < cantMax) {
			float largo = (rand() % (largoMax * 100)) / 100 + 0.1;
			int cantidad = rand() % cantMaxUnit + 1;
			cant = cant + cantidad;
			printf("L: %f %d Cantidad %d\n", largo, cantidad, cant);
			largoTotal = largoTotal + largo * cantidad;
			largos.push_back(largo);
			cantidades.push_back(cantidad);
		}
		float largoMaterial = 0;
		cant = 0;
		while (largoMaterial < largoTotal * 1.2) {
			float largo = (((rand() % (largoMMax - largoMMin)) * 100) / 100) + largoMMin;
			int cantidad = rand() % cantMaxM;
			cant = cant + cantidad;
			largoMaterial = largoMaterial + largo * cantidad;
			largosMateriales.push_back(largo);
			cantidadesMateriales.push_back(cantidad);
		}

		//Productos
		largos;
		printf("Largos %d: %d\n", i, largos.size());
		std::string word = "out";
		word.append(std::to_string(i));
		word.append(".txt");
		std::ofstream out(word);
		std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
		std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

		for (int j = 0;j < largos.size();j++) {

			std::cout << j << "\t" << std::setprecision(2) << largos.at(j) << "\n";
		}
		std::cout.rdbuf(coutbuf);



		//Pedido
		cantidades;
		std::string word2 = "pedido";
		word2.append(std::to_string(i));
		word2.append(".txt");
		std::ofstream out2(word2);
		std::streambuf* coutbuf2 = std::cout.rdbuf(); //save old buf
		std::cout.rdbuf(out2.rdbuf()); //redirect std::cout to out.txt!

		for (int j = 0;j < cantidades.size();j++) {

			std::cout << j << "\t" << cantidades.at(j) << "\n";
		}
		std::cout.rdbuf(coutbuf2);


		//Materiales
		largosMateriales;
		cantidadesMateriales;

		std::string word3 = "materiales";
		word3.append(std::to_string(i));
		word3.append(".txt");
		std::ofstream out3(word3);
		std::streambuf* coutbuf3 = std::cout.rdbuf(); //save old buf
		std::cout.rdbuf(out3.rdbuf()); //redirect std::cout to out.txt!

		for (int j = 0;j < cantidadesMateriales.size();j++) {

			std::cout << j << "\t" << largosMateriales.at(j) << "\t" << cantidadesMateriales.at(j) << "\n";
		}
		std::cout.rdbuf(coutbuf3);


	}
}

int main() {
	vector<float> puntajes;
	srand(time(0));

	//generateDatos();
	//exit(0);

	vector<float> mejores;
	for (int s = 0;s < 39;s++) {
		for (int i = 0; i < 100; i++) {
			int cantidadGeneraciones = 100;
			int tamPoblacion = 1000;
			Poblacion* poblacion = new Poblacion(cantidadGeneraciones, tamPoblacion);
			poblacion->levantaDatos(s);

			Evolucion* evolucion = new Evolucion(poblacion);

			cantidadGeneraciones = 0;
			while (cantidadGeneraciones <= poblacion->cantidadGeneraciones) {
				printf("------------\nGeneracion %d\n", cantidadGeneraciones);
				vector<Solucion*> seleccionados = evolucion->seleccion();
				vector<Solucion*> nuevosHijos = evolucion->crossover(seleccionados);
				evolucion->mutacion(nuevosHijos);
				//evolucion->busquedaLocal(nuevosHijos);
				evolucion->agregaHijos(nuevosHijos);
				poblacion->evaluaSoluciones();
				evolucion->elitismo();
				cantidadGeneraciones = cantidadGeneraciones + 1;
				evolucion->poblacion->imprimeMejorSolucion(1);
			}
			evolucion->poblacion->imprimeMejorSolucion(1);
			puntajes.push_back(evolucion->poblacion->soluciones.at(0)->puntaje);
		}
		sort(puntajes.begin(), puntajes.end());
		printf("Mejor: %f\n", puntajes.at(0));
		mejores.push_back(puntajes.at(0));
	}

	mejores;

	printf("RESULTADOS\n");
	float sumaPromedio = 0;
	for (int i = 0;i < 39;i++) {
		printf("%d) %f\n", i, mejores.at(i));
		sumaPromedio = sumaPromedio + mejores.at(i);
	}
	printf("PROMEDIO\n");
	printf("%f", sumaPromedio / 40);

	return EXIT_SUCCESS;

}