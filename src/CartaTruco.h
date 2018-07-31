#pragma once
#include "Carta.h"

class CartaTruco :
	public Carta
{
private:
	int valor;

public:
	CartaTruco();
	CartaTruco(const int aNum, const char aNaipe);
	~CartaTruco();
	void setValor(const int aValor);
	const int getValor();
};

