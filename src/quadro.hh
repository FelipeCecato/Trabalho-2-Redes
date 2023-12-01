#ifndef QUADRO_HH
#define QUADRO_HH

#include <iostream>

// Representação do quadro de bits 
struct Quadro {
    int *listaBits;
    std::size_t tamanhoListaBits;
    int bitParidade;
};

#endif