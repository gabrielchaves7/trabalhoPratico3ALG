#include <vector>
using namespace std;

class Escala
{
public:
    int tempo;
    int preco;
    Escala(int tempo, int preco)
    {
        this->tempo = tempo;
        this->preco = preco;
    }
};

class Descontos
{
public:
    vector<int> valores;
    void adicionarDesconto(int desconto){
        this->valores.push_back(desconto);
    }
    int obterDescontoCumulativo(int posicao){
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