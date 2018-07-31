#pragma once

class Rodada;
#include "CartaTruco.h"
#include "Jogador.h"

class Turno
{
private:
    int id;
    static int auto_incr;
	Rodada* rodada;
	CartaTruco* maiorCarta;
	Jogador* venceuTurno;
	int cont;
    bool empate;
public:
	Turno(Rodada* const pRodada = nullptr);
	~Turno();
	void setRodada(Rodada* const pRodada);
	Rodada* const getRodada();
	void iniciarTurno();
	Jogador* const getVenceuTurno();
	CartaTruco* const getMaiorCarta();
	void comparaMaiorCarta(CartaTruco* const pCarta);
	const bool getEmpate();
};

