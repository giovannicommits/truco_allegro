#pragma once
#include "Jogador.h"
#include "Baralho.h"
#include "Rodada.h"
#include <list>

class Sistema_Grafico;

using namespace std;

class Partida
{
private:
	int id;
	static int auto_incr;
	int pontos[2];
    int timeVenc;
	
	list<Jogador*> jogadores;
	list<Jogador*> jogs1;
	list<Jogador*> jogs2;
    list<Jogador*>::iterator it;
	int num_rodadas;

	Baralho* baralho;
	Sistema_Grafico* sistGraf;
	list<Rodada*> rodadas;

public:
    Partida(Sistema_Grafico* const pSist = nullptr);
	~Partida();
	void addJogador(Jogador* const pJogador, const int numTime);
	void addJogador(Jogador* const pJogador);
	void removeJogadores();
	const int getNumJogs();
	void addJogs1(Jogador* const pJog1);
	void addJogs2(Jogador* const pJog2);
	//  passa o jogador
	Jogador* const proxJogador();
	//  apenas retorna quem é o próximo jogador
	Jogador* const getProxJogador();
	void setJogadorAtual(Jogador* const pJog);
	Jogador* const getJogadorAtual();
	void setBaralho(Baralho* const pBaralho);
	Baralho* const getBaralho();
	const int getPontosTime1();
	const int getPontosTime2();
	void iniciaPartida();
	void addPontosJogs1(const int aPontos = 1);
	void addPontosJogs2(const int aPontos = 1);
	const int getTimeJogador(Jogador* const pJog);
	const int getTimeVenc();
	Rodada* getRodadaAtual();
	Sistema_Grafico* const getSistemaGrafico();
	list<Jogador*> getJogsEmOrdem();
	void resetaCartasJogs();
	static bool fechar;
	list<Jogador*> getJogsDoTime(int ctime);
};

