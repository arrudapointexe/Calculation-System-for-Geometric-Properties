#include "funcoes.h"

int main() {
    int capacidade = 5;
    int totalFiguras = 0;
    Figura *figuras = malloc(capacidade * sizeof(Figura));
    
    if (!figuras) {
        printf("Erro ao alocar memória inicial!\n");
        return 1;
    }

    while (1) {
        menu();
        int opcao;
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch(opcao) {
            case 1: case 2: case 3: case 4: // Criar figuras
                if (totalFiguras >= capacidade) {
                    figuras = realocarFiguras(figuras, &capacidade);
                }
                Figura *nova = criarFigura(opcao);
                if (nova) {
                    figuras[totalFiguras++] = *nova;
                    free(nova);
                    printf("Figura adicionada com sucesso!\n");
                }
                break;
                
            case 5: // Trocar dimensões
                if (totalFiguras < 2) {
                    printf("Necessário pelo menos 2 figuras!\n");
                } else {
                    printf("Digite os IDs (1 a %d): ", totalFiguras);
                    int id1, id2;
                    scanf("%d %d", &id1, &id2);
                    if (id1 > 0 && id1 <= totalFiguras && 
                        id2 > 0 && id2 <= totalFiguras) {
                        trocarDimensoes(&figuras[id1-1], &figuras[id2-1]);
                        printf("Dimensões trocadas!\n");
                    } else {
                        printf("IDs inválidos!\n");
                    }
                }
                break;
                
            case 6: // Listar figuras
                if (totalFiguras == 0) {
                    printf("Nenhuma figura cadastrada!\n");
                } else {
                    exibirFiguras(figuras, totalFiguras);
                }
                break;
                
            case 7: // Sair
                free(figuras);
                printf("Programa encerrado.\n");
                return 0;
                
            default:
                printf("Opção inválida!\n");
        }
        sleep(1);
    }
}
