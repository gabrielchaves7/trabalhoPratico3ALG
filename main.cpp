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
    double precoAcumulado = 0;
    Rota(int tempoAcumulado, int posDesconto, int descontoAtual, int sequenciaAtual, double precoAcumulado){
        this->tempoAcumulado += tempoAcumulado ;
        this->descontoAtual += descontoAtual ;
        this->sequenciaAtual += sequenciaAtual ;
        this->precoAcumulado += precoAcumulado ; 
        this->posDesconto = posDesconto;
    };
};

Rota continuarComDescontoETempoAtual(Rota rotaAtual, Escala escalaAtual, Descontos descontos, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto){
    rotaAtual.sequenciaAtual++;
    rotaAtual.posDesconto++;

    if(rotaAtual.sequenciaAtual > qtdMaximaEscalasParaDesconto || rotaAtual.tempoAcumulado >= tempoMaximoDesconto){
        rotaAtual.posDesconto = 0;
        rotaAtual.sequenciaAtual = 0;
        rotaAtual.tempoAcumulado = 0;
    } else {
        rotaAtual.tempoAcumulado+=escalaAtual.tempo;
    }

    rotaAtual.descontoAtual = descontos.obterDescontoCumulativo(rotaAtual.posDesconto);
    rotaAtual.precoAcumulado+= ((escalaAtual.preco * (100 - rotaAtual.descontoAtual) ) / 100);

    return rotaAtual;
}

Rota pararEResetarDescontoETempo(Rota rotaAtual, Escala escalaAtual, Descontos descontos){
    rotaAtual.sequenciaAtual = 1;
    rotaAtual.posDesconto = 0;
    rotaAtual.descontoAtual = descontos.obterDescontoCumulativo(0);

    rotaAtual.precoAcumulado += ((escalaAtual.preco * (100 - rotaAtual.descontoAtual) ) / 100);
    rotaAtual.tempoAcumulado = escalaAtual.tempo;

    return rotaAtual;
}

vector<Rota> acharMelhorOpcao(vector<Escala> vetorEscalas, Descontos descontos, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto){
    vector<Rota> rotas;
    vector<Rota> rotasTemp;

    Escala escalaInicial = vetorEscalas.at(0);
    Rota rotaInicial = Rota(escalaInicial.tempo, 0, descontos.valores.at(0), 1, escalaInicial.preco);
    
    Escala escalaAtual = vetorEscalas.at(1);
    Rota rotaContinuar = continuarComDescontoETempoAtual(rotaInicial, escalaAtual, descontos, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
    Rota rotaResetar = pararEResetarDescontoETempo(rotaInicial, escalaAtual, descontos);

    rotasTemp.push_back(rotaContinuar);
    rotasTemp.push_back(rotaResetar);

    for(int j = 2; j<vetorEscalas.size(); j ++){
        rotas.clear();

        Escala escalaAtual = vetorEscalas.at(j);
        for(int i =0 ; i<rotasTemp.size(); i++){
            Rota rotaAtual = rotasTemp.at(i);
            Rota rotaContinuar = continuarComDescontoETempoAtual(rotaAtual, escalaAtual, descontos, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
            Rota rotaResetar = pararEResetarDescontoETempo(rotaAtual, escalaAtual, descontos);
            rotas.push_back(rotaContinuar);
            rotas.push_back(rotaResetar);
        }

        rotasTemp.clear();

        for(int i = 0; i<rotas.size(); i++){
            rotasTemp.push_back(rotas.at(i));
        }
    }



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
    
    int menorPreco = rotas.at(0).precoAcumulado;
    Rota rotaComMenorPreco = rotas.at(0);
    for(int i =1; i< rotas.size(); i++){
        if(rotas.at(i).precoAcumulado < menorPreco){
            menorPreco = rotas.at(i).precoAcumulado;
            rotaComMenorPreco = rotas.at(i);
        }
            
    }


    return 0;
}