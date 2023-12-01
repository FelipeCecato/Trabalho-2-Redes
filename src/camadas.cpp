#include <iostream>
#include <string>
#include <bitset>
#include "camadas.hh"
#include "controle_erros.hh"

Camada::Camada(){}
Camada::~Camada(){}


// Transforma string de caracteres em uma string de 0 e 1 
std::string Camada::bitIntListToBitStringList(std::string mensagem) {
    std::string bitstring;

    for(int i = 0; i < mensagem.size(); i++)  {
        char &_letra = mensagem[i];
        bitstring.append(std::bitset<8>(_letra).to_string());
    }

    return bitstring;
}

// Funcao que transforma uma string em uma lista de bits e retorna o tamanho da lista
void Camada::stringToIntBitList(std::string mensagem, int *intBitList) {
    std::string bitstring = bitIntListToBitStringList(mensagem);

    // Copia a string de bits para a lista de inteiros
    for(int i = 0; i < bitstring.size(); i++) {
        intBitList[i] = (bitstring[i] == '1')? 1 : 0;
    }
}

// Funcao que transforma uma lista de bits em uma string
std::string Camada::intBitListToString(int *bitList, int listsize) {
    std::string bitstring;
    std::string mensagem;

    // Copia a lista de bits para uma string
    for(int i = 0; i < listsize; i++) {
        (bitList[i] == 1)? bitstring.append("1") : bitstring.append("0");
    }

    // Transforma a string de 0 e 1 em uma mensagem legível
    for(int i = 0; i < bitstring.size(); i+=8) {
        std::bitset<8> b(bitstring.substr(i, 8));
        unsigned char c = b.to_ulong();
        mensagem += c;
    }

    return mensagem;
}

CamadaTransmissora::CamadaTransmissora(std::string mensagem) {
    this->mensagem = mensagem;
    this->quadro.tamanhoListaBits = mensagem.size()*8;
    this->quadro.listaBits = new int[this->quadro.tamanhoListaBits];
}

CamadaTransmissora::~CamadaTransmissora() {
    free(this->quadro.listaBits);
}

// Função que transforma a mensagem em uma lista de bits
void CamadaTransmissora::CamadaDeAplicacaoTransmissora() {
    stringToIntBitList(this->mensagem, this->quadro.listaBits);
}

// Funçã́o que implementa o método de controle de erro no quadro
void CamadaTransmissora::CamadaEnlaceDadosTransmissora() {
    CamadaEnlaceDadosTransmissoraControleDeErro controleErroTransmissora(&(this->quadro));
    std::cout << "[camadas] Quadro codificado para transmissao: ";
    for(int i = 0; i < (this->quadro).tamanhoListaBits; i++)
        std::cout << (this->quadro).listaBits[i];
    std::cout << std::endl;
}

Quadro CamadaTransmissora::getQuadro() {
    return this->quadro;
}

CamadaReceptora::CamadaReceptora(Quadro quadro) {
    this->quadro = quadro;
}

Quadro CamadaReceptora::getQuadro() {
    return this->quadro;
}

void CamadaReceptora::CamadaEnlaceDadosReceptora() {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "[camadas] Quadro codificado recebido: ";
    for(int i = 0; i < (this->quadro).tamanhoListaBits; i++)
        std::cout << (this->quadro).listaBits[i];
    std::cout << std::endl;

    CamadaEnlaceDadosReceptoraControleDeErro controleErroReceptora(this->quadro);
    free(this->quadro.listaBits);
    this->quadro = controleErroReceptora.getQuadroRecebido();
}

std::string CamadaReceptora::CamadaDeAplicacaoReceptora() {
    std::string mensagemRecebida = intBitListToString(this->quadro.listaBits, this->quadro.tamanhoListaBits);

    return mensagemRecebida;
}

CamadaReceptora::~CamadaReceptora() {
    free(this->quadro.listaBits);
}