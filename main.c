#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define TAM 3

struct tab
{
    char matriz[TAM][TAM];
};
typedef struct tab board;

void mov(int mov, struct tab *mat, char locateCoord[]); // Realiza os movimentos do jogo
void printMatrix(struct tab mat); // Exibe o tabuleiro passado como argumento
void shuffleMatrix(struct tab *mat); //Embaralha o tabuleiro
void locateVoid(struct tab mat, char *LocateCoord); //Localiza as coordenadas do 'X'
int checkMov(int mov, struct tab mat, char locateCoord[]); //Verifica o movimento do usuario

int main()
{

    board correct =
    {
        {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', 'X'}
        }
    };

    board game = correct;
    printMatrix(correct);

    printf("\n");
    printf("\n");

    shuffleMatrix(&game);
    printMatrix(game);

    printf("\n");
    printf("\n");

    char locateX[3]; // Guarda as coordenadas do X(Espaço vazio para movimentacao)
    int input; // Guarda os comandos do jogo
    int check = 1; // Guarda a verificacao dos status do jogo
    int cont = 0; // Contador de jogadas

    while (check != 0)
    {
        locateVoid(game, locateX);
        input = _getch();
        input = checkMov(input, game, locateX);
        mov(input, &game, locateX);
        cont++;
        check = checkVictory(game, correct);
    }

    printf("Parabéns, você venceu!\n");
    printf("Voce realizou %i jogadas\n", cont);

    return 0;
}
int checkVictory(struct tab mat1, struct tab mat2)
{

    int i, j, cont = 0;

    for ( i = TAM - 1; i >= 0; i--)
    {
        for ( j = TAM - 1; j >= 0; j--)
        {
            if (mat1.matriz[i][j] != mat2.matriz[i][j])
            {
                cont = 1;
            }
        }
    }

    return cont;

}
void mov(int direction, struct tab *mat, char locateCoord[])
{
    char temp;
    int row = locateCoord[0] - '0';
    int col = locateCoord[1] - '0';

    if (direction != 0)
    {
        switch (direction)
        {
        case 72: // Tecla seta para cima
            if (row > 0)
            {
                temp = mat->matriz[row][col];
                mat->matriz[row][col] = mat->matriz[row - 1][col];
                mat->matriz[row - 1][col] = temp;
            }
            break;
        case 80: // Tecla seta para baixo
            if (row < TAM - 1)
            {
                temp = mat->matriz[row][col];
                mat->matriz[row][col] = mat->matriz[row + 1][col];
                mat->matriz[row + 1][col] = temp;
            }
            break;
        case 75: // Tecla seta para a esquerda
            if (col > 0)
            {
                temp = mat->matriz[row][col];
                mat->matriz[row][col] = mat->matriz[row][col - 1];
                mat->matriz[row][col - 1] = temp;
            }
            break;
        case 77: // Tecla seta para a direita
            if (col < TAM - 1)
            {
                temp = mat->matriz[row][col];
                mat->matriz[row][col] = mat->matriz[row][col + 1];
                mat->matriz[row][col + 1] = temp;
            }
            break;
        default:
            printf("Tecla Invalida!\n");
            break;
        }
    }
    else
    {
        printf("Movimento Invalido\n");
    }

    system("cls");
    printMatrix(*mat);
}

int checkMov(int mov, struct tab mat, char locateCoord[])
{
    int i = locateCoord[0] - '0';
    int j = locateCoord[1] - '0';

    if (mov == 224)
    {
        int arrowKey = _getch(); // Ler o próximo byte para determinar a tecla de seta

        switch (arrowKey)
        {
        case 72: // Tecla seta para cima
            return (i == 1 || i == 2) ? 72 : 0;
        case 80: // Tecla seta para baixo
            return (i == 0 || i == 1) ? 80 : 0;
        case 75: // Tecla seta para a esquerda
            return (j == 1 || j == 2) ? 75 : 0;
        case 77: // Tecla seta para a direita
            return (j == 0 || j == 1) ? 77 : 0;
        }
    }

    return 0;
}

void locateVoid(struct tab mat, char *LocateCoord)
{
    int i, j;

    for (i = 0; i < TAM; i++)
    {
        for (j = 0; j < TAM; j++)
        {
            if (mat.matriz[i][j] == 'X')
            {
                LocateCoord[0] = i + '0';
                LocateCoord[1] = j + '0';
                LocateCoord[2] = '\0';
            }
        }
    }

}

void printMatrix(struct tab mat)
{
    int i, j;

    printf("      8 - Puzzle");
    printf("\n ------------------------ \n");

    for (i = 0; i < TAM; i++)
    {
        for (j = 0; j < TAM; j++)
        {
            printf("    %c ", mat.matriz[i][j]);
        }
        printf("\n");
    }
}

void shuffleMatrix(struct tab *mat)
{
    int i, j;

    srand(time(NULL));// Mantem a aleatoriedade

    for (i = TAM - 1; i >= 0; i--)
    {
        for (j = TAM - 1; j >= 0; j--)
        {
            int randomRow = rand() % (i + 1); // gera um indice aleatorio menor que 3
            int randomCol = rand() % (j + 1); // gera um indice aleatorio menor que 3

            char temp = mat->matriz[i][j];
            mat->matriz[i][j] = mat->matriz[randomRow][randomCol];
            mat->matriz[randomRow][randomCol] = temp;
        }
    }
}
