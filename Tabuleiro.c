//
// Created by ricardo on 27/04/21.
//
//Ricardo Ferreira - 21260251

#include "Tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>


Tabuleiro *criaTab(int tam) {
    Tabuleiro *tab;
    tab = (Tabuleiro *) malloc(sizeof(Tabuleiro));
    tab->tamX = tab->tamY = tam;

    if (tab == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        return NULL;
    }
    tab->tab = malloc(tam * sizeof(char *));
    if (tab->tab == NULL) {
        printf("Erro de alocacao de memoria\n");
        free(tab);
        return NULL;
    }
    for (int i = 0; i < tam; i++) {
        tab->tab[i] = malloc(tam * sizeof(char));
        if (tab->tab[i] == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria\n");
            while (--i >= 0) freeTabuleiro(tab);
            return NULL;
        }
        for (int j = 0; j < tam; j++) {
            tab->tab[i][j] = '_';
        }
    }
    return tab;
}


void mostraTab(Tabuleiro *tab) {
    for (int i = 0; i < tab->tamX; i++) {
        for (int j = 0; j < tab->tamY; j++) {
            printf("%c ", tab->tab[i][j]);
        }
        putchar('\n');
    }
}

Tabuleiro *duplicaTabuleiro(Tabuleiro *tab) {
    Tabuleiro *novoTab = (Tabuleiro *) malloc(sizeof(Tabuleiro));
    if (novoTab == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        return NULL;
    }
    novoTab->tamY = tab->tamY;
    novoTab->tamX = tab->tamX;
    novoTab->tab = malloc(sizeof(char *) * novoTab->tamX);
    if (novoTab->tab == NULL) {
        printf("Erro de alocacao de memoria\n");
        free(tab);
        return NULL;
    }
    for (int i = 0; i < novoTab->tamX; i++) {
        novoTab->tab[i] = malloc(sizeof(char) * novoTab->tamY);
        if (novoTab->tab[i] == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria\n");
            while (--i >= 0) freeTabuleiro(novoTab);
        }
        for (int j = 0; j < novoTab->tamY; j++) {
            novoTab->tab[i][j] = tab->tab[i][j];
        }
    }
    return novoTab;
}

void freeTabuleiro(Tabuleiro *tab) {
    for (int i = 0; i < tab->tamX; i++)
        free(tab->tab[i]);
    free(tab->tab);
    free(tab);
}
