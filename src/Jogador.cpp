#include "stdafx.h"
#include "Jogador.h"
int Jogador::auto_incr = 1;

Jogador::Jogador(const string aNome)
{
	id = auto_incr;
	nome = aNome;
	auto_incr++;
}


Jogador::~Jogador()
{
	cartas.clear();
}

int Jogador::getId() { return id; }

/*
	define as cartas do jogador como pCartas
*/
void Jogador::setCartas(const vector<CartaTruco*> pCartas)
{
    cartas = pCartas;
}

/*
	retorna todas as cartas do jogador
*/
vector<CartaTruco*> const Jogador::getCartas()
{
	return cartas;
}

/*
	adiciona pCarta a mão do jogador
*/
void Jogador::addCarta(CartaTruco* const pCarta)
{
    cartas.push_back(pCarta);
}

/*
	deleta pCarta da mão do jogador
*/
void Jogador::delCarta(CartaTruco* const pCarta)
{
    for(int i = 0; i < cartas.size(); i++)
    {
        if(cartas[i] == pCarta)
        {
            cartas.erase(cartas.begin()+i);
            return;
        }
    }
}

/*
	retira todas cartas da mão do jogador
*/
void Jogador::resetaCartas()
{
	while (cartas.size() > 0)
	{
		cartas.erase(cartas.begin());
	}
}


void Jogador::setNome(const string aNome)
{
    nome = aNome;
}


const string Jogador::getNome()
{
	return nome;
}

CartaTruco* Jogador::getCarta(int pos) {
	return getCartas().at(pos);
}
