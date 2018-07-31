#include "stdafx.h"
#include "Partida.h"
#include "Sistema_Grafico.h"

int Partida::auto_incr = 1;
bool Partida::fechar = false;

Partida::Partida(Sistema_Grafico* const pSist)
{
	id = auto_incr;
	pontos[0] = 0;
	pontos[1] = 0;
	baralho = nullptr;
	auto_incr++;
	timeVenc = 0;
	num_rodadas = 0;
	sistGraf = pSist;
	pSist->setPartida(this);
}


Partida::~Partida()
{
	baralho = nullptr;
	jogadores.clear();
	jogs1.clear();
	jogs2.clear();

	Rodada* pRodada;
	while (rodadas.size() > 0)
	{
		pRodada = rodadas.front();
		delete(pRodada);
		rodadas.pop_front();
	}
	sistGraf = nullptr;
}

void Partida::setBaralho(Baralho* const pBaralho)
{
    baralho = pBaralho;
}

/*
	adiciona um jogador a partida
*/
void Partida::addJogador(Jogador* const pJogador)
{
    jogadores.push_back(pJogador);
	if (jogadores.size() == 1)
		it = jogadores.begin();
}

/*
	adiciona um jogador a partida e ao time do valor numTime (time 1 ou 2)
*/
void Partida::addJogador(Jogador* const pJogador, const int numTime)
{
    jogadores.push_back(pJogador);
    if(jogadores.size() == 1)
        it = jogadores.begin();
    if(numTime == 1)
        addJogs1(pJogador);
    else if(numTime == 2)
        addJogs2(pJogador);
}

/*
	remove todos jogadores da partida
*/
void Partida::removeJogadores()
{
    jogadores.clear();
	jogs1.clear();
	jogs2.clear();
}

/*
	adiciona um jogador ao time 1
*/
void Partida::addJogs1(Jogador* const pJog1)
{
    jogs1.push_back(pJog1);
}

/*
	adiciona um jogador ao time 2
*/
void Partida::addJogs2(Jogador* const pJog2)
{
    jogs2.push_back(pJog2);
}

/*
	passa a vez para o próximo jogador
*/
Jogador* const Partida::proxJogador()
{
    it++;
    if(it == jogadores.end())
        it = jogadores.begin();
    return (*it);
}

/*
	retorna o próximo jogador
*/
Jogador* const Partida::getProxJogador()
{
    list<Jogador*>::iterator auxIt = it;
    auxIt++;
    if(auxIt == jogadores.end())
        auxIt = jogadores.begin();
    return (*auxIt);
}

/*
	define qual é o jogador atual
*/
void Partida::setJogadorAtual(Jogador* const pJog)
{
    for(it = jogadores.begin(); it != jogadores.end(); it++)
        if(*it == pJog)
            return;
}


Jogador* const Partida::getJogadorAtual()
{
    return (*it);
}


const int Partida::getNumJogs()
{
	return jogadores.size();
}


const int Partida::getPontosTime1()
{
	return pontos[0];
}


const int Partida::getPontosTime2()
{
	return pontos[1];
}

/*
	loop da partida
*/
void Partida::iniciaPartida()
{
	fechar = false;
	// reseta o baralho e as cartas dos jogadores antes da partida iniciar
	baralho->resetaBaralho();
	resetaCartasJogs();
	// enquanto um dos times não atingir 12 pontos
    while(pontos[0] < 12 && pontos[1] < 12)
    {
	// cria uma rodada e adiciona-a ao vetor de rodadas da partida e inicia-a
        Rodada* rodadaAtual = new Rodada();
        rodadas.push_back(rodadaAtual);
        rodadaAtual->setPartida(this);
        rodadaAtual->iniciarRodada();
		if (fechar)
			return;
		num_rodadas++;
    }
	// caso o time 1 (pontos[0] se refere aos pontos do time 1) atingido
	// 12 pontos, define o time 1 como vencedor e mostra a tela de vitória 
	if (pontos[0] >= 12) {
		cout << "tela de vitoria time 1" << endl;
		timeVenc = 1;
		sistGraf->tela_vitoria();
	}
	// caso o time 2 (pontos[1] se refere aos pontos do time 2) atingido
	// 12 pontos, define o time 2 como vencedor e mostra a tela de vitória 
	else if (pontos[1] >= 12) {
		cout << "tela de vitoria time 2" << endl;
		timeVenc = 2;
		sistGraf->tela_vitoria();
	}
}


void Partida::addPontosJogs1(const int aPontos)
{
    pontos[0]+=aPontos;
}


void Partida::addPontosJogs2(const int aPontos)
{
    pontos[1]+=aPontos;
}


Baralho* const Partida::getBaralho()
{
    return baralho;
}

/*
	retorna o time (1, 2 ou -1 caso não seja de time nenhum) do jogador "pJog"
*/
const int Partida::getTimeJogador(Jogador* const pJog)
{
    for(list<Jogador*>::iterator auxIt = jogs1.begin(); auxIt != jogs1.end(); auxIt++)
    {
        if((*auxIt) == pJog)
            return 1;
    }
    for(list<Jogador*>::iterator auxIt = jogs2.begin(); auxIt != jogs2.end(); auxIt++)
    {
        if((*auxIt) == pJog)
            return 2;
    }
    return -1;
}

const int Partida::getTimeVenc()
{
    return timeVenc;
}

Rodada* Partida::getRodadaAtual() {
	std::list<Rodada*>::iterator it = std::next(rodadas.begin(), num_rodadas);
	return *it;
}

Sistema_Grafico * const Partida::getSistemaGrafico()
{
	return sistGraf;
}

/*
	retorna os jogadores em ordem de vez (primeiro quem está jogando, segundo o próximo a jogar e assim por diante)
*/
list<Jogador*> Partida::getJogsEmOrdem()
{
	list<Jogador*>::iterator aux = it;
	list<Jogador*> jogsEmOrdem;
	for (int i = 0; i < jogadores.size(); i++)	
	{
		jogsEmOrdem.push_back(*aux);
		aux++;
		if (aux == jogadores.end())
			aux = jogadores.begin();
	}
	return jogsEmOrdem;
}

/*
	retira dos jogadores todas cartas que estão com eles
*/
void Partida::resetaCartasJogs()
{
	list<Jogador*>::iterator auxIt;
	for (auxIt = jogadores.begin(); auxIt != jogadores.end(); auxIt++)
	{
		(*auxIt)->resetaCartas();
	}
}


list<Jogador*> Partida::getJogsDoTime(int ctime) {
	if (ctime == 1)
		return jogs1;
	else if (ctime == 2)
		return jogs2;
}
