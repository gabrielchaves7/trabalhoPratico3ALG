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

class Promocoes
{
public:
    vector<int> valores;
    void adicionarPromocao(int promocao){
        this->valores.push_back(promocao);
    }
    int obterPromocaoCumulativa(int posicao){
        int resultado = 0;
        for(int i =0; i<=posicao; i++){
            resultado += valores.at(i);
            if(resultado >= 100){
                return 100;
            }
        }

        return resultado;
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