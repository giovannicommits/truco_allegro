#include "stdafx.h"
#include "Menu.h"

//define as posicoes e os tamanhos dos objetos
#define LARGURA_BTN 100
#define ALTURA_BTN 50
#define X_JOGAR 100
#define Y_JOGAR ALTURA_DISPLAY / 2 - 25
#define X_SAIR LARGURA_DISPLAY - 200


Menu::Menu(ALLEGRO_DISPLAY* display) : players_number(0), run(true), jogar(true), sair(false) {
	font32 = al_load_font("arial.ttf", 32, 0);
	background = al_load_bitmap("sprites/menu_background.jpg");
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	//tratamento de erros ao carregar arquivos
	if (!background)
		cout << "falhou ao carregar imagem de fundo" << endl;
	if (!font32)
		cout << "falhou ao carregar fonte" << endl;

	//registra eventos do teclado, do mouse, do display e do timer
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	//cria os botoes que o menu possui
	btn_jogar = new Button(LARGURA_BTN, ALTURA_BTN, X_JOGAR, Y_JOGAR, JOGAR, "JOGAR", 0);
	btn_sair = new Button(LARGURA_BTN, ALTURA_BTN, X_SAIR, Y_JOGAR, SAIR, "SAIR", 0);
	btn_two_players = new Button(LARGURA_BTN, ALTURA_BTN, X_JOGAR, Y_JOGAR, TWO_PLAYERS, "2 JOGS", 0);
	btn_four_players = new Button(LARGURA_BTN, ALTURA_BTN, X_SAIR, Y_JOGAR, FOUR_PLAYERS, "4 JOGS", 0);
	btn_resumir = new Button(LARGURA_BTN, ALTURA_BTN, X_SAIR, Y_JOGAR, RESUMIR, "RESUMIR", 0);
	btn_main_menu = new Button(LARGURA_BTN, ALTURA_BTN, X_JOGAR, Y_JOGAR, MAIN_MENU, "MAIN", 0);
}


Menu::~Menu() {
	al_destroy_font(font32);
	al_destroy_bitmap(background);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);	
	for (Button* bt : buttons_vector)
		delete bt;
}

/*
	menu principal, na qual possui a opcao de sair e de jogar
*/
int Menu::main_menu() {
	//adiciona os devidos botoes
	buttons_vector.clear();
	buttons_vector.push_back(btn_jogar);
	buttons_vector.push_back(btn_sair);

	al_flush_event_queue(event_queue);

	while (run) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&state);
			for (Button* button : buttons_vector) {
				if (button->isClicked(state)) {
					switch (button->getId())
					{
					case JOGAR:
						return players_menu(); //chama o loop do players_menu
						break;
					case SAIR:
						run = false;
						break;
					}
				}
			}
		}

		//desenha os devidos objetos na tela
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			al_draw_scaled_bitmap(background, 0, 0, 1280, 800, 0, 0, 800, 600, 0);
			al_draw_text(font32, al_map_rgb(255, 255, 255), LARGURA_DISPLAY / 2, 50, ALLEGRO_ALIGN_CENTER, "TRUCO");
			for (Button* button : buttons_vector) {
				button->draw();
			}
			al_flip_display();
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			run = false;
	}
	return -1;
}

/*
	menu que decide quantos jogadores a partida vai ter
*/
int Menu::players_menu() {
	//adiciona os devidos botoes (4 JOGADORES/2 JOGADORES)
	buttons_vector.clear();
	buttons_vector.push_back(btn_two_players);
	buttons_vector.push_back(btn_four_players);

	al_flush_event_queue(event_queue);

	while (run) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&state);
			for (Button* button : buttons_vector) {
				if (button->isClicked(state)) {
					switch (button->getId()) {
					case TWO_PLAYERS:
						players_number = 2;
						return players_number; //escolheu-se 2 jogadores
					case FOUR_PLAYERS:
						players_number = 4;
						return players_number; //escolheu-se 4 jogadores
					}
				}
			}
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			run = false;

		//desenha os devidos objetos na tela
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			al_draw_scaled_bitmap(background, 0, 0, 1280, 800, 0, 0, LARGURA_DISPLAY, ALTURA_DISPLAY, 0);
			al_draw_text(font32, al_map_rgb(255, 255, 255), LARGURA_DISPLAY / 2, 50, ALLEGRO_ALIGN_CENTER, "Numero de Jogadores");
			for (Button* button : buttons_vector) {
				button->draw();
			}
			al_flip_display();
		}
	}
	return -1;
}

/*
	menu chamado quando uma partida ja esta acontecendo
*/
int Menu::pause_menu() {
	//adiciona os devidos botoes 
	buttons_vector.clear();
	buttons_vector.push_back(btn_main_menu);
	buttons_vector.push_back(btn_resumir);

	al_flush_event_queue(event_queue);

	while (run) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&state);
			for (Button* button : buttons_vector) {
				if (button->isClicked(state)) {
					switch (button->getId()) {
					case RESUMIR:
						return -1; //sai do menu e volta pra partida
						break;
					case MAIN_MENU:
						return 666; //volta pro menu principal
						break;
					}
				}
			}
		}

		//desenha os objetos na tela
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			al_draw_scaled_bitmap(background, 0, 0, 1280, 800, 0, 0, LARGURA_DISPLAY, ALTURA_DISPLAY, 0);
			al_draw_text(font32, al_map_rgb(255, 255, 255), LARGURA_DISPLAY / 2, 50, ALLEGRO_ALIGN_CENTER, "Jogo pausado");
			for (Button* button : buttons_vector) {
				button->draw();
			}
			al_flip_display();
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			run = false;
			return 666; //sai do jogo
		}
	}
	return -1;
}

/*
	confere se o jogo ainda deveria estar rodando
*/
bool Menu::getRun() {  return run;  }
void Menu::setRun(bool crun) {  run = crun;  }
