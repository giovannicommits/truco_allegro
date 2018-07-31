#pragma once
#include "CartaTruco.h"
#include <vector>

#include <iostream>
#include <time.h>

using namespace std;

class Baralho
{
private:
    vector<CartaTruco*> todasCartas;
	vector<CartaTruco*> cartasUsadas;
	vector<CartaTruco*> cartasBaralho;
	vector<CartaTruco*> cartasDescarte;
	vector<CartaTruco*>::iterator it;
	CartaTruco* cartaVirada;

	int numZap;

public:
	Baralho();
	~Baralho();
	void baralhoParaUsada(CartaTruco* const pCarta);
	void usadaParaBaralho(CartaTruco* const pCarta);
	void usadaParaDescarte(CartaTruco* const pCarta);
	void descarteParaBaralho(CartaTruco* const pCarta);
	CartaTruco* const cartaBaralhoParaUsada();
	void resetaBaralho();
	void devolveUsadas();
	void devolveDescartes();
	void resetaValores();
	void embaralha();
	void atualizaValores();
    void setNumZap(const int aNum);
    const int getNumZap();
	CartaTruco* const virarCarta();
	CartaTruco* const getCartaVirada();
	vector<CartaTruco*> get_cartas_descarte();
	void desvirarCarta();
};
