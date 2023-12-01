#ifndef CAMADAS_HH
#define CAMADAS_HH

#include <iostream>
#include "quadro.hh"

// Classe genérica de camada
class Camada {
    public:
        Camada();
        ~Camada();
        void stringToIntBitList(std::string mensagem, int *intBitList);
        std::string intBitListToString(int *bitList, int listsize);
        std::string bitIntListToBitStringList(std::string mensagem);
};

// Classe que abrange as camadas transmissoras de aplicação e enlace
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

// Classe que abrange as camadas receptoras de aplicação e enlace
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