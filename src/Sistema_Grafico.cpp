#include "stdafx.h"
#include "Sistema_Grafico.h"
#include <vector>

//define as posicoes e tamanhos dos objetos graficos
#define FPS 30
#define ALTURA_CARTA 96
#define LARGURA_CARTA 72
#define FONT_SIZE 16
#define COSTAS_CARTA LARGURA_CARTA * 13
#define PI 3.1415
#define GRAUS_90 PI/2
#define X_CIMA_BAIXO 200
#define Y_BAIXO 500
#define Y_CIMA 10
#define X_DIREITA 700
#define X_ESQUERDA 100
#define Y_DIREITA_ESQUERDA 400
#define Y_DESCARTE LARGURA_DISPLAY/2-ALTURA_CARTA
#define X_MANILHA LARGURA_DISPLAY / 2 - LARGURA_CARTA + 10 
#define Y_MANILHA ALTURA_DISPLAY / 2 - ALTURA_CARTA
#define X_BARALHO LARGURA_DISPLAY / 2 - 10
#define Y_BARALHO ALTURA_DISPLAY / 2 - ALTURA_CARTA
#define X_NOME_JOG_ATUAL 110
#define Y_NOME_JOG_ATUAL 525
#define X_VENCENDO 110
#define Y_VENCENDO 550
#define X_PONT_RODADAS_TITLE 100
#define Y_PONT_RODADAS_TITLE 10
#define X_PONT_RODADAS 100
#define Y_PONT_RODADAS 30
#define ENTRE_RODADAS 20
#define X_PONT_TURNOS 670
#define RAIO_PONT_TURNOS 12
#define Y_PONT_TURNOS 40
#define X_PONT_TURNOS_TIME_DESLOC 60
#define ENTRE_PONTS 30
#define X_BOT_TRUCO 500
#define Y_BOT_TRUCO 500
#define LARGURA_BOT_TRUCO 80
#define ALTURA_BOT_TRUCO 50
#define X_TRUCO_POP_UP 250
#define Y_TRUCO_POP_UP 100
#define LARGURA_TRUCO_POP_UP 300
#define ALTURA_TRUCO_POP_UP 75
#define PADDING_RIGHT_YES 15
#define PADDING_TOP_YES 15
#define LARGURA_YES_BOT 50
#define ALTURA_YES_BOT 50 // o "botao de sim" e o "botao de nao" sao do mesmo tamanho
#define AFASTAMENTO_YESNO_X 220
#define PADDING_TOP_TRUCO_MSG 5
#define X_VITORIOSO LARGURA_DISPLAY/2
#define Y_VITORIOSO 30
#define LARGURA_BTN_VITORIA 100
#define ALTURA_BTN_VITORIA 50
#define X_JOGAR 100
#define Y_JOGAR ALTURA_DISPLAY / 2 - 25
#define X_SAIR LARGURA_DISPLAY - 200
#define X_VALENDO 620
#define Y_VALENDO 560
#define X_TIME_JOGS 100
#define Y_TIME_JOGS 375
#define ESPACAMENTO_Y_TIME_JOGS 10
#define DESLOC_X_TITLE_TIME_JOGS 60


Sistema_Grafico::Sistema_Grafico(ALLEGRO_DISPLAY* pDisplay, Menu* pMenu) {
	display = pDisplay;
	menu = pMenu;
	font32 = al_load_font("arial.ttf", 16, 0);
	background = al_load_bitmap("sprites/match_background.jpg");
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	cartas_sprite = al_load_bitmap("sprites/cards.png");

	//cria os objetos que contam a pontuacao dos turnos (as bolinhas no canto direito superior)
	for (int i = 0; i < 3; i++) {
		pontuacao_time1.push_back(new Pontuacao_Grafica(X_PONT_TURNOS + i * ENTRE_PONTS, Y_PONT_TURNOS, RAIO_PONT_TURNOS));
		pontuacao_time2.push_back(new Pontuacao_Grafica(X_PONT_TURNOS + i * ENTRE_PONTS, Y_PONT_TURNOS + 3*RAIO_PONT_TURNOS, RAIO_PONT_TURNOS));
	}

	//registra os eventos oriundos do teclado, mouse, tela e do timer
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	//tratamento de erros para o carregamento de arquivos
	if (!background)
		cout << "falhou ao carregar imagem de fundo" << endl;
	if (!font32)
		cout << "falhou ao carregar fonte" << endl;
	if (!cartas_sprite)
		cout << "falhou ao carregar cartas sprite" << endl;
	if (!background)
		cout << "falhou ao carregar background" << endl;

	//cria todos os objetos clicaveis da tela
	gerar_botoes();
}


Sistema_Grafico::~Sistema_Grafico() {
	for (Button* botao : botoes) 
		delete botao;
	botoes.clear();
	for (Pontuacao_Grafica* pt : pontuacao_time1)
		delete pt;
	pontuacao_time1.clear();
	for (Pontuacao_Grafica* pt : pontuacao_time2)
		delete pt;
	pontuacao_time2.clear();
	
	partida = nullptr;
	al_destroy_bitmap(background);
	al_destroy_bitmap(cartas_sprite);
	al_destroy_font(font32);
	display = nullptr;
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	menu = nullptr;
}

/*
	define qual partida sera exibida na tela
*/
void Sistema_Grafico::setPartida(Partida* cpartida) {
	partida = cpartida;
}

/*
	desenha as cartas que os jogadores desceram
*/
void Sistema_Grafico::draw_cartas_descarte() {
	int i = 1;
	vector<CartaTruco*> cartas_descarte = partida->getBaralho()->get_cartas_descarte();
	for (CartaTruco* carta : cartas_descarte) {
		switch (carta->getNaipe()) {
		case PAUS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), PAUS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i) - LARGURA_CARTA / 2, Y_DESCARTE, 0);
			break;
		case OUROS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), OUROS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i) - LARGURA_CARTA / 2, Y_DESCARTE, 0);
			break;
		case ESPADAS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), ESPADAS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i) - LARGURA_CARTA / 2, Y_DESCARTE, 0);
			break;
		case COPAS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), COPAS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i) - LARGURA_CARTA/2, Y_DESCARTE, 0);
			break;
		}
		i++;
	}
}

/*
	chama todas as funcoes de desenhar
*/
void Sistema_Grafico::show() {
	draw_background();
	draw_manilha();
	draw_players_cards();
	draw_cartas_descarte();
	draw_highest_card();
	draw_baralho();
	draw_jogador_atual();
	draw_pontuacao_total();
	draw_pontuacao_turnos();
	draw_vencendo_turno();
	draw_valendo_pontos();
	draw_times();
	draw_botao_truco();
	al_flip_display();
}

/*
	escreve o texto "RODADA VALENDO X PONTOS" no canto direito inferior
*/
void Sistema_Grafico::draw_valendo_pontos() {
	int valor = partida->getRodadaAtual()->getValor();
	if(valor > 1)
		al_draw_textf(font32, al_map_rgb(255, 255, 255), X_VALENDO, Y_VALENDO, ALLEGRO_ALIGN_CENTRE, "RODADA VALENDO %i PONTOS", valor);
	else
		al_draw_textf(font32, al_map_rgb(255, 255, 255), X_VALENDO, Y_VALENDO, ALLEGRO_ALIGN_CENTRE, "RODADA VALENDO %i PONTO", valor);
}

/*
	desenha a pontuacao dos turnos atuais no canto direito superior
*/
void Sistema_Grafico::draw_pontuacao_turnos() {
	//primeiro desenha as bolinhas brancas
	al_draw_text(font32, al_map_rgb(255, 255, 255), X_PONT_TURNOS - RAIO_PONT_TURNOS * 3, Y_PONT_TURNOS - RAIO_PONT_TURNOS * 3, 0, "TURNOS FEITOS:");
	al_draw_text(font32, al_map_rgb(255, 255, 255), X_PONT_TURNOS - X_PONT_TURNOS_TIME_DESLOC, Y_PONT_TURNOS - RAIO_PONT_TURNOS/2, ALLEGRO_ALIGN_CENTRE, "TIME 1:");
	al_draw_text(font32, al_map_rgb(255, 255, 255), X_PONT_TURNOS - X_PONT_TURNOS_TIME_DESLOC, Y_PONT_TURNOS + 3*RAIO_PONT_TURNOS - RAIO_PONT_TURNOS / 2, ALLEGRO_ALIGN_CENTRE, "TIME 2:");
	
	//preenche de vermelho dependendo de como os turnos fluiram
	for (int i = 0; i < 3; i++) {
		pontuacao_time1.at(i)->draw();
		pontuacao_time2.at(i)->draw();
	}
}

/*
	limpa as bolinhas vermelhas que indicam a pontuacao de cada turno
*/
void Sistema_Grafico::deactivate_all() {
	for (int i = 0; i < 3; i++) {
		pontuacao_time1.at(i)->deactivate();
		pontuacao_time2.at(i)->deactivate();
	}
}

/*
	altera os objetos Pontuacao Grafica de forma que eles indiquem qual times fez cada turno
*/
void Sistema_Grafico::activateFeitas(int ctime, int cpos) {
	if (ctime == 1) {
		pontuacao_time1.at(cpos)->activate();
	}
	else if (ctime == 2) {
		pontuacao_time2.at(cpos)->activate();
	}
}

/*
	tela entre rodadas que indica qual time ganhou quantos pontos
*/
void Sistema_Grafico::tela_entre_rodadas() {
	draw_background();
	if(partida->getRodadaAtual()->getFeitas1() > partida->getRodadaAtual()->getFeitas2())
		al_draw_textf(font32, al_map_rgb(255, 255, 255), LARGURA_DISPLAY/2, ALTURA_DISPLAY/2, ALLEGRO_ALIGN_CENTRE, "TIME 1 GANHOU %i PONTOS", partida->getRodadaAtual()->getValor());
	else
		al_draw_textf(font32, al_map_rgb(255, 255, 255), LARGURA_DISPLAY / 2, ALTURA_DISPLAY / 2, ALLEGRO_ALIGN_CENTRE, "TIME 2 GANHOU %i PONTOS", partida->getRodadaAtual()->getValor());
	al_flip_display();
	al_rest(2);
}

/*
	desenha o nome dos jogadores de cada time na esquerda e no meio da tela
*/
void Sistema_Grafico::draw_times() {
	int i = 0;
	al_draw_text(font32, al_map_rgb(255, 255, 255), X_TIME_JOGS - DESLOC_X_TITLE_TIME_JOGS, Y_TIME_JOGS + i * FONT_SIZE * 3 / 2, 0, "Time 1:");
	for (Jogador* jog : partida->getJogsDoTime(1)) {
		al_draw_textf(font32, al_map_rgb(255, 255, 255), X_TIME_JOGS, Y_TIME_JOGS + i * FONT_SIZE * 3/2, 0, jog->getNome().c_str());
		i++;
	}
	al_draw_text(font32, al_map_rgb(255, 255, 255), X_TIME_JOGS - DESLOC_X_TITLE_TIME_JOGS, Y_TIME_JOGS + i * FONT_SIZE * 3 / 2 + ESPACAMENTO_Y_TIME_JOGS, 0, "Time 2:");
	for (Jogador* jog : partida->getJogsDoTime(2)) {
		al_draw_textf(font32, al_map_rgb(255, 255, 255), X_TIME_JOGS, Y_TIME_JOGS + i * FONT_SIZE * 3 / 2 + ESPACAMENTO_Y_TIME_JOGS, 0, jog->getNome().c_str());
		i++;
	}
}

/*
	desenha no canto superior esquerdo quantas rodadas cada time fez
*/
void Sistema_Grafico::draw_pontuacao_total() {
	int pts_time1 = partida->getPontosTime1();
	al_draw_text(font32, al_map_rgb(255, 255, 255), X_PONT_RODADAS_TITLE, Y_PONT_RODADAS_TITLE, ALLEGRO_ALIGN_CENTRE, "RODADAS FEITAS");
	al_draw_textf(font32, al_map_rgb(255, 255, 255), X_PONT_RODADAS, Y_PONT_RODADAS, ALLEGRO_ALIGN_CENTRE, "Time 1: %i", pts_time1);
	int pts_time2 = partida->getPontosTime2();
	al_draw_textf(font32, al_map_rgb(255, 255, 255), X_PONT_RODADAS, Y_PONT_RODADAS + ENTRE_RODADAS, ALLEGRO_ALIGN_CENTRE, "Time 2: %i", pts_time2);
}

/*
	desenha o nome do jogador que esta vencendo o turno atualmente no canto esquerdo inferior
*/
void Sistema_Grafico::draw_vencendo_turno() {
	string nome;
	if (partida->getRodadaAtual()->getTurnoAtual()->getVenceuTurno())
		nome = partida->getRodadaAtual()->getTurnoAtual()->getVenceuTurno()->getNome();
	al_draw_textf(font32, al_map_rgb(255, 255, 255), X_VENCENDO, Y_VENCENDO, ALLEGRO_ALIGN_CENTRE, "Jogador Vencendo: %s", nome.c_str());
}

/*
	desenha o nome do jogador atual no canto esquerdo inferior
*/
void Sistema_Grafico::draw_jogador_atual() {
	al_draw_textf(font32, al_map_rgb(255, 255, 255), X_NOME_JOG_ATUAL, Y_NOME_JOG_ATUAL, ALLEGRO_ALIGN_CENTRE, "Jogador Atual: %s", partida->getJogadorAtual()->getNome().c_str());
}

/*
	ativa o botao de truco (eh chamado quando o botao foi previamente desativado e precisa ser reativado)
*/
void Sistema_Grafico::activate_truco_btn() {
	botoes.at(3)->activate();
	//o botao 3 eh o botao de truco
}

/*
	confere os cliques na tela, seja nas cartas (indicando desejo de jogada-las), 
	ou no botao de truco (indicando desejo de trucar)
*/
int Sistema_Grafico::confere_click() {
	al_get_mouse_state(&state);
	vector<CartaTruco*> cartas_jog_atual = partida->getJogadorAtual()->getCartas();
	int quant_cartas = cartas_jog_atual.size();

	//confere apenas os botoes referentes as cartas que o jogador atual possui na mao
	for (int i = 0; i < quant_cartas; i++) {
		if (botoes.at(i)->isClicked(state))
			return botoes.at(i)->getId();
	}

	//o botao 3 eh o botao de truco
	if (botoes.at(3)->isClicked(state) && botoes.at(3)->isActive()) {
		return decisao_truco();
	}
	return -1; 
}

/*
	funcao que espera com as cartas viradas ate o proximo jogador apertar ENTER
*/
int Sistema_Grafico::flipWait() {
	bool wait = true;
	deactivate_truco_btn();
	while (wait) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ENTER:
				wait = false;
			}
		}
		//desenha na tela
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			show();
			flip_cards();
			al_flip_display();
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			menu->setRun(false);
			return 666; //codigo de fechar o jogo
		}	
	}
	activate_truco_btn();
	return -1;
}

/*
	funcao que desenha as cartas de cabeca para baixo (para que os outros jogadores nao vejam as cartas um do outro)
*/
void Sistema_Grafico::flip_cards() {
	int id_atual = partida->getJogadorAtual()->getId();
	list<Jogador*> jogsEmOrdem = partida->getJogsEmOrdem();
	list<Jogador*>::iterator it;

	it = jogsEmOrdem.begin();

	int i = 1;
	for (CartaTruco* carta : (*it)->getCartas()) {
		al_draw_bitmap_region(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_BAIXO, 0);
		i++;
	}

	i = 1;
	it = std::next(it, 1);

	//caso 2 jogadores, vira as cartas dos 2 jogadores
	if (jogsEmOrdem.size() == 2) {

		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_bitmap_region(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_CIMA, 0);
			i++;
		}
	}
	//caso 4 jogadores, vira todas as cartas dos 4 jogadores
	else {
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_rotated_bitmap(al_create_sub_bitmap(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA), LARGURA_CARTA / 2, ALTURA_CARTA / 2, X_DIREITA, Y_DIREITA_ESQUERDA - i * LARGURA_CARTA, GRAUS_90, 0);
			i++;
		}
		i = 1;
		it = std::next(it, 1);
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_bitmap_region(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_CIMA, 0);
			i++;
		}
		i = 1;
		it = std::next(it, 1);
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_rotated_bitmap(al_create_sub_bitmap(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA), LARGURA_CARTA / 2, ALTURA_CARTA / 2, X_ESQUERDA, Y_DIREITA_ESQUERDA - i * LARGURA_CARTA, GRAUS_90, 0);
			i++;
		}
	}
}

/*
	desenha uma carta de cabeca pra baixo no centro da tela indicando que seria o baralho do jogo
*/
void Sistema_Grafico::draw_baralho() {
	al_draw_bitmap_region(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA, X_BARALHO, Y_BARALHO, 0);
}

/*
	desenha o botao de truco na tela se estiver ativo
*/
void Sistema_Grafico::draw_botao_truco() {
	if (botoes.at(3)->isActive())
		botoes.at(3)->draw();
}

/*
	desenha um pequeno circulo vermelho embaixo da maior carta que foi jogada pelos jogadores
*/
void Sistema_Grafico::draw_highest_card() {
	CartaTruco* maior_carta = partida->getRodadaAtual()->getTurnoAtual()->getMaiorCarta();
	if(maior_carta) {
		for(int i = 0; i < partida->getBaralho()->get_cartas_descarte().size(); i++)
			if(partida->getBaralho()->get_cartas_descarte().at(i) == maior_carta)
				al_draw_circle(X_CIMA_BAIXO + (LARGURA_CARTA * (i + 1)), Y_DESCARTE + ALTURA_CARTA, 10, al_map_rgb(255, 0, 0), 20);
	}
}

/*
	desenha o fundo (mesa)
*/
void Sistema_Grafico::draw_background() {
	al_draw_scaled_bitmap(background, 0, 0, 1280, 900, 0, 0, LARGURA_DISPLAY, ALTURA_DISPLAY, 0);
}

/*
	cria todos os objetos botoes, com suas posicoes, largura, altura e texto, e os colocam num vetor de botoes
*/
void Sistema_Grafico::gerar_botoes() {
	for (int i = 1; i <= 3; i++) {
		botoes.push_back(new Button(LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_BAIXO, i - 1, "", 0));
	}
	botoes.push_back(new Button(LARGURA_BOT_TRUCO, ALTURA_BOT_TRUCO, X_BOT_TRUCO, Y_BOT_TRUCO, 333, "TRUCO", 255));
	botoes.push_back(new Button(LARGURA_BTN_VITORIA, ALTURA_BTN_VITORIA, X_JOGAR, Y_JOGAR, 12, "MENU", 255));
	botoes.push_back(new Button(LARGURA_BTN_VITORIA, ALTURA_BTN_VITORIA, X_SAIR, Y_JOGAR, 13, "SAIR", 255));
	botoes.push_back(new Button(LARGURA_YES_BOT, LARGURA_YES_BOT, X_TRUCO_POP_UP + PADDING_RIGHT_YES, Y_TRUCO_POP_UP + PADDING_TOP_YES, 12, "SIM", 255));
	botoes.push_back(new Button(LARGURA_YES_BOT, LARGURA_YES_BOT, X_TRUCO_POP_UP + PADDING_RIGHT_YES + AFASTAMENTO_YESNO_X, Y_TRUCO_POP_UP + PADDING_TOP_YES, 13, "NAO", 255));
}

/*
	desenha as cartas na mao dos jogadores, tanto do jogador atual (que sao desenhadas viradas pra cima), 
	quanto dos outros jogadores (que sao desenhadas viradas para baixo). Essa funcao leva em conta
	quantas cartas estao na mao de cada jogador para desenhar. Essa funcao serve para desenhar as cartas
	tanto de partidas de 2 jogadores quanto de 4
*/
void Sistema_Grafico::draw_players_cards() {
	int id_atual = partida->getJogadorAtual()->getId();
	list<Jogador*> jogsEmOrdem = partida->getJogsEmOrdem();
	list<Jogador*>::iterator it;

	it = jogsEmOrdem.begin();
	int i = 1;

	for (CartaTruco* carta : (*it)->getCartas()) {
		switch (carta->getNaipe()) {
		case PAUS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), PAUS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_BAIXO, 0);
			break;
		case OUROS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), OUROS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_BAIXO, 0);
			break;
		case ESPADAS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), ESPADAS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_BAIXO, 0);
			break;
		case COPAS:
			al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), COPAS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_BAIXO, 0);
			break;
		}
		i++;
	}

	i = 1;
	it = std::next(it, 1);

	//caso a partida seja de 2 jogadores apenas, desenha 2 jogadores, um de frente pro outro
	if (partida->getNumJogs() == 2) {
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_bitmap_region(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_CIMA, 0);
			i++;
		}
	}
	//se for de 4 jogadores a partida, desenha-se 4 jogadores, um ao lado do outro
	else {
		i = 1;
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_rotated_bitmap(al_create_sub_bitmap(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA), LARGURA_CARTA / 2, ALTURA_CARTA / 2, X_DIREITA, Y_DIREITA_ESQUERDA - i * LARGURA_CARTA, GRAUS_90, 0);
			i++;
		}
		i = 1;
		it = std::next(it, 1);
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_bitmap_region(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA, X_CIMA_BAIXO + (LARGURA_CARTA * i), Y_CIMA, 0);
			i++;
		}
		i = 1;
		it = std::next(it, 1);
		for (CartaTruco* carta : (*it)->getCartas()) {
			al_draw_rotated_bitmap(al_create_sub_bitmap(cartas_sprite, COSTAS_CARTA, 0, LARGURA_CARTA, ALTURA_CARTA), LARGURA_CARTA / 2, ALTURA_CARTA / 2, X_ESQUERDA, Y_DIREITA_ESQUERDA - i * LARGURA_CARTA, GRAUS_90, 0);
			i++;
		}
	}
}

/*
	loop que desenha tudo que precisa ser desenhado, aguarda cliques, e retorna os codigos de clique
*/
int Sistema_Grafico::loop() {
	al_flush_event_queue(event_queue);
	int time = partida->getTimeJogador(partida->getJogadorAtual());
	int timeTruco = partida->getRodadaAtual()->getTimeTruco();

	if (partida->getRodadaAtual()->getValor() >= 12 || time == timeTruco)
		deactivate_truco_btn();
	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			int confereclick = confere_click();
			cout << confereclick << endl;
			return confereclick;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				return menu->pause_menu();
				break;
			}
		}

		//desenha os objetos na tela
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			show();
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			menu->setRun(false);
			return 666; //codigo de fechar o jogo
		}
	}
}

/*
	desenha uma carta ao lado da carta que representa o baralho, indicando qual eh a manilha atual
*/
void Sistema_Grafico::draw_manilha() {
	CartaTruco* carta = partida->getBaralho()->getCartaVirada();
	switch (carta->getNaipe()) {
	case PAUS:
		al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), PAUS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_MANILHA, Y_MANILHA, 0);
		break;
	case OUROS:
		al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), OUROS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_MANILHA, Y_MANILHA, 0);
		break;
	case ESPADAS:
		al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), ESPADAS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_MANILHA, Y_MANILHA, 0);
		break;
	case COPAS:
		al_draw_bitmap_region(cartas_sprite, LARGURA_CARTA * (carta->getNumero() - 1), COPAS * ALTURA_CARTA, LARGURA_CARTA, ALTURA_CARTA, X_MANILHA, Y_MANILHA, 0);
		break;
	}
}

/*
	desativa o botao de truco quando necessario
*/
void Sistema_Grafico::deactivate_truco_btn() {
	botoes.at(3)->deactivate();
	//o botao 3 eh o botao de TRUCO
}

/*
	loop que decide quanto a rodada valera apos apertar o botao de truco
*/
int Sistema_Grafico::decisao_truco() {
	flip_cards(); //esconde as cartas
	deactivate_truco_btn(); //desliga o botao de truco
	bool wait = true;
	
	while (true) {
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				al_get_mouse_state(&state);

				//o botao 6 eh o botao de SIM
				if (botoes.at(6)->isClicked(state))
				{
					Rodada* rodada = partida->getRodadaAtual();
					rodada->truco();
					rodada->setTimeTruco(partida->getTimeJogador(partida->getJogadorAtual()));
					cout << "aceitou truco" << endl;
					cout << "rodada valendo: " << partida->getRodadaAtual()->getValor() << endl;
					return -1;
				}
					
				//o botao 7 eh o botao de NAO
				else if (botoes.at(7)->isClicked(state)) {
					if (partida->getTimeJogador(partida->getJogadorAtual()) == 1) {
						cout << "time 1 ganhou" << endl;
						return 11;		
					}
					else {
						cout << "time 2 ganhou" << endl;
						return 12;
					}
				}
			}

			//desenha os devidos objetos na tela
			else if (ev.type == ALLEGRO_EVENT_TIMER) {
				
				al_draw_textf(font32, al_map_rgb(0, 0, 0), X_TRUCO_POP_UP + LARGURA_TRUCO_POP_UP / 2, Y_TRUCO_POP_UP + + ALTURA_TRUCO_POP_UP + PADDING_TOP_TRUCO_MSG, ALLEGRO_ALIGN_CENTRE, "Time %i pediu truco, deseja aceitar?", partida->getTimeJogador(partida->getJogadorAtual()));
				al_draw_filled_rectangle(X_TRUCO_POP_UP, Y_TRUCO_POP_UP, X_TRUCO_POP_UP + LARGURA_TRUCO_POP_UP, Y_TRUCO_POP_UP + ALTURA_TRUCO_POP_UP, al_map_rgb(255, 255, 255));
				
				for (int i = 6; i <= 7; i++)
					botoes.at(i)->draw();
				al_flip_display();
			}

			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				menu->setRun(false);
				return 666; //codigo de fechar o jogo
			}
	}
}

/*
	desenha uma tela de vitoria mostrando qual time ganhou e dando as opcoes de sair ou jogar novamente
*/
int Sistema_Grafico::tela_vitoria() {
	al_flush_event_queue(event_queue);
	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&state);

			//o botao 4 eh o botao do MENU
			if (botoes.at(4)->isClicked(state))
				return 7;

			//o botao 5 eh o botao de SAIR
			else if (botoes.at(5)->isClicked(state)) {
				menu->setRun(false);
				return 666; //codigo de fechar o jogo
			}
		}

		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			draw_background();
			al_draw_textf(font32, al_map_rgb(255, 255, 255), X_VITORIOSO, Y_VITORIOSO, ALLEGRO_ALIGN_CENTRE, "PARABENS TIME %i VOCE GANHOU!", partida->getTimeVenc());

			//o botao 4 eh o botao de JOGAR NOVAMENTE e o botao 5 eh o botao de SAIR
			for (int i = 4; i <= 5; i++)
				botoes.at(i)->draw();

			draw_times();
			al_flip_display();
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			menu->setRun(false);
			return 666; //codigo de fechar o jogo
		}
	}
	return -1;
}