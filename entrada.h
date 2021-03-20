#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void leEntradaPrincipal(int &qtdEscalas, int &qtdMaximaEscalasParaDesconto, int &tempoMaximoDesconto)
{
    string temp;
    getline(cin, temp);
    vector<string> result;
    istringstream iss(temp);
    for (string s; iss >> s;)
        result.push_back(s);

    qtdEscalas = stoi(result.at(0));
    qtdMaximaEscalasParaDesconto = stoi(result.at(1));
    tempoMaximoDesconto = stoi(result.at(2));
}

vector<int> leEntradaDescontos()
{
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> promocoes;
    for (string s; iss >> s;)
    {
        promocoes.push_back(stoi(s));
    }

    return promocoes;
}

vector<Escala> leEntradaEscalas(int quantidadeEscalas)
{

    vector<Escala> vetorEscala;

    for (int i = 0; i < quantidadeEscalas; i++)
    {
        string line;
        getline(cin, line);
        istringstream iss(line);
        vector<string> temp;
        for (string s; iss >> s;)
        {
            temp.push_back(s);
        }

        int tempo = stoi(temp.at(0));
        int preco = stoi(temp.at(1));

        Escala escalaAtual = Escala(tempo, preco, i);
        vetorEscala.push_back(escalaAtual);
    }

    return vetorEscala;
}