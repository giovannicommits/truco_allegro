#pragma once
#include <iostream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include <vector>
#include "Button.h"

#define LARGURA_DISPLAY 800
#define ALTURA_DISPLAY 600
#define FPS 60

using namespace std;

class Menu {
private:
	enum buttonIds { JOGAR, SAIR, TWO_PLAYERS, FOUR_PLAYERS, RESUMIR, MAIN_MENU };
	ALLEGRO_FONT * font32;
	ALLEGRO_BITMAP* background;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	int players_number;
	bool jogar;
	bool sair;
	bool run;
	Button* btn_jogar;
	Button* btn_sair;
	Button* btn_two_players;
	Button* btn_four_players;
	Button* btn_resumir;
	Button* btn_main_menu;
	vector<Button*> buttons_vector;
	ALLEGRO_MOUSE_STATE state;

public:
	Menu(ALLEGRO_DISPLAY* display);
	~Menu();
	int players_menu();
	int main_menu();
	int pause_menu();
	bool getRun();
	void setRun(bool crun);
};