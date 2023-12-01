#include <iostream>
#include "meioDeComunicacao.hh"

// Simulação do meio de comunicação; o fluxoBrutoDeBitsPontoA é a mensagem enviada pelo transmissor e o fluxoBrutoDeBitsPontoB é a mensagem recebida pelo receptor
Quadro meioDeComunicacao(Quadro fluxoBrutoDeBitsPontoA) {
    int erro, porcentagemDeErros;
    Quadro fluxoBrutoDeBitsPontoB;
    fluxoBrutoDeBitsPontoB.listaBits = new int[fluxoBrutoDeBitsPontoA.tamanhoListaBits];

    porcentagemDeErros = 0;
    for(int i = 0; i < fluxoBrutoDeBitsPontoA.tamanhoListaBits; i ++) {
        if(rand()%100 >= porcentagemDeErros)
            fluxoBrutoDeBitsPontoB.listaBits[i] = fluxoBrutoDeBitsPontoA.listaBits[i];
        else
            fluxoBrutoDeBitsPontoA.listaBits[i] == 0? (fluxoBrutoDeBitsPontoB.listaBits[i] = 1) : (fluxoBrutoDeBitsPontoB.listaBits[i] = 0);
    }

    fluxoBrutoDeBitsPontoB.tamanhoListaBits =  fluxoBrutoDeBitsPontoA.tamanhoListaBits;
    fluxoBrutoDeBitsPontoB.bitParidade = fluxoBrutoDeBitsPontoA.bitParidade;

    return fluxoBrutoDeBitsPontoB;   
}