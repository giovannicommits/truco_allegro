#pragma once
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"

class Pontuacao_Grafica
{
private:
	int x;
	int y;
	int raio;
	bool is_active;
public:
	Pontuacao_Grafica();
	Pontuacao_Grafica(int cx, int cy, int craio);
	~Pontuacao_Grafica();
	void activate();
	void deactivate();
	void draw();
};

