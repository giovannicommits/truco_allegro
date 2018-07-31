#pragma once
#include "Turno.h"
#include "CartaTruco.h"

class Partida;

class Rodada
{
private:
	int id;
	static int auto_incr;
	int valor;
	int timeTruco;
	//	turnos feitos de cada equipe
	int feitas[2];
	Partida* partida;
	Turno* turnos[3];
	Jogador* jogadorInicial;
	int num_turnos;

public:
	Rodada();
	Rodada(Partida* const pPartida);
	~Rodada();
	void distribuirCartas();
	void truco();
	void setPartida(Partida* const pPartida);
	Partida* const getPartida();
	void addFeitas1();
	void addFeitas2();
	const int getFeitas1();
	const int getFeitas2();
	void resetaFeitas();
	void iniciarRodada();
	Turno* getTurnoAtual();
	int getValor();
	int getNumTurnos();
	int getTimeTruco();
	void setTimeTruco(int aTime);
};

