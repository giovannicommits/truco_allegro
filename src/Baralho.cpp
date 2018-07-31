#include "stdafx.h"
#include "Baralho.h"

Baralho::Baralho()
{
	// cria todas as cartas de um baralho de truco e adiciona-as ao vetor de cartasBaralho e todasCartas
    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 11, 12, 13};
    int naipes[] = { OUROS , ESPADAS , COPAS , PAUS };

    for(int i = 0; i < 4; i++)
    {
        for(int u = 0; u < 10; u++)
        {
            CartaTruco* carta = new CartaTruco(numeros[u], naipes[i]);
            cartasBaralho.push_back(carta);
            todasCartas.push_back(carta);
        }
    }
	numZap = -1;
}

vector<CartaTruco*> Baralho::get_cartas_descarte() {
	return cartasDescarte;
}

Baralho::~Baralho()
{
    cartasBaralho.clear();
    cartasUsadas.clear();
    cartasDescarte.clear();

    while(todasCartas.size() > 0)
    {
        CartaTruco* pCarta = todasCartas[0];
        todasCartas.erase(todasCartas.begin());
        delete(pCarta);
    }
	todasCartas.clear();
	cartaVirada = nullptr;
}

/*
	Move a carta referida das cartasUsadas para cartasBaralho, caso possível
*/
void Baralho::baralhoParaUsada(CartaTruco* const pCarta)
{
    for(it = cartasBaralho.begin(); it != cartasBaralho.end(); it++)
    {
        if(*(it) == pCarta)
        {
            cartasBaralho.erase(it);
            cartasUsadas.push_back(pCarta);
            return;
        }
    }
}

/* 
	Move a carta referida das cartasBaralho para cartasUsadas, caso possível
*/
void Baralho::usadaParaBaralho(CartaTruco* const pCarta)
{
    for(it = cartasUsadas.begin(); it != cartasUsadas.end(); it++)
    {
        if(*(it) == pCarta)
        {
            cartasUsadas.erase(it);
            cartasBaralho.push_back(pCarta);
            return;
        }
    }
}

/*
	Move a carta referida das cartasUsadas para cartasDescarte, caso possível
*/
void Baralho::usadaParaDescarte(CartaTruco* const pCarta)
{
    for(it = cartasUsadas.begin(); it != cartasUsadas.end(); it++)
    {
        if(*(it) == pCarta)
        {
            cartasUsadas.erase(it);
            cartasDescarte.push_back(pCarta);
            return;
        }
    }
}

/*
	Move a carta referida das cartasDescarte para cartasBaralho, caso possível
*/
void Baralho::descarteParaBaralho(CartaTruco* const pCarta)
{
    for(it = cartasDescarte.begin(); it != cartasDescarte.end(); it++)
    {
        if(*(it) == pCarta)
        {
            cartasDescarte.erase(it);
            cartasBaralho.push_back(pCarta);
            return;
        }
    }
}

/* 
	Reseta os valores das cartas e devolve todas as cartasUsadas e cartasDescarte para o cartasBaralho
*/
void Baralho::resetaBaralho()
{
    resetaValores();
    devolveDescartes();
    devolveUsadas();
}

void Baralho::resetaValores()
{
    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 11, 12, 13};
    int valores[] = {8, 9, 10, 1, 2, 3, 4, 6, 5, 7};
    for(it = todasCartas.begin(); it != todasCartas.end(); it++)
    {
        if((*it)->getValor() > 10)
        {
            for(int i = 0; i < 10; i++)
            {
                if((*it)->getNumero() == numeros[i])
                {
                    (*it)->setValor(valores[i]);
                    break;
                }
            }
        }
    }
}

/* 
	Embaralha as cartasBaralho
*/
void Baralho::embaralha()
{
    srand(time(nullptr));
    int tam = cartasBaralho.size();
    for(int i = 0; i < tam; i++)
    {
        int u;
        CartaTruco* aux;
        u = rand()%tam;

        aux = cartasBaralho[i];
        cartasBaralho[i] = cartasBaralho[u];
        cartasBaralho[u] = aux;
    }
}

/*
	Devolve todas cartasUsadas para cartasBaralho
*/
void Baralho::devolveUsadas()
{
    while(cartasUsadas.size() > 0)
    {
        CartaTruco* pCarta;
        pCarta = cartasUsadas[0];
        cartasUsadas.erase(cartasUsadas.begin());
        cartasBaralho.push_back(pCarta);
    }
}

/*
	Devolve todas cartasDescarte para cartasBaralho
*/
void Baralho::devolveDescartes()
{
    while(cartasDescarte.size() > 0)
    {
        CartaTruco* pCarta;
        pCarta = cartasDescarte[0];
        cartasDescarte.erase(cartasDescarte.begin());
        cartasBaralho.push_back(pCarta);
    }
}

/*
	Move a carta referida das cartasBaralho para cartasUsada, caso possível
*/
CartaTruco* const Baralho::cartaBaralhoParaUsada()
{
	int tam = cartasBaralho.size();
	if (tam == 0)
		return nullptr;

    int pos = rand()%tam;
    CartaTruco* pCarta = cartasBaralho[pos];
    cartasBaralho.erase(cartasBaralho.begin()+pos);
    cartasUsadas.push_back(pCarta);
    return pCarta;
}

/*
	Atualiza os valores das cartas conforme a cartaVirada e as regras de truco
*/
void Baralho::atualizaValores()
{
    for(it = todasCartas.begin(); it != todasCartas.end(); it++)
    {
        if((*it)->getNumero() == numZap)
        {
            switch((*it)->getNaipe())
            {
                case OUROS:
                    (*it)->setValor(11);
                    break;
                case ESPADAS:
                    (*it)->setValor(12);
                    break;
                case COPAS:
                    (*it)->setValor(13);
                    break;
                case PAUS:
                    (*it)->setValor(14);
                    break;
            }
        }
    }
}

void Baralho::setNumZap(const int aNum)
{
    numZap = aNum;
}

const int Baralho::getNumZap()
{
    return numZap;
}

/*
	Vira uma carta e define qual o número do zap conforme as regras do truco
*/
CartaTruco* const Baralho::virarCarta()
{
	desvirarCarta();

	cartaVirada = cartaBaralhoParaUsada();

	int num = cartaVirada->getNumero();

	if (num >= 1 && num < 7)
		setNumZap(num + 1);
	else if (num == 13)
		setNumZap(1);
	else if (num == 7)
		setNumZap(12);
	else if (num == 12)
		setNumZap(11);
	else
		setNumZap(13);
	atualizaValores();

	return cartaVirada;
}


CartaTruco* const Baralho::getCartaVirada()
{
	return cartaVirada;
}

/*
	Devolve a carta Virada ao baralho
*/
void Baralho::desvirarCarta()
{
	if (cartaVirada != nullptr)
		usadaParaBaralho(cartaVirada);
	cartaVirada = nullptr;
}
