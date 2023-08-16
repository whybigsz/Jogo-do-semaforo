//
// Created by ferr_ on 04/05/2021.
//
//Ricardo Ferreira - 21260251

#include "Jogo.h"
#include "EstadoJogo.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


Jogo *iniciaJogo(Tabuleiro *tab, int jogador, int cl1, int cl2, int p1, int p2) {
    Jogo *novoJogo = (Jogo *) malloc(sizeof(Jogo));

    if (novoJogo == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        return NULL;
    }

    novoJogo->tab = tab;
    novoJogo->jogador = jogador;
    novoJogo->linhas_colunas1 = cl1;
    novoJogo->linhas_colunas2 = cl2;
    novoJogo->pedras1 = p1;
    novoJogo->pedras2 = p2;

    if (!iniciaEstado(novoJogo)) {
        printf("Erro a iniciar o estado do jogo\n");
        freeJogo(novoJogo);
        return NULL;
    }

    return novoJogo;
}

int colocaPeca(char peca, Jogo *jogo, int x, int y) {

    if (x < 0 || y < 0 || x >= jogo->tab->tamX || y >= jogo->tab->tamY) {
        printf("Erro de coordenadas\n");
        return 0;
    }
    int valido = 0;
    if (peca == 'G' && jogo->tab->tab[x][y] == '_') {
        jogo->tab->tab[x][y] = peca;
        valido = 1;
    } else if (peca == 'Y' && jogo->tab->tab[x][y] == 'G') {
        jogo->tab->tab[x][y] = peca;
        valido = 1;
    } else if (peca == 'R' && jogo->tab->tab[x][y] == 'Y') {
        jogo->tab->tab[x][y] = peca;
        valido = 1;
    } else if (peca == 'X' && jogo->tab->tab[x][y] == '_') {
        jogo->tab->tab[x][y] = peca;
        valido = 1;
    }
    return valido;
}

int colocaColuna(Jogo *jogo) {

    for (int i = 0; i < jogo->tab->tamX; i++) {
        char *aux = realloc(jogo->tab->tab[i], sizeof(char) * (jogo->tab->tamY + 1));
        if (aux == NULL) {
            fprintf(stderr, "Erro de realocacao de memoria\n");
            return 0;
        }
        jogo->tab->tab[i] = aux;
        jogo->tab->tab[i][jogo->tab->tamY] = '_';
    }
    jogo->tab->tamY++;
    return 1;
}


int colocaLinha(Jogo *jogo) {
    char **aux = realloc(jogo->tab->tab, sizeof(char *) * (jogo->tab->tamX + 1));
    if (aux == NULL) {
        fprintf(stderr, "Erro de realocacao de memoria\n");
        return 0;
    }
    jogo->tab->tab = aux;
    jogo->tab->tab[jogo->tab->tamX] = malloc(sizeof(char *) * jogo->tab->tamY);
    if (jogo->tab->tab[jogo->tab->tamX] == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        return 0;
    }
    for (int i = 0; i < jogo->tab->tamY; i++) {
        jogo->tab->tab[jogo->tab->tamX][i] = '_';
    }
    jogo->tab->tamX++;
    return 1;
}


int verificaLinha(Jogo *jogo) {
    for (int i = 0; i < jogo->tab->tamX; i++) {
        char c = jogo->tab->tab[i][0];
        if (c == '_' || c == 'X') continue;
        int vitoria = 1;
        for (int j = 1; j < jogo->tab->tamY; j++) {
            if (jogo->tab->tab[i][j] != c) {
                vitoria = 0;
                break;
            }
        }
        if (vitoria) return vitoria;
    }
    return 0;
}

int verificaColuna(Jogo *jogo) {
    for (int i = 0; i < jogo->tab->tamY; i++) {
        char c = jogo->tab->tab[0][i];
        if (c == '_' || c == 'X') continue;
        int vitoria = 1;
        for (int j = 1; j < jogo->tab->tamX; j++) {
            if (jogo->tab->tab[j][i] != c) {
                vitoria = 0;
                break;
            }
        }
        if (vitoria) return vitoria;
    }
    return 0;
}

int verificaDiag(Jogo *jogo) {
    if (jogo->tab->tamX != jogo->tab->tamY)
        return 0;

    char c = jogo->tab->tab[0][0];
    if (c != '_' && c != 'X') {
        int vitoria = 1;
        for (int i = 1; i < jogo->tab->tamX; i++) {
            if (jogo->tab->tab[i][i] != c) {
                vitoria = 0;
                break;
            }
        }
        if (vitoria) return vitoria;
    }

    c = jogo->tab->tab[jogo->tab->tamX - 1][0];
    if (c != '_' && c != 'X') {
        int vitoria = 1;
        for (int i = jogo->tab->tamX - 2, j = 1; i >= 0 && j < jogo->tab->tamY; i--, j++) {
            if (jogo->tab->tab[i][j] != c) {
                vitoria = 0;
                break;
            }
        }
        if (vitoria) return vitoria;
    }
    return 0;
}

int verificaVitoria(Jogo *jogo) {
    if (verificaLinha(jogo)) return 1;
    if (verificaColuna(jogo)) return 2;
    if (verificaDiag(jogo)) return 3;
    return 0;
}

int escolheOpcao(Jogo *jogo,int opcao){
    opcao=intUniformRnd(1, 5);

    if(jogo->pedras2==1 && jogo->linhas_colunas2== 2 && opcao==4 || jogo->pedras2==1 && jogo->linhas_colunas2== 2 && opcao==5)
        opcao=intUniformRnd(1, 3);
    else if(jogo->linhas_colunas2==2 && opcao==5)
        opcao=intUniformRnd(1, 4);
    else if(jogo->pedras2==1 && opcao==4)
        opcao=opcao - intUniformRnd(1, 3);

    return opcao;
}

void incPedras1(Jogo *jogo) {
    jogo->pedras1 = 1;
}

void incPedras2(Jogo *jogo) {
    jogo->pedras2 = 1;
}

void incCl1(Jogo *jogo) {
    jogo->linhas_colunas1++;
}

void incCl2(Jogo *jogo) {
    jogo->linhas_colunas2++;
}

void mudaJogador(Jogo *jogo) {
    salvaJogo(jogo);
    jogo->jogador = jogo->jogador == 1 ? 2 : 1;
}

void freeJogo(Jogo *jogo) {
    freeTabuleiro(jogo->tab);
    free(jogo);
}

