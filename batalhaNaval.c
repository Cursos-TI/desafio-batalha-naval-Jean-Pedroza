#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // Declaração e inicialização do tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Coordenadas iniciais do navio horizontal (linha, coluna)
    int linhaH = 2, colunaH = 4;
    // Coordenadas iniciais do navio vertical (linha, coluna)
    int linhaV = 5, colunaV = 7;

    // Valida se os navios estão dentro dos limites
    if (colunaH + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && linhaV + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verifica sobreposição antes de posicionar
        int sobreposicao = 0;

        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] == NAVIO || tabuleiro[linhaV + i][colunaV] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posiciona navio horizontal
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = NAVIO;
            }

            // Posiciona navio vertical
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = NAVIO;
            }
        } else {
            printf("Erro: os navios se sobrepõem.\n");
            return 1;
        }
    } else {
        printf("Erro: posição fora dos limites do tabuleiro.\n");
        return 1;
    }

    // Impressão do tabuleiro
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
