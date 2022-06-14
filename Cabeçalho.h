//Registro de estoque
struct estoque {
	char produto[20];
	float preco;
	unsigned kg;
};

//Gerar .txt do recibo referente ao pedido
void Recibo();

void Menu(estoque*, int);

//Vetor expandido
estoque *VetorDinamico(estoque[], int);

//Menu
void Pedir(estoque[], int);

estoque *Adicionar(estoque[], int);

estoque *Excluir(estoque[], int);

void Listar(estoque [], int);

void Sair(estoque[], int);