// Tesis2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
/*
class TipoBarra {
	int id;
	float largoBarra;
};

class Material {
	Barra *tiposdeBarrasDisponibles;
	int *cantidadPorTipoDeBarra;
};

class Producto {
	int id;
	float largo;
};

class LineaPedido {
	int idLinea;
	Producto productoPedido;
	int cantidad;
};

class Pedido {
	int idPedido;
	Material materialDisponible;
	LineaPedido* lineasDePedido;
};

class Cromosoma {
	int idCromosoma;
	int idPedido;
	int* idProductoProducido;
};

class Poblacion {
	int idMejorSolucion;
	int cantidadGeneraciones;
	Cromosoma* cromosomas;
};
*/

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
class Barra {

public:
	float largo;
	Barra(float largoBarra) {
		largo = largoBarra;
	}
};
class Solucion {
public:
	int* cromosoma;
	float puntaje;
	Solucion() {
		cromosoma = new int[cantidadBarrasPedido];
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			cromosoma[i] = i;
		}
		std::random_shuffle(cromosoma, cromosoma + cantidadBarrasPedido);
	}
	void evalua(vector<Barra> barrasPedido) {
		int sizeBarrasPedido = barrasPedido.size();
		int cantMaterialesConsumidos = 1;
		float sumaLargos = 0;
		for (int i = 0; i < sizeBarrasPedido; i++) {
			//printf("(((%f)))", barrasPedido.at(i).largo);
			
			if (largoMaterial - sumaLargos >= barrasPedido.at(i).largo) {
				sumaLargos = sumaLargos + barrasPedido.at(i).largo;
			}
			else {
				cantMaterialesConsumidos = cantMaterialesConsumidos + 1;
				sumaLargos = barrasPedido.at(i).largo;
			}
			//printf("(((%f)))", sumaLargos);

		}
//		printf("---%d---", cantMaterialesConsumidos);
		puntaje = cantMaterialesConsumidos * 1.0f;
	}
};
class Poblacion {
public:
	vector<Solucion> soluciones;
	vector<Barra> barrasPedido;
	Solucion mejorSolucion;
	int maximoGeneraciones;
	int actualGeneracion;
	Poblacion() {
		
	}
	void inicializaPoblacion() {
		for (int i = 0; i < sizePoblacion; i++) {
			Solucion actSolucion = Solucion();
			soluciones.push_back(actSolucion);
		}
		for (int i = 0;i < tiposBarras;i++) {
			for (int j = 0;j < cantidadBarras[i];j++) {
				Barra actBarra = Barra(largoBarras[i]);
				barrasPedido.push_back(actBarra);
			}
		}
		evaluaSoluciones();
	}
	void evaluaSoluciones() {
		int cantSoluciones = soluciones.size();
		for (int i = 0; i < cantSoluciones; i++) {
			soluciones.at(i).evalua(barrasPedido);
		}
	}
	void imprimeTodaPoblacion() {
		for (int i = 0; i < sizePoblacion; i++) {
			printf("%d)", i);
			printf("%f)", soluciones.at(i).puntaje);
			for (int j = 0;j < cantidadBarrasPedido;j++) {
				printf("%d-", soluciones.at(i).cromosoma[j]);
				printf("(%f)-", barrasPedido.at(soluciones.at(i).cromosoma[j]).largo);
			}
			printf("\n");
		}
		/*for (int i = 0; i < cantidadBarrasPedido; i++) {
			printf("%d-", i);
			printf("%f-", barrasPedido.at(i).largo);

			printf("\n");
		}*/
	}
	void generaInicial() {

		// Podria generarse con un algoritmo voraz
		// Se genera aleatoriamente
		inicializaPoblacion();
		imprimeTodaPoblacion();

	}
	void imprimeMejorSolucion() {

	}
};
void levantaDatos() {
	// Genera las clases a partir de arreglos de datos
}

class Evolucion {
public:
	Evolucion() {

	}
	vector<Solucion> seleccion() {

	}
	vector<Solucion> crossover(vector < Solucion> seleccionados) {

	}
	void mutacion(vector<Solucion> nuevosHijos) {

	}
	void agregaHijos(Poblacion poblacion, vector<Solucion> nuevosHijos) {

	}
	void elitismo(vector<Solucion> nuevosHijos) {

	}
};
int main()
{

	std::cout << "Hello World!\n";
	srand(time(NULL));
	Poblacion poblacion = Poblacion();
	poblacion.generaInicial();
	/*givePuntaje();
	//imprimeResult();
	int cant = 0;
	*/
	int cantidadGeneraciones = 0;
	while (cantidadGeneraciones <= poblacion.maximoGeneraciones) {
		vector<Solucion> seleccionados = evolucion.seleccion();
		vector<Solucion> nuevosHijos = evolucion.crossover(seleccionados);
		evolucion.mutacion(nuevosHijos);
		evolucion.agregarHijos(poblacion, nuevosHijos);
		evolucion.elistimo(poblacion);
		cantidadGeneraciones = cantidadGeneraciones + 1;
	}
	poblacion.imprimeMejorSolucion();

}
