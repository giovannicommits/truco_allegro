#include "stdafx.h"
#include "Rodada.h"
#include "Partida.h"
#include "Sistema_Grafico.h"
int Rodada::auto_incr = 1;

Rodada::Rodada()
{
	id = auto_incr;
	valor = 1;
	num_turnos = 0;
	feitas[0] = 0;
	feitas[1] = 0;
	partida = nullptr;
	turnos[0] = nullptr;
	turnos[1] = nullptr;
	turnos[2] = nullptr;
	timeTruco = 0;
	auto_incr++;
}


Rodada::Rodada(Partida* const pPartida)
{
	id = auto_incr;
	valor = 1;
	num_turnos = 0;
	feitas[0] = 0;
	feitas[1] = 0;
	partida = pPartida;
	turnos[0] = nullptr;
	turnos[1] = nullptr;
	turnos[2] = nullptr;
	timeTruco = 0;
	auto_incr++;
}

Rodada::~Rodada()
{
	partida = nullptr;
	for (int i = 0; i < num_turnos; i++)
	{
		delete(turnos[i]);
	}
	jogadorInicial = nullptr;
}

/*
	Distribui cartas para todos jogadores da partida
*/
void Rodada::distribuirCartas()
{
    Jogador* pJog = partida->getJogadorAtual();
    int numJogs = partida->getNumJogs();
    for(int i = 0; i < 3; i++)
    {
        for(int u = 0; u < numJogs; u++)
        {
            pJog->addCarta((partida->getBaralho())->cartaBaralhoParaUsada());
            pJog = partida->proxJogador();
        }
    }
}

/*
	Atualiza o valor da rodada caso haja truco
*/
void Rodada::truco()
{
    if(valor == 1)
        valor = 3;
    else if(valor == 3)
        valor = 6;
    else if(valor == 6)
        valor = 9;
    else if(valor == 9)
        valor = 12;
}


void Rodada::setPartida(Partida* const pPartida)
{
    partida = pPartida;
}

/*
	Adiciona um turno feito ao time 1
*/
void Rodada::addFeitas1()
{
	feitas[0]++;
}

/*
	Adiciona um turno feito ao time 1
*/
void Rodada::addFeitas2()
{
	feitas[1]++;
}


const int Rodada::getFeitas1()
{
	return feitas[0];
}


const int Rodada::getFeitas2()
{
	return feitas[1];
}

/*
	Coloca como 0 o número de turnos feitos do time 1 e do time 2
*/
void Rodada::resetaFeitas()
{
	feitas[0] = 0;
	feitas[1] = 0;
}

Partida* const Rodada::getPartida()
{
    return partida;
}

void Rodada::iniciarRodada()
{
    //  primeira condição para caso as duas primeiras rodadas empatem (caso haja empate no turno os dois gaham pontos)
    //  segunda e terceira condições para o caso normal, enquanto nenhuma das duas equipes ganhar dois turnos
    //  quarta condição para não ultrapassar o número de turnos máximo, 3
	partida->getBaralho()->embaralha();
	distribuirCartas();
	partida->getBaralho()->virarCarta();
    jogadorInicial = partida->getJogadorAtual();
    while(((feitas[0] == feitas[1] && feitas[0] == 2) || (feitas[0] < 2 && feitas[1] < 2)) && num_turnos < 3)
    {
	// cria um novo turno e adiciona-o ao vetor de turnos da rodada
        turnos[num_turnos] = new Turno(this);
        Turno* turnoAtual = turnos[num_turnos];
	
        turnoAtual->iniciarTurno();
		if (Partida::fechar)
			return;
        partida->setJogadorAtual(turnoAtual->getVenceuTurno());
	// caso haja empate no turno
        if(turnoAtual->getEmpate())
        {
            feitas[1]++;
            feitas[0]++;
			// ativa a bola de turno feito de ambos times
			partida->getSistemaGrafico()->activateFeitas(1, num_turnos);
			partida->getSistemaGrafico()->activateFeitas(2, num_turnos);
        }
        else
        {
            Jogador* venceuTurno = turnoAtual->getVenceuTurno();
            int time = partida->getTimeJogador(venceuTurno);
            //  GARANTIR QUE O JOGADOR ESTÁ EM ALGUMA EQUIPE, SE NÃO ESTIVER É UM ERRO
            if(time != -1)
            {
                feitas[time-1]++;
				// ativa a bola de turno feito do time vencedor
				partida->getSistemaGrafico()->activateFeitas(time, num_turnos);
            }
        }
        num_turnos++;
    }

	// caso o número de turnos feitos dos dois times seja o mesmo
	if (feitas[0] == feitas[1])
	{
		//  para o caso de empatar tres rodadas, ninguem ganha
		if (feitas[0] == 3)
			return;
		int time = partida->getTimeJogador(turnos[0]->getVenceuTurno());
		// vence o time que ganhou o primeiro turno
		if (time == 1)
			partida->addPontosJogs1(valor);
		else if (time == 2)
			partida->addPontosJogs2(valor);
	}
	// adiciona os pontos da rodada ao time que venceu-a
    else if(feitas[0] > feitas[1])
        partida->addPontosJogs1(valor);
    else
        partida->addPontosJogs2(valor);

	// reseta o baralho, as cartas dos jogadores, o sistema gráfico e o jogador inicial
	partida->getSistemaGrafico()->tela_entre_rodadas();
	partida->getBaralho()->resetaBaralho();
	partida->resetaCartasJogs();
    partida->setJogadorAtual(jogadorInicial);
    partida->proxJogador();
	partida->getSistemaGrafico()->deactivate_all();
}

Turno* Rodada::getTurnoAtual() {
	return turnos[num_turnos];
}

int Rodada::getNumTurnos() {
	return num_turnos;
}

int Rodada::getValor() {
	return valor;
}

int Rodada::getTimeTruco()
{
	return timeTruco;
}

void Rodada::setTimeTruco(int aTime)
{
	timeTruco = aTime;
}
