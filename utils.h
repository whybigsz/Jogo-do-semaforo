//
// Created by ricardo on 27/04/21.
//
//Ricardo Ferreira - 21260251

#ifndef TP1__UTILS_H_
#define TP1__UTILS_H_

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

#endif //TP1__UTILS_H_
