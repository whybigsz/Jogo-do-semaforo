//
// Created by ferr_ on 11/05/2021.
//
//Ricardo Ferreira - 21260251

#ifndef TP1_ESTADOJOGO_H
#define TP1_ESTADOJOGO_H
#include "Jogo.h"
#include <stdio.h>

typedef struct EstadoJogo EstadoJogo;
struct EstadoJogo{
    Jogo *jogo;
    struct EstadoJogo *next;
};

int insereEstado(Jogo *jogo);
int salvaJogo(Jogo *jogo);
void mostraEstado(int k);
int iniciaEstado(Jogo *jogo);
int exportaEstados(char *nomefich);
int exportaEstados2(char *nomefich);
Jogo * importaEstados(char *nomefich);
static void escreveJogo(FILE *fp, Jogo *jogo);
static void escreveJogo2(FILE *fp, Jogo *jogo);
static Jogo *leJogo(FILE *fp);
#endif //TP1_ESTADOJOGO_H
