int acharPosicaoEscalaMaisCara(vector<Escala> vetorEscalas){
    Escala escalaMaisCara = vetorEscalas.at(0);
    int posicaoEscalaMaisCara = 0;
    for(int i=1; i<vetorEscalas.size(); i++){
        Escala escalaAtual = vetorEscalas.at(i);
        if(escalaMaisCara.preco < escalaAtual.preco){
            escalaMaisCara = escalaAtual;
            posicaoEscalaMaisCara = i;
        }
    }

    return posicaoEscalaMaisCara;
}

vector<Escala> particaoComEscalaMaisCara(vector<Escala> vetorEscalas, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto, int posicaoEscalaMaisCara){
    vector<Escala> particaoComEscalaMaisCara;
    int tempoAcumulado = 0;
    for(int i=posicaoEscalaMaisCara; i>=0; i--){
        if(particaoComEscalaMaisCara.size() < qtdMaximaEscalasParaDesconto && tempoAcumulado < tempoMaximoDesconto){
            particaoComEscalaMaisCara.push_back(vetorEscalas.at(i));
            tempoAcumulado += vetorEscalas.at(i).tempo;
        }
    }

    return particaoComEscalaMaisCara;
}