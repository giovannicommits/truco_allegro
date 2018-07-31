#pragma once
#include <iostream>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include "Partida.h"
#include "Button.h"
#include "Menu.h"
#include "Pontuacao_Grafica.h"

class Sistema_Grafico {
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font32;
	ALLEGRO_BITMAP* background;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP* cartas_sprite;
	Partida* partida;
	vector<Button*> botoes;
	ALLEGRO_MOUSE_STATE state;
	vector<Pontuacao_Grafica*> pontuacao_time1;
	vector<Pontuacao_Grafica*> pontuacao_time2;
	Menu* menu;

public:
	Sistema_Grafico(ALLEGRO_DISPLAY* pDisplay, Menu* pMenu);
	~Sistema_Grafico();
	void show();
	void draw_players_cards();
	void draw_background();
	void draw_highest_card();
	int flipWait();
	void draw_manilha();
	int confere_click();
	void gerar_botoes();
	int loop();
	void draw_cartas_descarte();
	void draw_baralho();
	void draw_jogador_atual();
	void draw_pontuacao_total();
	void draw_pontuacao_turnos();
	void draw_vencendo_turno();
	void activateFeitas(int ctime, int cpos);
	void deactivate_all();
	void draw_botao_truco();
	int decisao_truco();
	void activate_truco_btn();
	void deactivate_truco_btn();
	int tela_vitoria();
	void setPartida(Partida* cpartida);
	void flip_cards();
	void draw_valendo_pontos();
	void draw_times();
	void tela_entre_rodadas();
};
