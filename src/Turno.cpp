#include "stdafx.h"
#include "Turno.h"
#include "Rodada.h"
#include "Partida.h"
#include "Sistema_Grafico.h"

int Turno::auto_incr = 1;

Turno::Turno(Rodada * const pRodada)
{
	id = auto_incr;
	auto_incr++;
	cont = 0;
	empate = false;
	rodada = pRodada;
	maiorCarta = nullptr;
	venceuTurno = nullptr;
}


Turno::~Turno()
{
	rodada = nullptr;
	maiorCarta = nullptr;
	venceuTurno = nullptr;
}


void Turno::setRodada(Rodada* const pRodada)
{
	rodada = pRodada;
}


Rodada* const Turno::getRodada()
{
	return rodada;
}

/*
	Loop do turno, os dois ou quatro jogadores lançam suas cartas e é
	definido o jogador/time que venceu o turno com a maior carta.
*/
void Turno::iniciarTurno()
{
    Partida* partida = rodada->getPartida();
	Baralho* baralho = partida->getBaralho();
    int num_jogs = partida->getNumJogs();
    Jogador* jogAtual = partida->getJogadorAtual();
	Sistema_Grafico* sistGraf = partida->getSistemaGrafico();
	sistGraf->activate_truco_btn();

    for(cont = 0; cont < num_jogs; cont++)
    {
		CartaTruco* cartaSelecionada = nullptr;

		int saida = -1;
		// enquanto o jogador não selecionar uma carta, fechar o jogo
		// ou não aceitar o truco, continua rodando o loop do sistema gráfico
		while((saida < 0 || saida > 2) && saida != 666 && saida != 12 && saida != 11)
			saida = sistGraf->loop();
		if (saida == 0 || saida == 1 || saida == 2)
		{
			cartaSelecionada = jogAtual->getCarta(saida);
			// loop de espera para o próximo jogador
			if (sistGraf->flipWait() == 666) {
				Partida::fechar = true;
				return;
			}
			jogAtual->delCarta(cartaSelecionada);
			baralho->usadaParaDescarte(cartaSelecionada);
			
			comparaMaiorCarta(cartaSelecionada);
			if (cartaSelecionada == maiorCarta)
				venceuTurno = jogAtual;
			// define se o botão de truco estará ou não ativado para o próximo jogador
			// caso o jogador seja do time que pediu truco, o botão estará desativado
			if (rodada->getTimeTruco() != partida->getTimeJogador(jogAtual))
				sistGraf->activate_truco_btn();
			jogAtual = partida->proxJogador();
		}
		// código quando um dos times não aceita o truco (11 caso o
 		// time 2 não tenha aceitado e 12 caso o time 1 não tenha aceitado)
		else if (saida == 11 || saida == 12)
		{
			if (saida == 11)
			{
				rodada->resetaFeitas();
				rodada->addFeitas1();
				rodada->addFeitas1();
				rodada->addFeitas1();
			}
			else
			{
				rodada->resetaFeitas();
				rodada->addFeitas2();
				rodada->addFeitas2();
				rodada->addFeitas2();
			}
			break;
		}
		else if (saida == 666)
		{
			Partida::fechar = true;
			return;
		}
    }
	// tela final do turno
	if (!Partida::fechar)
	{
		sistGraf->deactivate_truco_btn();
		sistGraf->show();
		al_rest(1);
	}
	// devolve ao baralho as cartas que foram jogadas pelos jogadores
	baralho->devolveDescartes();
}


Jogador* const Turno::getVenceuTurno() {  return venceuTurno;  }
CartaTruco* const Turno::getMaiorCarta() {  return maiorCarta;  }

/*
	Compara o valor da "pCarta" com o da "maiorCarta", caso o valor daquela seja maior
	que o dessa, a maiorCarta é atualizada e recebe pCarta
*/
void Turno::comparaMaiorCarta(CartaTruco* const pCarta)
{
    if(maiorCarta != nullptr)
    {
        if(pCarta->getValor() > maiorCarta->getValor())
        {
            maiorCarta = pCarta;
            empate = false;
        }
        else if(pCarta->getValor() == maiorCarta->getValor())
        {
            maiorCarta = pCarta;
            empate = true;
        }
    }
    else
        maiorCarta = pCarta;
}

const bool Turno::getEmpate() {  return empate; }
