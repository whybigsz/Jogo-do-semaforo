#include <stdio.h>
#include "Tabuleiro.h"
#include "Jogo.h"
#include "EstadoJogo.h"
#include "utils.h"
#include "Interface.h"
#include "unistd.h"
//Ricardo Ferreira - 21260251

#define N intUniformRnd(3, 5)

int main() {

    initRandom();
    char c;
    Tabuleiro *tab = criaTab(N);
    Jogo *jogo = iniciaJogo(tab, 1, 0, 0, 0, 0);
    if( access( "jogo.bin", F_OK ) == 0 ) {
        printf("\nDeseja importar jogo gravado? (y/n)\n");
        scanf(" %c",&c);
        switch (c) {
            case 'y':
            case 'Y':
                jogo = importaEstados("jogo.bin");
        }
    }

    menu2(jogo);

    return 0;
}
