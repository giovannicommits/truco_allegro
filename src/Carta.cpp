#include "stdafx.h"
#include "Carta.h"
int Carta::auto_incr = 1;

Carta::Carta()
{
	id = auto_incr;
	numero = 1;
	naipe = OUROS;
	auto_incr++;
}

Carta::Carta(int aNum, int aNaipe)
{
	id = auto_incr;
	numero = aNum;
	naipe = aNaipe;
	auto_incr++;
}


Carta::~Carta()
{

}


void Carta::setNaipe(const int aNaipe)
{
    naipe = aNaipe;
}


const int Carta::getNaipe()
{
	return naipe;
}


void Carta::setNumero(const int aNumero)
{
    numero = aNumero;
}


const int Carta::getNumero()
{
	return numero;
}


const int Carta::getID()
{
	return id;
}
