#include <iostream>
#include <iomanip>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
using namespace std;

int obterDescontoAcumulado(int descontos[], int posDesconto){
    int descontoAcumulado = 0;
    for(int i =0; i <=posDesconto; i ++){
        descontoAcumulado += descontos[i];
    }

    return descontoAcumulado;
}

double knapSack(int limiteTempo, int limiteSequencia, int tempos[], double precos[], int descontos[], int n, int qtdEscalas, int tempoAcumulado, double precoAcumulado, int posDesconto, vector<Escala>* escalas)
{
    if (n == qtdEscalas){
        return precoAcumulado;
    }

    if(tempoAcumulado < limiteTempo && posDesconto < limiteSequencia ){
        int descontoAcumulado = obterDescontoAcumulado(descontos, posDesconto);
        double preco = ((precos[n] * (100 - descontoAcumulado) ) / 100);
        precoAcumulado += preco;
        escalas->at(n).preco = preco;
        escalas->at(n).posDescontoRecebido = posDesconto;

        escalas->at(n).tempoAcumulado = tempoAcumulado;
        tempoAcumulado += tempos[n];
        
    } else {
        posDesconto = 0;
        double preco = ((precos[n] * (100 - descontos[posDesconto]) ) / 100);
        precoAcumulado += preco;
        escalas->at(n).preco = preco;
        escalas->at(n).posDescontoRecebido = posDesconto;

        escalas->at(n).tempoAcumulado = tempoAcumulado;
        tempoAcumulado = tempos[n];
        
    }
    
    return knapSack(limiteTempo, limiteSequencia, tempos, precos, descontos, n + 1, qtdEscalas, tempoAcumulado, precoAcumulado, posDesconto + 1, escalas);
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
    vector<Escala> resultado;


    for(int i =0; i <vetorEscalas.size(); i ++){
        int posicaoDesconto = 0;
        int tempoAcumulado = 0;
        if(i != 0){
            Escala escalaAtual = vetorEscalas.at(i);
            posicaoDesconto = escalaAtual.posDescontoRecebido;
            tempoAcumulado = escalaAtual.tempoAcumulado;
        }
        
        double continuarComDesconto = knapSack(limiteTempo, limiteSequencia, tempos, precos, descontos, i, qtdEscalas, tempoAcumulado, 0, posicaoDesconto, &vetorEscalas);
        double novoPrecoContinuarComDesconto = 0;
        for(int i =0; i<qtdEscalas; i ++){            
            Escala escalaAtual = vetorEscalas.at(i);
            novoPrecoContinuarComDesconto += escalaAtual.preco;
        }

        double novoPrecoResetarDesconto = 0;
        double resetarDesconto = knapSack(limiteTempo, limiteSequencia, tempos, precos, descontos, i, qtdEscalas, 0, 0, 0, &vetorEscalas);
        for(int i =0; i<qtdEscalas; i ++){            
            Escala escalaAtual = vetorEscalas.at(i);
            novoPrecoResetarDesconto += escalaAtual.preco;
        }

        if(novoPrecoContinuarComDesconto < melhorPreco || novoPrecoResetarDesconto < melhorPreco || melhorPreco == 0){
            if(novoPrecoContinuarComDesconto < novoPrecoResetarDesconto){
                melhorPreco = novoPrecoResetarDesconto;
            } else {
                melhorPreco = novoPrecoResetarDesconto;
            }
        }
        
    }

    cout << "--------------- \n";
    cout << melhorPreco;
    cout << "--------------- \n";
    return 0;
}