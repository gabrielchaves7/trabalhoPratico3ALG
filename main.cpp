#include <iostream>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
#include "particao.h"
#include "descontos.h"
using namespace std;

vector<Descontos> calcularRota(vector<Escala> vetorEscalas, Promocoes promocoes, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto){
    vector<Descontos> resultado;
    bool todasEscalasUtilizadas = false;
    do{
        int posicaoEscalaMaisCara = acharPosicaoEscalaMaisCara(vetorEscalas);
        Escala escalaMaisCara = vetorEscalas.at(posicaoEscalaMaisCara);

        vector<Escala> particao = particaoComEscalaMaisCara(&vetorEscalas, qtdMaximaEscalasParaDesconto,tempoMaximoDesconto, posicaoEscalaMaisCara);
        Descontos melhorDesconto = acharMelhorDesconto(particao, promocoes, tempoMaximoDesconto);
        melhorDesconto = continuarComMelhorDesconto(melhorDesconto, promocoes, tempoMaximoDesconto, &vetorEscalas, particao.at(particao.size() - 1).codigo, &particao, qtdMaximaEscalasParaDesconto);

        todasEscalasUtilizadas = true;
        for(int i = 0; i<vetorEscalas.size(); i++){
            if(vetorEscalas.at(i).utilizada == false){
                todasEscalasUtilizadas = false;
            }

        }
        resultado.push_back(melhorDesconto);
    } while(todasEscalasUtilizadas != true);

    return resultado;
}

int main()
{
    int qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto;
    Promocoes promocoes;
    vector<Escala> vetorEscalas;
    leEntradaPrincipal(qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
    promocoes = leEntradaDescontos();
    vetorEscalas = leEntradaEscalas(qtdEscalas);
    vector<Descontos> resultado = calcularRota(vetorEscalas, promocoes, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);

    int total = 0;
    for(int i = 0; i<resultado.size(); i ++){
        total+=resultado.at(i).precoAcumulado;
    }
    cout << "--------------- \n";
    cout << total; 
    return 0;
}