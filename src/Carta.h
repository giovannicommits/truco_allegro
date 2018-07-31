#pragma once

enum Naipes { PAUS, ESPADAS, COPAS, OUROS };

class Carta
{
protected:
	
	int id;
	static int auto_incr;
	int numero;
	int naipe;
public:
	Carta();
	Carta(int aNum, int aNaipe);
	~Carta();
	void setNaipe(const int aNaipe);
	const int getNaipe();
	void setNumero(const int aNumero);
	const int getNumero();
	const int getID();
};

