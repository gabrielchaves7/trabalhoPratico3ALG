#include <iostream>
#include <vector>
#include "estruturas.h"
#include "entrada.h"
using namespace std;

class Rota
{
public:
    vector<Escala> escalas;
    int tempoAcumulado = 0;
    int descontoAtual = 0;
    int sequenciaAtual = 0;
    Rota();
    Rota(vector<Escala> escalas)
    {
        this->escalas = escalas;
        for(int i=0; i< escalas.size(); i++){
            this->tempoAcumulado += escalas.at(i).tempo;
        }
    }
    void adicionarEscala(Escala escala){
        this->escalas.push_back(escala);
        this->tempoAcumulado += escala.tempo;
    }
};

void continuarComDescontoETempoAtual(){

}

void pararEResetarDescontoETempo(){

}

vector<Rota> acharMelhorOpcao(vector<Escala> vetorEscalas){
    vector<Rota> rotas;
    
    for(int i =0; i<vetorEscalas.size(); i++){
        Escala escalaAtual = vetorEscalas.at(i);
        if(i==0){
            vector<Escala> escalas;
            escalas.push_back(escalaAtual);
            rotas.push_back(escalas);    
        } else {
            for(int j=0; j<=i;j++){
                if(j < rotas.size()){
                    rotas.at(j).adicionarEscala(escalaAtual);
                } else {
                    vector<Escala> teste = rotas.at(j -1).escalas;
                    vector<Escala> escalas;
                    for(int k =0; k< teste.size(); k++){
                        escalas.push_back(teste.at(k));
                    }
                    
                    rotas.push_back(escalas);    
                }
            }
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
    vector<Rota> rotas = acharMelhorOpcao(vetorEscalas);

    return 0;
}