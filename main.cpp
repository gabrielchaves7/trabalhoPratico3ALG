#include <iostream>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
#include "particao.h"
#include "descontos.h"
using namespace std;

int obterDescontoAcumulado(int descontos[], int posDesconto){
    int descontoAcumulado = 0;
    for(int i =0; i <=posDesconto; i ++){
        descontoAcumulado += descontos[i];
    }

    return descontoAcumulado;
}

double knapSack(int limiteTempo, int limiteSequencia, int tempos[], double precos[], int descontos[], int n, int qtdEscalas, int tempoAcumulado, double precoAcumulado, int *posDesconto)
{
    if (n == qtdEscalas){
        return precoAcumulado;
    }

    if(tempoAcumulado < limiteTempo && *posDesconto < limiteSequencia ){
        int descontoAcumulado = obterDescontoAcumulado(descontos, *posDesconto);
        precoAcumulado += ((precos[n] * (100 - descontoAcumulado) ) / 100);
        tempoAcumulado += tempos[n];
    } else {
        *posDesconto = 0;
        precoAcumulado += ((precos[n] * (100 - descontos[*posDesconto]) ) / 100);
        tempoAcumulado = tempos[n];
    }
    

    return knapSack(limiteTempo, limiteSequencia, tempos, precos, descontos, n + 1, qtdEscalas, tempoAcumulado, precoAcumulado, posDesconto + 1);
}


int main()
{
    int qtdEscalas, limiteSequencia, limiteTempo;
    Promocoes promocoes;
    vector<Escala> vetorEscalas;
    leEntradaPrincipal(qtdEscalas, limiteSequencia, limiteTempo);
    promocoes = leEntradaDescontos();
    vetorEscalas = leEntradaEscalas(qtdEscalas);


    double precos[qtdEscalas];
    int tempos[qtdEscalas];
    int descontos[promocoes.valores.size()];
    for(int i =0; i <vetorEscalas.size(); i++){
        precos[i] = vetorEscalas.at(i).preco;
        tempos[i] = vetorEscalas.at(i).tempo;
    }

    for(int i =0; i<promocoes.valores.size(); i++){
        descontos[i] = promocoes.valores.at(i);
    }

    double melhorPreco = 0;
    int posicaoDesconto = 0;
    for(int i =0; i <vetorEscalas.size(); i ++){
        double continuarComDesconto = knapSack(limiteTempo, limiteSequencia, tempos, precos, descontos, i, qtdEscalas, 0, 0, &posicaoDesconto);
        double resetarDesconto = knapSack(limiteTempo, limiteSequencia, tempos, precos, descontos, i, qtdEscalas, limiteSequencia, 0, &posicaoDesconto);

        if(continuarComDesconto < melhorPreco || resetarDesconto < melhorPreco || melhorPreco == 0){
            if(continuarComDesconto < resetarDesconto){
                melhorPreco = continuarComDesconto;
            } else {
                melhorPreco = resetarDesconto;
            }
        }
        
    }

    cout << "--------------- \n";
    cout << melhorPreco;
    cout << "--------------- \n";
    return 0;
}