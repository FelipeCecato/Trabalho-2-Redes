#ifndef CAMADAS_HH
#define CAMADAS_HH

#include <iostream>
#include "quadro.hh"

class Camada {
    public:
        Camada();
        ~Camada();
        void stringToIntBitList(std::string mensagem, int *intBitList);
        std::string intBitListToString(int *bitList, int listsize);
        std::string bitIntListToBitStringList(std::string mensagem);
};

class CamadaTransmissora : public Camada {
    private:
        Quadro quadro;
        std::string mensagem;

    public:
        CamadaTransmissora(std::string mensagem);
        ~CamadaTransmissora();
        void CamadaDeAplicacaoTransmissora();
        void CamadaEnlaceDadosTransmissora();
        Quadro getQuadro();
};

class CamadaReceptora : public Camada {
    private:
        Quadro quadro;
    
    public:
        CamadaReceptora(Quadro quadro);
        ~CamadaReceptora();
        std::string CamadaDeAplicacaoReceptora();
        void CamadaEnlaceDadosReceptora();
        Quadro getQuadro();
};


#endif