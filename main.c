#include <stdio.h>

#define TAM 8

void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 8)
                printf(" R ");
            else if (tabuleiro[i][j] == 1)
                printf(" * ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

void limparTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Torre - for
void moverTorre(int x, int y, int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        tabuleiro[x][i] = 1;
        tabuleiro[i][y] = 1;
    }
    tabuleiro[x][y] = 8;
}

// Bispo - while
void moverBispo(int x, int y, int tabuleiro[TAM][TAM]) {
    int i, j;

    i = x - 1; j = y - 1;
    while (i >= 0 && j >= 0) tabuleiro[i--][j--] = 1;

    i = x - 1; j = y + 1;
    while (i >= 0 && j < TAM) tabuleiro[i--][j++] = 1;

    i = x + 1; j = y - 1;
    while (i < TAM && j >= 0) tabuleiro[i++][j--] = 1;

    i = x + 1; j = y + 1;
    while (i < TAM && j < TAM) tabuleiro[i++][j++] = 1;

    tabuleiro[x][y] = 8;
}

// Rainha - combina tudo
void moverRainha(int x, int y, int tabuleiro[TAM][TAM]) {
    moverTorre(x, y, tabuleiro);
    moverBispo(x, y, tabuleiro);
}

// Cavalo - loops aninhados
void moverCavalo(int x, int y, int tabuleiro[TAM][TAM]) {
    int dx[] = {-2,-1,1,2,2,1,-1,-2};
    int dy[] = {1,2,2,1,-1,-2,-2,-1};

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < TAM && ny < TAM)
            tabuleiro[nx][ny] = 1;
    }
    tabuleiro[x][y] = 8;
}

// Recursividade
void moverRainhaRecursivo(int x, int y, int tabuleiro[TAM][TAM], int dx, int dy) {
    int nx = x + dx;
    int ny = y + dy;
    if (nx >= 0 && ny >= 0 && nx < TAM && ny < TAM) {
        tabuleiro[nx][ny] = 1;
        moverRainhaRecursivo(nx, ny, tabuleiro, dx, dy);
    }
}

void rainhaComRecursao(int x, int y, int tabuleiro[TAM][TAM]) {
    int dir[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };
    for (int i = 0; i < 8; i++)
        moverRainhaRecursivo(x, y, tabuleiro, dir[i][0], dir[i][1]);
    tabuleiro[x][y] = 8;
}

int main() {
    int tabuleiro[TAM][TAM];
    int x, y, opcao;

    do {
        printf("\n===== SIMULADOR DE XADREZ =====\n");
        printf("Escolha a peça para simular o movimento:\n");
        printf("1 - Torre\n");
        printf("2 - Bispo\n");
        printf("3 - Rainha\n");
        printf("4 - Cavalo\n");
        printf("5 - Rainha com recursividade\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            printf("Digite a posição inicial (linha e coluna de 0 a 7): ");
            scanf("%d %d", &x, &y);

            if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
                printf("Posição inválida.\n");
                continue;
            }

            limparTabuleiro(tabuleiro);

            switch (opcao) {
                case 1: moverTorre(x, y, tabuleiro); break;
                case 2: moverBispo(x, y, tabuleiro); break;
                case 3: moverRainha(x, y, tabuleiro); break;
                case 4: moverCavalo(x, y, tabuleiro); break;
                case 5: rainhaComRecursao(x, y, tabuleiro); break;
            }

            mostrarTabuleiro(tabuleiro);
        }

    } while (opcao != 0);

    printf("Encerrando o programa.\n");
    return 0;
}
