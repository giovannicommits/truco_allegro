#pragma once
#include <vector>
#include <string>
#include "CartaTruco.h"

using namespace std;

class Jogador
{
private:
	int id;
	static int auto_incr;
	vector<CartaTruco*> cartas;
	string nome;
public:
	Jogador(const string aNome = "");
	~Jogador();
	void setCartas(const vector<CartaTruco*> pCartas);
	vector<CartaTruco*> const getCartas();
	void addCarta(CartaTruco* const pCarta);
	void delCarta(CartaTruco* const pCarta);
	void resetaCartas();
	void setNome(const string aNome);
	const string getNome();
	int getId();
	CartaTruco* getCarta(int pos);
};

//	TODO: overload para delCarta para ID ou numero e naipe
