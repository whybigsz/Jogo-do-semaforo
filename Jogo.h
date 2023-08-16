//
// Created by ferr_ on 04/05/2021.
//
//Ricardo Ferreira - 21260251

#ifndef TP1_JOGO_H
#define TP1_JOGO_H

#include "Tabuleiro.h"


typedef struct Jogo Jogo;

struct Jogo{
    Tabuleiro *tab;
	int pedras1,pedras2;
	int linhas_colunas1,linhas_colunas2;
	int jogador;
};

Jogo * iniciaJogo(Tabuleiro *tab, int jogador, int cl1, int cl2,int p1, int p2);
int colocaPeca(char peca,Jogo *jogo,int x,int y);
int colocaColuna(Jogo *jogo);
int colocaLinha(Jogo *jogo);
void incPedras1(Jogo *jogo);
void incPedras2(Jogo *jogo);
void incCl1(Jogo *jogo);
void incCl2(Jogo *jogo);
void mudaJogador(Jogo *jogo);
int verificaLinha(Jogo *jogo);
int verificaColuna(Jogo *jogo);
int verificaDiag(Jogo *jogo);
int verificaVitoria(Jogo *jogo);
int escolheOpcao(Jogo *jogo,int opcao);
void freeJogo(Jogo *jogo);



#endif //TP1_JOGO_H
