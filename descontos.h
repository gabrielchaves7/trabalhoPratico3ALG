Descontos continuarComDesconto(Descontos descontosAtuais, Promocoes promocoes, int posicao, Escala escalaAtual, int tempoMaximo){
    int porcentagemDesconto;
    if(descontosAtuais.tempoAcumulado >= tempoMaximo){
        descontosAtuais.tempoAcumulado = 0;
        descontosAtuais.posicaoDescontoAtual = 0;
        porcentagemDesconto = promocoes.obterPromocaoCumulativa(descontosAtuais.posicaoDescontoAtual);
        descontosAtuais.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
        descontosAtuais.valores.push_back(porcentagemDesconto);
    } else {
        descontosAtuais.tempoAcumulado += escalaAtual.tempo;
        descontosAtuais.posicaoDescontoAtual = posicao + 1;
        porcentagemDesconto = promocoes.obterPromocaoCumulativa(descontosAtuais.posicaoDescontoAtual);
        descontosAtuais.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
        descontosAtuais.valores.push_back(porcentagemDesconto);
    }
    
    return descontosAtuais;
}

Descontos pararComDesconto(Descontos descontosAtuais, Promocoes promocoes, Escala escalaAtual){
    descontosAtuais.valores.push_back(0);
    descontosAtuais.posicaoDescontoAtual = 0;
    descontosAtuais.tempoAcumulado = 0;
    int porcentagemDesconto = promocoes.obterPromocaoCumulativa(descontosAtuais.posicaoDescontoAtual);
    descontosAtuais.precoAcumulado += ((escalaAtual.preco * (100-porcentagemDesconto))/100);
    return descontosAtuais;
}

vector<Descontos> obterDescontosPossiveis(vector<Escala> particao, Promocoes promocoes, int tempoMaximo){
    Escala escalaInicial = particao.at(0);
    Descontos descontos(0, escalaInicial.tempo, escalaInicial.preco);
    descontos.valores.push_back(promocoes.valores.at(0));

    vector<Descontos> opcoesDescontos;
    opcoesDescontos.push_back(descontos);
    vector<Descontos> opcoesDescontosTemp;
    opcoesDescontosTemp.push_back(descontos);


    for(int i = 1; i<particao.size(); i ++){
        opcoesDescontos.clear();

        for(int j = 0; j<opcoesDescontosTemp.size(); j ++){
            Descontos descontos = opcoesDescontosTemp.at(j);
            Descontos continuar = continuarComDesconto(descontos, promocoes, descontos.posicaoDescontoAtual, particao.at(i), tempoMaximo);
            Descontos parar = pararComDesconto(descontos,promocoes, particao.at(i));
            opcoesDescontos.push_back(continuar);
            opcoesDescontos.push_back(parar);
        }

        opcoesDescontosTemp.clear();

        for(int i = 0; i<opcoesDescontos.size(); i++){
            opcoesDescontosTemp.push_back(opcoesDescontos.at(i));
        }
    }

    return opcoesDescontos;
}

Descontos acharMelhorDesconto(vector<Escala> particao, Promocoes promocoes, int tempoMaximo){
    vector<Descontos> opcoesDescontos = obterDescontosPossiveis(particao, promocoes, tempoMaximo);

    Descontos melhorDesconto = opcoesDescontos.at(0);
    for(int i=1 ; i<opcoesDescontos.size(); i ++){
        if(melhorDesconto.precoAcumulado > opcoesDescontos.at(i).precoAcumulado){
            melhorDesconto = opcoesDescontos.at(i);
        }
    }

    
    return melhorDesconto;
}

Descontos continuarComMelhorDesconto(Descontos melhorDesconto, Promocoes promocoes, int tempoMaximo, vector<Escala>* escalas, int codigoEscalaInicial, vector<Escala>* particao, int qtdMaximaEscalasParaDesconto){

    int posicaoEscalaAtual = codigoEscalaInicial + 1;
    if(escalas->size() > posicaoEscalaAtual){
        Escala* escalaAtual = &escalas->at(posicaoEscalaAtual);
        if(escalaAtual->utilizada == false){
            for(int i = melhorDesconto.posicaoDescontoAtual;i<promocoes.valores.size(); i ++){
                if(melhorDesconto.tempoAcumulado < tempoMaximo && melhorDesconto.valores.size() < qtdMaximaEscalasParaDesconto && posicaoEscalaAtual <= (escalas->size() - 1)){
                    particao->push_back(*escalaAtual);
                    melhorDesconto.tempoAcumulado += escalaAtual->tempo;
                    melhorDesconto.posicaoDescontoAtual = melhorDesconto.posicaoDescontoAtual + 1;
                    int porcentagemDesconto = promocoes.obterPromocaoCumulativa(melhorDesconto.posicaoDescontoAtual);
                    melhorDesconto.precoAcumulado += ((escalaAtual->preco * (100-porcentagemDesconto))/100);
                    melhorDesconto.valores.push_back(porcentagemDesconto);
                    
                    escalaAtual->utilizada = true;
                    posicaoEscalaAtual +=1;
                    if(posicaoEscalaAtual <= (escalas->size() - 1))
                        escalaAtual = &escalas->at(posicaoEscalaAtual);
                }
            }
        }
    }

    return melhorDesconto;
}
