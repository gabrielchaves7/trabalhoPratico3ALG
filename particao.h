int acharPosicaoEscalaMaisCara(vector<Escala> vetorEscalas){
    Escala escalaMaisCara = vetorEscalas.at(0);
    int posicaoEscalaMaisCara = 0;
    for(int i=1; i<vetorEscalas.size(); i++){
        Escala escalaAtual = vetorEscalas.at(i);
        if((escalaMaisCara.preco < escalaAtual.preco && escalaAtual.utilizada == false) || escalaMaisCara.utilizada == true){
            escalaMaisCara = escalaAtual;
            posicaoEscalaMaisCara = i;
        }
    }

    return posicaoEscalaMaisCara;
}

vector<Escala> particaoComEscalaMaisCara(vector<Escala>* vetorEscalas, int qtdMaximaEscalasParaDesconto, int tempoMaximoDesconto, int posicaoEscalaMaisCara){
    vector<Escala> particaoComEscalaMaisCara;
    int tempoAcumulado = 0;
    for(int i=0; i<posicaoEscalaMaisCara; i++){
        Escala* escalaAtual = &vetorEscalas->at(i);
        if(escalaAtual->utilizada == false){
            if(particaoComEscalaMaisCara.size() < qtdMaximaEscalasParaDesconto && tempoAcumulado < tempoMaximoDesconto){
                particaoComEscalaMaisCara.push_back(*escalaAtual);
                tempoAcumulado += escalaAtual->tempo;
                
            } else {
                particaoComEscalaMaisCara.clear();
                tempoAcumulado = 0;
            }
        }
    }


    Escala* escalaMaisCara = &vetorEscalas->at(posicaoEscalaMaisCara);
    particaoComEscalaMaisCara.push_back(*escalaMaisCara);

    for(int i =0; i <particaoComEscalaMaisCara.size(); i ++){
        vetorEscalas->at(particaoComEscalaMaisCara.at(i).codigo).utilizada = true;
    }
    
    return particaoComEscalaMaisCara;
}