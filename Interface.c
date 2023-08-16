//
// Created by ferr_ on 12/06/2021.
//


#include "Jogo.h"
#include "Tabuleiro.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EstadoJogo.h"

void menu() {

    printf("1.Colocar uma peca Verde numa celula vazia\n");
    printf("2.Trocar uma peca Verde que esteja colocada no tabuleiro por uma peca Amarela\n");
    printf("3.Trocar uma peca Amarela que esteja colocada no tabuleiro por uma peca Vermelha\n");
    printf("4.Coloca Pedra\n");
    printf("5.Coloca Linha ou Coluna\n");
    printf("6.Mostra estados de jogo\n");
    printf("7.Gravar Jogo\n");
    printf("8.Terminar Jogo\n");

}

void handler(Jogo *jogo, char peca, int bot) {
    int x, y;
    if (peca != 'C' && peca != 'L') {
        if (bot == 1 && jogo->jogador == 2) {
            x = intUniformRnd(0, jogo->tab->tamX - 1);
            y = intUniformRnd(0, jogo->tab->tamY - 1);
        } else {
            printf("Jogador %d indique x e y a jogar \n", jogo->jogador);
            scanf("%d%d", &x, &y);
        }
    }
    if (peca == 'X') {
        if (jogo->jogador == 1 && jogo->pedras1 == 0 || jogo->jogador == 2 && jogo->pedras2 == 0) {
            if (!colocaPeca(peca, jogo, x, y)) {
                printf("Jogada invalida , tente de novo\n");
            } else {
                if (jogo->jogador == 1) incPedras1(jogo);
                else incPedras2(jogo);
                mudaJogador(jogo);
            }
        } else {
            printf("Ja jogou a pedra!Impedido de jogar ate ao final do jogo\n");
        }

    } else if (peca == 'C' || peca == 'L') {
        if (jogo->jogador == 1 && jogo->linhas_colunas1 < 2 || jogo->jogador == 2 && jogo->linhas_colunas2 < 2) {
            if (peca == 'C' && colocaColuna(jogo) || peca == 'L' && colocaLinha(jogo)) {
                if (jogo->jogador == 1)
                    incCl1(jogo);
                else
                    incCl2(jogo);
                mudaJogador(jogo);
            } else {
                printf("Erro , tente outra vez\n");
            }
        } else {
            printf("O jogador %d ja utilizou o max de linhas e colunas\n", jogo->jogador);
        }
    } else if (colocaPeca(peca, jogo, x, y)) {
        mudaJogador(jogo);
    } else {
        printf("Jogada invalida , tente de novo\n");
    }
}

void menu2(Jogo *jogo) {

    int k, linhacoluna, choice = 0, vitoria = 0,bot=0;

    char nomeFich[256], c;

    printf("\nDeseja jogar online? (y/n)\n");
    scanf(" %c", &c);
    switch (c) {
        case 'y':
        case 'Y':
            bot = 1;
    }

    while (choice != 8 && vitoria == 0) {
        printf("\nJogador %d a jogar, selecione opcao\n", jogo->jogador);
        mostraTab(jogo->tab);
        menu();
        if (bot == 1 && jogo->jogador == 2) {
            choice = escolheOpcao(jogo, choice);
        } else {
            scanf("%d", &choice);
        }

        switch (choice) {
            case 1:
                printf("\nJogador %d Selecionou opcao 1\n", jogo->jogador);
                handler(jogo, 'G', bot);
                break;
            case 2:
                printf("\nJogador %d Selecionou opcao 2\n", jogo->jogador);
                handler(jogo, 'Y', bot);
                break;
            case 3:
                printf("\nJogador %d Selecionou opcao 3\n", jogo->jogador);
                handler(jogo, 'R', bot);
                break;
            case 4:
                printf("\nJogador %d Selecionou opcao 4\n", jogo->jogador);
                if(bot==1)printf("Player Automatico lancou 1 pedra\n");
                handler(jogo, 'X', bot);
                break;
            case 5:
                printf("\nJogador %d Selecionou opcao 5\n", jogo->jogador);
                if (bot == 1 && jogo->jogador == 2) {
                    linhacoluna = intUniformRnd(1, 2);
                    if(linhacoluna==1)printf("Player Automatico jogou um coluna\n");
                    else
                        printf("Player Automatico jogou uma linha\n");
                } else {
                    printf("Quer linha ou Coluna(1=coluna,2=linha)\n");
                    scanf("%d", &linhacoluna);
                }
                if (linhacoluna == 1)
                    handler(jogo, 'C', bot);
                else if (linhacoluna == 2)
                    handler(jogo, 'L', bot);
                else printf("erro...\n");
                break;
            case 6:
                printf("\nJogador %d Selecionou opcao 6\n", jogo->jogador);
                printf("Digite numero de estados a observar\n ");
                scanf("%d", &k);
                mostraEstado(k);
                break;
            case 7:
                printf("\nJogador %d Selecionou opcao 7\n", jogo->jogador);
                exportaEstados("jogo.bin");
                printf("\nJogo Gravado!\n");
                choice=8;
                break;
            case 8:
                printf("\nJogador %d Selecionou opcao 8\n", jogo->jogador);
                break;
            default:
                printf("\nSelecao invalida... Tende de novo\n");
        }
        vitoria = verificaVitoria(jogo);
    }
    switch (vitoria) {
        case 1:
            printf("O jogador %d ganhou com a Linha Preenchida\n", jogo->jogador == 1 ? 2 : 1);
            break;
        case 2:
            printf("O jogador %d ganhou com a Coluna Preenchida\n", jogo->jogador == 1 ? 2 : 1);
            break;
        case 3:
            printf("O jogador %d ganhou com a Diagonal Preenchida\n", jogo->jogador == 1 ? 2 : 1);
            break;
    }
    mostraTab(jogo->tab);

    printf("\nDeseja exportar o jogo para ficheiro texto? (y/n)\n");
    scanf(" %c", &c);
    switch (c) {
        case 'y':
        case 'Y':
            printf("\nQual o nome do ficheiro a exportar?\n");
            scanf(" %256s", nomeFich);
            exportaEstados2(nomeFich);
    }
}
