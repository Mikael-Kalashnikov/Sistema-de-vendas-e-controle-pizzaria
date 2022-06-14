#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <string.h>
#include <math.h>
#include "Cabeçalho.h"
using namespace std;

//Gerar arquivo .txt do pedido
void Recibo() {
	ifstream fin;
	ofstream fout;

	//Teste se foi aberto o arquivo com sucesso
	fin.open("pedido.txt");
	if (!fin.is_open())
	{
		cout << "A abertura do arquivo falhou!" << endl;
		exit(EXIT_FAILURE);
	}

	//Se existir documento com mesmo nome irá transcrever, senão será criado um novo
	fout.open("recibo.txt");

	//Gerar recibo
	char pizzaria[50];
	fin.getline(pizzaria, 50);
	char linha[20];
	fin.getline(linha, 20);
	unsigned quilos;
	float totalkg = 0;


	fout << pizzaria << endl;

	fout << "--------------------------------------------------" << endl;

	char ingredientes[20];
	while (!fin.eof()) {
		//Pega os ingredientes acrescentados no arquivo e padroniza, deixando a primeira letra maiuscula e as demais minusculas
		fin >> ingredientes;
		for (int i = 0; i < strlen(ingredientes); i++) {
			//Diferença entre maiúsculas e minúsculas é no quinto bit, logo, podemos fazer um OR do quinto bit com 1 para deixar a letra minúscla e depois um AND do quinto bit com 0 nas primeiras letras.
			ingredientes[i] |= (1 << 5);
			if (!i || ingredientes[i - 1] == ' ')
				ingredientes[i] &= ~(1 << 5);
		}
		fin >> quilos;
		fout << ingredientes << "\t\t" << quilos << "Kg \t" << " a \t" << " 2.50" << "/Kg \t= \tR$ " << totalkg << endl;
	}

	fout << "--------------------------------------------------" << endl;

	float totalcompra = 0;
	totalcompra += totalkg;
	fout << "\t\t\t\t\t\t\tCompra\t=\tR$" << totalcompra << endl;

	float desconto;
	if (totalcompra > 1000)
		desconto = totalcompra * 0.10f;
	else
		desconto = 0.0f;
	fout << "\t\t\t\t\t\t  Desconto\t=\tR$" << desconto << endl;

	float total;
	total = (totalcompra - desconto);
	fout << "\t\t\t\t\t\t\t Total\t=\tR$" << total << endl;

	//Fecha a leitura e escrita no documento
	fin.close();
	fout.close();
}
//Menu principal
void Menu(estoque *estoque_pedidos, int cont) {
	char opc;
	ifstream fin;
	do {
		cout << "Sistema de Controle\n"
			<< "===================\n"
			<< "(P)edir\n"
			<< "(A)dicionar\n"
			<< "(E)xcluir\n"
			<< "(L)istar\n"
			<< "(S)air\n"
			<< "===================\n"
			<< "Opção: [ ]\b\b";
		cin >> opc;
		cout << endl;

		if (opc == 'p' || opc == 'P') {
			Pedir(estoque_pedidos, cont);
		}

		if (opc == 'a' || opc == 'A') {
			estoque_pedidos = Adicionar(estoque_pedidos, cont);
		}

		if (opc == 'e' || opc == 'E') {
			Excluir(estoque_pedidos, cont);
		}

		if (opc == 'l' || opc == 'L') {
			Listar(estoque_pedidos, cont);
		}

	} while ((opc != 's') && (opc != 'S'));
	Sair(estoque_pedidos, cont);
}
//Gerar vetor expandido
estoque *VetorDinamico(estoque EstoqueProdutos[], int inicio) {
		int final = inicio * 2;
	if (inicio == 0)
		final = 2;
	if (inicio < final) {
		int n;
		n = final - inicio;
		final = inicio + pow(2, n);
	}
	else {
		final = inicio;
	}

	estoque* EstoqueAtual = new estoque[final]{};
	copy(EstoqueProdutos, EstoqueProdutos + inicio, EstoqueAtual);
	delete[] EstoqueProdutos;

	return EstoqueAtual;
}
//Itens do Menu principal
void Pedir(estoque estoque_produtos[], int cont) {
	ifstream fin;
	cout << "pedir\n"
		<< "-----\n"
		<< "Arquivo: ";
	char arquivo_pedido[20];
	cin >> arquivo_pedido;

	fin.open(arquivo_pedido);

	fin.close();
}
//Acrescenta um novo produto informado e adiciona no vetor dinâmico
estoque *Adicionar(estoque estoque_produtos[], int cont) {
	char c;
	int i = 0;
	cout << "Adicionar\n"
		<< "---------\n";
	do {
		if (i >= cont) {
			estoque_produtos = VetorDinamico(estoque_produtos, pow(2, i));
		}
		cout << "Produto: ";
		char nome[20];
		cin >> nome;

		cout << "Preço: ";
		float preco;
		cin >> preco;

		cout << "Quantidade: ";
		unsigned kg;
		cin >> kg;

		for (int i = 0; i < cont; i++) {
			if (!strcmp(nome, estoque_produtos[i].produto)) {
				estoque_produtos[i].preco = preco;
				estoque_produtos[i].kg += kg;
			}
			else if(estoque_produtos[i].kg==0) {
				strcpy(estoque_produtos[i].produto, nome);
				estoque_produtos[i].preco = preco;
				estoque_produtos[i].kg = kg;
				i++;
			}
		}

		cout << "Item adicionado com sucesso!\n\n";
		cout << "Deseja adicionar outro produto ? [S]im / [N]ão\n";
		cin >> c;
		cout << endl;
	} while (c != 'n' && c != 'N');

	return estoque_produtos;
}
//Exclui os dados do produto selecionado e remove do vetor dinâmico
estoque *Excluir(estoque estoque_produtos[], int cont) {
	cout << "Excluir\n"
		<< "-------\n";
	for (int i = 0; i < cont; i++) {
		cout << i + 1 << ") " << estoque_produtos[i].produto << endl;
	}
	cout << "Número do produto: ";
	int posicao_excluir;
	cin >> posicao_excluir;

	cout << "Deseja excluir " << estoque_produtos[posicao_excluir - 1].produto << " (S / N) ? ";
	char excluir_pedido;
	cin >> excluir_pedido;

	if (excluir_pedido == 's' || excluir_pedido == 'S') {
		for (posicao_excluir; posicao_excluir < cont; posicao_excluir++)
			estoque_produtos[posicao_excluir] = estoque_produtos[posicao_excluir + 1];
			
		strcpy(estoque_produtos[posicao_excluir].produto, " ");
		estoque_produtos[posicao_excluir].preco = 0;
		estoque_produtos[posicao_excluir].kg = 0;

		cout << "Pedido excluido com sucesso!\n" << endl;
	}
	else
		cout << "Pedido mantido!\n" << endl;

	return estoque_produtos;
}
//Lista os dados do estoque contidos no vetor dinâmico
void Listar(estoque estoque_produtos[], int cont) {
	cout << "Listagem\n"
		<< "--------\n";
	for (int i = 0; i < cont; i++) {
		cout << estoque_produtos[i].produto << "\t-  R$"
			<< fixed << setprecision(2)
			<< estoque_produtos[i].preco << "   -  "
			<< estoque_produtos[i].kg << "kg\n";
	}
	cout << endl;
}
//Repassa os dados do vetor dinâmico para um arquivo binário e encerra o programa 
void Sair(estoque estoque_produtos[], int cont) {
	ofstream fout;
	fout.open("Estoque.bin", ios_base::out | ios_base::binary);
	fout.write((char*) &estoque_produtos, sizeof(estoque));
	fout << endl;
	fout.close();
}