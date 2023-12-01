#ifndef CONTROLEERROS_HH
#define CONTROLEERROS_HH

#include <iostream>
#include "quadro.hh"

// Classe que abrange a codificação da mensagem do transmissor
class CamadaEnlaceDadosTransmissoraControleDeErro {
    public:
        CamadaEnlaceDadosTransmissoraControleDeErro(Quadro *quadro);
        void CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro *quadro);
        void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro *quadro);
        void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro *quadro);
};

// Classe que abrange a detecção de erros do receptor
class CamadaEnlaceDadosReceptoraControleDeErro {
    private:
        Quadro quadroRecebido;
    public:
        CamadaEnlaceDadosReceptoraControleDeErro(Quadro quadro);
        void CamadaEnlaceDadosReceptoraControleDeErroCRC(Quadro quadro);
        void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(Quadro quadro);
        void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(Quadro quadro);
        void copiaQuadro(Quadro quadro);
        Quadro getQuadroRecebido();
};

#endif