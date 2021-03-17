#include <iostream>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
#include "particao.h"
#include "descontos.h"
using namespace std;

vector<Descontos> calcularRota(vector<Escala> vetorEscalas, Promocoes promocoes, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto){
    vector<Descontos> resultado;
    do{
        int posicaoEscalaMaisCara = acharPosicaoEscalaMaisCara(vetorEscalas);
        Escala escalaMaisCara = vetorEscalas.at(posicaoEscalaMaisCara);

        vector<Escala> particao = particaoComEscalaMaisCara(vetorEscalas, qtdMaximaEscalasParaDesconto,tempoMaximoDesconto, posicaoEscalaMaisCara);
        Descontos melhorDesconto = acharMelhorDesconto(particao, promocoes, tempoMaximoDesconto);
        melhorDesconto = continuarComMelhorDesconto(melhorDesconto, promocoes, tempoMaximoDesconto, vetorEscalas, particao.at(posicaoEscalaMaisCara).codigo, &particao);


        vector<int> codigosEscalasParaRemover;
        for(int i =0; i<particao.size(); i++){
            codigosEscalasParaRemover.push_back(particao.at(i).codigo);   
        }

        vector<Escala> novoVetorEscalas;
        for(int i =0; i<vetorEscalas.size(); i++){
            Escala escalaAtual = vetorEscalas.at(i);
            if(! (find(codigosEscalasParaRemover.begin(), codigosEscalasParaRemover.end(), escalaAtual.codigo) != codigosEscalasParaRemover.end())){
                novoVetorEscalas.push_back(escalaAtual);
            }
        }

        for(int i =0; i<novoVetorEscalas.size(); i ++){
            novoVetorEscalas.at(i).codigo = i;
        }
        vetorEscalas.clear();
        vetorEscalas = novoVetorEscalas;
        resultado.push_back(melhorDesconto);
    } while(vetorEscalas.size() > 0);

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
    calcularRota(vetorEscalas, promocoes, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
    int menorPreco = 0;
    cout << "--------------- \n";
    cout << menorPreco; 
    return 0;
}