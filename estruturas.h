#include <vector>
using namespace std;

class Escala
{
public:
    int tempo;
    double preco;
    int codigo;
    Escala(int tempo, double preco, int codigo)
    {
        this->tempo = tempo;
        this->preco = preco;
        this->codigo = codigo;   
    }
};

class Desconto
{
public:
    int tempoAcumulado;
    double precoAcumulado;
    Desconto(){};
    Desconto(int tempoAcumulado, double precoAcumulado){
        this->tempoAcumulado = tempoAcumulado;
        this->precoAcumulado = precoAcumulado;
    }
};