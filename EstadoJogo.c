//
// Created by ferr_ on 11/05/2021.
//
//Ricardo Ferreira - 21260251


#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"
#include "EstadoJogo.h"

EstadoJogo *estadoJogo;
int estados;

int iniciaEstado(Jogo *jogo) {
    estadoJogo = (EstadoJogo *) malloc(sizeof(EstadoJogo));
    if (estadoJogo == NULL) {
        printf("Erro na Alocacao de memoria");
        return 0;
    }
    estadoJogo->jogo = NULL;
    estadoJogo->next = NULL;
    estados = 0;
    return salvaJogo(jogo);
}

//void inserir Estado jogo
int insereEstado(Jogo *jogo) {
    EstadoJogo *novoEstado = (EstadoJogo *) malloc(sizeof(EstadoJogo));
    if (novoEstado == NULL) {
        printf("Erro na Alocacao de memoria");
        return 0;
    }

    novoEstado->jogo = jogo;
    novoEstado->next = estadoJogo->next;
    estadoJogo->next = novoEstado;
    estados++;
    return 1;
}

int salvaJogo(Jogo *jogo) {
    Jogo *novoJogo = (Jogo *) malloc(sizeof(Jogo));

    if (novoJogo == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        return 0;
    }

    novoJogo->linhas_colunas2 = jogo->linhas_colunas2;
    novoJogo->linhas_colunas1 = jogo->linhas_colunas1;
    novoJogo->jogador = jogo->jogador;
    novoJogo->pedras1 = jogo->pedras1;
    novoJogo->pedras2 = jogo->pedras2;
    novoJogo->tab = duplicaTabuleiro(jogo->tab);

    return insereEstado(novoJogo);
}


void mostraEstado(int k) {
    EstadoJogo *it = estadoJogo->next;
    int i = 0;
    while (it != NULL && i < k) {
        if (it->jogo->jogador == 1)
            printf("j:%d lc:%d p:%d\n", it->jogo->jogador, it->jogo->linhas_colunas1, it->jogo->pedras1);
        else
            printf("j:%d lc:%d p:%d\n", it->jogo->jogador, it->jogo->linhas_colunas2, it->jogo->pedras2);
        mostraTab(it->jogo->tab);
        putchar('\n');
        it = it->next;
        i++;
    }
}

int exportaEstados(char *nomefich) {
    FILE *fp = fopen(nomefich, "wb");
    if (fp == NULL) {
        printf("Erro a abrir o ficheiro\n");
        return 0;
    }
    fwrite(&estados, sizeof(int), 1, fp);

    EstadoJogo *it = estadoJogo->next;
    while (it != NULL) {
        escreveJogo(fp, it->jogo);
        it = it->next;
    }
    fclose(fp);
    return 1;
}

static void escreveJogo(FILE *fp, Jogo *jogo) {
    if (jogo == NULL) return;
    fwrite(&jogo->jogador, sizeof(int), 1, fp);
    fwrite(&jogo->linhas_colunas1, sizeof(int), 1, fp);
    fwrite(&jogo->linhas_colunas2, sizeof(int), 1, fp);
    fwrite(&jogo->pedras1, sizeof(int), 1, fp);
    fwrite(&jogo->pedras2, sizeof(int), 1, fp);
    fwrite(&jogo->tab->tamX, sizeof(int), 1, fp);
    fwrite(&jogo->tab->tamY, sizeof(int), 1, fp);
    for (int i = 0; i < jogo->tab->tamX; i++)
        for (int j = 0; j < jogo->tab->tamY; j++)
            fwrite(&jogo->tab->tab[i][j], sizeof(char), 1, fp);
}

int exportaEstados2(char *nomefich) {
    FILE *fp = fopen(nomefich, "wt");
    if (fp == NULL) {
        printf("Erro a abrir o ficheiro\n");
        return 0;
    }
    fprintf(fp, "NEstados:%d\n", estados);

    EstadoJogo *it = estadoJogo->next;
    while (it != NULL) {
        escreveJogo2(fp, it->jogo);
        it = it->next;
    }
    fclose(fp);
    return 1;
}

static void escreveJogo2(FILE *fp, Jogo *jogo) {
    if (jogo == NULL) return;
    fprintf(fp, "Jogador:%d Linhas_colunas1:%d Linhas_colunas2:%d Pedras1:%d Pedras2:%d TabTamX:%d TabTamY:%d\n",
            jogo->jogador, jogo->linhas_colunas1, jogo->linhas_colunas2, jogo->pedras1, jogo->pedras2, jogo->tab->tamX,
            jogo->tab->tamY);
    for (int i = 0; i < jogo->tab->tamX; i++){
        for (int j = 0; j < jogo->tab->tamY; j++)
            fprintf(fp, " %c", jogo->tab->tab[i][j]);
        fprintf(fp, "\n");
    }


}

Jogo * importaEstados(char *nomeFich) {

    FILE *fp = fopen(nomeFich, "rb");
    if (fp == NULL) {
        printf("Erro a abrir o ficheiro\n");
        return 0;
    }
    int nEstados;
    fread(&nEstados, sizeof(int), 1, fp);
    Jogo *jogos[nEstados];
    for (int i = 0; i < nEstados; i++) {
        jogos[i] = leJogo(fp);

        if (jogos[i] == NULL) {
            printf("Deu erro ao ler o jogo %d\n", i);
            while (--i >= 0) freeJogo(jogos[i]);
            return 0;
        }
    }

    for (int i = 0; i < nEstados; i++) {
        insereEstado(jogos[i]);
    }
    fclose(fp);
    return jogos[0];
}

static Jogo *leJogo(FILE *fp) {
    Jogo *jogo = malloc(sizeof(Jogo));
    if (jogo == NULL) {
        printf("erro\n");
        return NULL;
    }
    jogo->tab = malloc(sizeof(Tabuleiro));
    if (jogo->tab == NULL) {
        printf("erro\n");
        free(jogo);
        return NULL;
    }
    fread(&jogo->jogador, sizeof(int), 1, fp);
    fread(&jogo->linhas_colunas1, sizeof(int), 1, fp);
    fread(&jogo->linhas_colunas2, sizeof(int), 1, fp);
    fread(&jogo->pedras1, sizeof(int), 1, fp);
    fread(&jogo->pedras2, sizeof(int), 1, fp);
    fread(&jogo->tab->tamX, sizeof(int), 1, fp);
    fread(&jogo->tab->tamY, sizeof(int), 1, fp);
    jogo->tab->tab = malloc(sizeof(char *) * jogo->tab->tamX);
    if (jogo->tab->tab == NULL) {
        printf("erro\n");
        free(jogo->tab);
        free(jogo);
        return NULL;
    }
    for (int i = 0; i < jogo->tab->tamX; i++) {
        jogo->tab->tab[i] = malloc(sizeof(char) * jogo->tab->tamY);
        if (jogo->tab->tab[i] == NULL) {
            while (--i >= 0) {
                free(jogo->tab->tab[i]);
            }
            free(jogo->tab);
            free(jogo);
            return NULL;
        }
        for (int j = 0; j < jogo->tab->tamY; j++)
            fread(&jogo->tab->tab[i][j], sizeof(char), 1, fp);
    }
    return jogo;
}


