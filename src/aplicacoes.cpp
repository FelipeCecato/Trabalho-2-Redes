#include <iostream>
#include "camadas.hh"

// Função que simula a aplicação transmissora; retorna uma mensagem digitada pelo usuário
std::string AplicacaoTransmissora() {
    std::string mensagem;
    std::cout << "Digite uma mensagem" << std::endl;

    // Leitura da mensagem a ser transmitida
    std::getline(std::cin, mensagem);

    // CamadaDeAplicacaoTransmissora(mensagem);
    return mensagem;
} // Fim do metodo AplicacaoTransmissora

// Função que simula a aplicação receptora; imprime a mensagem recebida pela aplicação
void AplicacaoReceptora(std::string mensagem) {
    // Print da mensagem recebida
    std::cout << "[aplicacoes] A mensagem recebida foi: " << mensagem << std::endl;
} // Fim do metodo AplicacaoReceptora
