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
int cantidadBarrasPedido = 132;
int tiposBarras = 5;
float largoBarras[] = { 2,4,5,6,5 };
int cantidadBarras[] = { 12,32,12,53,23 };
// Sumaria = 24+148+60+318+115 = 172+378+115 = 680;
// 680 / 15 = 45.34;
int cantidadMateriales = 60;
float largoMaterial = 15;
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
		float sizeBarrasPedido = barrasPedido.size();
		int cantMaterialesConsumidos = 0;
		float sumaLargos = 0;
		for (int i = 0; i < sizeBarrasPedido; i++) {
			if (largoMaterial - sumaLargos >= barrasPedido.at(i).largo) {
				sumaLargos = sumaLargos + barrasPedido.at(i).largo;
			}
			else {
				cantMaterialesConsumidos = cantMaterialesConsumidos + 1;
				sumaLargos = 0;
			}
		}
		puntaje = cantMaterialesConsumidos;
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
			printf("((%d))", barrasPedido.size());
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
			}
			printf("\n");
		}
		for (int i = 0; i < cantidadBarrasPedido; i++) {
			printf("%d-", i);
			printf("%f-", barrasPedido.at(i).largo);

			printf("\n");
		}
	}
};
void levantaDatos() {
	// Genera las clases a partir de arreglos de datos
}
void generaInicial() {

	// Podria generarse con un algoritmo voraz
	// Se genera aleatoriamente
	
	Poblacion poblacion = Poblacion();
	poblacion.inicializaPoblacion();
	poblacion.imprimeTodaPoblacion();

}

int main()
{

	std::cout << "Hello World!\n";
	srand(time(NULL));
	generaInicial();
	/*givePuntaje();
	//imprimeResult();
	int cant = 0;
	while (cant < 100) {
		setElegidos();
		combinaElegidos();
		givePuntaje();
		//imprimeTop();
		cant = cant + 1;
		//printf("_%d_", cant);
	}
	sort(mapas.begin(), mapas.end(), compara);

	imprimeResult();*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
