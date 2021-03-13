#include <iostream>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
using namespace std;

class Rota
{
public:
    int tempoAcumulado = 0;
    int descontoAtual = 0;
    int posDesconto = 0;
    int sequenciaAtual = 0;
    int precoAcumulado = 0;
    Rota(int tempoAcumulado, int posDesconto, int descontoAtual, int sequenciaAtual, int precoAcumulado){
        this->tempoAcumulado += tempoAcumulado ;
        this->descontoAtual += descontoAtual ;
        this->sequenciaAtual += sequenciaAtual ;
        this->precoAcumulado += precoAcumulado ; 
        this->posDesconto = posDesconto;
    };
};

Rota continuarComDescontoETempoAtual(Rota rotaAtual, Escala escalaAtual, Descontos descontos){
    rotaAtual.sequenciaAtual++;
    rotaAtual.posDesconto++;

    int descontoAtual = descontos.obterDescontoCumulativo(rotaAtual.posDesconto);

    rotaAtual.descontoAtual = descontoAtual;

    rotaAtual.tempoAcumulado+=escalaAtual.tempo;
    rotaAtual.precoAcumulado+= ((escalaAtual.preco * descontoAtual) / 100);

    return rotaAtual;
}

Rota pararEResetarDescontoETempo(Rota rotaAtual, Escala escalaAtual, Descontos descontos){
    rotaAtual.sequenciaAtual = 1;
    rotaAtual.posDesconto = 0;
    rotaAtual.descontoAtual = descontos.obterDescontoCumulativo(0);

    rotaAtual.precoAcumulado += escalaAtual.preco;
    rotaAtual.tempoAcumulado += escalaAtual.tempo;

    return rotaAtual;
}

vector<Rota> acharMelhorOpcao(vector<Escala> vetorEscalas, Descontos descontos, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto){
    vector<Rota> rotas;

    Escala escalaInicial = vetorEscalas.at(0);
    Rota rotaInicial = Rota(escalaInicial.tempo, 0, descontos.valores.at(0), 1, escalaInicial.preco);
    
    Escala escalaAtual = vetorEscalas.at(1);

    Rota rotaContinuar = continuarComDescontoETempoAtual(rotaInicial, escalaAtual, descontos);
    Rota rotaResetar = pararEResetarDescontoETempo(rotaInicial, escalaAtual, descontos);



    rotas.push_back(rotaContinuar);
    rotas.push_back(rotaResetar);

    return rotas;
}

int main()
{
    int qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto;
    Descontos descontos;
    vector<Escala> vetorEscalas;
    leEntradaPrincipal(qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
    descontos = leEntradaDescontos();
    vetorEscalas = leEntradaEscalas(qtdEscalas);
    vector<Rota> rotas = acharMelhorOpcao(vetorEscalas, descontos, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);

    return 0;
}