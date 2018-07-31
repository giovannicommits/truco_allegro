#pragma once
#include <iostream>
#include <fstream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include <iostream>
#include <string>
#include <vector>
#include "Menu.h"
#include "Sistema_Grafico.h"
#include "Baralho.h"

#define ARQUIVO_NOME_JOGS "nome_jogs.txt"

using namespace std;

class Game {
private:
	ALLEGRO_DISPLAY* display;
	vector<Partida*> partidas;
	Menu* menu;
	Sistema_Grafico* sist_graf;
	Baralho baralho;
	Jogador jog1;
	Jogador jog2;
	Jogador jog3;
	Jogador jog4;

public:
	Game();
	~Game();
	void execute();
	void defineNomeJogs(int numJogs);
};