#include <iostream>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
using namespace std;

int acharPosicaoEscalaMaisCara(vector<Escala> vetorEscalas){
    Escala escalaMaisCara = vetorEscalas.at(0);
    int posicaoEscalaMaisCara = 0;
    for(int i=1; i<vetorEscalas.size(); i++){
        Escala escalaAtual = vetorEscalas.at(i);
        if(escalaMaisCara.preco < escalaAtual.preco){
            escalaMaisCara = escalaAtual;
            posicaoEscalaMaisCara = i;
        }
    }

    return posicaoEscalaMaisCara;
}

vector<Escala> particaoComEscalaMaisCara(vector<Escala> vetorEscalas, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto, int posicaoEscalaMaisCara){
    vector<Escala> particaoComEscalaMaisCara;
    int tempoAcumulado = 0;
    for(int i=posicaoEscalaMaisCara; i>=0; i--){
        if(particaoComEscalaMaisCara.size() < qtdMaximaEscalasParaDesconto && tempoAcumulado < tempoMaximoDesconto){
            particaoComEscalaMaisCara.push_back(vetorEscalas.at(i));
            tempoAcumulado += vetorEscalas.at(i).tempo;
        }
    }

    return particaoComEscalaMaisCara;
}

Descontos continuarComDesconto(Descontos descontosAtuais, Promocoes promocoes, int posicao, Escala escalaAtual, int tempoMaximo){
    int porcentagemDesconto;
    if(descontosAtuais.tempoAcumulado >= tempoMaximo){
        descontosAtuais.tempoAcumulado = 0;
        descontosAtuais.posicaoDescontoAtual = 0;
        porcentagemDesconto = promocoes.obterDescontoCumulativo(descontosAtuais.posicaoDescontoAtual);
        descontosAtuais.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
        descontosAtuais.valores.push_back(porcentagemDesconto);
    } else {
        descontosAtuais.tempoAcumulado += escalaAtual.tempo;
        descontosAtuais.posicaoDescontoAtual = posicao + 1;
        porcentagemDesconto = promocoes.obterDescontoCumulativo(descontosAtuais.posicaoDescontoAtual);
        descontosAtuais.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
        descontosAtuais.valores.push_back(porcentagemDesconto);
    }
    
    return descontosAtuais;
}

Descontos pararComDesconto(Descontos descontosAtuais, Promocoes promocoes, Escala escalaAtual){
    descontosAtuais.valores.push_back(0);
    descontosAtuais.posicaoDescontoAtual = 0;
    descontosAtuais.tempoAcumulado = 0;
    int porcentagemDesconto = promocoes.obterDescontoCumulativo(descontosAtuais.posicaoDescontoAtual);
    descontosAtuais.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
    return descontosAtuais;
}

vector<Descontos> obterDescontosPossiveis(vector<Escala> particao, Promocoes promocoes, int tempoMaximo){
    Escala escalaInicial = particao.at(particao.size() - 1);
    Descontos descontos(0, escalaInicial.tempo, escalaInicial.preco);
    descontos.valores.push_back(promocoes.valores.at(0));

    vector<Descontos> opcoesDescontos;
    vector<Descontos> opcoesDescontosTemp;
    opcoesDescontosTemp.push_back(descontos);


    for(int i = (particao.size() - 2); i>=0; i --){
        opcoesDescontos.clear();

        for(int j = 0; j<opcoesDescontosTemp.size(); j ++){
            Descontos descontos = opcoesDescontosTemp.at(j);
            Descontos continuar = continuarComDesconto(descontos, promocoes, descontos.posicaoDescontoAtual, particao.at(i), tempoMaximo);
            Descontos parar = pararComDesconto(descontos,promocoes, particao.at(i));
            opcoesDescontos.push_back(continuar);
            opcoesDescontos.push_back(parar);
        }

        opcoesDescontosTemp.clear();

        for(int i = 0; i<opcoesDescontos.size(); i++){
            opcoesDescontosTemp.push_back(opcoesDescontos.at(i));
        }
    }

    return opcoesDescontos;
}

Descontos acharMelhorDesconto(vector<Escala> particao, Promocoes promocoes, int tempoMaximo){
    vector<Descontos> opcoesDescontos = obterDescontosPossiveis(particao, promocoes, tempoMaximo);

    Descontos melhorDesconto = opcoesDescontos.at(0);
    for(int i=1 ; i<opcoesDescontos.size(); i ++){
        if(melhorDesconto.precoAcumulado > opcoesDescontos.at(i).precoAcumulado){
            melhorDesconto = opcoesDescontos.at(i);
        }
    }

    
    return melhorDesconto;
}

Descontos continuarComMelhorDesconto(Descontos melhorDesconto, Promocoes promocoes, int tempoMaximo, vector<Escala> escalas, int codigoEscalaInicial){

    int posicaoEscalaAtual = codigoEscalaInicial + 1;
    Escala escalaAtual = escalas.at(posicaoEscalaAtual);

    for(int i = melhorDesconto.posicaoDescontoAtual;i<promocoes.valores.size(); i ++){
        if(melhorDesconto.tempoAcumulado < tempoMaximo){
            melhorDesconto.tempoAcumulado += escalaAtual.tempo;
            melhorDesconto.posicaoDescontoAtual = melhorDesconto.posicaoDescontoAtual + 1;
            int porcentagemDesconto = promocoes.obterDescontoCumulativo(melhorDesconto.posicaoDescontoAtual);
            melhorDesconto.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
            melhorDesconto.valores.push_back(porcentagemDesconto);
            posicaoEscalaAtual +=1;
            escalaAtual = escalas.at(posicaoEscalaAtual);
        }
    }

    return melhorDesconto;
}

int main()
{
    int qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto;
    Promocoes promocoes;
    vector<Escala> vetorEscalas;
    leEntradaPrincipal(qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
    promocoes = leEntradaDescontos();
    vetorEscalas = leEntradaEscalas(qtdEscalas);

    int posicaoEscalaMaisCara = acharPosicaoEscalaMaisCara(vetorEscalas);
    Escala escalaMaisCara = vetorEscalas.at(posicaoEscalaMaisCara);

    vector<Escala> particao = particaoComEscalaMaisCara(vetorEscalas, qtdMaximaEscalasParaDesconto,tempoMaximoDesconto, posicaoEscalaMaisCara);
    Descontos melhorDesconto = acharMelhorDesconto(particao, promocoes, tempoMaximoDesconto);
    melhorDesconto = continuarComMelhorDesconto(melhorDesconto, promocoes, tempoMaximoDesconto, vetorEscalas, particao.at(0).codigo);
    int menorPreco = 0;
    cout << "--------------- \n";
    cout << menorPreco; 
    return 0;
}