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

double calcularDesconto(double preco, int desconto){
    return ((preco * (100 - desconto))/100);
}


Desconto acharMenorPrecoLinha(vector<Desconto> descontos){
    Desconto melhorDesconto = descontos.at(0);
    for(int i =1; i<descontos.size(); i ++){    
        Desconto descontoAtual = descontos.at(i);
        if(descontoAtual.precoAcumulado < melhorDesconto.precoAcumulado){
            melhorDesconto = descontoAtual;
        }
    }

    return melhorDesconto;
}

vector<vector<Desconto> > knapSack(int qtdEscalas, int limiteTempo, int qtdMaximaSequencia, int descontos[], vector<vector<Desconto> > matriz, vector<Escala> escalas)
{   
    int limiteSequencia = 2;
    for(int linhaAtual = 1; linhaAtual < qtdEscalas; linhaAtual ++){
        Escala escalaAtual = escalas.at(linhaAtual);
        for(int colunaAtual = 0; colunaAtual<limiteSequencia; colunaAtual++){
            Desconto melhorDescontoAnterior;
            int porcentagemDesconto;
            if(colunaAtual == 0){
                porcentagemDesconto = obterDescontoAcumulado(descontos, colunaAtual);
                melhorDescontoAnterior = acharMenorPrecoLinha(matriz.at(linhaAtual - 1));
                melhorDescontoAnterior.precoAcumulado += calcularDesconto(escalaAtual.preco, porcentagemDesconto);
                melhorDescontoAnterior.tempoAcumulado = 0;
                
            } else {
                melhorDescontoAnterior = matriz.at(linhaAtual - 1).at(colunaAtual - 1);
                if(melhorDescontoAnterior.tempoAcumulado >= limiteTempo ){
                    porcentagemDesconto = obterDescontoAcumulado(descontos, 0);
                } else {
                    porcentagemDesconto = obterDescontoAcumulado(descontos, colunaAtual);
                }

                melhorDescontoAnterior.precoAcumulado += calcularDesconto(escalaAtual.preco, porcentagemDesconto);
            }

                melhorDescontoAnterior.tempoAcumulado += escalaAtual.tempo;
                matriz.at(linhaAtual).push_back(melhorDescontoAnterior);
        }

        if(limiteSequencia < qtdMaximaSequencia){
            limiteSequencia = limiteSequencia + 1;
        }
        
    }

    return matriz;
}

int main()
{
    int qtdEscalas, limiteSequencia, limiteTempo;
    Promocoes promocoes;
    vector<Escala> vetorEscalas;
    leEntradaPrincipal(qtdEscalas, limiteSequencia, limiteTempo);
    promocoes = leEntradaDescontos();
    vetorEscalas = leEntradaEscalas(qtdEscalas);
    int descontos[promocoes.valores.size()];
    for(int i =0; i <promocoes.valores.size(); i++){
        descontos[i] = promocoes.valores.at(i);
    }


    vector<vector<Desconto> > matriz;
    for(int i =0; i<qtdEscalas; i ++){
        vector<Desconto> vetorInicial;
        matriz.push_back(vetorInicial);
    }

    

    Escala escalaInicial = vetorEscalas.at(0);
    Desconto desconto = Desconto(escalaInicial.tempo, calcularDesconto(escalaInicial.preco, descontos[0]));
    matriz.at(0).push_back(desconto);

    matriz = knapSack(qtdEscalas, limiteTempo, limiteSequencia, descontos, matriz, vetorEscalas);

    double melhorPreco = matriz.at(qtdEscalas - 1).at(0).precoAcumulado;
    for(int i =1; i<limiteSequencia; i++){
        if(matriz.at(qtdEscalas - 1).at(i).precoAcumulado < melhorPreco){
            melhorPreco = matriz.at(qtdEscalas - 1).at(i).precoAcumulado;
        }
    }

    cout << fixed << setprecision(2) << melhorPreco << "\n";
    return 0;
}