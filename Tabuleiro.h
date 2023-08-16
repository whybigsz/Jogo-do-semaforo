//
// Created by ricardo on 27/04/21.
//
//Ricardo Ferreira - 21260251

#ifndef TP1__TABULEIRO_H_
#define TP1__TABULEIRO_H_

typedef struct _tabuleiro Tabuleiro;

struct _tabuleiro{
    int tamX, tamY;
    char **tab;
} ;

Tabuleiro* criaTab(int tam);
void mostraTab(Tabuleiro *tab);
Tabuleiro* duplicaTabuleiro(Tabuleiro *tab);
void freeTabuleiro(Tabuleiro *tab);

#endif //TP1__TABULEIRO_H_
