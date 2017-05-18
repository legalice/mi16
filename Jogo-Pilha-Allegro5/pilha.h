#pragma once

#define TAMANHO 4
using namespace std;
class Pilha
{
private:
	int topo;
	int marcador[TAMANHO];
public:
	Pilha();
	bool Vazia();
	bool Cheia();
	void Empilha(int valor, bool &deuCerto);
	void Desempilha(int &valor, bool &deuCerto);
	void ImprimePilha(Pilha &p1);
	~Pilha();
};

Pilha::Pilha() {
	topo = -1;
}

bool Pilha::Vazia() {
	if (topo == -1)
		return true;
	else return false;
}

bool Pilha::Cheia() {
	if (topo == (TAMANHO - 1))
		return true;
	else return false;
}

void Pilha::Empilha(int valor, bool &deuCerto) {
	if (Cheia())
		deuCerto = false;
	else {
		deuCerto = true;
		topo += 1;
		marcador[topo] = valor;
	}
}

void Pilha::Desempilha(int &valor, bool &deuCerto) {
	if (Vazia())
		deuCerto = false;
	else {
		deuCerto = true;
		valor = marcador[topo];
		topo -= 1;
	}
}

Pilha::~Pilha() {

}

void Pilha::ImprimePilha(Pilha &p1)
{
	int valor;
	Pilha pAux;
	bool flag1;
	while (p1.Vazia() == false) {
		p1.Desempilha(valor, flag1);
		if (flag1 == true) {
			pAux.Empilha(valor, flag1);
		}
	}
	while (pAux.Vazia() == false) {
		pAux.Desempilha(valor, flag1);
		if (flag1 == true) {
			cout << valor << endl;
			p1.Empilha(valor, flag1);
		}
	}
}
