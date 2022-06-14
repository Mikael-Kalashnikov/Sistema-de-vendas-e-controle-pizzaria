#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Cabeçalho.h"
#include <fstream>
using namespace std;

int main() {
	int cont = 0;
	//Inicialização do vetor dinâmico de forma vazia
	estoque* estoque_pedidos = new estoque[cont]{};

	//Gera recibo do pedido
	Recibo();

	//Menu principal
	Menu(estoque_pedidos, cont);

	delete [] estoque_pedidos;
}