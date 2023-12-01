#include <iostream>
#include <bitset>
#include <math.h>
#include "controle_erros.hh"
#include "camadas.hh"

#define TIPODECONTROLEDEERRO 0
#define ORDEMPOLINOMIO 32

// Camada de enlace do transmissor
// Função que seleciona o tipo de controle de erro a ser utilizado
CamadaEnlaceDadosTransmissoraControleDeErro::CamadaEnlaceDadosTransmissoraControleDeErro(Quadro *quadro) {
    switch (TIPODECONTROLEDEERRO) {
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2:
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
    }
}

// Função que detecta um número par 
bool ehPar(int num) {
    bool par = (num%2 == 0);
    return par;
}

// Encontra o número de bits 1 existentes na lista
int numeroBitsUm(int *lista, int tamanhoLista)  {
    int numBitsUm = 0;
    for(int i = 0; i < tamanhoLista; i++) {
        if(lista[i] == 1)
            numBitsUm++;
    }
    return numBitsUm;
}

// Função que implementa a codificação de paridade par 
void CamadaEnlaceDadosTransmissoraControleDeErro::CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro *quadro) {
    // Pega a quantidade de números um na lista de bits
    int numBitsUm = numeroBitsUm(quadro->listaBits, quadro->tamanhoListaBits);

    // Confere se o número de bits um é par (retorna true) ou ímpar (retorna false).
    bool par = ehPar(numBitsUm);

    // Caso o número de bits 1 seja par, o bit de paridade será 0; caso seja ímpar, será 1
    quadro->bitParidade = (int) !par;
}

// Função que implementa a codificação de paridade ímpar
void CamadaEnlaceDadosTransmissoraControleDeErro::CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro *quadro) {
    // Pega a quantidade de números 1 na lista de bits
    int numBitsUm = numeroBitsUm(quadro->listaBits, quadro->tamanhoListaBits);

    // Confere se o número de bits um é par (retorna true) ou ímpar (retorna false).
    bool par = ehPar(numBitsUm);

    // Caso o número de bits 1 seja par, o bit de paridade será 1; caso seja ímpar, será 0
    quadro->bitParidade = (int) par;
}

// Realiza operação de XOR entre as listas 1 e 2 e guarda o resultado na lista1.
void operacaoXOR(int *lista1, int *lista2, int n, int posicaoInicialLista1) {
    for(int j = 0; j < n; j++)
        lista1[posicaoInicialLista1 + j] ^= lista2[j];
}

// Implementação da divisão polinomial utlizada no algorítmo CRC; a lista de bits do objeto quadro é o dividendo 
void divisaoCRC(Quadro *quadro, int *divisor) {
    int tamanhoDivisor = ORDEMPOLINOMIO + 1;
    int tamanhoQuadroOriginal = quadro->tamanhoListaBits - ORDEMPOLINOMIO;

    for(int i = 0; i < tamanhoQuadroOriginal; i++) {
        // Aplica a operação XOR entre o dividendo e o divisor sem que encontra um bit 1 no dividendo
        if(quadro->listaBits[i] == 1)
            operacaoXOR(quadro->listaBits, divisor, tamanhoDivisor, i);
    }
}

// Implementa o controle de erro com o algorítmo CRC
void CamadaEnlaceDadosTransmissoraControleDeErro::CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro *quadro) {
    std::size_t tamanhoDivisor = ORDEMPOLINOMIO + 1;
    int divisor[] = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};

    std::size_t novoTamanho =  quadro->tamanhoListaBits + ORDEMPOLINOMIO;
    Quadro quadroCodificado;
    quadroCodificado.listaBits = new int[novoTamanho];
    quadroCodificado.tamanhoListaBits = novoTamanho;

    // copia os bits da mensagem original no quadro codificado e coloca zero nas posições reservadas para o resto da divisão
    int tamanhoOriginal = quadro->tamanhoListaBits;
    for(int i = 0; i < tamanhoOriginal; i++) {
        quadroCodificado.listaBits[i] = quadro->listaBits[i];
    }
    for(int i = tamanhoOriginal; i < novoTamanho; i++) {
        quadroCodificado.listaBits[i] = 0;
    }

    // Faz resto da divisão da lista de bits do quadro pelo polinômio divisor
    divisaoCRC(&quadroCodificado, divisor);

    // Copia os bits da mesagem original de volta no quadro codificado 
    for(int i = 0; i < tamanhoOriginal; i++) {
        quadroCodificado.listaBits[i] = quadro->listaBits[i];
    }

    // Copia dados do novo quadro para o quadro original e faz o ponteiro do lista de bits apontar para a nova lista; libera o espaço da lista antiga;
    free(quadro->listaBits);
    quadro->listaBits = quadroCodificado.listaBits;
    quadro->tamanhoListaBits = novoTamanho;
}

void CamadaEnlaceDadosReceptoraControleDeErro::copiaQuadro(Quadro quadro) {
    this->quadroRecebido.tamanhoListaBits = quadro.tamanhoListaBits;    
    this->quadroRecebido.listaBits = new int[this->quadroRecebido.tamanhoListaBits];
    this->quadroRecebido.bitParidade = quadro.bitParidade;
    for(int i = 0; i < quadro.tamanhoListaBits; i++)
        this->quadroRecebido.listaBits[i] = quadro.listaBits[i];
}

// Camada de enlace do receptor
CamadaEnlaceDadosReceptoraControleDeErro::CamadaEnlaceDadosReceptoraControleDeErro(Quadro quadro) {
    switch (TIPODECONTROLEDEERRO) {
        case 0:
            copiaQuadro(quadro);
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
            break;
        case 1:
            copiaQuadro(quadro);
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2:
            this->quadroRecebido.tamanhoListaBits = quadro.tamanhoListaBits - ORDEMPOLINOMIO;
            this->quadroRecebido.listaBits = new int[this->quadroRecebido.tamanhoListaBits];
            for(int i = 0; i < quadro.tamanhoListaBits - ORDEMPOLINOMIO; i++)
                this->quadroRecebido.listaBits[i] = quadro.listaBits[i];

            CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            break;
    }
}

// Verificação de erros usando o algorítmo de paridade par
void CamadaEnlaceDadosReceptoraControleDeErro::CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(Quadro quadro) {
    int numBitsUm = numeroBitsUm(quadro.listaBits, quadro.tamanhoListaBits);

    // Confere se o número de bits um é par (retorna true) ou ímpar (retorna false).
    bool par = ehPar(numBitsUm);

    // Caso o número de bits 1 seja par, o bit de paridade será 0; caso seja ímpar, será 1
    std::cout << "----------------------------------------------------------" << std::endl;
    if(quadro.bitParidade == (int) !par)  {
        std::cout << "[controle_erros] Bit paridade par - Mensagem recebida corretamente! " << std::endl;
    } else {
        std::cout << "[controle_erros] Bit paridade par - Erro na recepcao da mensagem" << std::endl;
    }
        std::cout << "----------------------------------------------------------" << std::endl;
}

// Verificação de erros usando o algorítmo de paridade ímpar
void CamadaEnlaceDadosReceptoraControleDeErro::CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(Quadro quadro) {
    int numBitsUm = numeroBitsUm(quadro.listaBits, quadro.tamanhoListaBits);

    // Confere se o número de bits um é par (retorna true) ou ímpar (retorna false).
    bool par = ehPar(numBitsUm);

    // Caso o número de bits 1 seja par, o bit de paridade será 0; caso seja ímpar, será 1
    std::cout << "----------------------------------------------------------" << std::endl;
    if(quadro.bitParidade == (int) par)  {
        std::cout << "[controle_erros] Bit paridade impar - Mensagem recebida corretamente! " << std::endl;
    } else {
        std::cout << "[controle_erros] Bit paridade impar - Erro na recepcao da mensagem" << std::endl;
    }
        std::cout << "----------------------------------------------------------" << std::endl;
}

// Verificação de erros usando o algorítmo CRC-32
void CamadaEnlaceDadosReceptoraControleDeErro::CamadaEnlaceDadosReceptoraControleDeErroCRC(Quadro quadro) {
    std::size_t tamanhoDivisor = ORDEMPOLINOMIO + 1;
    int divisor[] = {1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};

    divisaoCRC(&quadro, divisor);

    std::cout << "----------------------------------------------------------" << std::endl;
    for(int i = 0; i < quadro.tamanhoListaBits; i++) {
        if(quadro.listaBits[i] != 0) {
            std::cout << "[controle_erros] CRC - Erro na recepcao da mensagem" << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
            return;
        }
    }
    std::cout << "[controle_erros] CRC - Mensagem recebida corretamente! " << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
}

Quadro CamadaEnlaceDadosReceptoraControleDeErro::getQuadroRecebido() {
    return this->quadroRecebido;
}