#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Cabe�alho.h"
#include <fstream>
using namespace std;

int main() {
	int cont = 0;
	//Inicializa��o do vetor din�mico de forma vazia
	estoque* estoque_pedidos = new estoque[cont]{};

	//Gera recibo do pedido
	Recibo();

	//Menu principal
	Menu(estoque_pedidos, cont);

	delete [] estoque_pedidos;
}