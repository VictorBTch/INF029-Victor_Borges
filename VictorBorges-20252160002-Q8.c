#include <stdio.h>

#define TAM 3
#define VAZIO ' '
#define J1 'X'
#define J2 'O'

void inicializar(char tab[TAM][TAM]);
void imprimir(char tab[TAM][TAM]);
int jogar(char tab[TAM][TAM], int jogador);
int converterLinha(char c);
int venceu(char tab[TAM][TAM]);
int cheia(char tab[TAM][TAM]);

int main() {
    char tab[TAM][TAM];
    int jogador = 1;
    int fim = 0;

    inicializar(tab);

    while (!fim) {
        imprimir(tab);

        if (jogar(tab, jogador)) {
            if (venceu(tab)) {
                imprimir(tab);
                printf("\nJOGADOR %d VENCEU!\n", jogador);
                break;
            }

            if (cheia(tab)) {
                imprimir(tab);
                printf("\nEMPATE!\n");
                break;
            }

            jogador = (jogador == 1) ? 2 : 1;
        }
    }

    return 0;
}

//funções

void inicializar(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = VAZIO;
        }
    }
}

void imprimir(char tab[TAM][TAM]) {
    printf("\n      1   2   3\n");
    printf("    -------------\n");

    for (int i = 0; i < TAM; i++) {
        printf("  %c |", 'A' + i);

        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tab[i][j]);

            if (j < TAM - 1)
                printf("|");
        }

        printf("|\n");

        if (i < TAM - 1)
            printf("    |---+---+---|\n");
    }

    printf("    -------------\n");
}

int converterLinha(char c) {
    if (c == 'A') return 0;
    if (c == 'B') return 1;
    if (c == 'C') return 2;
    return -1;
}

int jogar(char tab[TAM][TAM], int jogador) {
    char linhaChar;
    int coluna;
    int l, c;

    printf("\nJogador %d (%c), jogue (ex: B3): ", jogador, (jogador == 1 ? J1 : J2));
    scanf(" %c%d", &linhaChar, &coluna);

    l = converterLinha(linhaChar);
    c = coluna - 1;

    if (l < 0 || l >= TAM || c < 0 || c >= TAM) {
        printf("Jogada invalida!\n");
        return 0;
    }

    if (tab[l][c] != VAZIO) {
        printf("Casa ocupada!\n");
        return 0;
    }

    tab[l][c] = (jogador == 1) ? J1 : J2;

    return 1;
}

int venceu(char tab[TAM][TAM]) {
    // linhas
    for (int i = 0; i < TAM; i++) {
        if (tab[i][0] != VAZIO &&
            tab[i][0] == tab[i][1] &&
            tab[i][1] == tab[i][2]) {
            return 1;
        }
    }

    // colunas
    for (int j = 0; j < TAM; j++) {
        if (tab[0][j] != VAZIO &&
            tab[0][j] == tab[1][j] &&
            tab[1][j] == tab[2][j]) {
            return 1;
        }
    }

    // diagonais
    if (tab[0][0] != VAZIO &&
        tab[0][0] == tab[1][1] &&
        tab[1][1] == tab[2][2]) {
        return 1;
    }

    if (tab[0][2] != VAZIO &&
        tab[0][2] == tab[1][1] &&
        tab[1][1] == tab[2][0]) {
        return 1;
    }

    return 0;
}

int cheia(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == VAZIO)
                return 0;
        }
    }
    return 1;
}