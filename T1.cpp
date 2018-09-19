#include <cstdio>
#include <cstdlib>

typedef struct _Peca{
	int linha;
	int coluna;
	int tipo;

}Peca;

Peca* resultado;
int **tab;
int nPecas = 0;

bool Jan_Ken_Puzzle(int R, int C){

	int peca;

	if(nPecas == 1){
		return true;
	}

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){ 
			if(tab[i][j] != 0){ // Se a posição n for vazia
				if(i > 0){ // Se eu puder ir para o norte
					if( (tab[i-1][j] == (tab[i][j]+1)) || ((tab[i-1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i-1][j];// guarda a peça que vai ser comida
						// come a peça
						tab[i-1][j] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;
						
						resultado.linha = i-1;
						resultado.coluna = j;
						resultado.tipo = tab[i-1][j];
						
						if(Jan_Ken_Puzzle(R, C) == true)// chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i-1][j];
						tab[i-1][j] = peca;
						nPecas++;
					}
				}
				if(j < (C -1)){ // Se eu puder ir para a direita
					if( (tab[i][j+1] == (tab[i][j]+1)) || ((tab[i][j+1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j+1];// guarda a peça que vai ser comida
						// come a peça
						tab[i][j+1] = tab[i][j];
						tab[i][j] = 0;
						
						nPecas--;
						resultado.linha = i;
						resultado.coluna = j+1;
						resultado.tipo = tab[i][j+1];
						
						if(Jan_Ken_Puzzle(R, C) == true)// chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j+1];
						tab[i][j+1] = peca;
						nPecas++;

					}
				}
				if(i < (R-1)){ // Se eu puder ir para o sul
					if( (tab[i+1][j] == (tab[i][j]+1)) || ((tab[i+1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i+1][j];// guarda a peça que vai ser comida
						// come a peça
						tab[i+1][j] = tab[i][j];
						tab[i][j] = 0;
						
						nPecas--;
						resultado.linha = i+1;
						resultado.coluna = j;
						resultado.tipo = tab[i+1][j];
						
						if(Jan_Ken_Puzzle(R, C) == true)// chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i+1][j];
						tab[i+1][j] = peca;
						nPecas++;

					}
				}
				if(j > 0){ // Se eu puder ir para a esquerda
					if( (tab[i][j-1] == (tab[i][j]+1)) || ((tab[i][j-1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j-1]; // guarda a peça que vai ser comida
						// come a peça
						tab[i][j-1] = tab[i][j];
						tab[i][j] = 0;
						nPecas--;

						resultado.linha = i;
						resultado.coluna = j-1;
						resultado.tipo = tab[i][j-1];
						
						if(Jan_Ken_Puzzle(R, C) == true) // chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j-1];
						tab[i][j-1] = peca;
						nPecas++;

					}
				}
			}

		}
	}

	return false;


}


int main(){
	int R, C;

	scanf("%d %d", &R, &C);

	

	tab = (int**) malloc(sizeof(int*) *R);
	for(int i = 0; i < C; i++)
		tab[i] = (int*) malloc(sizeof(int)*C);

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; ++j)
		{
			scanf("%d", &tab[i][j]);
			if(tab[i][j] != 0)
				nPecas++;
		}
	}

	if(Jan_Ken_Puzzle(R,C) == true){
		printf("%d %d %d\n", resultado.linha+1, resultado.coluna+1, resultado.tipo);

	}

	// for(int i = 0; i < R; i++){
	// 	for (int j = 0; j < C; ++j)
	// 	{
	// 		printf("%d ", tab[i][j]);

	// 	}
	// 	printf("\n");
	// }


	return 0;
}