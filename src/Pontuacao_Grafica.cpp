#include "stdafx.h"
#include "Pontuacao_Grafica.h"

/*
	construtora da pontuacao grafica (objeto que representa quais turnos cada time fez). Indicado pelas
	bolinhas vermelhas no canto superior direito
*/
Pontuacao_Grafica::Pontuacao_Grafica()
{
	is_active = false;
}

/*
	construtora, com parametros, da pontuacao grafica (objeto que representa quais turnos cada time fez). Indicado pelas
	bolinhas vermelhas no canto superior direito
*/
Pontuacao_Grafica::Pontuacao_Grafica(int cx, int cy, int craio) {
	x = cx;
	y = cy;
	raio = craio;
	is_active = false;
}


Pontuacao_Grafica::~Pontuacao_Grafica()
{
}

void Pontuacao_Grafica::activate() {  is_active = true;  }
void Pontuacao_Grafica::deactivate() {  is_active = false;  }

/*
	desenha as bolinhas vermelhas
*/
void Pontuacao_Grafica::draw() {
	al_draw_circle(x, y, raio, al_map_rgb(255, 255, 255), 1.5);
	if (is_active) {
		al_draw_filled_circle(x, y, raio, al_map_rgb(255, 0, 0));
	}
}