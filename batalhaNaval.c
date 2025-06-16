#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define EFEITO 5

// Inicializa o tabuleiro com valor 0 (AGUA) em todas as posições
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

// Posiciona um navio no tabuleiro verificando os limites e evitando sobreposição
int posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna,
                    int dLinha, int dColuna, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != AGUA)
            return 0; // Falha: fora dos limites ou sobreposição
    }
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i * dLinha;
        int c = coluna + i * dColuna;
        tabuleiro[l][c] = NAVIO;
    }
    return 1; // Sucesso
}

// Gera a matriz de habilidade de acordo com o tipo
// Tipo 1 = Cone, Tipo 2 = Cruz, Tipo 3 = Octaedro
void gerarMatrizHabilidade(int tipo, int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            hab[i][j] = 0;
            if (tipo == 1) {
                // Cone: área expandindo para baixo
                if (i <= meio && j >= meio - i && j <= meio + i)
                    hab[i][j] = 1;
            } else if (tipo == 2) {
                // Cruz: linha e coluna centrais
                if (i == meio || j == meio)
                    hab[i][j] = 1;
            } else if (tipo == 3) {
                // Octaedro: losango
                if (abs(i - meio) + abs(j - meio) <= meio)
                    hab[i][j] = 1;
            }
        }
    }
}

// Aplica a habilidade no tabuleiro respeitando os limites
void aplicarHabilidade(int tabuleiro[TAM][TAM],
                       int hab[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna, int tipo) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (hab[i][j] == 1) {
                int l = origemLinha + (tipo == 1 ? i : i - meio);
                int c = origemColuna + (j - meio);
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == AGUA) {
                    tabuleiro[l][c] = EFEITO;
                }
            }
        }
    }
}

// Imprime o tabuleiro no console
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int habCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habOct[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // Posiciona navios em posições válidas
    posicionarNavio(tabuleiro, 2, 1, 0, 1, 3);      // Horizontal
    posicionarNavio(tabuleiro, 5, 2, 1, 0, 3);      // Vertical
    posicionarNavio(tabuleiro, 0, 7, 1, 1, 3);      // Diagonal \
    posicionarNavio(tabuleiro, 7, 9, -1, -1, 3);    // Diagonal /

    gerarMatrizHabilidade(1, habCone);
    gerarMatrizHabilidade(2, habCruz);
    gerarMatrizHabilidade(3, habOct);

    aplicarHabilidade(tabuleiro, habCone, 0, 2, 1);   // Cone no topo
    aplicarHabilidade(tabuleiro, habCruz, 5, 5, 2);   // Cruz no centro
    aplicarHabilidade(tabuleiro, habOct, 7, 7, 3);    // Octaedro mais para baixo

    imprimirTabuleiro(tabuleiro);
    return 0;
}
