#include <iostream>
#include "aplicacoes.hh"
#include "camadas.hh"
#include "meioDeComunicacao.hh"

int main(void) {
    // Captação da mensagem pela aplicação
    std::string mensagem = AplicacaoTransmissora();

    // Passagem da mensagem (em string) para a camada de aplicação transmissora
    CamadaTransmissora transmissor(mensagem);
    transmissor.CamadaDeAplicacaoTransmissora();

    // Passagem da mensagem (em bits) para a camada de enlace transmissora
    transmissor.CamadaEnlaceDadosTransmissora();

    // Recepção da mensagem (em bits) pelo receptor
    Quadro quadroReceptor = meioDeComunicacao(transmissor.getQuadro());
    
    // Verificação de erro na mensagem do receptor
    CamadaReceptora receptor(quadroReceptor);
    receptor.CamadaEnlaceDadosReceptora();

    // Envio da mensagem (em bits) para a camada de aplicação receptora
    std::string mensagemFinal = receptor.CamadaDeAplicacaoReceptora();

    // Envio da mensagem (em string) para a aplicação receptora
    AplicacaoReceptora(mensagemFinal);
} // Fim do metodo main
