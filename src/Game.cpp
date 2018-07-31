#include "stdafx.h"
#include "Game.h"

//tamanho da tela criada
#define LARGURA_DISPLAY 800
#define ALTURA_DISPLAY 600


Game::Game() {
	//inicializa a biblioteca allegro
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();

	display = al_create_display(LARGURA_DISPLAY, ALTURA_DISPLAY);

	menu = new Menu(display);
	sist_graf = new Sistema_Grafico(display, menu);
}


Game::~Game()
{
	al_destroy_display(display);
	while (partidas.size() > 0)
	{
		delete(partidas[0]);
		partidas.erase(partidas.begin());
	}
	partidas.clear();

	delete (menu);
	delete (sist_graf);
}

/*
	executa o jogo
*/
void Game::execute() {
	Partida* partida;
	while (menu->getRun())
	{
		switch (menu->main_menu())
		{
		case 2: //cria uma nova partida para 2 jogadores
			partida = new Partida(sist_graf);
			baralho.resetaBaralho();
			partida->setBaralho(&baralho);
			defineNomeJogs(2);
			partida->addJogador(&jog1, 1);
			partida->addJogador(&jog2, 2);
			partidas.push_back(partida);
			partida->iniciaPartida();
			break;

		case 4: //cria uma nova partida para 4 jogadores
			partida = new Partida(sist_graf);
			baralho.resetaBaralho();
			partida->setBaralho(&baralho);
			defineNomeJogs(4);
			partida->addJogador(&jog1, 1);
			partida->addJogador(&jog2, 2);
			partida->addJogador(&jog3, 1);
			partida->addJogador(&jog4, 2);
			partidas.push_back(partida);
			partida->iniciaPartida();
			break;

		default:
			break;
		}
	}
}

//abre arquivo .txt com o nome dos jogadores e atribui aos objetos Jogador
void Game::defineNomeJogs(int numJogs)
{
	ifstream r_file(ARQUIVO_NOME_JOGS);
	int i;
	for (i = 0; i < numJogs && !r_file.eof(); i++)
	{
		string nome;
		getline(r_file, nome);
		if (i == 0)
			jog1.setNome(nome);
		else if (i == 1)
			jog2.setNome(nome);
		else if (i == 2)
			jog3.setNome(nome);
		else if (i == 3)
			jog4.setNome(nome);
	}
	if (i < numJogs)
	{
		while (i < numJogs)
		{
			if (i == 0)
				jog1.setNome("Jogador 1");
			else if (i == 1)
				jog2.setNome("Jogador 2");
			else if (i == 2)
				jog3.setNome("Jogador 3");
			else if (i == 3)
				jog4.setNome("Jogador 4");
			i++;
		}
	}
}
