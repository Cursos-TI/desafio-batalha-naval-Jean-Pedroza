#include <stdio.h>

#define TAM 10
#define NAVIO 3

// Função para verificar se é seguro posicionar o navio
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int deltaLinha, int deltaColuna) {
    for (int i = 0; i < 3; i++) {
        int l = linha + i * deltaLinha;
        int c = coluna + i * deltaColuna;

        if (l < 0 || l >= TAM || c < 0 || c >= TAM) return 0; // Fora dos limites
        if (tabuleiro[l][c] != 0) return 0; // Sobreposição
    }
    return 1;
}

// Função para posicionar o navio
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int deltaLinha, int deltaColuna) {
    for (int i = 0; i < 3; i++) {
        int l = linha + i * deltaLinha;
        int c = coluna + i * deltaColuna;
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0}; // Inicializa todas as posições com 0 (agua)

    // Navio horizontal
    if (podePosicionar(tabuleiro, 1, 2, 0, 1)) {
        posicionarNavio(tabuleiro, 1, 2, 0, 1);
    }

    // Navio vertical
    if (podePosicionar(tabuleiro, 3, 5, 1, 0)) {
        posicionarNavio(tabuleiro, 3, 5, 1, 0);
    }

    // Navio diagonal principal
    if (podePosicionar(tabuleiro, 5, 0, 1, 1)) {
        posicionarNavio(tabuleiro, 5, 0, 1, 1);
    }

    // Navio diagonal secundária
    if (podePosicionar(tabuleiro, 0, 9, 1, -1)) {
        posicionarNavio(tabuleiro, 0, 9, 1, -1);
    }

    // Exibe o tabuleiro
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
