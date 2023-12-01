#ifndef CONTROLEERROS_HH
#define CONTROLEERROS_HH

#include <iostream>
#include "quadro.hh"

class CamadaEnlaceDadosTransmissoraControleDeErro {
    public:
        CamadaEnlaceDadosTransmissoraControleDeErro(Quadro *quadro);
        void CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro *quadro);
        void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro *quadro);
        void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro *quadro);
};

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