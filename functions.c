#include "funcoes.h"

void limparBuffer() {
    while (getchar() != '\n');
}

void menu() {
    printf("%s", LINHAS);
    printf("\n      Menu de Operações     \n");
    printf("Opção 1 --> Círculo\n");
    printf("Opção 2 --> Retângulo\n");
    printf("Opção 3 --> Triângulo\n");
    printf("Opção 4 --> Figura Irregular\n");
    printf("Opção 5 --> Trocar dimensões de figuras\n");
    printf("Opção 6 --> Mostrar todas as figuras\n");
    printf("Opção 7 --> Sair\n");
    printf("%s", LINHAS);
    printf("\nDigite uma opção válida aqui --->  ");
}

// Implementações básicas (permanecem iguais)
float areaCirculo(float raio) { return raio * raio * PI; }
float perimetroCirculo(float raio) { return 2 * PI * raio; }
float areaRetangulo(float base, float altura) { return base * altura; }
float perimetroRetangulo(float base, float altura) { return 2 * (base + altura); }
float areaTriangulo(float base, float altura) { return (base * altura) / 2; }

float validacaoValor(float valor) {
    while (scanf("%f", &valor) != 1 || valor <= 0) {
        printf("Valor inválido. Informe um valor positivo --> ");
        limparBuffer();
    }
    return valor;
}

// Funções avançadas (Módulo 3)
unsigned long long fatorialRecursivo(int n) {
    if (n <= 1) return 1;
    return n * fatorialRecursivo(n - 1);
}

float aproximarPerimetroIrregular(int lados, float comprimentoLado) {
    if (lados < 3) return 0;
    float fator = 1.0 - (1.0 / fatorialRecursivo(lados));
    return lados * comprimentoLado * fator;
}

void trocarDimensoes(Figura *a, Figura *b) {
    float temp[2] = {a->dimensoes[0], a->dimensoes[1]};
    a->dimensoes[0] = b->dimensoes[0];
    a->dimensoes[1] = b->dimensoes[1];
    b->dimensoes[0] = temp[0];
    b->dimensoes[1] = temp[1];
}

Figura* criarFigura(int tipo) {
    Figura *nova = malloc(sizeof(Figura));
    if (!nova) return NULL;

    switch(tipo) {
        case 1: // Círculo
            strcpy(nova->tipo, "Círculo");
            printf("Raio: ");
            nova->dimensoes[0] = validacaoValor(0);
            nova->dimensoes[1] = 0;
            nova->area = areaCirculo(nova->dimensoes[0]);
            nova->perimetro = perimetroCirculo(nova->dimensoes[0]);
            break;
        
        case 2: // Retângulo
            strcpy(nova->tipo, "Retângulo");
            printf("Base: ");
            nova->dimensoes[0] = validacaoValor(0);
            printf("Altura: ");
            nova->dimensoes[1] = validacaoValor(0);
            nova->area = areaRetangulo(nova->dimensoes[0], nova->dimensoes[1]);
            nova->perimetro = perimetroRetangulo(nova->dimensoes[0], nova->dimensoes[1]);
            break;
        
        case 3: // Triângulo
            strcpy(nova->tipo, "Triângulo");
            printf("Base: ");
            nova->dimensoes[0] = validacaoValor(0);
            printf("Altura: ");
            nova->dimensoes[1] = validacaoValor(0);
            nova->area = areaTriangulo(nova->dimensoes[0], nova->dimensoes[1]);
            nova->perimetro = 0;
            break;
        
        case 4: // Irregular
            strcpy(nova->tipo, "Irregular");
            printf("Número de lados: ");
            int lados = (int)validacaoValor(0);
            printf("Comprimento médio: ");
            float comprimento = validacaoValor(0);
            nova->dimensoes[0] = lados;
            nova->dimensoes[1] = comprimento;
            nova->area = 0;
            nova->perimetro = aproximarPerimetroIrregular(lados, comprimento);
            break;
    }
    return nova;
}

void exibirFiguras(Figura *figuras, int total) {
    printf("\n%5s %15s %20s %10s %12s\n", "ID", "Tipo", "Dimensões", "Área", "Perímetro");
    for (int i = 0; i < total; i++) {
        if (strcmp(figuras[i].tipo, "Círculo") == 0) {
            printf("%4d %15s %15s%.2f %10.2f %12.2f\n", 
                  i+1, figuras[i].tipo, "Raio:", figuras[i].dimensoes[0], 
                  figuras[i].area, figuras[i].perimetro);
        } else if (strcmp(figuras[i].tipo, "Irregular") == 0) {
            printf("%4d %15s %8s%d lados/%.2f %10.2f %12.2f\n", 
                  i+1, figuras[i].tipo, "", (int)figuras[i].dimensoes[0], 
                  figuras[i].dimensoes[1], figuras[i].area, figuras[i].perimetro);
        } else {
            printf("%4d %15s %8s%.2f/%.2f %10.2f %12.2f\n", 
                  i+1, figuras[i].tipo, "", figuras[i].dimensoes[0], 
                  figuras[i].dimensoes[1], figuras[i].area, figuras[i].perimetro);
        }
    }
}

Figura* realocarFiguras(Figura *figuras, int *capacidade) {
    *capacidade *= 2;
    Figura *novo = realloc(figuras, *capacidade * sizeof(Figura));
    if (!novo) {
        printf("Erro ao realocar memória!\n");
        free(figuras);
        exit(1);
    }
    return novo;
}
