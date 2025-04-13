#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PI 3.1415
#define LINHAS "-----------------------------------------"

typedef struct {
    char tipo[20];
    float dimensoes[2]; // [0] = raio/base, [1] = altura
    float area;
    float perimetro;
} Figura;

// Funções básicas
void limparBuffer();
void menu();

// Funções de cálculo
float areaCirculo(float raio);
float perimetroCirculo(float raio);
float areaRetangulo(float base, float altura);
float perimetroRetangulo(float base, float altura);
float areaTriangulo(float base, float altura);
float validacaoValor(float valor);

// Funções avançadas (Módulo 3)
unsigned long long fatorialRecursivo(int n);
float aproximarPerimetroIrregular(int lados, float comprimentoLado);
void trocarDimensoes(Figura *a, Figura *b);

// Manipulação de figuras
Figura* criarFigura(int tipo);
void exibirFiguras(Figura *figuras, int total);
Figura* realocarFiguras(Figura *figuras, int *capacidade);

#endif
