
#include <iostream>
#include <vector>
#include "entrada.h"
using namespace std;

class Configuracoes
{
public:
    int custoTotal = 0;
    int atratividadeAgregada = 0;
    int quantidadePontosDeInteresse;
    void imprimirResultado()
    {
    }
};

int main()
{
    int qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto;
    Descontos descontos;
    vector<Escala> vetorEscalas;
    leEntradaPrincipal(qtdEscalas, qtdMaximaEscalasParaDesconto, tempoMaximoDesconto);
    descontos = leEntradaDescontos();
    vetorEscalas = leEntradaEscalas(qtdEscalas);

    return 0;
}