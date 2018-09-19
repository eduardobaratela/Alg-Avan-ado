#include <cstdio>
#include <cstdlib>

int **tab;
int nPeças;

bool Jan_Ken_Puzzle(int R, int C){

	int peca;

	if(nPeças == 1){
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
						nPeças--;
						if(Jan_Ken_Puzzle(R, C) == true)// chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i-1][j];
						tab[i-1][j] = peca;
						nPeças++;
					}
				}
				if(j < (C -1)){ // Se eu puder ir para a direita
					if( (tab[i][j+1] == (tab[i][j]+1)) || ((tab[i][j+1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j+1];// guarda a peça que vai ser comida
						// come a peça
						tab[i][j+1] = tab[i][j];
						tab[i][j] = 0;
						nPeças--;
						if(Jan_Ken_Puzzle(R, C) == true)// chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j+1];
						tab[i][j+1] = peca;
						nPeças++;

					}
				}
				if(i < (R-1)){ // Se eu puder ir para o sul
					if( (tab[i+1][j] == (tab[i][j]+1)) || ((tab[i+1][j] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i+1][j];// guarda a peça que vai ser comida
						// come a peça
						tab[i+1][j] = tab[i][j];
						tab[i][j] = 0;
						nPeças--;
						if(Jan_Ken_Puzzle(R, C) == true)// chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i+1][j];
						tab[i+1][j] = peca;
						nPeças++;

					}
				}
				if(j > 0){ // Se eu puder ir para a esquerda
					if( (tab[i][j-1] == (tab[i][j]+1)) || ((tab[i][j-1] == 1) && (tab[i][j] == 3)) ){
						peca = tab[i][j-1]; // guarda a peça que vai ser comida
						// come a peça
						tab[i][j-1] = tab[i][j];
						tab[i][j] = 0;
						nPeças--;
						if(Jan_Ken_Puzzle(R, C) == true) // chama a função recursivamente
							return true;
						// restaura o tabuleiro como ele tava
						tab[i][j] = tab[i][j-1];
						tab[i][j-1] = peca;
						nPeças++;

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
		}
	}

	if(Jan_Ken_Puzzle(R,C) == true){
		printf("deu bom\n");
	}

	for(int i = 0; i < R; i++){
		for (int j = 0; j < C; ++j)
		{
			printf("%d ", &tab[i][j]);

		}
		printf("\n");
	}


	return 0;
}