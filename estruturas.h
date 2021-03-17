#include <vector>
using namespace std;

class Escala
{
public:
    int tempo;
    int preco;
    int codigo;
    Escala(int tempo, int preco, int codigo)
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

class Descontos
{
public:
    vector<int> valores;
    int posicaoDescontoAtual;
    int tempoAcumulado;
    int precoAcumulado;
    Descontos(int posDesconto, int tempoAcumulado, int precoAcumulado){
        this->posicaoDescontoAtual = posDesconto;
        this->tempoAcumulado = tempoAcumulado;
        this->precoAcumulado = precoAcumulado;
    }
};