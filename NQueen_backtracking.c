#include <stdio.h>
#include <stdlib.h>

#define N 4
#define true 1
#define false 0

int isSafe(int board[N][N], int row, int column){
    for (int i = 0; i < N; i++) {
        if(board[row][i] == 1 && i != column)
            return false;                             //checa validez na mesma linha
        if(board[i][column] == 1 && i != row)
            return false;
    }

    int j = 1;
    while(row+j < N && column+j < N){       //checa validez na diagonal pra cima
        if(board[row+j][column+j] == 1)
            return false;
        j++;
    }

    j = 1;
    while(row-j >= 0 && column-j >= 0){
        if(board[row-j][column-j] == 1)
            return false;
        j++;
    }

    j = 1;
    while(row+j < N && column-j >= 0){
        if(board[row+j][column-j] == 1)
            return false;
        j++;
    }

    j = 1;
    while(column+j < N && row-j >= 0){
        if(board[row-j][column+j] == 1)
            return false;
        j++;
    }

    return true;        //se tiver safe retorna true
}

int solveNQUtil(int board[N][N], int col){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    if(col >= N)
        return true;        //Se todas as colunas foram preenchidas

    //Para cada linha da coluna
    for (int i = 0; i < N; i++) {
        if(isSafe(board, i, col)){
            board[i][col] = 1;       //Atualiza como 1 na matriz do tabuleiro
                                    //se a posicao for valida
            if(solveNQUtil(board, col+1))   //chama recursivamente a função e
                return true;                //retorna true se a posicao for possivel

            board[i][col] = 0;      //Se o arranjo não for possivel, volta a posicao
                                    //da matriz como 0
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return false;       //caso o arranjo não for possivel faz o backtracking,
                        //rearranjando o tabuleiro
}


int main(int argc, char const *argv[]) {
    int board[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    solveNQUtil(board, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
