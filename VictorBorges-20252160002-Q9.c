#include <stdio.h>

#define TAM 10
#define AGUA ' '
#define NAVIO 'N'
#define ACERTO 'O'
#define ERRO 'X'

void inicializarTabuleiro(char tab[TAM][TAM]);
void imprimirTabuleiro(char tab[TAM][TAM], int esconderNavios);
void posicionarNavios(char tab[TAM][TAM], int jogador);
int podePosicionar(char tab[TAM][TAM], int x, int y, int tamanho, int direcao);
void colocarNavio(char tab[TAM][TAM], int x, int y, int tamanho, int direcao);
int atacar(char tab[TAM][TAM], char vis[TAM][TAM]);
int venceu(char tab[TAM][TAM]);

int main() {
    char j1[TAM][TAM], j2[TAM][TAM];
    char v1[TAM][TAM], v2[TAM][TAM];

    int vez = 1;
    int fim = 0;

    inicializarTabuleiro(j1);
    inicializarTabuleiro(j2);
    inicializarTabuleiro(v1);
    inicializarTabuleiro(v2);

    printf("=== BATALHA NAVAL ===\n\n");

    printf("JOGADOR 1, posicione seus navios:\n");
    posicionarNavios(j1, 1);

    printf("\nJOGADOR 2, posicione seus navios:\n");
    posicionarNavios(j2, 2);

    printf("\n=== COMEÇOU O JOGO ===\n");

    while (!fim) {

        if (vez == 1) {
            printf("\nJOGADOR 1 ATACA\n");
            imprimirTabuleiro(v1, 0);
            fim = atacar(j2, v1);

            if (fim) {
                printf("JOGADOR 1 VENCEU!\n");
                break;
            }
            vez = 2;
        } 
        else {
            printf("\nJOGADOR 2 ATACA\n");
            imprimirTabuleiro(v2, 0);
            fim = atacar(j1, v2);

            if (fim) {
                printf("JOGADOR 2 VENCEU!\n");
                break;
            }
            vez = 1;
        }
    }

    return 0;
}

//funções

void inicializarTabuleiro(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = AGUA;
        }
    }
}

void imprimirTabuleiro(char tab[TAM][TAM], int esconderNavios) {
    printf("\n  ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {

            if (esconderNavios && tab[i][j] == NAVIO)
                printf("%c ", AGUA);
            else
                printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}

int podePosicionar(char tab[TAM][TAM], int x, int y, int tamanho, int direcao) {
    // direcao: 0 = horizontal, 1 = vertical

    if (direcao == 0) {
        if (y + tamanho > TAM) return 0;

        for (int j = 0; j < tamanho; j++)
            if (tab[x][y + j] != AGUA) return 0;
    } else {
        if (x + tamanho > TAM) return 0;

        for (int i = 0; i < tamanho; i++)
            if (tab[x + i][y] != AGUA) return 0;
    }

    return 1;
}

void colocarNavio(char tab[TAM][TAM], int x, int y, int tamanho, int direcao) {
    if (direcao == 0) {
        for (int j = 0; j < tamanho; j++)
            tab[x][y + j] = NAVIO;
    } else {
        for (int i = 0; i < tamanho; i++)
            tab[x + i][y] = NAVIO;
    }
}

void posicionarNavios(char tab[TAM][TAM], int jogador) {
    int tamanhos[] = {4, 3, 2, 2, 2, 1, 1, 1};
    int qtd = 8;

    for (int i = 0; i < qtd; i++) {
        int x, y, d;

        imprimirTabuleiro(tab, 0);

        printf("\nJogador %d - Navio tamanho %d\n", jogador, tamanhos[i]);

        do {
            printf("Digite linha e coluna: ");
            scanf("%d %d", &x, &y);

            printf("Direcao (0-horizontal / 1-vertical): ");
            scanf("%d", &d);

        } while (!podePosicionar(tab, x, y, tamanhos[i], d));

        colocarNavio(tab, x, y, tamanhos[i], d);
    }
}

int atacar(char tab[TAM][TAM], char vis[TAM][TAM]) {
    int x, y;

    printf("Digite linha e coluna do ataque: ");
    scanf("%d %d", &x, &y);

    if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
        printf("Ataque inválido!\n");
        vis[x][y] = ERRO;
        return 0;
    }

    if (tab[x][y] == NAVIO) {
        printf("ACERTOU!\n");
        tab[x][y] = ACERTO;
        vis[x][y] = ACERTO;
    } else {
        printf("ERROU!\n");
        vis[x][y] = ERRO;
    }

    return venceu(tab);
}

int venceu(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tab[i][j] == NAVIO)
                return 0;

    return 1;
}