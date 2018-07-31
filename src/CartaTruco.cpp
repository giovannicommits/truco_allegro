#include "stdafx.h"
#include "CartaTruco.h"


CartaTruco::CartaTruco():Carta()
{
	valor = -1;
}

CartaTruco::CartaTruco(const int aNum, const char aNaipe):Carta(aNum, aNaipe)
{
	// define o valor da carta conforme as regras do truco
    valor = -1;
    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 11, 12, 13};
    int valores[] = {8, 9, 10, 1, 2, 3, 4, 6, 5, 7};
    for(int i = 0; i < 10; i++)
    {
        if(aNum == numeros[i])
            valor = valores[i];
    }
}

CartaTruco::~CartaTruco()
{
}


void CartaTruco::setValor(const int aValor)
{
    valor = aValor;
}


const int CartaTruco::getValor()
{
	return valor;
}
